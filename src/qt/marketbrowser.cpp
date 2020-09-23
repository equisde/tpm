#include "marketbrowser.h"
#include "ui_marketbrowser.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <QDesktopServices>

#include <sstream>
#include <string>

using namespace json_spirit;

const QString kBaseUrl = "http://cryptotpmcoin.com/tpmcoinusd.php";
const QString kBaseUrl1 = "http://blockchain.info/tobtc?currency=USD&value=1";
const QString kBaseUrl2 = "http://cryptotpmcoin.com/tpmcoinmkt.php";
const QString kBaseUrl4 = "http://cryptotpmcoin.com/tpmcoinclp.php";
const QString kBaseUrl3 = "http://cryptotpmcoin.com/tpmcoinbtc.php";

QString bitcoinp = "";
QString tpmcoinp = "";
QString tpmcoinp2 = "";
QString dnrmcp = "";
QString dnrbtcp = "";
double bitcoin2;
double tpmcoin2;
double tpmcoin3;
double dnrmc2;
double dnrbtc2;
QString bitcoing;
QString dnrmarket;
QString dollarg;
QString clpg;
int mode=1;
int o = 0;


MarketBrowser::MarketBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketBrowser)
{
    ui->setupUi(this);
    setFixedSize(400, 420);


requests();
QObject::connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
connect(ui->startButton, SIGNAL(pressed()), this, SLOT( requests()));
connect(ui->egal, SIGNAL(pressed()), this, SLOT( update()));

}

void MarketBrowser::update()
{
    QString temps = ui->egals->text();
    double totald = dollarg.toDouble() * temps.toDouble();
    double totaldb = clpg.toDouble() * temps.toDouble();
    double totaldq = bitcoing.toDouble() * temps.toDouble();
    ui->egald->setText("$ "+QString::number(totald)+" USD or "+QString::number(totaldq)+" BTC");

}

void MarketBrowser::requests()
{
	getRequest(kBaseUrl);
    getRequest(kBaseUrl1);
	getRequest(kBaseUrl2);
	getRequest(kBaseUrl3);
	getRequest(kBaseUrl4);
}

void MarketBrowser::getRequest( const QString &urlString )
{
    QUrl url ( urlString );
    QNetworkRequest req ( url );
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    m_nam.get(req);
}

void MarketBrowser::parseNetworkResponse(QNetworkReply *finished )
{

    QUrl what = finished->url();

    if ( finished->error() != QNetworkReply::NoError )
    {
        // A communication error has occurred
        emit networkError( finished->error() );
        return;
    }
	
if (what == kBaseUrl) // TpmCoin Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString tpmcoin = finished->readAll();
    tpmcoin2 = (tpmcoin.toDouble());
    tpmcoin = QString::number(tpmcoin2, 'f', 2);
	
    if(tpmcoin > tpmcoinp)
    {
        ui->tpmcoin->setText("<font color=\"yellow\">$" + tpmcoin + "</font>");
    } else if (tpmcoin < tpmcoinp) {
        ui->tpmcoin->setText("<font color=\"red\">$" + tpmcoin + "</font>");
        } else {
    ui->tpmcoin->setText("$"+tpmcoin+" USD");
    }

    tpmcoinp = tpmcoin;
	dollarg = tpmcoin;
    
}

if (what == kBaseUrl1) // Bitcoin Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString bitcoin = finished->readAll();
    bitcoin2 = (1 / bitcoin.toDouble());
    bitcoin = QString::number(bitcoin2, 'f', 2);
    if(bitcoin > bitcoinp)
    {
        ui->bitcoin->setText("<font color=\"yellow\">$" + bitcoin + " USD</font>");
    } else if (bitcoin < bitcoinp) {
        ui->bitcoin->setText("<font color=\"red\">$" + bitcoin + " USD</font>");
        } else {
    ui->bitcoin->setText("$"+bitcoin+" USD");
    }

    bitcoinp = bitcoin;
}

if (what == kBaseUrl2) // TpmCoin Market Cap
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString dnrmc = finished->readAll();
    dnrmc2 = (dnrmc.toDouble());
    dnrmc = QString::number(dnrmc2, 'f', 2);
	
    if(dnrmc > dnrmcp)
    {
        ui->dnrmc->setText("<font color=\"yellow\">$" + dnrmc + "</font>");
    } else if (dnrmc < dnrmcp) {
        ui->dnrmc->setText("<font color=\"red\">$" + dnrmc + "</font>");
        } else {
    ui->dnrmc->setText("$"+dnrmc+" USD");
    }

    dnrmcp = dnrmc;
	dnrmarket = dnrmc;
}
if (what == kBaseUrl4) // TpmCoin Price BRL
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString tpmcoinz = finished->readAll();
    tpmcoin3 = (tpmcoinz.toDouble());
    tpmcoinz = QString::number(tpmcoin3, 'f', 2);
	
	/* 
    if(tpmcoinz > tpmcoinp2)
    {
        ui->tpmcoinz->setText("<font color=\"yellow\">$" + tpmcoinz + "</font>");
    } else if (tpmcoinz < tpmcoinp) {
        ui->tpmcoinz->setText("<font color=\"red\">$" + tpmcoinz + "</font>");
        } else {
    ui->tpmcoin->setText("$"+tpmcoinz+" BRL");
    } */
	
    tpmcoinp2 = tpmcoinz;
	clpg = tpmcoinz;
}

if (what == kBaseUrl3) // TpmCoin BTC Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString dnrbtc = finished->readAll();
    dnrbtc2 = (dnrbtc.toDouble());
    dnrbtc = QString::number(dnrbtc2, 'f', 8);
	
    if(dnrbtc > dnrbtcp)
    {
        ui->dnrbtc->setText("<font color=\"yellow\">" + dnrbtc + " BTC</font>");
    } else if (dnrbtc < dnrbtcp) {
        ui->dnrbtc->setText("<font color=\"red\">" + dnrbtc + " BTC</font>");
        } else {
    ui->dnrbtc->setText(dnrbtc+" BTC");
    }

    dnrbtcp = dnrbtc;
	bitcoing = dnrbtc;
}

finished->deleteLater();
}


void MarketBrowser::setModel(ClientModel *model)
{
    this->model = model;
}

MarketBrowser::~MarketBrowser()
{
    delete ui;
}
