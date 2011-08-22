#ifndef DLGAPSETUP_H
#define DLGAPSETUP_H

#include <QDialog>
#include <QVector>
class QSpinBox;
class QDoubleSpinBox;
class IoDev;

namespace Ui {
    class DlgApSetup;
}

class DlgApSetup : public QDialog {
    Q_OBJECT
public:
    DlgApSetup(IoDev &source,QWidget *parent = 0);
    ~DlgApSetup();

public slots:
    void slotSetValue(int);
    void slotSetValue(double);
    void slotSetBalue();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DlgApSetup *ui;
    QVector<QSpinBox*> sb;
    QVector<QDoubleSpinBox*> dsb;
    IoDev &src;
};

#endif // DLGAPSETUP_H
