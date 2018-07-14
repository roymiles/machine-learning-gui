#include "texteditor.h"
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

namespace je { namespace component { namespace io {

TextEditor::TextEditor(QString fileName) : IComponent(C_TEXT_EDITOR)
{
    this->fileName = fileName;
}

TextEditor::~TextEditor()
{
    // Free up memory
    delete plainTextEdit;
}

inline const QString TextEditor::getCompleteFilePath() const
{
    // TODO: This needs to be changed
    return "C:\\Users\\Roy\\Documents\\JumboEagle\\" + this->fileName + ".txt";
}

bool TextEditor::createSourceFile()
{

    QFile file(getCompleteFilePath());
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Empty source file" << endl;
    }

    return true;
}

QPlainTextEdit* TextEditor::getContent() const
{
    return plainTextEdit;
}

bool TextEditor::loadSourceFile()
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

