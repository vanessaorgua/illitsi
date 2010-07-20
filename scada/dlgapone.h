#ifndef DLGAPONE_H
#define DLGAPONE_H

#include <QDialog>

class ApOne;

namespace Ui {
    class DlgApOne;
}

class DlgApOne : public QDialog {
    Q_OBJECT
public:
    DlgApOne(QWidget *parent = 0);
    ~DlgApOne();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DlgApOne *ui;
    ApOne *ap;

};

#endif // DLGAPONE_H
