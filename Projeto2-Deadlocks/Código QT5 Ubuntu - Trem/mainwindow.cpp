#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Criar os 6 trens com posições iniciais
    trem1 = new Trem(1, 60, 100);    // Verde (Top-Left)
    trem2 = new Trem(2, 480, 30);   // Vermelho (Top-Middle)
    trem3 = new Trem(3, 870, 90);   // Azul (Top-Right)
    trem4 = new Trem(4, 60, 220);   // Laranja (Bottom-Left)
    trem5 = new Trem(5, 870, 210);  // Roxo (Bottom-Middle/Right)
    trem6 = new Trem(6, 330, 270);  // Preto (Outer Loop)

    // Conectar sinais de atualização da GUI
    connect(trem1, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem2, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem3, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem4, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem5, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));
    connect(trem6, SIGNAL(updateGUI(int,int,int)), SLOT(updateInterface(int,int,int)));

    // Conectar sliders aos trens
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), trem1, SLOT(setVelocidade(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), trem2, SLOT(setVelocidade(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), trem3, SLOT(setVelocidade(int)));
    connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), trem4, SLOT(setVelocidade(int)));
    connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), trem5, SLOT(setVelocidade(int)));
    connect(ui->horizontalSlider_6, SIGNAL(valueChanged(int)), trem6, SLOT(setVelocidade(int)));

    // Iniciar todos os trens automaticamente
    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();
    trem6->start();
}

// Atualiza a posição visual dos trens na interface
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1:
        ui->label_trem1->setGeometry(x, y, 21, 17);
        break;
    case 2:
        ui->label_trem2->setGeometry(x, y, 21, 17);
        break;
    case 3:
        ui->label_trem3->setGeometry(x, y, 21, 17);
        break;
    case 4:
        ui->label_trem4->setGeometry(x, y, 21, 17);
        break;
    case 5:
        ui->label_trem5->setGeometry(x, y, 21, 17);
        break;
    case 6:
        ui->label_trem6->setGeometry(x, y, 21, 17);
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    // Parar as threads ao fechar
    trem1->terminate();
    trem2->terminate();
    trem3->terminate();
    trem4->terminate();
    trem5->terminate();
    trem6->terminate();

    delete ui;
}
