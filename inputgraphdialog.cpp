#include "inputgraphdialog.h"
#include "ui_inputgraphdialog.h"
#include <QDebug>

InputGraphDialog::InputGraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputGraphDialog)
{
    ui->setupUi(this);
}

InputGraphDialog::~InputGraphDialog()
{
    delete ui;
}

void InputGraphDialog::on_lineEdit_editingFinished()
{

}

void InputGraphDialog::on_buttonBox_accepted()
{
    int num;
    num=ui->lineEdit->text().toInt();
    qDebug()<<num;

}
