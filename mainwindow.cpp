#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    xLabelFormat="rot X: %1";
    yLabelFormat="rot Y: %1";
    zLabelFormat="rot Z: %1";
    y=0;
    connect(ui->openglWidget,SIGNAL(xRotationChanged(int)),this,SLOT(setLabelX(int)));
    connect(ui->openglWidget,SIGNAL(yRotationChanged(int)),this,SLOT(setLabelY(int)));
    connect(ui->openglWidget,SIGNAL(zRotationChanged(int)),this,SLOT(setLabelZ(int)));
    connect(timer,SIGNAL(timeout()),this,SLOT(leerDatos()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLabelX(int x)
{
    QString text=QString(xLabelFormat).arg(x/16);
    ui->posX->setText(text);
}

void MainWindow::setLabelY(int y)
{
    QString text=QString(yLabelFormat).arg(y/16);
    ui->posY->setText(text);
}

void MainWindow::setLabelZ(int z)
{
    QString text=QString(zLabelFormat).arg(z/16);
    ui->posZ->setText(text);
}

void MainWindow::iniciarPuerto()
{
   //TODO: Inicializar puerto serie.
}

void MainWindow::leerDatos()
{
    //TODO: solicitar coordenadas al sensor MPU6050 a través del puerto serie.
    qDebug()<<"leyendo";
    y+=16;
    ui->openglWidget->setYRotation(y);
}
