#ifndef QTGRAPH_H
#define QTGRAPH_H
#include <QColor>
#include <QFile>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QString>
#include <QtCore/qmath.h>
#include <QTextStream>
#include "Graph.h"

class QtGraph :  public Graph
{
public:
    // constructors
    QtGraph() : Graph() {}

    QtGraph(vector<vector<int>> source) : Graph(source) {}

    // drawing
    void Draw(QGraphicsScene *scene);

private:
    void DrawWays(QGraphicsScene *scene);

    void DrawKomivoyazer(QGraphicsScene *scene);

    void DrawNodes(QGraphicsScene *scene);

    void DrawArrows(QGraphicsScene *scene);
};

#endif // QTGRAPH_H
