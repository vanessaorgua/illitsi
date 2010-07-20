#include "dlgapsetup.h"
#include "ui_dlgapsetup.h"

DlgApSetup::DlgApSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgApSetup)
{
    ui->setupUi(this);
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
