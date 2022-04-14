#include "mainwindow.h"
#include "myscene.h"
#include "dialog.h"
//#include "pattern.h"


QColor MyScene::m_Color = Qt::black;
QPen MyScene::m_Pen;


MyScene::MyScene(QWidget *parent) : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 500.0, 500.0);

    m_startPoint = QPointF(1.0, 1.0);//левый верхний угол прямоугольника

    m_Pen.setColor(m_Color);
    m_Pen.setWidth(m_Width);
    m_Pen.setStyle(m_LineStyle);
}


void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() == Qt::RightButton)
    {
        m_startPoint = mouseEvent->scenePos();//получил/запомнил верхний левый угол
        if ( signShape == RECT )
        {
            m_current = new QGraphicsRectItem(m_startPoint.x(), m_startPoint.y(), 0., 0.);
        }
        else if ( signShape == ELLIPSE )
        {
            m_current = new QGraphicsEllipseItem(m_startPoint.x(), m_startPoint.y(), 0., 0.);
        }

        m_current->setPen(m_Pen);//v.1
        //m_current->QAbstractGraphicsShapeItem::setPen(m_Pen);//v.2

        m_current->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

        this->addItem(m_current);
        m_drawingInProcess = true;
    }
    //для получения базовой функциональности (выделение, перетаскивание…) метод базового класса:
    this->QGraphicsScene::mousePressEvent(mouseEvent);
}

//------------------------------------------------------------------------------------------------
void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(m_drawingInProcess)
    {
        if(signShape == RECT)
        {
            m_currPoint = mouseEvent->scenePos();//текущая логическая координата курсора
            QRectF newRect = QRectF(m_startPoint, m_currPoint);

            QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(m_current);

            newRect = newRect.normalized();//нормализую свой прямоугольник

            rectItem->QGraphicsRectItem::setRect(newRect);
        }
        else  if(signShape == ELLIPSE)
        {
            m_currPoint = mouseEvent->scenePos();//текущая логическая координата курсора
            QRectF newRect = QRectF(m_startPoint, m_currPoint);

            //template <typename T> T qgraphicsitem_cast(QGraphicsItem *item)
            QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(m_current);

            newRect = newRect.normalized();//нормализую свой прямоугольник

            ellipseItem->QGraphicsEllipseItem::setRect(newRect);
        }
    }
    this->QGraphicsScene::mouseMoveEvent(mouseEvent);
}

//------------------------------------------------------------------------------------------------
void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QRectF newRectTheLast = QRectF(m_startPoint, mouseEvent->lastScenePos());//отрисованный примитив, final version
    emit signalNewShape(signShape, newRectTheLast, m_Color, m_Width, m_LineStyle);//сигнал в таблицу

    if(mouseEvent && m_drawingInProcess)
    {
       m_drawingInProcess = false;
       m_current = nullptr;
    }
    this->QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

//------------------------------------------------------------------------------------------------
//диалог выбора цвета для установки параметров пера:

void MyScene::slotColorDialog()
{
    m_Color = QColorDialog::getColor();

    if(m_Color.isValid())
    {
        m_Pen.setColor(m_Color);
    }

    else
    {
        m_Pen.setColor(Qt::black);
        m_Pen.setStyle(Qt::SolidLine);
        m_Pen.setWidth(m_Width*2);
    }
}

//------------------------------------------------------------------------------------------------
//вызов !модального диалогового окна  Options:

void MyScene::slotUserDialog()
{
    if ( !optionsDialog )
    {
        optionsDialog = new Dialog;
    }

    optionsDialog->setColorToSliders();//установка цвета на слайдеры диалога
    optionsDialog->setPatternStyle(m_LineStyle);
    optionsDialog->setPatternWidth(m_Width);

    if ( optionsDialog->exec() == QDialog::Accepted )
    {
        //здесь присваиваются значения из optionsDialog:
        m_Color = optionsDialog->getPatternColor();
        m_Width = optionsDialog->getPatternWidth();
        m_LineStyle = optionsDialog->getPatternStyle();

        m_Pen.setColor(m_Color);
        m_Pen.setStyle(m_LineStyle);
        m_Pen.setWidth(m_Width);
    }
}

//------------------------------------------------------------------------------------------------
//выбор фигуры

void MyScene::onChangeCurrentShape(ShapeType shapeType)
{
    signShape = shapeType;
}

//------------------------------------------------------------------------------------------------




