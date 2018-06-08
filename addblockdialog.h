#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>
#include "graphwidget.h"

namespace Ui {
class AddBlockDialog;
}

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
