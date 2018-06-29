#include "customblock.h"
#include "../../Utility/utilities.h"

namespace je {

/*
 * Only initialise the ports if required for the given block type
 * All constructors pass default transform parameters to the parent
 * Block, however, these can be changed at runtime.
 *
 * Following specialisations for blockType
 */
template<typename inType,
         typename outType,
         typename tabType>
CustomBlock<source_t, inType, outType, tabType>::CustomBlock() : Block(50, 50, 100, 100)
{
    ports.first = nullptr;
    ports.second = std::make_shared<OutputPort>(this);
}

template<typename inType,
         typename outType,
         typename tabType>
CustomBlock<sink_t, inType, outType, tabType>::CustomBlock() : Block(50, 50, 100, 100)
{
    ports.first = std::make_shared<InputPort>(this);
    ports.second = nullptr;
}

template<typename inType,
         typename outType,
         typename tabType>
CustomBlock<block_t, inType, outType, tabType>::CustomBlock() : Block(50, 50, 100, 100)
{
    ports.first = std::make_shared<InputPort>(this);
    ports.second = std::make_shared<OutputPort>(this);
}

/*
 * Following specialisations for tabType
 */
template<typename blockType,
         typename inType,
         typename outType>
QWidget* CustomBlock<blockType, inType, outType, editable_t>::loadTabWidget()
{
    // First time opening tab, so create an instance of the file manager
    if(blockSourceCodeManager == nullptr)
        blockSourceCodeManager = std::make_unique<io::BlockSourceCodeManager>(this->getName());

    // Attempt to load the source file. If file does not exist, create it
    if(!blockSourceCodeManager->loadSourceFile())
        blockSourceCodeManager->createSourceFile(); // Create the source file, build boiler plate code

    return blockSourceCodeManager->getContent();
}

template<typename blockType,
         typename inType,
         typename outType>
QWidget* CustomBlock<blockType, inType, outType, graph_t>::loadTabWidget()
{
    return nullptr;
}

/*
 * Following specialisations for tabType
 */
/*template<typename blockType,
         typename inType,
         typename outType>
outType CustomBlock<blockType, inType, outType, editable_t>::execute(inType in)
{
    // Load from DLL
}

template<typename blockType,
         typename inType,
         typename outType>
outType CustomBlock<blockType, inType, outType, graph_t>::execute(inType in)
{
    // Load internally
}*/

/*
 * Might want each block type to look different, different colour etc
 * Only attempt draw ports that exist for the given block type
 *
 * Following specialisations for blockType
 */
template<typename inType,
         typename outType,
         typename tabType>
void CustomBlock<source_t, inType, outType, tabType>::draw(QPainter *painter)
{
    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

    // Write name inside block
    painter->drawText(rectangle, Qt::AlignCenter, getName());

    ports.second->draw(painter);
}

template<typename inType,
         typename outType,
         typename tabType>
void CustomBlock<sink_t, inType, outType, tabType>::draw(QPainter *painter)
{
    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

    // Write name inside block
    painter->drawText(rectangle, Qt::AlignCenter, getName());

    ports.first->draw(painter);
}

template<typename inType,
         typename outType,
         typename tabType>
void CustomBlock<block_t, inType, outType, tabType>::draw(QPainter *painter)
{
    QRect rectangle(Block::getX(), Block::getY(), Block::getW(), Block::getH());
    painter->fillRect(rectangle, Qt::white);
    painter->drawRect(rectangle);

    // Write name inside block
    painter->drawText(rectangle, Qt::AlignCenter, getName());

    ports.first->draw(painter);
    ports.second->draw(painter);
}

/*
 * Check if the block is inside the main block or any (if any) of the ports
 * e.g. For the source type, do not need to check input port as it does not exist
 *
 * Following specialisations for blockType
 */
template<typename inType,
         typename outType,
         typename tabType>
clickType CustomBlock<source_t, inType, outType, tabType>::mousePressEvent(QPoint &point)
{
    if(insideRect(this, point))
        return clickType::block;
    else if(insideRect(ports.second, point))
        return clickType::outPort;
    else
        return clickType::none;
}

template<typename inType,
         typename outType,
         typename tabType>
clickType CustomBlock<sink_t, inType, outType, tabType>::mousePressEvent(QPoint &point)
{
    if(insideRect(this, point))
        return clickType::block;
    else if(insideRect(ports.first, point))
        return clickType::inPort;
    else
        return clickType::none;
}

template<typename inType,
         typename outType,
         typename tabType>
clickType CustomBlock<block_t, inType, outType, tabType>::mousePressEvent(QPoint &point)
{
    if(insideRect(this, point))
        return clickType::block;
    else if(insideRect(ports.first, point))
        return clickType::inPort;
    else if(insideRect(ports.second, point))
        return clickType::outPort;
    else
        return clickType::none;
}

} // je

