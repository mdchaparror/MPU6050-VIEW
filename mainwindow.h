#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
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
    void iniciarPuerto();
    void leerDatos();


private:
    Ui::MainWindow *ui;
    QString xLabelFormat;
    QString yLabelFormat;
    QString zLabelFormat;
    QTimer *timer;
    int y;

};

#endif // MAINWINDOW_H
