#ifndef DLGALARM_H
#define DLGALARM_H

#include <QDialog>

namespace Ui {
    class DlgAlarm;
}

class DlgAlarm : public QDialog {
    Q_OBJECT
public:
    DlgAlarm(QWidget *parent = 0);
    ~DlgAlarm();
public slots:
    void slotPlay();

private:
    Ui::DlgAlarm *ui;

};

#endif // DLGALARM_H
