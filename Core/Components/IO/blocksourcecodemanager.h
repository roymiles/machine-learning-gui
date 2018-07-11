#pragma once

#include <QString>
#include <QPlainTextEdit>
#include <memory>
#include "../icomponent.h"

namespace je { namespace component { namespace io {

/*
 * Responsible for creating the block source files (adding boilerplate code)
 * and validating file names
 *
 *
 * THIS CLASS NAME IS CRAP DO SOMEN ABOUT PLUZ
 * NEED TO MAKE IT GENERIC AND THEN THIS CAN BE A SPECIFIC IMPLEMENTATION OF...
 * MAYBE JUST "TEXTEDITOR"?
 */
class BlockSourceCodeManager : public IComponent
{
public:
    BlockSourceCodeManager();
    BlockSourceCodeManager(QString fileName);
    ~BlockSourceCodeManager();

    const QString getCompleteFilePath() const;
    bool createSourceFile();

    bool loadSourceFile(); // Attempt to load the source file (and place in textEdit)
    QPlainTextEdit* getContent() const; // getter for textEdit

    static component_types componentType()
    {
        return C_TEXT_EDITOR;
    }

private:
    QString fileName;
    QPlainTextEdit* plainTextEdit;
};

} } } // io, component, je
