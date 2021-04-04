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
    sem_init(&sem, 0, 1);
}

//Função a ser executada após executar trem->START
void Trem::run()
{
    findRails();

    for (;;) {

        /*
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
        */


        test(this->ID);

        if (this->y == yStart && this->x < xEnd){
            this->x += STEP;
        }
        else if (this->x == xEnd && this->y < yEnd){
            this->y += STEP;
        }
        else if (this->x > xStart && this->y == yEnd){  
            this->x -= STEP;
        }
        else{
            this->y -= STEP;
        }

        emit updateGUI(ID, this->x, this->y);    //Emite um sinal
        msleep(velocidade);
    }
}

void Trem::test(int i){

    int mid = (this->xEnd - this->xStart)/2;

    switch (i) {
        case 1:

            //colisao Trem1 com Trem2
            if(this->x <= this->xEnd - (STEP*2) && this->x >= this->xEnd - (STEP*4) && this->y == this->yStart){
                if(trens[1]->x >= trens[1]->xStart && trens[1]->x <= trens[1]->xStart + (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[1]->x == trens[1]->xStart);
                    sem_post(&this->sem);
                }
            }
            //colisao Trem1 com Trem4
            else if(this->y <= this->yEnd - (STEP*2) && this->y >= this->yEnd - (STEP*4) && this->x == this->xEnd){
                if(trens[3]->y <= trens[3]->yStart && trens[3]->y >= trens[3]->yStart - (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[3]->x < trens[3]->xStart + mid + (STEP*3));
                    sem_post(&this->sem);
                }
            }


            break;
        case 2:

            //colisao Trem2 com Trem1
            if(this->x >= this->xStart + (STEP*2) && this->x <= this->xStart + (STEP*4) && this->y == this->yEnd){
                if(trens[0]->x <= trens[0]->xEnd && trens[0]->x > trens[0]->xEnd - (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[0]->x == trens[0]->xEnd);
                    sem_post(&this->sem);
                }
            }
            //colisao Trem2 com Trem3
            else if(this->x <= this->xEnd - (STEP*2) && this->x >= this->xEnd - (STEP*4) && this->y == this->yStart){
                if(trens[2]->x >= trens[2]->xStart && trens[2]->x <= trens[2]->xStart + (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[2]->x == trens[2]->xStart);
                    sem_post(&this->sem);
                }
            }
            //colisao Trem2 com Trem4
            else if(this->x >= this->xStart + mid  && this->x <= this->xStart + mid + (STEP*2) && this->y == this->yEnd){
                if(trens[3]->x >= trens[3]->xStart + mid - (2*STEP) && trens[3]->x <= trens[3]->xEnd){
                    sem_wait(&this->sem);
                    while(trens[3]->y == trens[3]->yStart);
                    sem_post(&this->sem);
                }
            }

            break;
        case 3:

            //colisao Trem3 com Trem2
            if(this->x >= this->xStart + (STEP*2) && this->x <= this->xStart + (STEP*4) && this->y == this->yEnd){
                if(trens[1]->x <= trens[1]->xEnd && trens[1]->x > trens[1]->xEnd - (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[1]->x == trens[1]->xEnd);
                    sem_post(&this->sem);
                }
            }
            //colisao Trem3 com Trem5
            else if(this->x >= this->xStart + mid  && this->x <= this->xStart + mid + (STEP*2) && this->y == this->yEnd){
                if(trens[4]->x >= trens[4]->xStart + mid - (2*STEP) && trens[4]->x <= trens[4]->xEnd){
                    sem_wait(&this->sem);
                    while(trens[4]->y == trens[4]->yStart);
                    sem_post(&this->sem);
                }
            }

            break;
        case 4:

            //colisao Trem4 com Trem1
            if(this->y >= this->yStart + (STEP*2) && this->y <= this->yStart + (STEP*4) && this->x == this->xStart){
                if(trens[0]->y <= trens[0]->yEnd && trens[0]->y >= trens[0]->yEnd - (STEP*2)){ //trem4 trilho da esquerda e de cima
                    sem_wait(&this->sem);
                    while(trens[0]->x > trens[0]->xStart + mid - (STEP*3));
                    sem_post(&this->sem);
                }
            }
            //colisao Trem4 com Trem2
            else if(this->x >= this->xStart + mid - (STEP*3) && this->x <= this->xStart + mid && this->y == this->yStart){ // trem2 trilho de baixo
                if(trens[1]->x >= trens[1]->xStart + (2 * STEP) && trens[1]->x <= trens[1]->xStart + mid + (2 * STEP)){
                    sem_wait(&this->sem);
                    while(trens[1]->y == trens[1]->yEnd);
                    sem_post(&this->sem);
                }
            }
            //colisao Trem4 com Trem5
            else if(this->x <= this->xEnd - (STEP*2) && this->x >= this->xEnd - (STEP*4) && this->y == this->yStart){
                if(trens[4]->x >= trens[4]->xStart && trens[4]->x <= trens[4]->xStart + (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[4]->x == trens[4]->xStart);
                    sem_post(&this->sem);
                }
            }
            break;
        case 5:

            //colisao Trem5 com Trem2
            if(this->y >= this->yStart + (STEP*2) && this->y <= this->yStart + (STEP*4) && this->x == this->xStart){
                if(trens[1]->y <= trens[1]->yEnd && trens[1]->y >= trens[1]->yEnd - (STEP*2)){ //trem4 trilho da esquerda e de cima
                    sem_wait(&this->sem);
                    while(trens[1]->x > trens[1]->xStart + mid - (STEP*3));
                    sem_post(&this->sem);
                }
            }
            //colisao Trem5 com Trem3
            else if(this->x >= this->xStart + mid - (STEP*3) && this->x <= this->xStart + mid && this->y == this->yStart){ // trem2 trilho de baixo
                if(trens[2]->x >= trens[2]->xStart + (2 * STEP) && trens[2]->x <= trens[2]->xStart + mid + (2 * STEP)){
                    sem_wait(&this->sem);
                    while(trens[2]->y == trens[2]->yEnd);
                    sem_post(&this->sem);
                }
            }
            //colisao Trem5 com Trem4
            else if(this->x >= this->xStart + (STEP*2) && this->x <= this->xStart + (STEP*4) && this->y == this->yEnd){
                if(trens[3]->x <= trens[3]->xEnd && trens[3]->x > trens[3]->xEnd - (STEP*2)){
                    sem_wait(&this->sem);
                    while(trens[3]->x == trens[3]->xEnd);
                    sem_post(&this->sem);
                }
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
void Trem::findRails(){
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




