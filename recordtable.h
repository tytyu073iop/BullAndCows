#ifndef RECORDTABLE_H
#define RECORDTABLE_H

#include <QTableWidget>
#include <QMultiMap>
#include <QString>
//#include <QtAlgorithms>
#include <algorithm>

class RecordMap : public QMultiMap<size_t, QString> {
    auto containsValue(QString value) {
        return std::find_if(this->begin(), this->end(), [value](auto i){
            return i == value;
        });
    }
public:
    void add(size_t tries, QString name) {
        auto it = containsValue(name);
        if (it != this->end()) {
            if (it.key() > tries) {
                this->erase(it);
            } else {
                return;
            }
        }
        if (this->count() >= 10) {
            auto preEnd = this->end();
            preEnd--;
            if (preEnd.key() > tries) {
                this->erase(preEnd);
            } else {
                return;
            }
        }
        this->insert(tries, name);
    }
    size_t getMin() {
        auto preEnd = this->end();
        preEnd--;
        return this->count() >= 10 ? preEnd.key() : 0;
    }
};

class RecordTable : public QTableWidget
{
    Q_OBJECT
    void reRender();
public:
    RecordMap rm;
    RecordTable(size_t rows, size_t colloms);
    size_t getMin() {
        return rm.getMin();
    }

public slots:
    void add(size_t tries, QString name);

};

#endif // RECORDTABLE_H
