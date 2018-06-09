#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QPlainTextEdit>
#include <memory>

/*
 * Responsible for creating the block source files (adding boilerplate code)
 * and validating file names
 */
class FileManager
{
public:
    FileManager();
    FileManager(QString fileName);

    bool isValidFileName();
    bool createSourceFile();

    bool loadSourceFile(); // Attempt to load the source file (and place in textEdit)
    QPlainTextEdit* getContent(); // getter for textEdit

private:
    QString fileName;
    QPlainTextEdit* plainTextEdit;
};

#endif // FILEMANAGER_H
