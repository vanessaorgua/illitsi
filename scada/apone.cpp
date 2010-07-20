#include "apone.h"
#include "ui_apone.h"

#include <QtGui>

ApOne::ApOne(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::ApOne)
{
    ui->setupUi(this);
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
