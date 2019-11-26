#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QWebSettings* settings =
    connect(ui->webView, SIGNAL(loadProgress(int)),this, SLOT(on_progess(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)),this, SLOT(on_load_finished(bool)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_load_clicked()
{
    QUrl url = ui->url->text();
    ui->webView->load(url);
}

void Widget::on_progess(int progess)
{
    QString title = QString::number(progess) + "%";

    this->setWindowTitle(title);
}

void Widget::on_load_finished(bool ok)
{
    qDebug() << "加载成功";
    QWebElementCollection elements = ui->webView->page()->mainFrame()->findAllElements("#imgid > div > ul > li > div > a > img");
    for(int i = 0; i < elements.count(); i++)
    {
        const QWebElement& ele = elements.at(i);
//        qDebug() << ele.attribute("src") << endl;
        QString url = ele.attribute("src");
        QImage image = DownLoadImage(url);

        QFileInfo info(url);
        image.save("F:/Project/Qt/webkit_debug/" + info.fileName());
//        qDebug() << "save image" << info.fileName();
        QEventLoop loop;
        QTimer::singleShot(2000, &loop, SLOT(quit()));
        loop.exec();
    }

    elements = ui->webView->page()->mainFrame()->findAllElements("#topRS > a:nth-child(3)");
    if(elements.count() < 0)
    {
        qDebug() << "not next page";
    }
    QString url = "https://image.baidu.com" + elements[0].attribute("href");
    ui->webView->load(url);

}

QImage Widget::DownLoadImage(const QString &url)
{
    QNetworkAccessManager mgr;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QNetworkReply* reply = mgr.get(request);

    // 异步改同步
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray data = reply->readAll();
    QImage image = QImage::fromData(data);
    return image;
}
