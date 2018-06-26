#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QPlainTextEdit>
#include <memory>

namespace je { namespace io {

/*
 * Responsible for creating the block source files (adding boilerplate code)
 * and validating file names
 */
class FileManager
{
public:
    FileManager();
    FileManager(QString fileName);
    ~FileManager();

    const QString getCompleteFilePath() const;
    bool isValidFileName() const;
    bool createSourceFile();

    bool loadSourceFile(); // Attempt to load the source file (and place in textEdit)
    QPlainTextEdit* getContent() const; // getter for textEdit

private:
    QString fileName;
    QPlainTextEdit* plainTextEdit;
};

} } // io, je

#endif // FILEMANAGER_H
