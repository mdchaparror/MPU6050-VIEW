#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    serial = new QSerialPort(this);
    connect(serial,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));

    xLabelFormat="rot X: %1";
    yLabelFormat="rot Y: %1";
    zLabelFormat="rot Z: %1";
    y=0;
    connect(ui->openglWidget,SIGNAL(xRotationChanged(int)),this,SLOT(setLabelX(int)));
    connect(ui->openglWidget,SIGNAL(yRotationChanged(int)),this,SLOT(setLabelY(int)));
    connect(ui->openglWidget,SIGNAL(zRotationChanged(int)),this,SLOT(setLabelZ(int)));
    connect(timer,SIGNAL(timeout()),this,SLOT(leerDatos()));
    ui->closePort->setEnabled(false);
    actualizarPuertos();
    const QList<qint32> baudrates = QSerialPortInfo::standardBaudRates();
    foreach (qint32 baud, baudrates) {
        if(baud>4800)
        ui->baudRate->addItem(QString::number(baud));
    }
    ui->baudRate->setCurrentText(QString::number(115200));



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



void MainWindow::leerDatos()
{
    //TODO: solicitar coordenadas al sensor MPU6050 a través del puerto serie.
   // qDebug()<<"leyendo";

   serial->write(QByteArray("."));


    y+=16;
    ui->openglWidget->setYRotation(y);
}

void MainWindow::actualizarPuertos()
{
    ui->puertosBox->clear();

    const QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();

    foreach (const QSerialPortInfo p, puertos) {
        ui->puertosBox->addItem(p.systemLocation());
        qDebug()<<p.systemLocation();
    }

}

void MainWindow::on_openPort_clicked()
{
   QString status;
    serial->setPortName(ui->puertosBox->currentText());
          serial->setBaudRate(ui->baudRate->currentText().toInt());
          serial->setDataBits(QSerialPort::Data8);
          serial->setParity(QSerialPort::NoParity);
          serial->setStopBits(QSerialPort::OneStop);
          serial->setFlowControl(QSerialPort::NoFlowControl);
          if (serial->open(QIODevice::ReadWrite)) {

               status=QString((tr("Connected to %1 : %2, %3, %4, %5, %6")))
                                .arg(serial->portName()).arg(serial->baudRate()).arg("8")
                                .arg(" no parity").arg("0ne stop bit").arg("no flow control");

                //connect(serial, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);


          } else {
              QMessageBox::critical(this, tr("Error"), serial->errorString());

              status=(tr("Open error"));
          }
          qDebug()<<status;
    timer->start(100);
    ui->baudRate->setEnabled(false);
    ui->puertosBox->setEnabled(false);
    ui->openPort->setEnabled(false);
    ui->closePort->setEnabled(true);


}
void MainWindow::handleReadyRead()
  {
    qDebug()<<"SEE";
    QByteArray data = serial->readAll();
    qDebug()<<data;
  }

void MainWindow::on_closePort_clicked()
{
    timer->stop();
    serial->close();
    ui->baudRate->setEnabled(true);
    ui->puertosBox->setEnabled(true);
    ui->openPort->setEnabled(true);
    ui->closePort->setEnabled(false);
}
