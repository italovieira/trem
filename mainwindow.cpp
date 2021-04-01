#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1, 60, 30);
    trem2 = new Trem(2, 320, 30);
    trem3 = new Trem(3, 580, 30);
    trem4 = new Trem(4, 180, 130);
    trem5 = new Trem(5, 440, 130);

    trem1->trens[0] = trem1;
    trem1->trens[1] = trem2;
    trem1->trens[2] = trem3;
    trem1->trens[3] = trem4;
    trem1->trens[4] = trem5;


    trem2->trens[0] = trem1;
    trem2->trens[1] = trem2;
    trem2->trens[2] = trem3;
    trem2->trens[3] = trem4;
    trem2->trens[4] = trem5;


    trem3->trens[0] = trem1;
    trem3->trens[1] = trem2;
    trem3->trens[2] = trem3;
    trem3->trens[3] = trem4;
    trem3->trens[4] = trem5;


    trem4->trens[0] = trem1;
    trem4->trens[1] = trem2;
    trem4->trens[2] = trem3;
    trem4->trens[3] = trem4;
    trem4->trens[4] = trem5;


    trem5->trens[0] = trem1;
    trem5->trens[1] = trem2;
    trem5->trens[2] = trem3;
    trem5->trens[3] = trem4;
    trem5->trens[4] = trem5;


    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    connect(trem2, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    connect(trem3, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    connect(trem4, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));
    connect(trem5, SIGNAL(updateGUI(int, int, int)), SLOT(updateInterface(int, int, int)));



}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y)
{
    switch (id) {
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x, y, 20, 20);
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x, y, 20, 20);
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->label_trem3->setGeometry(x, y, 20, 20);
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x, y, 20, 20);
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x, y, 20, 20);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Ao clicar, trens começam execução
 */
void MainWindow::on_pushButton_clicked()
{
    trem1->start();
    trem2->start();
    //trem3->start();
    trem4->start();
    //trem5->start();
}

/*
 * Ao clicar, trens param execução
 */
void MainWindow::on_pushButton_2_clicked()
{
    trem1->terminate();
    trem2->terminate();
    //trem3->terminate();
    trem4->terminate();
    //trem5->terminate();
}

void MainWindow::on_sliderT1_valueChanged(int value)
{
    trem1->setVelocidade(value);
}

void MainWindow::on_sliderT2_valueChanged(int value)
{
    trem2->setVelocidade(value);
}

void MainWindow::on_sliderT3_valueChanged(int value)
{
    trem3->setVelocidade(value);
}

void MainWindow::on_sliderT4_valueChanged(int value)
{
    trem4->setVelocidade(value);
}

void MainWindow::on_sliderT5_valueChanged(int value)
{
    trem5->setVelocidade(value);
}
