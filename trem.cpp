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

//Construtor

QMutex Trem::mutex[7];

Trem::Trem(int ID, int x, int y)
{
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = MAXIMUM;
}

void Trem::move()
{
    if (this->y == yStart && this->x < xEnd) {
        this->x += STEP;
    }
    else if (this->x == xEnd && this->y < yEnd) {
        this->y += STEP;
    }
    else if (this->x > xStart && this->y == yEnd) {
        this->x -= STEP;
    }
    else {
        this->y -= STEP;
    }

    emit updateGUI(ID, this->x, this->y);    //Emite um sinal
    msleep(velocidade);
}

//Função a ser executada após executar trem->START
void Trem::run()
{
    findRails();

    for (;;) {
        test(this->ID);
        this->move();
    }
}

void Trem::test(int i)
{
    switch (i) {
        case 1:
            // Se T1 está entrando na região crítica 1
            if (this->x == this->xEnd - TRAIN_WIDTH && this->y == this->yStart) {
                mutex[0].lock();
                // Enquanto T1 não sair da região crítica 1
                while (!(this->x == this->xEnd && this->y == this->yEnd)) {
                    this->move();
                }
                mutex[0].unlock();
            }

            break;

        case 2:
            // Se T2 está entrando na região crítica 1
            if (this->x == this->xStart + TRAIN_WIDTH && this->y == this->yEnd) {
                mutex[0].lock();
                // Enquanto T2 não sair da região crítica 1
                while (!(this->x == this->xStart && this->y == this->yStart)) {
                    this->move();
                }
                mutex[0].unlock();
            }

            // Se T2 está entrando na região crítica 2
            if (this->x == this->xEnd - TRAIN_WIDTH && this->y == this->yStart) {
                mutex[1].lock();
                // Enquanto T1 não sair da região crítica 1
                while (!(this->x == this->xEnd && this->y == this->yEnd)) {
                    this->move();
                }
                mutex[1].unlock();
            }

            break;

        case 3:
            // Se T3 está entrando na região crítica 2
            if (this->x == this->xStart + TRAIN_WIDTH && this->y == this->yEnd) {
                mutex[1].lock();
                // Enquanto T2 não sair da região crítica 1
                while (!(this->x == this->xStart && this->y == this->yStart)) {
                    this->move();
                }
                mutex[1].unlock();
            }

            break;
        default:
            break;
    }
}

void Trem::setVelocidade(int value)
{
    if (value >= MINIMUM && value <= MAXIMUM) {
        this->velocidade = MAXIMUM - value;
    }
}

//define os Trilhos de cada trem
void Trem::findRails()
{
    int x = X_START;
    int y = Y_START;

    int column = (this->ID - 1) % 3;
    int row = this->ID / 4;

    if (row == 1) {
        x = 180;
    }

    int xStart = x + WIDTH * column;
    int yStart = y + HEIGHT * row;
    int xEnd = xStart + WIDTH;
    int yEnd = yStart + HEIGHT;

    this->xStart = xStart;
    this->yStart = yStart;
    this->xEnd = xEnd;
    this->yEnd = yEnd;
}




