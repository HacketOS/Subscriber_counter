// This programm show subscriber count

#include "mainwindow.h"
#include <QApplication>
#include <QtNetwork>
#include <QLabel>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QNetworkAccessManager manager;
    // chanel ref
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl("https://www.youtube.com/user/PewDiePie")));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();// response waiting loop

    QString html = response->readAll(); // get page html
    html = html.toHtmlEscaped();

    int pos1,pos2;
    QString mem;

    pos1 = html.lastIndexOf("subscriber"); // serach for a subscriber count
    pos2 = html.indexOf("title",pos1)+12;
    pos1 = html.indexOf("&",pos2);
    mem = html.mid(pos2,pos1-pos2);
    QLabel* l = new QLabel(&w);
    l->setText(mem);
    w.resize(200,100);
    w.show();
    return a.exec();
}
