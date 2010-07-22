#include "dlgapone.h"
#include "ui_dlgapone.h"
#include "apone.h"
#include "iodev.h"

DlgApOne::DlgApOne(IoDev &source,QWidget *parent) :
    QDialog(parent),
    src(source),
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

