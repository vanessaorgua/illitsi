#ifndef APONE_H
#define APONE_H

#include <QLabel>
#include <QVector>

class QCheckBox;
class QLCDNumber;
class IoDev;


namespace Ui {
    class ApOne;
}

class ApOne : public QLabel {
    Q_OBJECT
public:
    ApOne(/*IoDev &source,*/ QWidget *parent = 0);
    ~ApOne();

public slots:
    void updateData(IoDev &src);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ApOne *ui;
    QVector<QCheckBox*> cb;
    QVector<QLCDNumber*> lcd;

    //IoDev &src;
};

#endif // APONE_H
