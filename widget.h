#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWebSettings>
#include <qdebug.h>
#include <QWebView>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFileInfo>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_load_clicked();
    void on_progess(int progess);
    void on_load_finished(bool ok);

private:
    Ui::Widget *ui;
    QImage DownLoadImage(const QString& url);
};

#endif // WIDGET_H
