#include "apone.h"
#include "ui_apone.h"

#include <QtGui>
#include "iodev.h"


ApOne::ApOne(/*IoDev &source,*/ QWidget *parent) :
    QLabel(parent),
    //src(source),
    ui(new Ui::ApOne)
{
    ui->setupUi(this);

    cb
            << ui->cb_sirup
            << ui->cb_sirup_r
            << ui->cb_bila
            << ui->cb_bila_r
            << ui->cb_voda
            << ui->cb_voda_r
            << ui->cb_para
            << ui->cb_para_r
            << ui->c1_vakume_r
            << ui->c2_vakume_r ;

    lcd
            << ui->lc_Opr
            << ui->lc_Vias
            << ui->lc_Lev
            << ui->lc_Vak
            << ui->lc_Temp;

//    QTimer *t=new QTimer(this);
//    t->setInterval(1000);
//    t->start();
//    connect(t,SIGNAL(timeout()),this,SLOT(updateData()));

}

ApOne::~ApOne()
{
    delete ui;
}

void ApOne::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ApOne::updateData(IoDev &src)
{
    foreach(QCheckBox* p ,cb)
    {
        p->setChecked(src.getValue16(p->objectName().right(p->objectName().size()-3)));
    }
    foreach(QLCDNumber *p, lcd)
    {
        p->display(src.getValueFloat(p->objectName().right(p->objectName().size()-3)));
    }
    ui->pb_Lev->setValue(src.getValueFloat("Lev"));
}


