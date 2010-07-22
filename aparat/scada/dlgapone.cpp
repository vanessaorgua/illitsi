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
    connect(ui->bnRarefaction,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_1,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_2,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnGrowth_3,SIGNAL(clicked()),this,SLOT(slotCommand()));
    connect(ui->bnClasp,SIGNAL(clicked()),this,SLOT(slotCommand()));

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
            << "Невизначено"
            << "Очікування"
            << "Старт"
            << "Набір"
            << "Згущення"
            << "Затравка"
            << "Згущення"
            << "Поличка"
            << "Розкачака 1"
            << "Згущення"
            << "Розкачка 2"
            << "Згущення"
            << "Розкачка 3"
            << "Згущення"
            << "Ріст 1"
            << "Ріст 2"
            << "Ріст 3"
            << "Ріст 4"
            << "Уварювання"
            << "Вивантаження";

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
        p.exec();
}

void DlgApOne::slotCommand()
{


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
