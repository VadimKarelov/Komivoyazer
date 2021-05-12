#include "QtGraph.h"

void QtGraph::Draw(QGraphicsScene *scene)
{
    DrawWays(scene);
    DrawKomivoyazer(scene);
    DrawNodes(scene);
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
                // draw line
                int x1 = centerX + cos(step * i) * l;
                int x2 = centerX + cos(step * j) * l;
                int y1 = centerY - sin(step * i) * l;
                int y2 = centerY - sin(step * j) * l;
                QGraphicsItem *ell = scene->addLine(x1, y1, x2, y2);
                scene->addItem(ell);

                // draw arrows
                //ell = scene->addEllipse(x2 + cos(step * i) * r - r / 2, y2 + sin(step * j) * r - r / 2, r / 1.5, r / 1.5, QPen(Qt::black), QBrush(Qt::yellow));

                // draw text
                QFont font("Times");
                QGraphicsTextItem *txt = scene->addText(QString::number(RoadLength(i + 1, j + 1)), font);
                txt->setPos(x2 + (x1 - x2) / 4, y2 - (y2 - y1) / 4);
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

        // draw line
        int x1 = centerX + cos(step * i) * l;
        int x2 = centerX + cos(step * j) * l;
        int y1 = centerY - sin(step * i) * l;
        int y2 = centerY - sin(step * j) * l;
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
        QGraphicsItem *ell = scene->addEllipse(centerX + cos(step * i) * l - r, centerY - sin(step * i) * l - r,
                                               2 * r, 2 * r,
                                               QPen(Qt::black), QBrush(Qt::green));
        scene->addItem(ell);

        // draw text
        QFont font("Times");
        QGraphicsTextItem *txt = scene->addText(QString::number(i + 1), font);
        txt->setPos(centerX + cos(step * i) * l - r, centerY - sin(step * i) * l - r);
    }
}
