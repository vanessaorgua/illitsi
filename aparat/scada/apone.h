#ifndef APONE_H
#define APONE_H

#include <QLabel>

namespace Ui {
    class ApOne;
}

class ApOne : public QLabel {
    Q_OBJECT
public:
    ApOne(QWidget *parent = 0);
    ~ApOne();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ApOne *ui;
};

#endif // APONE_H
