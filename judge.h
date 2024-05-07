#ifndef JUDGE_H
#define JUDGE_H

#include <QObject>
#include <tuple>
#include <ctime>

class Judge : public QObject
{
    Q_OBJECT
    int num = 0;
public:
    explicit Judge(QObject *parent = nullptr);

public slots:
    void check(int num);

signals:
    void result(int buls, int cows);
    void win();
};

#endif // JUDGE_H
