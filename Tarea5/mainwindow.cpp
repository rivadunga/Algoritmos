#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <math.h>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QSpinBox>
#include <QString>
#include <cstdlib>
#include <QGraphicsEllipseItem>
#define PI    3.14159265

float *matrixT = new float[9];
float *transform(float, float);

void drawGraph();
void drawLine(QGraphicsScene *, int, int, int, int, int, int);
void drawEllipse(QGraphicsScene *, int, int, float, int, int);
void drawPrism(QGraphicsScene *, int, int, int, int);
void drawPolygon(QGraphicsScene *);
void drawCone(QGraphicsScene *, int, int, int);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Poligono");
    ui->comboBox->addItem("Cubo");
    ui->comboBox->addItem("Prisma rectangular");
    ui->comboBox->addItem("Prisma triangular");
    ui->comboBox->addItem("Cono");
    ui->comboBox->addItem("Arco");

    ui->comboBox_2->addItem("Original");
    ui->comboBox_2->addItem("Rotación");
    ui->comboBox_2->addItem("Translación");
    ui->comboBox_2->addItem("Zoom in");
    ui->comboBox_2->addItem("Zoom out");
    ui->comboBox_2->addItem("Reflexion");
}


void MainWindow::drawGraph()
{
    QGraphicsScene *scene = new QGraphicsScene;

    scene->setSceneRect(0, 0, 256, 192);
    int index = ui->comboBox->currentIndex();
    //Select figure
    if (index == 0) {
        drawPolygon(scene);
    }
    if (index == 1) {
        drawPrism(scene, 4, 80, 80, 80);
    }
    if (index == 2) {
        drawPrism(scene, 4, 100, 50, 50);
    }
    if (index == 3) {
        drawPrism(scene, 3, 100, 50, 100);
    }
    if (index == 4) {
        drawCone(scene, 80, 80, 80);
    }
    if (index == 5) {
        drawEllipse(scene, 80, 80, 60, 40, 40);
    }

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}


float *transform(float x, float y)
{
    //Transform according to the transform matrix
    float xT     = x * matrixT[0] + y * matrixT[1] + 1 * matrixT[2];
    float yT     = x * matrixT[3] + y * matrixT[4] + 1 * matrixT[5];
    float res[2] = { xT, yT };

    return res;
}


void drawLine(QGraphicsScene *scene, int x0, int y0, int xf, int yf, int offX, int offY)
{
    x0 = (int)(transform(x0, y0)[0]) + offX;
    y0 = (int)(transform(x0, y0)[1]) + offY;
    xf = (int)(transform(xf, yf)[0]) + offX;
    yf = (int)(transform(xf, yf)[1]) + offY;
    scene->addLine(x0, y0, xf, yf);
}


void drawEllipse(QGraphicsScene *scene, int a, int b, float rad, int offX, int offY)
{
    a = (int)(transform(a, b)[0]);
    b = (int)(transform(a, b)[1]);
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(offX, offY, a, b);
    item->setStartAngle(0);
    item->setSpanAngle(rad * 16);
    scene->addItem(item);
}


void drawPolygon(QGraphicsScene *scene)
{
    float c     = 100;
    float d     = 100;
    int   l     = 5;
    int   r     = 80;
    float delta = (2 * PI / l);

    for (int i = 1; i <= l; i++)
    {
        float ang  = i * delta;
        float ang2 = (i + 1) * delta;
        int   x1   = (int)(r * cos(ang));
        int   y1   = (int)(r * sin(ang));
        int   x2   = (int)(r * cos(ang2));
        int   y2   = (int)(r * sin(ang2));
        drawLine(scene, x1, y1, x2, y2, c, d);
    }
}


void drawPrism(QGraphicsScene *scene, int l, int SX, int SY, int SZ)
{
    int c = 20;
    int d = 20;

    float p1B[] = { 0, 0 };
    float p2B[] = { SX, 0 };
    float p3B[] = { p1B[0] + SY * cos(2 * PI / 45), p1B[1] + SY * sin(2 * PI / 45) };
    float p4B[] = { p2B[0] + SY * cos(2 * PI / 45), p2B[1] + SY * sin(2 * PI / 45) };

    float p1T[] = { p1B[0], p1B[1] + SZ };
    float p2T[] = { p2B[0], p2B[1] + SZ };
    float p3T[] = { p3B[0], p3B[1] + SZ };
    float p4T[] = { p4B[0], p4B[1] + SZ };

    drawLine(scene, p1B[0], p1B[1], p2B[0], p2B[1], c, d);
    drawLine(scene, p1B[0], p1B[1], p3B[0], p3B[1], c, d);

    if (l == 4) {
        drawLine(scene, p2B[0], p2B[1], p4B[0], p4B[1], c, d);
        drawLine(scene, p3B[0], p3B[1], p4B[0], p4B[1], c, d);
        drawLine(scene, p2T[0], p2T[1], p4T[0], p4T[1], c, d);
        drawLine(scene, p3T[0], p3T[1], p4T[0], p4T[1], c, d);
    }
    else{
        drawLine(scene, p2B[0], p2B[1], p3B[0], p3B[1], c, d);
        drawLine(scene, p2T[0], p2T[1], p3T[0], p3T[1], c, d);
    }

    drawLine(scene, p1T[0], p1T[1], p2T[0], p2T[1], c, d);
    drawLine(scene, p1T[0], p1T[1], p3T[0], p3T[1], c, d);
    drawLine(scene, p1B[0], p1B[1], p1T[0], p1T[1], c, d);
    drawLine(scene, p2B[0], p2B[1], p2T[0], p2T[1], c, d);
    drawLine(scene, p3B[0], p3B[1], p3T[0], p3T[1], c, d);

    if (l == 4) {
        drawLine(scene, p4B[0], p4B[1], p4T[0], p4T[1], c, d);
    }
}


void drawCone(QGraphicsScene *scene, int SX, int SY, int SZ)
{
    int c = 40;
    int d = 40;
    int a = SX;
    int b = SY * sin(2 * PI / 45.0);

    int p1[] = { -SX / 2, 0 };
    int p2[] = { 0, SZ };
    int p3[] = { SX / 2, 0 };
    int p4[] = { 0, -b / 2 };

    drawLine(scene, p1[0], p1[1], p2[0], p2[1], c + a / 2, d + b / 2);
    drawLine(scene, p2[0], p2[1], p3[0], p3[1], c + a / 2, d + b / 2);
    drawLine(scene, p4[0], p4[1], p2[0], p2[1], c + a / 2, d + b / 2);
    drawEllipse(scene, a, b, 360, c, d);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    updateMatrix();
    drawGraph();
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if (index == 0)
    {
        float matrix[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
        fillUI(matrix);
    }
    if (index == 1)
    {
        float matrix[] = { 0.7071, -0.7071, 0, 0.7071, 0.7071, 0, 0, 0, 1 };
        fillUI(matrix);
    }
    if (index == 2)
    {
        float matrix[] = { 1, 0, 20, 0, 1, 20, 0, 0, 1 };
        fillUI(matrix);
    }
    if (index == 3)
    {
        float matrix[] = { 1.5, 0, 0, 0, 1.5, 0, 0, 0, 1 };
        fillUI(matrix);
    }
    if (index == 4)
    {
        float matrix[] = { 0.5, 0, 0, 0, 0.5, 0, 0, 0, 1 };
        fillUI(matrix);
    }
    if (index == 5)
    {
        float matrix[] = { -1, 0, 0, 0, 1, 0, 0, 0, 1 };
        fillUI(matrix);
    }

    updateMatrix();
    drawGraph();
}


void MainWindow::fillUI(float *matrix)
{
    ui->textA->document()->setPlainText(std::to_string(matrix[0]).substr(0, 4).c_str());
    ui->textB->document()->setPlainText(std::to_string(matrix[1]).substr(0, 4).c_str());
    ui->textC->document()->setPlainText(std::to_string(matrix[2]).substr(0, 4).c_str());
    ui->textD->document()->setPlainText(std::to_string(matrix[3]).substr(0, 4).c_str());
    ui->textE->document()->setPlainText(std::to_string(matrix[4]).substr(0, 4).c_str());
    ui->textF->document()->setPlainText(std::to_string(matrix[5]).substr(0, 4).c_str());
    ui->textG->document()->setPlainText(std::to_string(matrix[6]).substr(0, 4).c_str());
    ui->textH->document()->setPlainText(std::to_string(matrix[7]).substr(0, 4).c_str());
    ui->textI->document()->setPlainText(std::to_string(matrix[8]).substr(0, 4).c_str());
}


void MainWindow::updateMatrix()
{
    matrixT[0] = std::atof(ui->textA->toPlainText().toUtf8().constData());
    matrixT[1] = std::atof(ui->textB->toPlainText().toUtf8().constData());
    matrixT[2] = std::atof(ui->textC->toPlainText().toUtf8().constData());
    matrixT[3] = std::atof(ui->textD->toPlainText().toUtf8().constData());
    matrixT[4] = std::atof(ui->textE->toPlainText().toUtf8().constData());
    matrixT[5] = std::atof(ui->textF->toPlainText().toUtf8().constData());
    matrixT[6] = std::atof(ui->textG->toPlainText().toUtf8().constData());
    matrixT[7] = std::atof(ui->textH->toPlainText().toUtf8().constData());
    matrixT[8] = std::atof(ui->textI->toPlainText().toUtf8().constData());
}
