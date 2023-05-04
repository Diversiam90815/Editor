#include "findwindow.h"
#include "ui_findwindow.h"

FindWindow::FindWindow(QWidget *parent, QTextEdit *text) :
    QDialog(parent),
    ui(new Ui::FindWindow)
{
    ui->setupUi(this);
    selText = text;

}

FindWindow::~FindWindow()
{
    delete ui;
}

void FindWindow::on_pushButton_2_clicked()
{
    close();
}


void FindWindow::on_btnSearch_clicked()
{
    //QTextEdit::ExtraSelection extra;
    QString word = ui->leWord->text();
    QTextCursor curs;
    int pos = selText->find(word);
    selText->setTextCursor(curs);
    curs.setPosition(pos);
}

