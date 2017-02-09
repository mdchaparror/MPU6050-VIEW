#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    serial = new QSerialPort(this);
    connect(serial,SIGNAL(readyRead()),this,SLOT(handleReadyRead()));
    buffer="";
    xLabelFormat="rot X: %1";
    yLabelFormat="rot Y: %1";
    zLabelFormat="rot Z: %1";
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

    serial->putChar('.');

}

void MainWindow::actualizarPuertos()
{
    ui->puertosBox->clear();

    const QList<QSerialPortInfo> puertos = QSerialPortInfo::availablePorts();

    foreach (const QSerialPortInfo p, puertos) {
        ui->puertosBox->addItem(p.systemLocation());

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

        status=QString((tr("Connected to %1 : %2, %3, %4, %5, %6")))
                .arg(serial->portName()).arg(serial->baudRate()).arg("8")
                .arg(" no parity").arg("0ne stop bit").arg("no flow control");

    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        status=(tr("Open error"));
    }

    timer->start(1000);
    ui->baudRate->setEnabled(false);
    ui->puertosBox->setEnabled(false);
    ui->openPort->setEnabled(false);
    ui->closePort->setEnabled(true);




}
void MainWindow::handleReadyRead()
{

   timer->stop();
    int j = serial->bytesAvailable();
    for(int i=0;i<j;i++){
        QByteArray data = serial->read(1);
        buffer += QString(data);

        if(QString(data)==QString("\n")){
            process(buffer.remove("\r\n"));
            buffer.clear();
        }
    }
    timer->start();


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
void MainWindow::process(QString s){
    QStringList l=s.split(",");
    if(l.length()==3){
        double x = l.at(0).toDouble();
        double z = l.at(1).toDouble();
        double y = l.at(2).toDouble();
        ui->openglWidget->setZRotation(z*16);
        ui->openglWidget->setXRotation(-x*16);
        // ui->openglWidget->setYRotation(y*16);
        //TODO: mejorar rotacion en z y velocidad de datos


    }

}
