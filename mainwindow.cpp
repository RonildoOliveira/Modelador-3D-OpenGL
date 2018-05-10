#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include "entities/models/objmodelloader.h"
using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                          Qt::AlignCenter, this->size(),
                                          qApp->desktop()->availableGeometry()));
    ui->setupUi(this);

    connect(ui->actionCarregar_Estado,&QAction::triggered, this, &MainWindow::carregarEstado);
    connect(ui->actionSalvar_Estado,&QAction::triggered, this, &MainWindow::salvarEstado);
    connect(ui->actionSair, &QAction::triggered, this, &MainWindow::sair);
    connect(ui->actionCarregarOBJ, &QAction::triggered, this, &MainWindow::carregarOBJ);

    connect(ui->actionTorus, &QAction::triggered, this, &MainWindow::addTorus);
    connect(ui->actionTeapot, &QAction::triggered, this, &MainWindow::addTeapot);
    connect(ui->actionCube, &QAction::triggered, this, &MainWindow::addCube);

    connect(ui->actionKratos, &QAction::triggered, this, &MainWindow::addKratos);
    connect(ui->actionMario, &QAction::triggered, this, &MainWindow::addMario);
    connect(ui->actionBoy, &QAction::triggered, this, &MainWindow::addBoy);
    connect(ui->actionShelf, &QAction::triggered, this, &MainWindow::addShelf);

    connect(ui->eixoXSlider, SIGNAL(valueChanged(int)), this, SLOT(xValueReceived(int)));
    connect(ui->eixoYSlider, SIGNAL(valueChanged(int)), this, SLOT(yValueReceived(int)));
    connect(ui->eixoZSlider, SIGNAL(valueChanged(int)), this, SLOT(zValueReceived(int)));
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

void MainWindow::on_nextObject_clicked(){
    QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier,"Key_Right");
    ui->openGLWidget->keyPressEvent(eve1);
}

void MainWindow::on_prevObject_clicked(){
    QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier,"Key_Left");
    ui->openGLWidget->keyPressEvent(eve1);
}

void MainWindow::on_eixoButton_clicked()
{
    QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_E,Qt::NoModifier,"Key_E");
    ui->openGLWidget->keyPressEvent(eve1);
}

void MainWindow::on_aplicarTransformacao_clicked()
{
    ui->campoTransformacao->setInputMask( "00.0000,00.0000,00.0000" );
    QString qTexto = ui->campoTransformacao->text();
    std::string texto = qTexto.toUtf8().constData();
    spliter(texto, ",");
}

void MainWindow::carregarEstado()
{
    ui->openGLWidget->carregarEstado();
}

void MainWindow::salvarEstado()
{
    ui->openGLWidget->salvarEstado();
}

void MainWindow::carregarOBJ()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Carregar Modelo 3D"), "/home/", tr("Modelos OBJ (*.obj)"));
    std::string utf8_text = filename.toUtf8().constData();

    ui->openGLWidget->carregarModelo3DOBJ(utf8_text,"Novo");
    std::cout << utf8_text << "-->";
}


void MainWindow::on_removerObjButton_clicked(){
    QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_R,Qt::NoModifier,"R");
    ui->openGLWidget->keyPressEvent(eve1);
}

void MainWindow::addTorus(){
    ui->openGLWidget->addTorusListaModelos();
    /*
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
    */
}

void MainWindow::addTeapot(){
    ui->openGLWidget->addTeapotListaModelos();
}

void MainWindow::addCube()
{
    ui->openGLWidget->addCubeListaModelos();
}

void MainWindow::addKratos()
{
    ui->openGLWidget->addKratosListaModelos();
}

void MainWindow::addMario()
{
    ui->openGLWidget->addMarioListaModelos();
}

void MainWindow::addBoy()
{
    ui->openGLWidget->addBoyListaModelos();
}

void MainWindow::addShelf()
{
    ui->openGLWidget->addShelfListaModelos();
}

void MainWindow::xValueReceived(int x)
{
    float fator = 10.0;

    if(!ui->openGLWidget->islistaVazia()){
        if(ui->tRadioButton->isChecked())
            ui->openGLWidget->mudancasEixoX('T', (x / (fator*10)));

        if(ui->aRadioButton->isChecked())
            ui->openGLWidget->mudancasEixoX('A', (x));

        if(ui->sRadioButton->isChecked())
            ui->openGLWidget->mudancasEixoX('S', (x / (fator*10)));
    }
}

void MainWindow::yValueReceived(int y)
{
    float fator = 10.0;

    if(ui->tRadioButton->isChecked())
        ui->openGLWidget->mudancasEixoY('T', (y / (fator*10)));

    if(ui->aRadioButton->isChecked())
        ui->openGLWidget->mudancasEixoY('A', (y));

    if(ui->sRadioButton->isChecked())
        ui->openGLWidget->mudancasEixoY('S', (y / (fator*10)));
}

void MainWindow::zValueReceived(int z)
{
    float fator = 10.0;

    if(ui->tRadioButton->isChecked())
        ui->openGLWidget->mudancasEixoZ('T', (z / (fator*10)));

    if(ui->aRadioButton->isChecked())
        ui->openGLWidget->mudancasEixoZ('A', (z));

    if(ui->sRadioButton->isChecked())
        ui->openGLWidget->mudancasEixoZ('S', (z / (fator*10)));
}

void MainWindow::spliter(string linha, string delimitador)
{
    std::vector<float> vetores;

    size_t pos = 0;
    std::string token;
    while ((pos = linha.find(delimitador)) != std::string::npos) {
        token = linha.substr(0, pos);
        std::cout << token << std::endl;
        linha.erase(0, pos + delimitador.length());

        vetores.push_back(::atof(token.c_str()));
    }
    vetores.push_back(::atof(linha.c_str()));
    std::cout << linha << std::endl;

    for (int var = 0; var < vetores.size(); ++var) {
        cout << vetores.at(var) << endl;
    }

    if(ui->aRadioButton->isChecked())
        ui->openGLWidget->mudancasAngulo(vetores.at(0),vetores.at(1),vetores.at(2));

    if(ui->sRadioButton->isChecked())
        ui->openGLWidget->mudancasEscala(vetores.at(0),vetores.at(1),vetores.at(2));

    if(ui->tRadioButton->isChecked())
        ui->openGLWidget->mudancasTranslacao(vetores.at(0),vetores.at(1),vetores.at(2));
}

void MainWindow::on_cam01PushButton_clicked()
{
    ui->openGLWidget->mudaCamera();
}

void MainWindow::sair(){
    exit(0);
}

