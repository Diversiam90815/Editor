
#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    QSettings registry("HKEY_CURRENT_USER\\Software\\Editor", QSettings::IniFormat);
    QString lang = registry.value("lang").toString();
    if(lang == "en")
    {
        QVariant variant = translator.load("N:/Coding/QT-Projects/TestMainWindow/tr_en.qm");
    }
    else if(lang == "de")
    {
        QVariant variant = translator.load("");
    }
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
