#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <vector>

class Trem: public QThread{
    Q_OBJECT
public:
    Trem(int id, int inicialX, int inicialY);
    void run();

signals:
    void updateGUI(int, int, int);

public slots:
    void setVelocidade(int);

private:
    int id;
    int x;
    int y;
    int velocidade;

    // Limites do retângulo do trem
    int leftX;
    int rightX;
    int topY;
    int bottomY;

    // Controle de direção
    bool isGoingRight;
    bool isGoingUp;

    // Regiões críticas que o trem usa
    std::vector<int> regioesCriticas;

    // Funções auxiliares
    void setupRegioesCriticas();
    void mover();
    int getRegiaoCritica();
    bool precisaTrava(int regiao);
};

#endif // TREM_H
