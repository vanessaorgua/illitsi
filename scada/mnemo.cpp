
#include "mnemo.h"
#include "ui_mnemo.h"

#include <IoNetClient.h>

#include <QVBoxLayout>
#include <QTimer>

#include <apone.h>
#include "trendchart.h"
#include "dlgapone.h"


Mnemo::Mnemo(IoNetClient &src, QWidget *p) : QLabel(p), m_ui(new Ui::mnemo),s(src)
{
    m_ui->setupUi(this);



    connect(&s,SIGNAL(updateDataRaw()),this,SLOT(updateDataRaw())); // при отриманні нових даних, засвітити їх на картинці
    connect(&s,SIGNAL(updateDataScaled()),this,SLOT(updateDataScaled())); // при отриманні нових даних, засвітити їх на картинці

    QTimer *t=new QTimer(this);
    t->setInterval(1000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(updateTrend()));

    {
        ApOne *t=new ApOne(m_ui->ap_1);
        ap << t;
    }
    {
        ApOne *t=new ApOne(m_ui->ap_2);
        ap << t;
    }
    {
        ApOne *t=new ApOne(m_ui->ap_3);
        ap << t;
    }
    trc << new TrendChart(m_ui->frame_1,7200,10) << new TrendChart(m_ui->frame_2,7200,10) << new TrendChart(m_ui->frame_3,7200,10);

    {
        QVBoxLayout *vbl=new QVBoxLayout(m_ui->frame_1);
        vbl->addWidget(trc[0]);
        m_ui->frame_1->setLayout(vbl);
    }
    {
        QVBoxLayout *vbl=new QVBoxLayout(m_ui->frame_2);
        vbl->addWidget(trc[1]);
        m_ui->frame_2->setLayout(vbl);
    }
    {
        QVBoxLayout *vbl=new QVBoxLayout(m_ui->frame_3);
        vbl->addWidget(trc[2]);
        m_ui->frame_3->setLayout(vbl);
    }
    connect(m_ui->bnCall_1,SIGNAL(clicked()),this,SLOT(slotCallDlgApOne()));
    connect(m_ui->bnCall_2,SIGNAL(clicked()),this,SLOT(slotCallDlgApOne()));
    connect(m_ui->bnCall_3,SIGNAL(clicked()),this,SLOT(slotCallDlgApOne()));

}

Mnemo::~Mnemo()
{
    delete m_ui;
}


void Mnemo::updateDataRaw()
{

}

void Mnemo::updateDataScaled() // слот обновляє дані на мнемосхемі
{

}

void Mnemo::updateTrend()
{
  //m_ui->labelSize->setText(QString("%1x%2").arg(size().width()).arg(size().height()));
  
}

void Mnemo::slotCallDlgApOne()
{
    DlgApOne p(*s[sender()->objectName().right(1).toInt()-1],this);
    p.exec();
}
