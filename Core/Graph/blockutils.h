#ifndef BLOCKUTILS_H
#define BLOCKUTILS_H

#include <QPainter>
#include "iblock.h"
#include "blockbase.h"
#include "../Components/plot.h"
#include "../Components/Maths/Linear/regression.h"
#include "../Components/IO/datamanager.h"
#include "../Components/IO/texteditor.h"
#include "../Utility/utilities.h"
#include <sstream>
#include <map>
#include <memory>

/*
 * Forward declare all the blocks.
 * Don't need to unnecessarily include them as we are not calling
 * any member function of the classes
 * Note: these classes are outside the je namespace for user convenience
 */
template<typename T>
class LinearRegressionBlock;

template<typename T>
class MyCustomBlock;

template<typename T>
class MyCustomSink;

template<typename T>
class MyCustomSource;

namespace je { namespace graph {

struct sink_t { enum { has_input = true, has_output = false }; };
struct source_t { enum { has_input = false, has_output = true }; };
struct block_t { enum { has_input = true, has_output = true }; };
// init() will still be called on this type but run() won't be
struct blank_t { enum { has_input = false, has_output = false }; };

struct editable_t { };
struct graph_t { };

// Define some proxy template classes
// These are needed because function specialisation alone won't work
// See: https://stackoverflow.com/questions/51118804/incorrect-template-function-being-called-from-within-a-templated-class-virtual-f/51118892#51118892

// Following are for block_type specialisation
template<typename block_type>
class block_type_impl
{
public:

    template<typename in_type,
             typename out_type>
    static void draw(QPainter *painter, IBlock* block)
    {
        qFatal("The non-specialised block_type_impl functions should not be used.");
    }

    static block_part_e mousePressEvent(QPoint &point, IBlock* block)
    {
        qFatal("The non-specialised block_type_impl functions should not be used.");
        return block_part_e::none;
    }
};

// ------- BLOCK -------
template<>
class block_type_impl<block_t>
{
public:

    template<typename in_type,
             typename out_type>
    static void draw(QPainter *painter, IBlock* block)
    {
        QRect rectangle;
        block->getRect(rectangle);
        painter->fillRect(rectangle, Qt::white);
        painter->drawRect(rectangle);
        painter->drawText(rectangle, Qt::AlignTop, "BLOCK"); // Block type
        painter->drawText(rectangle, Qt::AlignCenter, block->getName()); // Block name

        std::ostringstream out;
        out << block->getExecutionTime().count();
        painter->drawText(rectangle, Qt::AlignBottom, QString::fromStdString(out.str())); // Previous execution time

        block->getPorts().first->draw(painter, utility::type_info<in_type>::colour());
        block->getPorts().second->draw(painter, utility::type_info<out_type>::colour());
    }

    static block_part_e mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return block_part_e::block;
        else if(utility::insideRect(block->getPorts().first, point))
            return block_part_e::in_port;
        else if(utility::insideRect(block->getPorts().second, point))
            return block_part_e::out_port;
        else
            return block_part_e::none;
    }

    template<typename in_type,
             typename out_type>
    static void mouseHoverEvent(block_part_e part, QPoint &point, utility::data_t prev_in, utility::data_t prev_out)
    {
        QString tooltip;

        if(part == block_part_e::in_port)
            tooltip = QString::number(boost::get<in_type>(prev_in));
        else if(part == block_part_e::out_port)
            tooltip = QString::number(boost::get<out_type>(prev_out));

        QToolTip::showText(point, tooltip);
    }
};

// ------- SOURCE -------
template<>
class block_type_impl<source_t>
{
public:
    template<typename in_type,
             typename out_type>
    static void draw(QPainter *painter, IBlock* block)
    {
        QRect rectangle;
        block->getRect(rectangle);
        painter->fillRect(rectangle, Qt::white);
        painter->drawRect(rectangle);
        painter->drawText(rectangle, Qt::AlignTop, "SOURCE");
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());

        std::ostringstream out;
        out << block->getExecutionTime().count();
        painter->drawText(rectangle, Qt::AlignBottom, QString::fromStdString(out.str()));

        block->getPorts().second->draw(painter, utility::type_info<out_type>::colour());
    }

    static block_part_e mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return block_part_e::block;
        else if(utility::insideRect(block->getPorts().second, point))
            return block_part_e::out_port;
        else
            return block_part_e::none;
    }

    template<typename in_type,
             typename out_type>
    static void mouseHoverEvent(block_part_e part, QPoint &point, utility::data_t prev_in, utility::data_t prev_out)
    {
        QString tooltip;

        if(part == block_part_e::out_port)
            tooltip = QString::number(boost::get<out_type>(prev_out));

        QToolTip::showText(point, tooltip);
    }

};

// ------- SINK -------
template<>
class block_type_impl<sink_t>
{
public:
    template<typename in_type,
             typename out_type>
    static void draw(QPainter *painter, IBlock* block)
    {
        QRect rectangle;
        block->getRect(rectangle);
        painter->fillRect(rectangle, Qt::white);
        painter->drawRect(rectangle);
        painter->drawText(rectangle, Qt::AlignTop, "SINK");
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());

        std::ostringstream out;
        out << block->getExecutionTime().count();
        painter->drawText(rectangle, Qt::AlignBottom, QString::fromStdString(out.str()));

        block->getPorts().first->draw(painter, utility::type_info<in_type>::colour());
    }

    static block_part_e mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return block_part_e::block;
        else if(utility::insideRect(block->getPorts().first, point))
            return block_part_e::in_port;
        else
            return block_part_e::none;
    }

    template<typename in_type,
             typename out_type>
    static void mouseHoverEvent(block_part_e part, QPoint &point, utility::data_t prev_in, utility::data_t prev_out)
    {
        QString tooltip;

        if(part == block_part_e::in_port)
            tooltip = QString::number(boost::get<in_type>(prev_in));

        QToolTip::showText(point, tooltip);
    }
};

// ------- BLANK -------
template<>
class block_type_impl<blank_t>
{
public:
    template<typename in_type,
             typename out_type>
    static void draw(QPainter *painter, IBlock* block)
    {
        QRect rectangle;
        block->getRect(rectangle);
        painter->fillRect(rectangle, Qt::white);
        painter->drawRect(rectangle);
        painter->drawText(rectangle, Qt::AlignTop, "BLANK");
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());

        std::ostringstream out;
        out << block->getExecutionTime().count();
        painter->drawText(rectangle, Qt::AlignBottom, QString::fromStdString(out.str()));
    }

    static block_part_e mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return block_part_e::block;
        else
            return block_part_e::none;
    }

    template<typename in_type,
             typename out_type>
    static void mouseHoverEvent(block_part_e part, QPoint &point, utility::data_t prev_in, utility::data_t prev_out)
    {
        // No ports so nothing to do
    }
};

// Following are for tab type specialisations
template<typename tab_type, typename in_type, typename out_type>
class tab_type_impl
{
public:
    static QWidget* tabWidget(IBlock* block)
    {
        qFatal("The non-specialised tab_type_impl functions should not be used.");
        return nullptr;
    }
};

// ------- EDITABLE -------
template<typename in_type, typename out_type>
class tab_type_impl<editable_t, in_type, out_type>
{
public:
    static QWidget* tabWidget(IBlock* block)
    {
        auto t = block->getComponent<io::TextEditor>();

        // Attempt to load the source file. If file does not exist, create it
        if(!t->loadSourceFile())
            t->createSourceFile(); // Create the source file, build boiler plate code

        return t->getContent();
    }
};

// ------- GRAPH -------
template<typename in_type, typename out_type>
class tab_type_impl<graph_t, in_type, out_type>
{
public:
    static QWidget* tabWidget(IBlock * block)
    {
        auto customPlot = new QCustomPlot(); // Remember to call delete at some point

        // Type checks : input and output types must be the same for a plot
        bool b = utility::is_same<in_type, out_type>::value;
        assert(b);

        using namespace maths::linear;
        typedef in_type dtype; // Same as out_type
        auto f = block->getComponent<Regression<dtype>>();

        component::Plot<dtype> p(customPlot);

        // Draw the input training data as a scatter pot
        auto d = block->getComponent<io::DataManager<dtype>>();
        matrix<dtype> X, Y;
        d->getLabels(Y);
        d->getData(X);
        p.scatterPlotYX(Y, X);

        // Delegate drawing to component
        f->draw(p);

        return customPlot;
    }
};

/*
 * This enum is used to populate the addblockdialog dropdown list of block types
 * and is then used in enum2blocktype to map the dropdown values to typedefs of the block classes
 */
enum block_type_e
{
    B_MYCUSTOMBLOCK               = 0,
    B_MYCUSTOMSOURCE              = 1,
    B_MYCUSTOMSINK                = 2,
    B_LINEARREGRESSIONBLOCK       = 3,
    B_MAX                         = 4 // Helps for iterating over the enum
};

/*
 * The following template structs convert the block_type enum to a typedef required
 * for instatiating the block type
 */
template<block_type_e B, utility::data_type_e D>
struct enum2blocktype
{
    // Default
    typedef typename utility::enum2datatype<D>::inner_type T;
    typedef MyCustomBlock<T> inner_type;
};

// Class specializations
template<utility::data_type_e D>
struct enum2blocktype<B_MYCUSTOMBLOCK, D>
{
    typedef typename utility::enum2datatype<D>::inner_type T;
    typedef MyCustomBlock<T> inner_type;
};

template<utility::data_type_e D>
struct enum2blocktype<B_MYCUSTOMSOURCE, D>
{
    typedef typename utility::enum2datatype<D>::inner_type T;
    typedef MyCustomSource<T> inner_type;
};

template<utility::data_type_e D>
struct enum2blocktype<B_MYCUSTOMSINK, D>
{
    typedef typename utility::enum2datatype<D>::inner_type T;
    typedef MyCustomSink<T> inner_type;
};

template<utility::data_type_e D>
struct enum2blocktype<B_LINEARREGRESSIONBLOCK, D>
{
    typedef typename utility::enum2datatype<D>::inner_type T;
    typedef LinearRegressionBlock<T> inner_type;
};

// Factory function for generating new blocks. This must include all the possible blocks
// TODO: MAKE THIS CONST WITHOUT COMPILER COMPLAINING PLEASE
extern std::map<block_type_e, std::function<std::shared_ptr<IBlock>()>> block_factory;

} } // graph, je


#endif // BLOCKUTILS_H
