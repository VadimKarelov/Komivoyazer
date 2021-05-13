#include "QtGraph.h"

int F(double n)
{
    if (n < 0) return -1;
    return 1;
}

void QtGraph::Draw(QGraphicsScene *scene)
{
    DrawWays(scene);
    DrawKomivoyazer(scene);
    DrawWaysLength(scene);
    DrawNodes(scene);
    DrawArrows(scene);
}

void QtGraph::DrawWays(QGraphicsScene *scene)
{
    double step = 2 * 3.14 / _mat.size();
    int centerX = scene->width() / 2;
    int centerY = scene->height() / 2;
    int r = 15;
    int l = 170;

    for (int i = 0; i < _mat.size(); i++)
    {
        for (int j = 0; j < _mat.size(); j++)
        {
            if (RoadLength(i + 1, j + 1) > 0)
            {
                // compute coord of nodes
                int x1 = centerX + cos(step * i) * l;
                int x2 = centerX + cos(step * j) * l;
                int y1 = centerY + sin(step * i) * l;
                int y2 = centerY + sin(step * j) * l;

                // draw line
                QGraphicsItem *ell = scene->addLine(x1, y1, x2, y2);
                scene->addItem(ell);
            }
        }
    }
}

void QtGraph::DrawWaysLength(QGraphicsScene *scene)
{
    double step = 2 * 3.14 / _mat.size();
    int centerX = scene->width() / 2;
    int centerY = scene->height() / 2;
    int r = 15;
    int l = 170;

    for (int i = 0; i < _mat.size(); i++)
    {
        for (int j = 0; j < _mat.size(); j++)
        {
            if (RoadLength(i + 1, j + 1) > 0)
            {
                // compute coord of nodes
                int x1 = centerX + cos(step * i) * l;
                int x2 = centerX + cos(step * j) * l;
                int y1 = centerY + sin(step * i) * l;
                int y2 = centerY + sin(step * j) * l;

                // compute const for drawing
                double t = r / sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

                // draw text
                QFont font("Times");
                QGraphicsTextItem *txt = scene->addText(QString::number(RoadLength(i + 1, j + 1)), font);
                txt->setPos(x2 + (x1 - x2) / 4, y2 + (y1 - y2) / 4);
                //txt->setPos(x2 - (x2 - x1) * t + 3 * F(x2 - x1), y2 - (y2 - y1) * t - 3 * F(y1 - y2));
            }
        }
    }
}

void QtGraph::DrawKomivoyazer(QGraphicsScene *scene)
{
    double step = 2 * 3.14 / _mat.size();
    int centerX = scene->width() / 2;
    int centerY = scene->height() / 2;
    int r = 15;
    int l = 170;

    for (int it = 0; it < _way.size() - 1; it++)
    {
        // adapting
        int i = _way[it];
        int j = _way[it + 1];

        // compute coord of nodes
        int x1 = centerX + cos(step * i) * l;
        int x2 = centerX + cos(step * j) * l;
        int y1 = centerY + sin(step * i) * l;
        int y2 = centerY + sin(step * j) * l;

        // draw line
        QGraphicsItem *ell = scene->addLine(x1, y1, x2, y2, QPen(QBrush(Qt::red), 3));
        scene->addItem(ell);
    }
}

void QtGraph::DrawNodes(QGraphicsScene *scene)
{
    double step = 2 * 3.14 / _mat.size();
    int centerX = scene->width() / 2;
    int centerY = scene->height() / 2;
    int r = 15;
    int l = 170;

    for (int i = 0; i < _mat.size(); i++)
    {
        QGraphicsItem *ell = scene->addEllipse(centerX + cos(step * i) * l - r, centerY + sin(step * i) * l - r,
                                               2 * r, 2 * r,
                                               QPen(Qt::black), QBrush(Qt::green));
        scene->addItem(ell);

        // draw text
        QFont font("Times");
        QGraphicsTextItem *txt = scene->addText(QString::number(i + 1), font);
        txt->setPos(centerX + cos(step * i) * l - r, centerY + sin(step * i) * l - r);
    }
}

void QtGraph::DrawArrows(QGraphicsScene *scene)
{
    double step = 2 * 3.14 / _mat.size();
    int centerX = scene->width() / 2;
    int centerY = scene->height() / 2;
    int r = 15;
    int l = 170;
    int r1 = r / 3;

    for (int i = 0; i < _mat.size(); i++)
    {
        for (int j = 0; j < _mat.size(); j++)
        {
            if (RoadLength(i + 1, j + 1) > 0)
            {
                // compute coord of nodes
                int x1 = centerX + cos(step * i) * l;
                int x2 = centerX + cos(step * j) * l;
                int y1 = centerY + sin(step * i) * l;
                int y2 = centerY + sin(step * j) * l;

                // compute const for drawing arrows
                double t = r / sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
                // draw arrows
                QGraphicsItem *ell = scene->addEllipse(x2 - (x2 - x1) * t - r1, y2 - (y2 - y1) * t - r1,
                                                       r1 * 2, r1 * 2,
                                                       QPen(Qt::black), QBrush(Qt::yellow));
                scene->addItem(ell);
            }
        }
    }
}
