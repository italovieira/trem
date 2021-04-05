#include "trem.h"
#include <QtCore>

#define MINIMUM 0
#define MAXIMUM 100
#define STEP 10
#define X_START 60
#define Y_START 30
#define WIDTH 260
#define HEIGHT 100
#define TRAIN_WIDTH 20

QMutex Trem::mutex[7];
QSemaphore Trem::sem1(2);
QSemaphore Trem::sem2(2);
QSemaphore Trem::sem3(2);
QSemaphore Trem::sem4(2);
QSemaphore Trem::sem5(2);

//Construtor
Trem::Trem(int ID, int x, int y)
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = MAXIMUM;
}

void Trem::move()
{
    if (y == yStart && x < xEnd) {
        x += STEP;
    }
    else if (x == xEnd && y < yEnd) {
        y += STEP;
    }
    else if (x > xStart && y == yEnd) {
        x -= STEP;
    }
    else {
        y -= STEP;
    }

    emit updateGUI(ID, x, y);    //Emite um sinal
    msleep(velocidade);
}

//Função a ser executada após executar trem->START
void Trem::run()
{
    findRails();

    for (;;) {
        test();
        move();
    }
}

void Trem::test()
{
    switch (ID) {
        case 1:
            // Se T1 está entrando na região crítica 1
            if (x == xEnd - TRAIN_WIDTH && y == yStart) {
                sem4.acquire();
                sem1.acquire();
                mutex[0].lock();
            }

            // Quandoo T1 sair da região crítica 1
            if (x == xEnd && y == yEnd) {
                sem1.release();
                sem4.release();
                mutex[0].unlock();
            }

            // Se T1 está entrando na região crítica 3
            if (x == xEnd && y == yEnd - TRAIN_WIDTH) {
                mutex[2].lock();
            }

            // Quando T1 sair da região crítica 3
            if (x == xMiddle - TRAIN_WIDTH && y == yEnd) {

                mutex[2].unlock();
            }

            break;

        case 2:
            // Se T2 está entrando na região crítica 1
            if (x == xStart + TRAIN_WIDTH && y == yEnd) {
                mutex[0].lock();
            }
            // Quando T2 sair da região crítica 1
            if (x == xStart && y == yStart) {


                mutex[0].unlock();
            }

            // Se T2 está entrando na região crítica 2
            if (x == xEnd - TRAIN_WIDTH && y == yStart) {
                sem5.acquire();
                sem4.acquire();
                sem3.acquire();
                mutex[1].lock();
            }

            // Quando T2 sair da região crítica 2
            if (x == xEnd && y == yEnd) {
                sem3.release();
                mutex[1].unlock();
            }

            // Se T2 está entrando na região crítica 5
            if (x == xEnd && y == yEnd - TRAIN_WIDTH) {
                sem2.acquire();
                mutex[4].lock();
            }

            // Quando T2 sair da região crítica 5
            if (x == xMiddle - TRAIN_WIDTH && y == yEnd) {
                sem2.release();
                mutex[4].unlock();
            }

            // Se T2 está entrando na região crítica 4
            if (x == xMiddle + TRAIN_WIDTH && y == yEnd) {
                sem1.acquire();
                mutex[3].lock();
            }

            // Quando T2 sair da região crítica 4
            if (x == xStart && y == yEnd - TRAIN_WIDTH) {
                sem1.release();
                sem4.release();
                sem5.release();
                mutex[3].unlock();
            }

            break;

        case 3:
            // Se T3 está entrando na região crítica 2
            if (x == xStart + TRAIN_WIDTH && y == yEnd) {
                mutex[1].lock();
            }

            // Quando T3 sair da região crítica 2
            if (x == xStart && y == yStart) {

                mutex[1].unlock();
            }

            // Se T3 está entrando na região crítica 6
            if (x == xMiddle + TRAIN_WIDTH && y == yEnd) {
                sem5.acquire();
                sem3.acquire();
                mutex[5].lock();
            }

            // Quando T3 sair da região crítica 6
            if (x == xStart && y == yEnd - TRAIN_WIDTH) {
                sem3.release();
                sem5.release();
                mutex[5].unlock();
            }

            break;

        case 4:
            // Se T4 está entrando na região crítica 7
            if (x == xEnd - TRAIN_WIDTH && y == yStart) {
                mutex[6].lock();
            }

            // Quando T4 sair da região crítica 7
            if (x == xEnd && y == yEnd) {


                mutex[6].unlock();
            }

            // Se T4 está entrando na região crítica 3
            if (x == xStart && y == yStart + TRAIN_WIDTH) {
                sem5.acquire();
                sem4.acquire();
                sem1.acquire();
                mutex[2].lock();
            }

            // Quando T4 sair da região crítica 3
            if (x == xMiddle + TRAIN_WIDTH && y == yStart) {
                sem1.release();
                mutex[2].unlock();
            }

            // Se T4 está entrando na região crítica 4
            if (x == xMiddle - TRAIN_WIDTH && y == yStart) {
                sem2.acquire();
                mutex[3].lock();
            }

            // Quando T4 sair da região crítica 4
            if (x == xEnd && y == yStart + TRAIN_WIDTH) {
                sem2.release();
                sem4.release();
                sem5.release();
                mutex[3].unlock();
            }

            break;

        case 5:
            // Se T5 está entrando na região crítica 7
            if (x == xStart + TRAIN_WIDTH && y == yEnd) {
                sem5.acquire();
                sem4.acquire();
                mutex[6].lock();
            }

            // Quando T5 sair da região crítica 7
            if (x == xStart && y == yStart) {
                mutex[6].unlock();
            }

            // Se T5 está entrando na região crítica 5
            if (x == xStart && y == yStart + TRAIN_WIDTH) {
                sem2.acquire();
                sem3.acquire();
                mutex[4].lock();
            }

            // Quando T5 sair da região crítica 5
            if (x == xMiddle + TRAIN_WIDTH && y == yStart) {
                sem2.release();
                sem3.release();
                sem4.release();
                sem5.release();
                mutex[4].unlock();
            }

            // Se T5 está entrando na região crítica 6
            if (x == xMiddle - TRAIN_WIDTH && y == yStart) {
                mutex[5].lock();
            }

            // Quando T5 sair da região crítica 6
            if (x == xEnd && y == yStart + TRAIN_WIDTH) {

                mutex[5].unlock();
            }

            break;

        default:
            break;
    }
}

void Trem::setVelocidade(int value)
{
    if (value >= MINIMUM && value <= MAXIMUM) {
        velocidade = MAXIMUM - value;
    }
}

//define os Trilhos de cada trem
void Trem::findRails()
{
    int x = X_START;
    int y = Y_START;

    int column = (ID - 1) % 3;
    int row = ID / 4;

    if (row == 1) {
        x = 190;
    }

    xStart = x + WIDTH * column;
    yStart = y + HEIGHT * row;
    xEnd = xStart + WIDTH;
    yEnd = yStart + HEIGHT;
    xMiddle = xStart + WIDTH / 2;
}
