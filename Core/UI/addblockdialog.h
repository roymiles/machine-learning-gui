#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>
#include "../Graph/graphwidget.h"

namespace Ui {
class AddBlockDialog;
}

namespace je {

enum BlockTypes : int {
    BLOCK = 0,
    SOURCE = 1,
    SINK = 2
};

class AddBlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBlockDialog(QWidget *parent = 0);
    ~AddBlockDialog();

    void setGraphWidget(graph::GraphWidget *graphWidget);

private slots:
    void on_AddBlockDialog_finished(int result);
    void on_AddBlockConfirmButton_accepted();
    void on_AddBlockConfirmButton_rejected();

private:
    Ui::AddBlockDialog *ui;
    graph::GraphWidget *graphWidget;
};

} // je

#endif // ADDBLOCKDIALOG_H
