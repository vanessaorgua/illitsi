#include "dlgtermctrl.h"
#include "ui_dlgtermctrl.h"

#include "iodev.h"
#include <QtGui>


DlgTermCtrl::DlgTermCtrl(IoDev &source,int Nom, QWidget *parent) :
    QDialog(parent),
    src(source),
    n(Nom),
    ui(new Ui::DlgTermCtrl)
{
    ui->setupUi(this);

    ui->sb_L_->setValue(src.getValueFloat(QString("sp_L_%1").arg(n)));
    ui->sb_T_->setValue(src.getValueFloat(QString("sp_T_%1").arg(n)));
    ui->cb_AM->setCurrentIndex(src.getValue16(QString("AM_%1").arg(n))?1:0);
    if(ui->cb_AM->currentIndex())
    {
        ui->c2_h_->blockSignals(true);
    }
    ui->c2_h_->setChecked(src.getValue16(QString("h_%1").arg(1)));

    connect(ui->sb_L_,SIGNAL(valueChanged(int)),this,SLOT(slotSetVal(int)));
    connect(ui->sb_T_,SIGNAL(valueChanged(int)),this,SLOT(slotSetVal(int)));
    connect(ui->cb_AM,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetAm(int)));
    //connect(ui->c2_h_,SIGNAL(stateChanged(int)),this,SLOT(slotSetV(int)));

    QTimer *t = new QTimer(this);
    t->setInterval(1000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(updateData()));
}

DlgTermCtrl::~DlgTermCtrl()
{
    delete ui;
}

void DlgTermCtrl::changeEvent(QEvent *e)
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

void DlgTermCtrl::updateData()
{
    ui->lc_L->display((int)src.getValueFloat(QString("L_%1").arg(n)));
    ui->pb_L_->setValue(src.getValueFloat(QString("L_%1").arg(n)));

    ui->lc_T->display((int)src.getValueFloat(QString("T_%1").arg(n)));
    ui->c1_h_->setChecked(src.getValue16(QString("h_%1").arg(n)));
    ui->c2_h_->setChecked(src.getValue16(QString("h_%1").arg(1)));

}


void DlgTermCtrl::slotSetVal(int v)
{
    src.sendValue(QString("sp_%1%2")
                  .arg(sender()->objectName().right(sender()->objectName().size()-3))
                  .arg(n),(double)v);
    src.sendValue("Save",qint16(-1));
}

void DlgTermCtrl::slotSetAm(int v)
{
    src.sendValue(QString("AM_%1").arg(n),qint16(v?-1:0));

}

void DlgTermCtrl::slotSetV(int v)
{
    src.sendValue(QString("h_%1").arg(n),qint16(v?-1:0));
}


