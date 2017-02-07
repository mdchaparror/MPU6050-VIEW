#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xLabelFormat="rot X: %1";
    yLabelFormat="rot Y: %1";
    zLabelFormat="rot Z: %1";
    connect(ui->widget,SIGNAL(xRotationChanged(int)),this,SLOT(setLabelX(int)));
    connect(ui->widget,SIGNAL(yRotationChanged(int)),this,SLOT(setLabelY(int)));
     connect(ui->widget,SIGNAL(zRotationChanged(int)),this,SLOT(setLabelZ(int)));
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
