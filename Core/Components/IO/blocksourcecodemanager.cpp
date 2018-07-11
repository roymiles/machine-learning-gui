#include "blocksourcecodemanager.h"
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

namespace je { namespace component { namespace io {

BlockSourceCodeManager::BlockSourceCodeManager() : IComponent(C_TEXT_EDITOR)
{
}

BlockSourceCodeManager::BlockSourceCodeManager(QString fileName) : IComponent(C_TEXT_EDITOR)
{
    this->fileName = fileName;
}

BlockSourceCodeManager::~BlockSourceCodeManager()
{
    // Free up memory
    delete plainTextEdit;
}

inline const QString BlockSourceCodeManager::getCompleteFilePath() const
{
    // TODO: This needs to be changed
    return "C:\\Users\\Roy\\Documents\\JumboEagle\\" + this->fileName + ".txt";
}

bool BlockSourceCodeManager::createSourceFile()
{

    QFile file(getCompleteFilePath());
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Empty source file" << endl;
    }

    return true;
}

QPlainTextEdit* BlockSourceCodeManager::getContent() const
{
    return plainTextEdit;
}

bool BlockSourceCodeManager::loadSourceFile()
{
    QString completeFilePath = getCompleteFilePath();
    if (!QFile::exists(completeFilePath))
        return false;

    QFile file(completeFilePath);
    if (!file.open(QFile::ReadOnly))
        return false;

    // I Don't understand any of the following code...
    // (found it online somewhere)
    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);

    str = QString::fromLocal8Bit(data);
    plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setPlainText(str);

    return true;
}

} } } // io, component, je

