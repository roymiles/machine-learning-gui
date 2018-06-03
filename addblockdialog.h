#ifndef ADDBLOCKDIALOG_H
#define ADDBLOCKDIALOG_H

#include <QDialog>

namespace Ui {
class AddBlockDialog;
}

class AddBlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBlockDialog(QWidget *parent = 0);
    ~AddBlockDialog();

private:
    Ui::AddBlockDialog *ui;
};

#endif // ADDBLOCK_H
