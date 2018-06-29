#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>
#include "../Graph/graphwidget.h"

namespace Ui {
class AddBlockDialog;
}

enum BlockTypes : int {
    USER_BLOCK = 0,
    LINEAR_REGRESSION = 1
};

class AddBlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBlockDialog(QWidget *parent = 0);
    ~AddBlockDialog();

    void setGraphWidget(GraphWidget *graphWidget);

private slots:
    void on_AddBlockDialog_finished(int result);
    void on_AddBlockConfirmButton_accepted();
    void on_AddBlockConfirmButton_rejected();

private:
    Ui::AddBlockDialog *ui;
    GraphWidget *graphWidget;
};

#endif // ADDBLOCKDIALOG_H
