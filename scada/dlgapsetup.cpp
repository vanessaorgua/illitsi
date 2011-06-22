#include "dlgapsetup.h"
#include "ui_dlgapsetup.h"

#include "iodev.h"

DlgApSetup::DlgApSetup(IoDev &source,QWidget *parent) :
    QDialog(parent),
    src(source),
    ui(new Ui::DlgApSetup)
{
    ui->setupUi(this);
    sb
            << ui->sb_H1
//            << ui->sb_H2
            << ui->sb_Rzv
            << ui->sb_Rz1
            << ui->sb_tpol
            << ui->sb_Rp1
            << ui->sb_Rz2
            << ui->sb_Rp2
            << ui->sb_Rz3
            << ui->sb_Rp3
            << ui->sb_Rr10
            << ui->sb_Mzv
            << ui->sb_Mz1
            << ui->sb_Mp1
            << ui->sb_Mz2
            << ui->sb_Mp2
            << ui->sb_Mz3
            << ui->sb_Mp3
            << ui->sb_Mr10
            << ui->sb_Hr1
            << ui->sb_Rr1
            << ui->sb_Mr1
            << ui->sb_Hr2
            << ui->sb_Rr2
            << ui->sb_Mr2
            << ui->sb_Hr3
            << ui->sb_Rr3
            << ui->sb_Mr3
            << ui->sb_Hr4
            << ui->sb_Rr4
            << ui->sb_Mr4
            << ui->sb_Ru
            << ui->sb_Mu
//            << ui->sb_Lsm_1
//            << ui->sb_Lsm_2
//            << ui->sb_Lsm_3
            << ui->sb_Pmin
            << ui->sb_Rmin
            << ui->sb_Mmin;
    dsb
            << ui->sb_dRr1
            << ui->sb_dMr1
            << ui->sb_dRr2
            << ui->sb_dMr2
            << ui->sb_dRr3
            << ui->sb_dMr3
            << ui->sb_dRr4
            << ui->sb_dMr4
            << ui->sb_dRPol
            << ui->sb_dMPol
            << ui->sb_Kpr
            << ui->sb_Ti
            << ui->sb_Td;

    foreach(QSpinBox* p,sb)
    {
        p->setValue(src.getValue16(p->objectName().right(p->objectName().size()-3)));
        connect(p,SIGNAL(valueChanged(int)),this,SLOT(slotSetValue(int)));
    }
    foreach(QDoubleSpinBox* p,dsb)
    {
        p->setValue(src.getValueFloat(p->objectName().right(p->objectName().size()-3)));
        connect(p,SIGNAL(valueChanged(double)),this,SLOT(slotSetValue(double)));
    }
    connect(ui->bx_mode,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetValue(int)));

    QVector<QRadioButton*> rb;
    rb << ui->rb_rej_0 << ui->rb_rej_1 << ui->rb_rej_2;
    int t=src.getValue16("rej");
    if(t<3 && t >-1)
        rb[t]->setChecked(true);
    foreach(QRadioButton*p , rb)
    {
        connect(p,SIGNAL(clicked()),this,SLOT(slotSetBalue()));
    }


}

DlgApSetup::~DlgApSetup()
{
    delete ui;
}

void DlgApSetup::changeEvent(QEvent *e)
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

 void DlgApSetup::slotSetValue(int v)
 {
    if(sender()->objectName()=="bx_mode")
    {
        src.sendValue("mode",qint16(v?-1:0));
    }
    else
    {
        src.sendValue(sender()->objectName().right(sender()->objectName().size()-3),qint16(v));
    }
    src.sendValue("Save",qint16(-1));
 }

void DlgApSetup::slotSetValue(double v)
{
    src.sendValue(sender()->objectName().right(sender()->objectName().size()-3),v);
    src.sendValue("Save",qint16(-1));
}

void DlgApSetup::slotSetBalue()
{
    src.sendValue("rej",qint16(sender()->objectName().right(1).toInt()));
    src.sendValue("Save",qint16(-1));
}
