#ifndef DLGAPSETUP_H
#define DLGAPSETUP_H

#include <QDialog>

namespace Ui {
    class DlgApSetup;
}

class DlgApSetup : public QDialog {
    Q_OBJECT
public:
    DlgApSetup(QWidget *parent = 0);
    ~DlgApSetup();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DlgApSetup *ui;
};

#endif // DLGAPSETUP_H
