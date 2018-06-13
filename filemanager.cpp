#include "filemanager.h"
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

FileManager::FileManager()
{
}

FileManager::FileManager(QString fileName)
{
    this->fileName = fileName;
}

FileManager::~FileManager()
{
    // Free up memory
    delete plainTextEdit;
}

inline QString FileManager::getCompleteFilePath()
{
    // TODO: This needs to be changed
    return "C:\\Users\\Roy\\Documents\\JumboEagle\\" + this->fileName + ".txt";
}

bool FileManager::isValidFileName()
{
    // TODO: Add extra validation, such as filename length
    // True if fileName only contains alphanumeric characters
    QRegularExpression re("^[A-Za-z]+$"); // Contains alphanumeric characters only
    QRegularExpressionMatch match = re.match(fileName);
    return match.hasMatch();
}

bool FileManager::createSourceFile()
{

    QFile file(getCompleteFilePath());
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Empty source file" << endl;
    }

    return true;
}

QPlainTextEdit* FileManager::getContent()
{
    return plainTextEdit;
}

bool FileManager::loadSourceFile()
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


