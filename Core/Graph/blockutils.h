#ifndef BLOCKUTILS_H
#define BLOCKUTILS_H

#include <QPainter>
#include "iblock.h"
#include "blockbase.h"
#include "../Utility/utilities.h"
#include "../Utility/plot.h"
#include "../Maths/Linear/regression.h"
#include "../Utility/utilities.h"
#include <sstream>
#include <map>
#include <memory>

/*
 * Forward declare all the blocks.
 * Don't need to unnecessarily include them as we are not calling
 * any member function of the classes
 * Note: these classes are outside the je namespace
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

    static click_types mousePressEvent(QPoint &point, IBlock* block)
    {
        qFatal("The non-specialised block_type_impl functions should not be used.");
        return click_types::none;
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

    static click_types mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return click_types::block;
        else if(utility::insideRect(block->getPorts().first, point))
            return click_types::inPort;
        else if(utility::insideRect(block->getPorts().second, point))
            return click_types::outPort;
        else
            return click_types::none;
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

    static click_types mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return click_types::block;
        else if(utility::insideRect(block->getPorts().second, point))
            return click_types::outPort;
        else
            return click_types::none;
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

    static click_types mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return click_types::block;
        else if(utility::insideRect(block->getPorts().first, point))
            return click_types::inPort;
        else
            return click_types::none;
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

    static click_types mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return click_types::block;
        else
            return click_types::none;
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
        // First time opening tab, so create an instance of the file manager
        /*if(blockSourceCodeManager == nullptr)
            blockSourceCodeManager = std::make_unique<io::BlockSourceCodeManager>(this->getName());

        // Attempt to load the source file. If file does not exist, create it
        if(!blockSourceCodeManager->loadSourceFile())
            blockSourceCodeManager->createSourceFile(); // Create the source file, build boiler plate code

        return blockSourceCodeManager->getContent();*/


        return nullptr;
    }
};

// ------- GRAPH -------
template<typename in_type, typename out_type>
class tab_type_impl<graph_t, in_type, out_type>
{
public:
    static QWidget* tabWidget(IBlock * block)
    {
        auto customPlot = new QCustomPlot();

        // Input and output types must be the same for a plot
        bool b = utility::is_same<in_type, out_type>::value;
        assert(b);

        typedef in_type dtype; // Same as out_type
        utility::Plot<dtype> p(customPlot);

        // Draw the input training data as a scatter pot
        matrix<dtype> X, Y; // NOTE: How do we get these from the base block class???
        p.scatterPlotYX(Y, X);

        // NOTE: Need to get this from LinearRegressionBlock::regression. HOW?
        auto f = new maths::linear::Regression<dtype>(Y, X);

        // And overlay the linear model prediction
        using namespace std::placeholders;  // For e.g. _1
        auto fptr = std::bind(&maths::linear::Regression<dtype>::calculate, f, _1);
        p.drawFunction(0, 100, 1, fptr);

        return customPlot;
    }
};

/*
 * Convert data_types enum to the appropriate intrinsic type using a typedef
 */
template<utility::data_types D>
struct enum2datatype
{
    // Default
    typedef int inner_type;
};

// Class specializations
template<>
struct enum2datatype<utility::data_types::INT>
{
    typedef int inner_type;
};

template<>
struct enum2datatype<utility::data_types::DOUBLE>
{
    typedef double inner_type;
};

template<>
struct enum2datatype<utility::data_types::_VOID>
{
    typedef void inner_type;
};

/*
 * This enum is used to populate the addblockdialog dropdown list of block types
 * and is then used in enum2blocktype to map the dropdown values to typedefs of the block classes
 */
enum block_types
{
    BLOCK               = 0,
    SOURCE              = 1,
    SINK                = 2,
    LINEAR_REGRESSION   = 3,
    _MAXB               = 4 // Helps for iterating over the enum
};

/*
 * The following template structs convert the block_type enum to a typedef required
 * for instatiating the block type
 */
template<block_types B, utility::data_types D>
struct enum2blocktype
{
    // Default
    typedef typename enum2datatype<D>::inner_type T;
    typedef MyCustomBlock<T> inner_type;
};

// Class specializations
template<utility::data_types D>
struct enum2blocktype<block_types::BLOCK, D>
{
    typedef typename enum2datatype<D>::inner_type T;
    typedef MyCustomBlock<T> inner_type;
};

template<utility::data_types D>
struct enum2blocktype<block_types::SOURCE, D>
{
    typedef typename enum2datatype<D>::inner_type T;
    typedef MyCustomSource<T> inner_type;
};

template<utility::data_types D>
struct enum2blocktype<block_types::SINK, D>
{
    typedef typename enum2datatype<D>::inner_type T;
    typedef MyCustomSink<T> inner_type;
};

template<utility::data_types D>
struct enum2blocktype<block_types::LINEAR_REGRESSION, D>
{
    typedef typename enum2datatype<D>::inner_type T;
    typedef LinearRegressionBlock<T> inner_type;
};

// Factory function for generating new blocks. This must include all the possible blocks
extern std::map<block_types, std::function<std::shared_ptr<IBlock>()>> block_factory;

} } // graph, je


#endif // BLOCKUTILS_H
