#pragma once

#include <QString>
#include <QPlainTextEdit>
#include <memory>
#include "../icomponent.h"

namespace je { namespace component { namespace io {

/*
 * Responsible for creating the block source files (adding boilerplate code)
 * and validating file names
 */
class TextEditor : public IComponent
{
public:
    TextEditor() = delete;
    TextEditor(QString fileName);
    ~TextEditor();

    const QString getCompleteFilePath() const;
    bool createSourceFile() override;

    bool loadSourceFile() override; // Attempt to load the source file (and place in textEdit)
    QPlainTextEdit* getContent() const override; // getter for textEdit

    static component_types componentType()
    {
        return C_TEXT_EDITOR;
    }

private:
    QString fileName;
    QPlainTextEdit* plainTextEdit;
};

} } } // io, component, je
