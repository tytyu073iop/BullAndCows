#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QTableWidget>
#include <QErrorMessage>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::send, judge, &Judge::check);
    connect(judge, &Judge::result, this, &MainWindow::gotResults);
    connect(judge, &Judge::win, this, &MainWindow::win);
    QLabel* num = new QLabel("№");
    this->records->setCellWidget(0,0, num);
    QLabel* tries = new QLabel("Tries");
    this->records->setCellWidget(0, 1, tries);
    QLabel* name = new QLabel("Name");
    this->records->setCellWidget(0, 2, name);


    QWidget* widget = new QWidget();
    QGridLayout* mainGrid = new QGridLayout(widget);
    QPushButton* newGame = new QPushButton("New Game");
    connect(newGame, &QPushButton::clicked, this, &MainWindow::clear);
    QIntValidator* validator = new QIntValidator(1000, 9999);
    textField->setValidator(validator);
    QPushButton* records = new QPushButton("Records");
    connect(records, &QPushButton::clicked, this, &MainWindow::showRecords);
    connect(checkButton, &QPushButton::clicked, this, &MainWindow::check);
    QLabel* number = new QLabel("number");
    QLabel* result = new QLabel("result");
    table->setCellWidget(0, 0, num);
    table->setCellWidget(0, 1, number);
    table->setCellWidget(0, 2, result);
    mainGrid->addWidget(newGame, 0, 0);
    mainGrid->addWidget(records, 0, 1);
    mainGrid->addWidget(checkButton, 1, 1);
    mainGrid->addWidget(textField, 1, 0);
    mainGrid->addWidget(table, 2, 0, 1, 2);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showRecords()
{
    qDebug() << records->rm.count();
    records->show();
}

void MainWindow::check()
{
    if (!textField->hasAcceptableInput()) {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage("wrong number");
        return;
    }

    auto gotNum = textField->text().toInt();
    emit send(gotNum);


}

void MainWindow::clear()
{
    delete judge;
    judge = new Judge();
    connect(this, &MainWindow::send, judge, &Judge::check);
    connect(judge, &Judge::result, this, &MainWindow::gotResults);
    connect(judge, &Judge::win, this, &MainWindow::win);
    table->setRowCount(1);
    checkButton->setDisabled(false);
}

void MainWindow::gotResults(int bulls, int cows)
{
    auto rowNum = table->rowCount();
    auto gotNum = textField->text().toInt();
    table->insertRow(table->rowCount());
    table->setCellWidget(rowNum, 0, new QLabel(QString::number(rowNum)));
    table->setCellWidget(rowNum, 1, new QLabel(QString::number(gotNum)));
    table->setCellWidget(rowNum, 2, new QLabel(QString("Bulls: %1, Cows: %2").arg(bulls).arg(cows)));
}

void MainWindow::win()
{
    auto rowNum = table->rowCount();
    rowNum--;
    if (rowNum < minRec || minRec == 0) {
        bool ok;
        QString name = QInputDialog::getText(this, "New record!", "Name:", QLineEdit::Normal, "", &ok);
        if (ok && !name.isEmpty()) {
            records->add(rowNum, name);
            minRec = records->getMin();
        }
    }
    checkButton->setDisabled(true);
}
