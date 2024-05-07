#include "recordtable.h"
#include <QLabel>

void RecordTable::reRender()
{
    this->setRowCount(1);
    size_t count = 1;
    for (auto i = rm.begin(); i != rm.end(); i++, count++) {
        this->insertRow(count);
        this->setCellWidget(count, 0, new QLabel(QString::number(count)));
        this->setCellWidget(count, 1, new QLabel(QString::number(i.key())));
        this->setCellWidget(count, 2, new QLabel(i.value()));
    }
}

RecordTable::RecordTable(size_t rows, size_t colloms) : QTableWidget(rows, colloms) {

}

void RecordTable::add(size_t tries, QString name)
{
    rm.add(tries, name);
    reRender();
}
