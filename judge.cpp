#include "judge.h"
#include <random>
#include <ctime>
#include <QDebug>
#include <QString>

Judge::Judge(QObject *parent)
    : QObject{parent}
{
    std::srand(std::time(nullptr));
    while (num > 10000 || num < 1000) {
        num = std::rand() % 10000;
    }
    qDebug() << "num is: " << num;
}

void Judge::check(int n)
{
    QString nums = QString::number(num);
    QString ns = QString::number(n);
    int buls = 0;
    int cows = 0;
    for (int var = 0; var < 4; ++var) {
        if (ns[var] == nums[var]) {
            buls++;
        } else if (nums.contains(ns[var])) {
            cows++;
        }
    }
    emit result(buls, cows);
    if (buls == 4) {
        emit win();
    }
}
