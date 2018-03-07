#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionSair, &QAction::triggered, this, &MainWindow::sair);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    //QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Q,Qt::NoModifier,"Q");
    //ui->openGLWidget->keyPressEvent(eve1);
    ui->openGLWidget->buttonPressEvent();
}

void MainWindow::sair(){
    exit(0);
}

