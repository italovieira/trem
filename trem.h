#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <QSemaphore>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    static QMutex mutex[];
    static QSemaphore sem1;
    static QSemaphore sem2;
    static QSemaphore sem3;
    static QSemaphore sem4;
    static QSemaphore sem5;

    Trem(int, int, int);          //construtor
    void run();                 //função a ser executada pela thread
    void setVelocidade(int);    //altera a velocidade do trem
    void findRails();
    void test(int i);
    void move();

    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int xMiddle;


//Cria um sinal
signals:
    void updateGUI(int, int, int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem

};

#endif // TREM_H
