#ifndef DLGAPONE_H
#define DLGAPONE_H

#include <QDialog>

class ApOne;
class IoDev;

namespace Ui {
    class DlgApOne;
}

class DlgApOne : public QDialog {
    Q_OBJECT
public:
    DlgApOne(IoDev &source, QWidget *parent = 0);
    ~DlgApOne();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::DlgApOne *ui;
    ApOne *ap;
    IoDev &src;
};

#endif // DLGAPONE_H
