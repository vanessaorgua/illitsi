#include "dlgapone.h"
#include "ui_dlgapone.h"
#include "apone.h"
#include "iodev.h"
#include "dlgapsetup.h"

#include <QtGui>

DlgApOne::DlgApOne(IoDev &source,QWidget *parent) :
    QDialog(parent),
    src(source),
    ui(new Ui::DlgApOne)
{
    ui->setupUi(this);

    ap=new ApOne(/*src,*/ui->apMnemo);

    connect(ui->bnSetup,SIGNAL(clicked()),this,SLOT(slotCallSetup()));

    connect(ui->bnStop,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnStart,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnConcretion,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnPriming,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnRarefaction,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_1,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_2,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_3,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_4,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnClasp,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bx_prod,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSendProd(int)));

    // заповнення хешу команд

    cmd[ui->bnStop->objectName()]=1;
    cmd[ui->bnStart->objectName()]=3;
    cmd[ui->bnConcretion->objectName()]=4;
    cmd[ui->bnPriming->objectName()]=6;
    cmd[ui->bnRarefaction->objectName()]=8;
    cmd[ui->bnGrowth_1->objectName()]=14;
    cmd[ui->bnGrowth_2->objectName()]=15;
    cmd[ui->bnGrowth_3->objectName()]=16;
    cmd[ui->bnGrowth_4->objectName()]=17;
    cmd[ui->bnClasp->objectName()]=18;

    page[ui->bnStop->objectName()]=1;
    page[ui->bnStart->objectName()]=2;
    page[ui->bnConcretion->objectName()]=3;
    page[ui->bnPriming->objectName()]=3;
    page[ui->bnRarefaction->objectName()]=4;
    page[ui->bnGrowth_1->objectName()]=8;
    page[ui->bnGrowth_2->objectName()]=9;
    page[ui->bnGrowth_3->objectName()]=10;
    page[ui->bnGrowth_4->objectName()]=11;
    page[ui->bnClasp->objectName()]=12;


    lastKor=src.getValue16("Kor");
    ui->sb_Kor->setValue(lastKor);
    ui->dl_Kor->setValue(lastKor);

    connect(ui->sb_Kor,SIGNAL(valueChanged(int)),this,SLOT(slotSetKor(int)));
    connect(ui->dl_Kor,SIGNAL(valueChanged(int)),this,SLOT(slotSetKor(int)));


    QTimer *t=new QTimer(this);
    t->setInterval(1000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(updateData()));

    state
            << tr("Невизначено")
            << tr("Очікування")
            << tr("Очікування")
            << tr("Набір")
            << tr("Згущення")
            << tr("Затравка")
            << tr("Згущення 1")
            << tr("Поличка ")
            << tr("Розкачка 1")
            << tr("Згущення 2")
            << tr("Розкачка 2")
            << tr("Згущення 3")
            << tr("Розкачка 3")
            << tr("Згущення 4")
            << tr("Ріст 1")
            << tr("Ріст 2")
            << tr("Ріст 3")
            << tr("Ріст 4")
            << tr("Уварювання")
            << tr("Вивантаження");

}

DlgApOne::~DlgApOne()
{
    delete ui;
}

void DlgApOne::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void DlgApOne::slotCallSetup()
{
        DlgApSetup p(src,this);
        p.setWindowTitle(QString(tr("Параметри апарату №%1")).arg(windowTitle().right(1)));
        p.exec();
}

void DlgApOne::slotCommand()
{

    if(sender()->objectName()=="bnStop")
    {
        if(QMessageBox::warning(this,tr("Попередження"),tr("Зупинити ?"),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes)
        {
            src.sendValue("Status",cmd[sender()->objectName()]);
            src.sendValue("Page",page[sender()->objectName()]);
        }

    }
    else
    {
        src.sendValue("Status",cmd[sender()->objectName()]);
        src.sendValue("Page",page[sender()->objectName()]);

    }

}
void DlgApOne::slotSetKor(int v)
{
    if(sender()->objectName()=="sb_Kor")
    {
        ui->dl_Kor->blockSignals(true);
        ui->dl_Kor->setValue(v);
        ui->dl_Kor->blockSignals(false);
    }
    else
    {
        ui->sb_Kor->blockSignals(true);
        ui->sb_Kor->setValue(v);
        ui->sb_Kor->blockSignals(false);
    }
    lastKor=v;

    src.sendValue("Kor",qint16(v));
   qDebug() << "kor = " << src.getValue16("Kor");
}


void DlgApOne::updateData()
{
    ui->le_State->setText(state[src.getValue16("Status")]);
    if(lastKor!=src.getValue16("Kor"))
    {
        lastKor=src.getValue16("Kor");
        ui->dl_Kor->blockSignals(true);
        ui->dl_Kor->setValue(lastKor);
        ui->dl_Kor->blockSignals(false);
        ui->sb_Kor->blockSignals(true);
        ui->sb_Kor->setValue(lastKor);
        ui->sb_Kor->blockSignals(false);
    }
    ap->updateData(src);

}

void DlgApOne::slotSendProd(int v)
{
    src.sendValue("prod",qint16(v));
}

