
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "findwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    dirty = false;
    filter = tr("Textdatei (*.txt);;Comma Separated Values (*.csv);;XML-Datei (*.xml)");
    filter += tr("CPlusPlus-Datei (*.CPP);; Header Datei (*.h) ");
    setWindowTitle("Editor");
    zoomfaktor = 100;
    printer.setPrinterName("Microsoft Print to PDF");
    ui->lblZoom->setText(tr("Zoom: ") + QString::number(zoomfaktor));
    ui->statusbar->addPermanentWidget(ui->lblZoom);

    QSettings registry("HKEY_CURRENT_USER\\Software\\Editor", QSettings::IniFormat);
    QString lang = registry.value("lang").toString();
    if(lang == "en")
    {
        ui->actionEnglisch->setChecked(true);
    }
    else if(lang == "de")
    {
        ui->actionDeutsch->setChecked(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_Beenden_triggered()
{
    //Wurde der Text verändert, dann speichern?
    checkDirty();
    close();
    QApplication::quit();
}


void MainWindow::on_textEdit_textChanged()
{
    dirty = true;
}


void MainWindow::on_action_Neu_triggered()
{
    checkDirty();       //Sorgt für das Speichern ungesicherter Veränderungen.
    //textedit leeren
    ui->textEdit->clear();
    filename = "";
    dirty = false;
}


void MainWindow::on_action_Speichern_triggered()
{
    //Gibt es einen Dateinamen?
    if(filename == "")
        filename = getFilenameForSave();
    if(filename != "")
        save(filename);
}


void MainWindow::on_actionSpeichern_unter_triggered()
{
    //Merke alten Dateinamen
    QString keep_filename = filename;
    //Speichern unter-Fenster anzeigen
    filename = getFilenameForSave();
    // und speichern
    if(filename != "")
        save(filename);
    else
        filename = keep_filename;
}


QString MainWindow::getFilenameForSave()
{
    return QFileDialog::getSaveFileName(this,
            tr("Datei speichern"),"c:/temp", filter);
}


void MainWindow::save(QString filename)
{
    //Datei wird gespeichert
    QFile file(filename);
    if(! file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("Fehler beim Speichern"),
                              tr("Speichern in diesem Verzeichnis nicht möglich"));
            return;
    }
    QTextStream buffer(&file);
    buffer << ui->textEdit->toPlainText();
    file.close();
    dirty = false;
    setWindowTitle("Editor - " + filename);
    ui->statusbar->showMessage(tr("Daten wurden gespeichert."),3000);
}


void MainWindow::on_action_Ausschneiden_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_action_Oeffnen_triggered()
{

    checkDirty();
    filename = QFileDialog::getOpenFileName(this, tr("Datei öffnen"),
                                            "c:/temp", filter);
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Datei öffnen"), tr("Die Datei lässt sich nicht öffnen."), QMessageBox::Ok);
        return;
    }
    QTextStream buffer(&file);
    ui->textEdit->setText(buffer.readAll());
    file.close();
    dirty = false;
    setWindowTitle("Editor - " + filename);
}


void MainWindow::checkDirty()
{
    QMessageBox::StandardButton reply;
    if(dirty)
    {
        reply = QMessageBox::question(this, tr("Neue Datei"),
                                      tr("Die Datei wurde verändert. \nWollen Sie speichern?"),
                                          QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        //ggf speichern
        if(reply == QMessageBox::Cancel)
        return;
        else if(reply == QMessageBox::Yes)
        {
            //Gibt es schon einen Dateinamen?
            if(filename == "")
            {
                //wenn nein dann Speichern unter Fenster anzeigen
                filename = getFilenameForSave();
            }
            //und speichern
            //Wenn ja, dann speichern
            if(filename != "")
                save(filename);
        }
    }
}


void MainWindow::on_action_Wiederholen_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_action_Kopieren_triggered()
{
    ui->textEdit->copy();
    ui->statusbar->showMessage(tr("Auswahl kopiert."), 3000);
}


void MainWindow::on_action_Einfuegen_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionZoomIn_triggered()
{
    ui->textEdit->zoomIn(10);
    zoomfaktor *= 2;
    ui->lblZoom->setText(tr("Zoom: ") + QString::number(zoomfaktor));
}


void MainWindow::on_actionZoomOut_triggered()
{
    ui->textEdit->zoomOut(10);
    zoomfaktor /= 2;
    ui->lblZoom->setText(tr("Zoom: ") + QString::number(zoomfaktor));
}


void MainWindow::on_action_Schriftart_triggered()
{
    bool ok;
    QFont font = ui->textEdit->font();
    font = QFontDialog::getFont(&ok, font, this);
    if(!ok) return;
    ui->textEdit->setFont(font);
    dirty = true;
}


void MainWindow::on_actionLinksbuendig_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_actionZentriert_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::on_actionRechtsbuendig_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}


void MainWindow::on_actionFarbe_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, tr("Schriftfarbe einstellen."));
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}


void MainWindow::on_actionEnglisch_triggered()
{
    QSettings registry("HKEY_CURRENT_USER\\Software\\Editor", QSettings::IniFormat);
    registry.setValue("lang", "en");
    enable_all_languages();
    ui->actionEnglisch->setChecked(true);
    ui->actionEnglisch->setEnabled(false);
    QMessageBox::information(this, "Change of language", "To change the language, please restart the application.");
}


void MainWindow::on_actionDeutsch_triggered()
{
    QSettings registry("HKEY_CURRENT_USER\\Software\\Editor", QSettings::IniFormat);
    registry.setValue("lang", "de");
    enable_all_languages();
    ui->actionDeutsch->setChecked(true);
    ui->actionDeutsch->setEnabled(false);
    QMessageBox::information(this, "Sprachumstellung", "Für die Umstellung auf eine andere Sprache "
                                                       "starten Sie die Anwendung bitte neu.");

}


void MainWindow::enable_all_languages()
{
    ui->actionDeutsch->setEnabled(true);
    ui->actionDeutsch->setChecked(false);
    ui->actionEnglisch->setEnabled(true);
    ui->actionEnglisch->setChecked(false);
    ui->actionFranz_sisch->setEnabled(true);
    ui->actionFranz_sisch->setChecked(false);
    ui->actionSpanisch->setEnabled(true);
    ui->actionSpanisch->setChecked(false);
    ui->actionRussisch->setEnabled(true);
    ui->actionRussisch->setChecked(false);
}


void MainWindow::on_action_Vorschau_triggered()
{
    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(&printer, this);
    QTextDocument * document = new QTextDocument;
    document->setPlainText(ui->textEdit->toPlainText());
    connect(dialog,     &QPrintPreviewDialog::paintRequested,
            [&](QPrinter *previewPrinter){document->print(previewPrinter);});
    dialog->exec();
    delete document;
    delete dialog;
}


void MainWindow::on_action_Drucken_2_triggered()
{
    QPrintDialog printdialog(&printer, this);
    if(printdialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}


void MainWindow::on_action_Suchen_triggered()
{
    QTextEdit * text = ui->textEdit;
    FindWindow * findwdw = new FindWindow(this, text);
    findwdw->show();
}

