#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_slicestackSubButton_clicked();
    void on_slicestackAddButton_clicked();
    void on_removerObjButton_clicked();

    void on_nextObject_clicked();
    void on_prevObject_clicked();

    void on_eixoButton_clicked();

    void carregarEstado();
    void salvarEstado();
    void sair();

    void addTorus();
    void addTeapot();

    void addKratos();
    void addMario();
    void addBoy();
    void addShelf();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

