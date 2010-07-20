#include "dlgapone.h"
#include "ui_dlgapone.h"
#include "apone.h"

DlgApOne::DlgApOne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgApOne)
{
    ui->setupUi(this);

    ap=new ApOne(ui->apMnemo);

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

