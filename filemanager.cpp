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
    QFile file(this->fileName);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "Empty source file" << endl;
    }

    file.close();

    return true;
}

QPlainTextEdit* FileManager::getContent()
{
    return plainTextEdit;
}

bool FileManager::loadSourceFile()
{
    if (!QFile::exists(this->fileName))
        return false;

    QFile file(this->fileName);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);

    str = QString::fromLocal8Bit(data);
    plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setPlainText(str);

    return true;
}


