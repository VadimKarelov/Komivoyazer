#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->clear();

    // create graph
    myGraph = new QtGraph();    
    myGraph->Komivoyazer();
    myGraph->Draw(scene);

    // add information
    string text = "Задача коммивояжёра: " + myGraph->GetWay() + "=" + to_string(myGraph->WaySize());
    QFont font("Times");
    QGraphicsTextItem *txt = scene->addText(QString::fromStdString(text), font);
    txt->setPos(10, 10);
}

MainWindow::~MainWindow()
{
    delete ui;
}
