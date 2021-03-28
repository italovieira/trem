#include "trem.h"
#include <QtCore>

#define MINIMUM 0
#define MAXIMUM 100
#define STEP 10
#define X_START 60
#define Y_START 30
#define WIDTH 260
#define HEIGHT 100

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = MAXIMUM;
}

//Função a ser executada após executar trem->START
void Trem::run()
{
    for (;;) {
        int x = X_START;
        int y = Y_START;

        int column = (ID - 1) % 3;
        int row = ID / 4;

        if (row == 1) {
            x = 180;
        }

        int xStart = x + WIDTH * column;
        int yStart = y + HEIGHT * row;
        int xEnd = xStart + WIDTH;
        int yEnd = yStart + HEIGHT;

        if (this->y == yStart && this->x < xEnd)
            this->x += STEP;
        else if (this->x == xEnd && this->y < yEnd)
            this->y += STEP;
        else if (this->x > xStart && this->y == yEnd)
            this->x -= STEP;
        else
            this->y -= STEP;

        emit updateGUI(ID, this->x, this->y);    //Emite um sinal
        msleep(velocidade);
    }
}

void Trem::setVelocidade(int value)
{
    if (value >= MINIMUM && value <= MAXIMUM) {
        this->velocidade = MAXIMUM - value;
    }
}




