#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QPoint>
#include <QString>
#include <QTextEdit>
#include <memory>
#include "port.h"
#include "../IO/filemanager.h"

namespace je { namespace graph {

// Checks where a click takes place
enum clickType{
    inPort,
    outPort,
    block,
    none
};

class Block
{
public:
    Block();
    Block(int x, int y, int width, int height);
    ~Block();

    virtual void draw(QPainter *painter) = 0;
    virtual clickType mousePressEvent(QPoint point) = 0;
    virtual void setActivePort(std::shared_ptr<Port> port) = 0;
    virtual std::shared_ptr<Port> getActivePort() = 0;

    void setX(int x);
    void setY(int y);
    void setPos(QPoint point);
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;

    void setName(QString name);
    const QString& getName() const;
    void setFileManager(std::unique_ptr<io::FileManager> fileManager);

    // Attempt to load source content
    bool loadSource();
    // After successfully loading the source, put it into a QTextEdit
    QPlainTextEdit* getSource();

    int tabIndex; // Current tab index, -1 if not in tab

private:
    int x, y, w, h;
    QString name;
    std::unique_ptr<io::FileManager> fileManager; // Definately a unique pointer as only block needs to access
};

} } // graph, je

#endif // BLOCK_H
