
#include "mnemo.h"
#include "ui_mnemo.h"

#include <IoNetClient.h>

#include <QVBoxLayout>
#include <QTimer>

#include <apone.h>
#include "trendchart.h"
#include "dlgapone.h"
#include "dlgtermctrl.h"

#include "dlgalarm.h"

Mnemo::Mnemo(IoNetClient &src, QWidget *p) : QLabel(p), m_ui(new Ui::mnemo),s(src)
{
    m_ui->setupUi(this);



    connect(&s,SIGNAL(updateDataRaw()),this,SLOT(updateDataRaw())); // при отриманні нових даних, засвітити їх на картинці
    connect(&s,SIGNAL(updateDataScaled()),this,SLOT(updateDataScaled())); // при отриманні нових даних, засвітити їх на картинці

    QTimer *t=new QTimer(this);
    t->setInterval(10000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(updateTrend()));

    {
        ApOne *t=new ApOne(/**s[0],*/m_ui->ap_1);
        ap << t;
    }
    {
        ApOne *t=new ApOne(/**s[1],*/m_ui->ap_2);
        ap << t;
    }
    {
        ApOne *t=new ApOne(/**s[2],*/m_ui->ap_3);
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

    connect(m_ui->bn_T_1,SIGNAL(clicked()),this,SLOT(slotCallTermCtrl()));
    connect(m_ui->bn_T_2,SIGNAL(clicked()),this,SLOT(slotCallTermCtrl()));
    connect(m_ui->bn_T_3,SIGNAL(clicked()),this,SLOT(slotCallTermCtrl()));

    state
            << tr("Невизначено")
            << tr("Очікування")
            << tr("Очікування")
            << tr("Набір")
            << tr("Згущення")
            << tr("Затравка")
            << tr("Згущення")
            << tr("Поличка")
            << tr("Розкачака 1")
            << tr("Згущення")
            << tr("Розкачка 2")
            << tr("Згущення")
            << tr("Розкачка 3")
            << tr("Згущення")
            << tr("Ріст 1")
            << tr("Ріст 2")
            << tr("Ріст 3")
            << tr("Ріст 4")
            << tr("Уварювання")
            << tr("Вивантаження");

    connect(this,SIGNAL(signalAlarm()),this,SLOT(slotAlarm()));
}

Mnemo::~Mnemo()
{
    delete m_ui;
}


void Mnemo::updateDataRaw()
{
    for(int i=0;i<3;++i)
    {
        ap[i]->updateData(*s[i]);
    }
    m_ui->le_State_1->setText(state[s[0]->getValue16("Status")]);
    m_ui->le_State_2->setText(state[s[1]->getValue16("Status")]);
    m_ui->le_State_3->setText(state[s[2]->getValue16("Status")]);

    m_ui->pn_L_1->setValue(s[3]->getValueFloat("L_1"));
    m_ui->pn_L_2->setValue(s[3]->getValueFloat("L_2"));
    m_ui->pn_L_3->setValue(s[3]->getValueFloat("L_3"));

    bool c=s[3]->getValueFloat("L_1")>90.0 || s[3]->getValueFloat("L_2")>90.0 ||  s[3]->getValueFloat("L_3")>90.0 ;
/*
    if(c && (!alm))
    {
        emit signalAlarm();
    }
    alm=c;*/

    m_ui->le_T_1->setText(QString("%1").arg(s[3]->getValueFloat("T_1"),3,'f',0));
    m_ui->le_T_2->setText(QString("%1").arg(s[3]->getValueFloat("T_2"),3,'f',0));
    m_ui->le_T_3->setText(QString("%1").arg(s[3]->getValueFloat("T_3"),3,'f',0));

    //m_ui->c1_h_1->setChecked(s[3]->getValue16("h_1"));
    //m_ui->c1_h_2->setChecked(s[3]->getValue16("h_2"));
    //m_ui->c1_h_3->setChecked(s[3]->getValue16("h_3"));

    m_ui->bn_T_1->setIcon(QIcon(QPixmap(s[3]->getValue16("h_1")
                                      ?	":/pict/pict/lib/valve_green_20x32.png":":/pict/pict/lib/valve_off_20x32.png")));
    m_ui->bn_T_2->setIcon(QIcon(QPixmap(s[3]->getValue16("h_2")
                                      ?	":/pict/pict/lib/valve_green_20x32.png":":/pict/pict/lib/valve_off_20x32.png")));
    m_ui->bn_T_3->setIcon(QIcon(QPixmap(s[3]->getValue16("h_3")
                                      ?	":/pict/pict/lib/valve_green_20x32.png":":/pict/pict/lib/valve_off_20x32.png")));


}

void Mnemo::updateDataScaled() // слот обновляє дані на мнемосхемі
{

}

void Mnemo::updateTrend()
{
    QVector<double> v;

    for(int i=0;i<3;++i)
    {
        v.clear();
        v
                << s[i]->getValueFloat("Lev")*40.0
                << s[i]->getValueFloat("Vias")*40.0
                << s[i]->getValueFloat("Temp")*26.6666666667
                << s[i]->getValueFloat("Opr")*40.0
                << s[i]->getValueFloat("Vias")*40.0;
        trc[i]->addPoint(v);

    }
    //m_ui->labelSize->setText(QString("%1x%2").arg(size().width()).arg(size().height()));
  
}

void Mnemo::slotCallDlgApOne()
{
    DlgApOne p(*s[sender()->objectName().right(1).toInt()-1],this);
    p.setWindowTitle(QString(tr("Управління апаратом №%1")).arg(sender()->objectName().right(1)));
    p.exec();
}

void Mnemo::slotCallTermCtrl()
{
    DlgTermCtrl p(*s[3],sender()->objectName().right(1).toInt(),this);
    p.setWindowTitle(QString(tr("Збірник №%1")).arg(sender()->objectName().right(1)));
    p.exec();
}


void Mnemo::slotAlarm()
{
    DlgAlarm p(this);
    p.exec();
}


