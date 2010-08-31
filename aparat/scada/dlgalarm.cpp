#include "dlgalarm.h"
#include "ui_dlgalarm.h"
#include <QSound>
#include <QProcess>
#include <QTimer>


DlgAlarm::DlgAlarm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAlarm)
{
    ui->setupUi(this);
    QTimer *t = new QTimer(this);
    t->setInterval(3000);
    connect(t,SIGNAL(timeout()),this,SLOT(slotPlay()));
    t->start();
}

DlgAlarm::~DlgAlarm()
{
    delete ui;
}

void DlgAlarm::slotPlay()
{
  //  QProcess *process = new QProcess(this)
                        ;
  //   process->start("mpg123 -q /usr/local/share/aparat/ring.wav.mp3");

}
