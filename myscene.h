#ifndef MYSCENE_H
#define MYSCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsSceneMouseEvent>
#include <QColorDialog>
//#include <QDebug>

enum ShapeType{RECT, ELLIPSE};

class Dialog;//предварительная декларация


class MyScene : public QGraphicsScene
{
    Q_OBJECT
    //enum ShapeType{RECT, ELLIPSE};
    //Q_ENUM(ShapeType)//registers an enum type with the meta-object system

    QAbstractGraphicsShapeItem *m_current;//указатель на текущий рисуемый примитив

    bool m_drawingInProcess;//признак "Идет рисование"

    ShapeType signShape = RECT;

    QPointF m_startPoint;//левый верхний угол прямоугольника
    QPointF m_currPoint;//точка, где курсор

    static QColor m_Color;//цвет линии пера
    uint m_Width = 2;//толщина линии пера
    Qt::PenStyle m_LineStyle = Qt::DotLine;//стиль линии пера
    static QPen m_Pen;

    Dialog *optionsDialog = nullptr;//диалог Опций


public:
    explicit MyScene(QWidget *parent = nullptr);

    virtual void mousePressEvent (QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *mouseEvent);

    static QColor getPenColor() {return m_Color;}
    uint getPenWidth() {return m_Width;}
    Qt::PenStyle getPenLineStyle() {return m_LineStyle;}
    static QPen getPen() {return m_Pen;}


    void setShapeType(ShapeType x) {signShape = x;}//установка признака, какую фигуру рисую


public slots:
    void slotColorDialog();
    void slotUserDialog();
    void onChangeCurrentShape(ShapeType shapeType);

signals:
    void signalNewShape(ShapeType, QRectF, QColor, uint, Qt::PenStyle);
};


#endif // MYSCENE_H
