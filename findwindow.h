#ifndef FINDWINDOW_H
#define FINDWINDOW_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class FindWindow;
}

class FindWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FindWindow(QWidget *parent = nullptr, QTextEdit *text = nullptr);
    ~FindWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_btnSearch_clicked();

private:
    Ui::FindWindow *ui;
    QTextEdit * selText;
};

#endif // FINDWINDOW_H
