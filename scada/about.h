#ifndef _ABOUT_H_
#define _ABOUT_H_

#include "ui_about.h"
#include <QMessageBox>

class aboutDlg: public QDialog,public Ui::About
{
Q_OBJECT
    public:
    aboutDlg(QWidget *parent) : QDialog(parent)
    {
	setupUi(this);
	connect(abQt,SIGNAL(clicked()),this,SLOT(slotQt()));
        label_4->setText(QString("%1 x %2").arg(parent->size().width()).arg(parent->size().height()));

    }
    private slots:
    void slotQt()
    {
	QMessageBox::aboutQt(this);
    }
};

#endif



