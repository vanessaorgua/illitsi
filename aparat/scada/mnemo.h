#ifndef __MNEMO_H__
#define __MNEMO_H__

#include <QLabel>
#include <QVector>

class TrendChart;
class IoNetClient;
class QCheckBox;
class QLineEdit;
class QStringList;
class ApOne;

namespace Ui {
    class mnemo;
}

class Mnemo: public QLabel
{
    Q_OBJECT
public:
    Mnemo(IoNetClient &src, QWidget *p=NULL);
    ~Mnemo();

public slots:
    void updateDataRaw(); // слот обновляє дані на мнемосхемі
    void updateDataScaled(); // слот обновляє дані на мнемосхемі
    void updateTrend();
    void slotCallDlgApOne();
    void slotCallTermCtrl();

private:
    Ui::mnemo *m_ui;
    IoNetClient &s;

    QVector<ApOne*> ap;
    QVector<TrendChart*> trc;

    QStringList state;
};

#endif
