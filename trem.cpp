#include "trem.h"
#include <QtCore>

#define MINIMUM 0
#define MAXIMUM 100
#define STEP 10
#define X_START 60
#define Y_START 30
#define X_END 320
#define Y_END 130
#define WIDTH 260
#define HEIGHT 130


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
        int xStart = 60 + WIDTH * (ID - 1);
        int yStart = 30;
        int xEnd = xStart + WIDTH;
        int yEnd = 130;

        if (ID > 3) {
            xStart = 100;
            yStart = 400;
        }

        if (y == yStart && x < xEnd)
            x += STEP;
        else if (x == xEnd && y < yEnd)
            y += STEP;
        else if (x > xStart && y == yEnd)
            x -= STEP;
        else
            y -= STEP;

        emit updateGUI(ID, x, y);    //Emite um sinal
        msleep(velocidade);
    }
}

void Trem::setVelocidade(int value)
{
    if (value >= MINIMUM && value <= MAXIMUM) {
        this->velocidade = MAXIMUM - value;
    }
}




