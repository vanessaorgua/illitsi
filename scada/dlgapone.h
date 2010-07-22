#ifndef DLGAPONE_H
#define DLGAPONE_H

#include <QDialog>

class ApOne;
class IoDev;
class QStringList;

namespace Ui {
    class DlgApOne;
}

class DlgApOne : public QDialog {
    Q_OBJECT
public:
    DlgApOne(IoDev &source, QWidget *parent = 0);
    ~DlgApOne();

public slots:
    void updateData();
    void slotCallSetup();
    void slotCommand();
    void slotSetKor(int v);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DlgApOne *ui;
    ApOne *ap;
    IoDev &src;

    QStringList state;
    qint16 lastKor;
};

#endif // DLGAPONE_H
