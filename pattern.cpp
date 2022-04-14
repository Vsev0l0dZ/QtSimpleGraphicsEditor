#include "pattern.h"
#include "myscene.h"
#include <QPainter>


Pattern::Pattern(QWidget *parent) : QWidget(parent)
{
    patternPen = MyScene::getPen();
}


void Pattern::slotChangePen(QPen newPen)
{
    patternPen = newPen;
    update();
}


void Pattern::paintEvent(QPaintEvent *event)
{
  //отрисовываю линию текущим пером:
    QPainter qPt(this);
    qPt.setPen(patternPen);
    qPt.drawLine(QPoint(0,0), QPoint(this->width(), this->height()));
}




