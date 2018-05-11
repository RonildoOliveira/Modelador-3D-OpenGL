#include <QKeyEvent>
#include <QMessageBox>

#include <fstream>
#include <iostream>
#include <vector>

#include "oglwidget.h"

#include "entities/model.h"
#include "entities/torus.h"
#include "entities/teapot.h"
#include "entities/cube.h"

#include "entities/models/objmodelloader.h"
#include "entities/models/tdsmodelloader.h"


OGLWidget::OGLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(16);
}

void OGLWidget::initializeGL()
{
    carregaCamera();

    //glClearColor(1,1,1,1);
    glClearColor(0,0,0,1);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada

    //glShadeModel(GL_SMOOTH);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);

//    //definindo uma luz
        glEnable(GL_LIGHT0);

        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

        const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void OGLWidget::paintGL()
{
    displayInit();

    //sistema global
    glPushMatrix();
        //desenhando eixos do sistema de coordenadas global
        Desenha::drawEixos( 0.5 );
        //chao
        glColor3d(0.3,0.3,0.3);
        Desenha::drawGrid( 15, 0, 15, 1 );
    glPopMatrix();

    if(listaModelos.size() > 0){
        for (int index = 0; index < listaModelos.size(); ++index) {
            listaModelos.at(index)->desenha();
        }
    }

    displayEnd();
}

void OGLWidget::displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y,cam->c.z, cam->u.x,cam->u.y,cam->u.z);
}

void OGLWidget::displayEnd()
{

}

void OGLWidget::resizeGL(int w, int h)
{
    width = w;
    height = h;
}

void OGLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Right:{
            if(!listaModelos.empty()){
                if(cont == -1){
                    cont++;
                    (listaModelos[cont])->setSelecionado(true);
                }else if(cont >= 0 && (cont < (listaModelos.size() - 1))){
                    (listaModelos[cont])->setSelecionado(false);
                    cont++;
                    (listaModelos[cont])->setSelecionado(true);
                }else{
                    (listaModelos[cont])->setSelecionado(false);
                    cont = -1;
                }
            }
        }
        break;

        case Qt::Key_E:{
            if(!listaModelos.empty()){
                if((listaModelos[cont])->isSelecionado()){
                    (listaModelos[cont])->setEixo(!(listaModelos[cont])->isEixo());
                }
            }
        }
        break;

        case Qt::Key_Escape:
        case Qt::Key_Return:
        case Qt::Key_Q:
            exit(0);
            break;

        case Qt::Key_T:
            trans_obj = !trans_obj;
            break;

        case Qt::Key_Plus:
        case Qt::Key_M:
            if(!listaModelos.empty()){
                if (listaModelos.at(cont)->getSlices() > 3 && listaModelos.at(cont)->getStacks() > 3)
                {
                    listaModelos.at(cont)->addSlices();
                    listaModelos.at(cont)->addStacks();
                }
            }
            break;

        case Qt::Key_Minus:
        case Qt::Key_N:
            if(!listaModelos.empty()){
                if (listaModelos.at(cont)->getSlices() > 3 && listaModelos.at(cont)->getStacks() > 3)
                {
                    listaModelos.at(cont)->decSlices();
                    listaModelos.at(cont)->decStacks();
                }
            }
            break;

        case Qt::Key_R:
            if(!listaModelos.empty()){
                listaModelos.erase (listaModelos.begin()+cont);
            }
            break;
    }
}

void OGLWidget::mousePressEvent(QMouseEvent *event) { lastPos = event->pos(); }

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float fator = 100.0;

    int x = event->x();
    int y = event->y();

    int lx = lastPos.x();
    int ly = lastPos.y();


    if(!listaModelos.empty()){
        if (event->buttons() & Qt::LeftButton) {
            listaModelos.at(cont)->addAX(0.1*(y - ly));
            listaModelos.at(cont)->addAY(0.1*(x - lx));
        } else if (event->buttons() & Qt::RightButton) {
            listaModelos.at(cont)->addTX((x - lx)/fator);
            listaModelos.at(cont)->addTY(-(y - ly)/fator);
        }

        else if (event->buttons() & Qt::MiddleButton) {

                listaModelos.at(cont)->addTZ((y - ly)/fator);

                listaModelos.at(cont)->addAZ(-(x - lx)/fator);

        }
    }

    //TODO AMBIENTE
    fator = 100.0;
    if (event->buttons() & Qt::RightButton && event->buttons() & Qt::MiddleButton) {
            if (!trans_obj) {
                cam->translatex(x,lx);
                cam->translatey(y,ly);
            }

        }

    if (event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton) {
        if (!trans_obj) {
            cam->zoom(y,ly);
        }
    }

    lastPos = event->pos();
}

void OGLWidget::addTorusListaModelos() { this->listaModelos.push_back(new Torus()); }
void OGLWidget::addTeapotListaModelos() { this->listaModelos.push_back(new Teapot()); }
void OGLWidget::addCubeListaModelos() { this->listaModelos.push_back(new Cube()); }

void OGLWidget::addKratosListaModelos() { this->listaModelos.push_back(new ObjModelLoader("../Modelador3D/data/obj/Kratos.obj", "Kratos")); }
void OGLWidget::addBoyListaModelos() { this->listaModelos.push_back(new ObjModelLoader("../Modelador3D/data/obj/Boy.obj", "Boy")); }
void OGLWidget::addMarioListaModelos() { this->listaModelos.push_back(new ObjModelLoader("../Modelador3D/data/obj/Mario.obj", "Mario")); }
void OGLWidget::addShelfListaModelos() { this->listaModelos.push_back(new ObjModelLoader("../Modelador3D/data/obj/Shelf.obj", "Shelf")); }

void OGLWidget::addEsqueletoListaModelos() { this->listaModelos.push_back(new TdsModelLoader("../Modelador3D/data/3ds/Esqueleto.3ds", "Esqueleto")); }
void OGLWidget::addCachorroListaModelos() { this->listaModelos.push_back(new TdsModelLoader("../Modelador3D/data/3ds/Cachorro.3ds", "Cachorro")); }
void OGLWidget::addLoboListaModelos() { this->listaModelos.push_back(new TdsModelLoader("../Modelador3D/data/3ds/Lobo.3ds", "Lobo"));}

void OGLWidget::increaseCont() { this->cont++; }
void OGLWidget::decreaseCont() { this->cont--; }

void OGLWidget::mudancasEixoX(char tipo, float valor)
{
    if(tipo == 'T'){
        listaModelos.at(cont)->setTX(valor);
    }
    if(tipo == 'A'){
        listaModelos.at(cont)->setAX(valor);
    }
    if(tipo == 'S'){
        listaModelos.at(cont)->setSX(valor);
    }
}

void OGLWidget::mudancasEixoY(char tipo, float valor)
{
    if(tipo == 'T'){
        listaModelos.at(cont)->setTY(valor);
    }
    if(tipo == 'A'){
        listaModelos.at(cont)->setAY(valor);
    }
    if(tipo == 'S'){
        listaModelos.at(cont)->setSY(valor);
    }
}

void OGLWidget::mudancasEixoZ(char tipo, float valor)
{
    if(tipo == 'T'){
        listaModelos.at(cont)->setTZ(valor);
    }
    if(tipo == 'A'){
        listaModelos.at(cont)->setAZ(valor);
    }
    if(tipo == 'S'){
        listaModelos.at(cont)->setSZ(valor);
    }
}

void OGLWidget::mudancasAngulo(float x, float y, float z)
{
    listaModelos.at(cont)->setAX(x);
    listaModelos.at(cont)->setAY(y);
    listaModelos.at(cont)->setAZ(z);
}

void OGLWidget::mudancasTranslacao(float x, float y, float z)
{
    listaModelos.at(cont)->setTX(x);
    listaModelos.at(cont)->setTY(y);
    listaModelos.at(cont)->setTZ(z);
}

void OGLWidget::mudancasEscala(float x, float y, float z)
{
    listaModelos.at(cont)->setSX(x);
    listaModelos.at(cont)->setSY(y);
    listaModelos.at(cont)->setSZ(z);
}

void OGLWidget::mudaCamera(int numeroCamera)
{
    switch (numeroCamera) {
    case 1:
        this->cam = new CameraDistante(13.9053,2.46208,7.26844,0.237068,1.11059,-0.439761,-0.0747426,0.996312,-0.0421512);
        break;
    case 2:
        this->cam = new CameraDistante(19.5323, 19.36482, 24.4429, -0.0726667, 3.927333, 0, -0.162686, 1.965604, -0.202832);
        break;
    default:
        break;
    }

}

void OGLWidget::carregarEstado(){
    std::ifstream file("../Modelador3D/state.txt");
    if (!file) {
        cout << "Erro de leitura";
    }

    string nomeModelo;
    float innerRadius = 0.0;
    float outterRadius = 0;
    int slices = 0;
    int stacks = 0;
    float tx, ty, tz = 0;
    float ax, ay, az = 0;
    float sx, sy, sz = 0;

    while(!file.eof()){

        file >> nomeModelo;

        if(nomeModelo == "Torus"){
            file >> tx >> ty >> tz;
            file >> ax >> ay >> az;
            file >> sx >> sy >> sz;

            listaModelos.push_back(new Torus(tx, ty, tz, ax, ay, az, sx, sy, sz));
        }
        else if(nomeModelo == "Teapot"){
            file >> tx >> ty >> tz;
            file >> ax >> ay >> az;
            file >> sx >> sy >> sz;

            listaModelos.push_back(new Teapot(tx,ty,tz, ax,ay,az, sx,sy,sz));
        }

        else if(nomeModelo == "Cube"){
            file >> tx >> ty >> tz;
            file >> ax >> ay >> az;
            file >> sx >> sy >> sz;

            listaModelos.push_back(new Cube(tx,ty,tz, ax,ay,az, sx,sy,sz));
        }

        else if(nomeModelo == "Kratos" || nomeModelo == "Mario" || nomeModelo == "Boy" || nomeModelo == "Shelf"){
            string diretorio = "../Modelador3D/data/obj/";
            string extensao = ".obj";

            file >> tx >> ty >> tz;
            file >> ax >> ay >> az;
            file >> sx >> sy >> sz;

            string param = diretorio+nomeModelo+extensao;

            listaModelos.push_back(new ObjModelLoader(param, nomeModelo, tx,ty,tz, ax,ay,az, sx,sy,sz));
        }

        else if(nomeModelo == "Esqueleto" || nomeModelo == "Cachorro" || nomeModelo == "Lobo"){
            string diretorio = "../Modelador3D/data/3ds/";
            string extensao = ".3ds";

            file >> tx >> ty >> tz;
            file >> ax >> ay >> az;
            file >> sx >> sy >> sz;

            string param = diretorio+nomeModelo+extensao;

            listaModelos.push_back(new ObjModelLoader(param, nomeModelo, tx,ty,tz, ax,ay,az, sx,sy,sz));
        }

    }

    listaModelos.pop_back();

}

void OGLWidget::carregarModelo3DOBJ(string caminho, string nome)
{
    listaModelos.push_back(new ObjModelLoader(caminho, nome));
}

void OGLWidget::carregaCamera()
{
    std::ifstream file("../Modelador3D/camera.txt");
    string nomeModelo;

    GLfloat ex;
    GLfloat ey;
    GLfloat ez;
    GLfloat cx;
    GLfloat cy;
    GLfloat cz;
    GLfloat ux;
    GLfloat uy;
    GLfloat uz;

    if (!file) {
        cout << "Erro de leitura";
    }

    while(!file.eof()){

        file >> nomeModelo;
        file >> ex >> ey >> ez;
        file >> cx >> cy >> cz;
        file >> ux >> uy >> uz;

        this->cam = new CameraDistante(ex,ey,ez, cx,cy,cz, ux,uy,uz);
    }
}

void OGLWidget::salvaCamera()
{
    ofstream myfile ("../Modelador3D/camera.txt");

    myfile << "CameraDistante";

    if (myfile.is_open())
    {
        //ecu
        myfile << " " << this->cam->e.x;
        myfile << " " << this->cam->e.y;
        myfile << " " << this->cam->e.z;

        myfile << " " << this->cam->c.x;
        myfile << " " << this->cam->c.y;
        myfile << " " << this->cam->c.z;

        myfile << " " << this->cam->u.x;
        myfile << " " << this->cam->u.y;
        myfile << " " << this->cam->u.z;

        myfile.close();
    }

    else cout << "Erro de leitura";
}

void OGLWidget::salvarEstado()
{
    ofstream myfile ("../Modelador3D/state.txt");
    if (myfile.is_open())
    {
        for (int index = 0; index < listaModelos.size(); ++index) {

            myfile << listaModelos.at(index)->getNome() << " ";

            myfile << listaModelos.at(index)->getTX() << " ";
            myfile << listaModelos.at(index)->getTY() << " ";
            myfile << listaModelos.at(index)->getTZ() << " ";

            myfile << listaModelos.at(index)->getAX() << " ";
            myfile << listaModelos.at(index)->getAY() << " ";
            myfile << listaModelos.at(index)->getAZ() << " ";

            myfile << listaModelos.at(index)->getSX() << " ";
            myfile << listaModelos.at(index)->getSY() << " ";
            myfile << listaModelos.at(index)->getSZ() << " ";

            myfile << "\n";
        }

        myfile.close();
    }
    else cout << "Erro de leitura";
}

bool OGLWidget::islistaVazia()
{
    if(this->listaModelos.empty())
        return true;
    return false;
}

OGLWidget::~OGLWidget() { }
