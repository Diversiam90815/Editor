
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QStatusBar>
#include <QLabel>
#include <QFontDialog>
#include <QColorDialog>
#include <QTranslator>
#include <QSettings>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QTextDocument>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_action_Beenden_triggered();

    void on_textEdit_textChanged();

    void on_action_Neu_triggered();

    void on_action_Speichern_triggered();

    void on_actionSpeichern_unter_triggered();

    void on_action_Ausschneiden_triggered();

    void on_action_Oeffnen_triggered();

    void on_action_Wiederholen_triggered();

    void on_action_Kopieren_triggered();

    void on_action_Einfuegen_triggered();

    void enable_all_languages();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_action_Schriftart_triggered();

    void on_actionLinksbuendig_triggered();

    void on_actionZentriert_triggered();

    void on_actionRechtsbuendig_triggered();

    void on_actionFarbe_triggered();

    void on_actionEnglisch_triggered();

    void on_actionDeutsch_triggered();

    void on_action_Vorschau_triggered();

    void on_action_Drucken_2_triggered();

    void on_action_Suchen_triggered();

private:
    Ui::MainWindow *ui;
    bool dirty;
    QString filename;
    QString filter;
    QLabel lblZoom;
    int zoomfaktor;
    QPrinter printer;


    void save(QString filename);
    QString getFilenameForSave();
    void checkDirty();
};

#endif // MAINWINDOW_H
