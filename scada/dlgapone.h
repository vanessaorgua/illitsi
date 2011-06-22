#ifndef DLGAPONE_H
#define DLGAPONE_H

#include <QDialog>
#include <QHash>

class ApOne;
class IoDev;
class QStringList;
class QString;


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
    void slotSendProd(int v);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DlgApOne *ui;
    ApOne *ap;
    IoDev &src;

    QStringList state;
    qint16 lastKor;
    QHash<QString,qint16> cmd;
    QHash<QString,qint16> page;

};

#endif // DLGAPONE_H
