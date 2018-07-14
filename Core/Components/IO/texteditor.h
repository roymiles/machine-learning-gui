#pragma once

#include <QString>
#include <QPlainTextEdit>
#include <memory>

namespace je { namespace component { namespace io {

/*
 * Responsible for creating the block source files (adding boilerplate code)
 * and validating file names
 */
class TextEditor
{
public:
    TextEditor() = delete;
    TextEditor(QString fileName);
    ~TextEditor();

    const QString getCompleteFilePath() const;
    bool createSourceFile();

    bool loadSourceFile(); // Attempt to load the source file (and place in textEdit)
    QPlainTextEdit* getContent() const; // getter for textEdit

private:
    QString fileName;
    QPlainTextEdit* plainTextEdit;
};

} } } // io, component, je
