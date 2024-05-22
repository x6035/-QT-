#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>

class Monitor_Timer : public QTimer
{
    Q_OBJECT

public:
    explicit Monitor_Timer(QObject *parent = nullptr,int id =0)
        : QTimer(parent), id() {
        this->id = id;
    }
    int id;
private:

};

#endif // MYTIMER_H
