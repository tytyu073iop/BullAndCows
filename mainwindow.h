#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <tuple>
#include "judge.h"
#include "recordtable.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    size_t minRec = 0;
    QTableWidget* table = new QTableWidget(1, 3);
    QLineEdit* textField = new QLineEdit();
    Judge* judge = new Judge();
    RecordTable* records = new RecordTable(1, 3);
    QPushButton* checkButton = new QPushButton("Check");

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showRecords();
    void check();
    void clear();

    void gotResults(int bulls, int cows);
    void win();

signals:
    void send(int num);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
