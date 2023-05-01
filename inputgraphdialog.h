#ifndef INPUTGRAPHDIALOG_H
#define INPUTGRAPHDIALOG_H

#include <QDialog>

namespace Ui {
class InputGraphDialog;
}

class InputGraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputGraphDialog(QWidget *parent = 0);
    ~InputGraphDialog();

private slots:
    void on_lineEdit_editingFinished();

    void on_buttonBox_accepted();

private:
    Ui::InputGraphDialog *ui;
};

#endif // INPUTGRAPHDIALOG_H
