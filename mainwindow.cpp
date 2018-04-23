#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSair, &QAction::triggered, this, &MainWindow::sair);
    connect(ui->actionTorus, &QAction::triggered, this, &MainWindow::tor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_slicestackSubButton_clicked(){
    QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_N,Qt::NoModifier,"N");
    ui->openGLWidget->keyPressEvent(eve1);
}

void MainWindow::on_slicestackAddButton_clicked(){
    QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_M,Qt::NoModifier,"M");
    ui->openGLWidget->keyPressEvent(eve1);
}

void MainWindow::tor(){
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

void MainWindow::sair(){
    exit(0);
}

