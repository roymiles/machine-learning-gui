#ifndef BLOCKUTILS_H
#define BLOCKUTILS_H

#include <QPainter>
#include "iblock.h"
#include "../Utility/utilities.h"
#include "../Utility/plot.h"

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

    static clickType mousePressEvent(QPoint &point, IBlock* block)
    {
        qFatal("The non-specialised block_type_impl functions should not be used.");
        return clickType::none;
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
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());

        block->getPorts().first->draw(painter, utility::type_info<in_type>::colour());
        block->getPorts().second->draw(painter, utility::type_info<out_type>::colour());
    }

    static clickType mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return clickType::block;
        else if(utility::insideRect(block->getPorts().first, point))
            return clickType::inPort;
        else if(utility::insideRect(block->getPorts().second, point))
            return clickType::outPort;
        else
            return clickType::none;
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
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());

        block->getPorts().second->draw(painter, utility::type_info<out_type>::colour());
    }

    static clickType mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return clickType::block;
        else if(utility::insideRect(block->getPorts().second, point))
            return clickType::outPort;
        else
            return clickType::none;
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
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());

        block->getPorts().first->draw(painter, utility::type_info<in_type>::colour());
    }

    static clickType mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return clickType::block;
        else if(utility::insideRect(block->getPorts().first, point))
            return clickType::inPort;
        else
            return clickType::none;
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
        painter->drawText(rectangle, Qt::AlignCenter, block->getName());
    }

    static clickType mousePressEvent(QPoint &point, IBlock* block)
    {
        if(utility::insideRect(block, point))
            return clickType::block;
        else
            return clickType::none;
    }
};

// Following are for tab type specialisations
template<typename tab_type>
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
template<>
class tab_type_impl<editable_t>
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
template<>
class tab_type_impl<graph_t>
{
public:
    static QWidget* tabWidget(IBlock* block)
    {
        auto customPlot = new QCustomPlot();
        /*utility::Plot<double> p(customPlot);

        // Draw the input training data as a scatter pot
        p.scatterPlotYX(Y, X);

        // And overlay the linear model prediction
        using namespace std::placeholders;  // For e.g. _1
        calc_t<double> fptr = std::bind(&maths::linear::Regression<double>::calculate, f, _1);
        p.drawFunction(0, 100, 1, fptr);*/

        return customPlot;
    }
};


} } // graph, je


#endif // BLOCKUTILS_H
