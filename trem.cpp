#include "trem.h"
#include <QtCore>

#define MINIMUM 0
#define MAXIMUM 100
#define STEP 10

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
    while (true) {
        switch (ID) {
        case 1:     //Trem 1
            if (y == 30 && x < 320)
                x += STEP;
            else if (x == 320 && y < 130)
                y += STEP;
            else if (x > 60 && y == 130)
                x -= STEP;
            else
                y -= STEP;
            emit updateGUI(ID, x , y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x < 580)
                x += STEP;
            else if (x == 580 && y < 130)
                y += STEP;
            else if (x > 320 && y == 130)
                x -= STEP;
            else
                y-=10;
            emit updateGUI(ID, x, y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}

void Trem::setVelocidade(int value)
{
    if (value >= MINIMUM && value <= MAXIMUM) {
        this->velocidade = MAXIMUM - value;
    }
}




