#include "block.h"
#include "../debug.h"

#include <QPainter>
#include <QRect>

namespace je {

Block::Block()
{
    x = 0;
    y = 0;
    w = 50;
    h = 50;
    fileManager = nullptr;
    tabIndex = -1; // Duplicate constructor code
}

Block::Block(int x, int y, int width, int height) // Maybe add constructor initialisation?
{
    this->x = x;
    this->y = y;
    this->w = width;
    this->h = height;
    fileManager = nullptr;
    tabIndex = -1;
}

Block::~Block()
{
    // Free up memory
    fileManager = nullptr;
}

void Block::setX(int x)
{
    this->x = x;
}

void Block::setY(int y)
{
    this->y = y;
}

void Block::setPos(QPoint point)
{
    this->x = point.x();
    this->y = point.y();
}

int Block::getX() const
{
    return x;
}

int Block::getY() const
{
    return y;
}

int Block::getW() const
{
    return w;
}

int Block::getH() const
{
    return h;
}


void Block::setName(QString name)
{
    this->name = name;
}

void Block::setFileManager(std::unique_ptr<FileManager> fileManager)
{
    this->fileManager = std::move(fileManager);
}

const QString& Block::getName() const
{
    return this->name;
}

bool Block::loadSource()
{
    if(fileManager == nullptr)
        return false;

    return fileManager->loadSourceFile();
}

QPlainTextEdit* Block::getSource()
{
    return fileManager->getContent();
}

} // je
