#include "trem.h"
#include <QtCore>
#include <QMutex>
#include <QDebug>

// Array global de 7 mutexes, um para cada região crítica
QMutex mutexes[7];

// Construtor
Trem::Trem(int id, int x, int y){
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

// Slot para controlar velocidade via slider
void Trem::setVelocidade(int valorSlider){
    this->velocidade = 205 - valorSlider;
}

// Função executada pela thread
void Trem::run(){
    while(true){
        switch(id){
        case 1:
            if(x==60 && y>30){ //Sobe o primeiro trilho
                if(y==150){
                    mutexes[2].unlock();
                }
                y-=10;
            }
            else if(y==30 && x<330){ // O trem está no trilho superior
                if (x == 310) { // Entra na RC0
                    mutexes[0].lock(); // Pega a chave para RC0
                }
                x+=10;
            }
            else if(x==330 && y<150){ // Na RC0
                if (y == 130) { // 1. Solta a RC0
                    mutexes[2].lock(); // 2. Pega a RC3
                }
                y+=10;
            }
            else if(y==150 && x>60){ // Trilho inferior
                if(x==310){
                    mutexes[0].unlock();
                }
                x-=10;
            }
            break;

        case 2:
            if (x<600 && y==30){
                if(x==460){
                    mutexes[0].unlock();
                }
                if (x==580){
                    mutexes[1].lock();
                }
                x+=10;
            } else if (x==600 && y<150){
                if (y==130){
                    mutexes[4].lock();
                    mutexes[3].lock();
                }
                y+=10;
            } else if (x>330 && y==150){
                if (x==580){
                    mutexes[1].unlock();
                }
                if(x==460){
                    mutexes[4].unlock();
                    mutexes[0].lock();
                }
                x-=10;
            } else if (x==330 && y>30){
                if(y==130){
                    mutexes[3].unlock();
                }
                y-=10;
            }
            break;

        case 3:
            if (x==870 && y<150){
                y+=10;
                if (y==130){
                    mutexes[5].lock();
                }
            } else if(y==150 && x>600){
                if(x==630){
                    mutexes[1].lock();
                }
                x-=10;
            } else if(x==600 && y>30){
                if(y==140){
                    mutexes[5].unlock();
                }
                y-=10;
            } else if(y==30 && x<870){
                if(x==610){
                    mutexes[1].unlock();
                }
                x+=10;
            }
            break;

        case 4:
            if(x==60 && y>150){
                if(y==170){
                    mutexes[2].lock();
                    mutexes[6].lock();
                    mutexes[3].lock();
                }
                y-=10;
            }
            else if(y==150 && x<480){
                if(x==350){
                    mutexes[2].unlock();
                }
                x+=10;
            }
            else if(x==480 && y<270){
                if(x==480 && y==170){
                    mutexes[3].unlock();  
                }
                y+=10;
            }
            else if(y==270 && x>60){
                if(x==460){
                    mutexes[6].unlock();
                }
                x-=10;
            }
            break;

        case 5:
            if(x==870 && y<270){
                if(y==170){
                    mutexes[5].unlock();
                }
                y+=10; //Descendo o primeiro trilho
            } else if(y==270 && x>480){
                x-=10; // Indo para a esquerda
                if(x==500){
                    mutexes[6].lock();
                }
            } else if(x==480 && y>150){
                if(y==170){
                    mutexes[4].lock();
                }
                y-=10; //Subindo a RC06
            } else if(x<870 && y==150){
                x+=10;
                if(x==500){
                    mutexes[6].unlock();
                }
                if(x==580){
                    mutexes[5].lock();
                }
                if(x==620){
                    mutexes[4].unlock();
                }
            }
            break;

        case 6:
            if (x<870 && y==270){
                x+=10;
            } else if (x==870 && y>30){
                y-=10;
            } else if (x>60 && y==30){
                x-=10;
            } else if (x==60 && y<270){
                y+=10;
            }
            break;

        default:
            break;
        }

        emit updateGUI(id, x, y);
        msleep(velocidade);
    }
}
