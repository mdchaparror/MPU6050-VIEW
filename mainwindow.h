#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void setLabelX(int x);
    void setLabelY(int y);
    void setLabelZ(int z);
    void leerDatos();
    void actualizarPuertos();


    void handleReadyRead();
private slots:
    void on_openPort_clicked();
    void on_closePort_clicked();

private:
    Ui::MainWindow *ui;
    QString xLabelFormat;
    QString yLabelFormat;
    QString zLabelFormat;
    QTimer *timer;
    int y;
    QSerialPort * serial;

};

#endif // MAINWINDOW_H
