#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void drawGraph();
    void fillUI(float *);
    void updateMatrix();
};
#endif // MAINWINDOW_H
