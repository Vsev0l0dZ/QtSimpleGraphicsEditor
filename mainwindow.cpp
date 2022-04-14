#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyScene *scene = new MyScene();//создаю СВОЮ сцену

    ui->graphicsL->setScene(scene);//ассоциирую её с QGraphicsView
    ui->graphicsR->setScene(scene);

    connect(ui->action_Color, SIGNAL(triggered()), scene, SLOT(slotColorDialog()));
    connect(ui->action_Options, SIGNAL(triggered()), scene, SLOT(slotUserDialog()));

    connect(this, &MainWindow::changeCurrentShape, scene, &MyScene::onChangeCurrentShape);

    //коннект для таблицы:
    connect(scene, &MyScene::signalNewShape, this, &MainWindow::slotAddItem);

    //чтобы на форме было видно, какой тип фигуры выбран в текущий момент
    pactionGroup = new QActionGroup(parent);
    pactionGroup->addAction(ui->actionRectangle);
    pactionGroup->addAction(ui->actionEllipse);
    ui->actionRectangle->setChecked(true);

    //настройка режима растяжения для секций заголовка таблицы параметров
    QHeaderView* pheader = ui->summTable->horizontalHeader();
    pheader->setSectionResizeMode(QHeaderView::Stretch);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionRectangle_triggered()
{
    emit changeCurrentShape(ShapeType::RECT);
}


void MainWindow::on_actionEllipse_triggered()
{
    emit changeCurrentShape(ShapeType::ELLIPSE);
}


void MainWindow::slotAddItem(ShapeType signShape, QRectF newRect,
                             QColor m_Color, uint m_Width, Qt::PenStyle m_LineStyle)
{
    int row = ui->summTable->rowCount();//определяю номер текущей строки
    ui->summTable->insertRow(row);//добавляю строку

    QString shapeItem = signShape ? "Ellipse" : "Rect";//1st column, figure description
    QTableWidgetItem *newShapeItem = new QTableWidgetItem();

    qreal x1, y1, x2, y2;
    newRect.getCoords(&x1, &y1, &x2, &y2);
    QString geometryString = QString::number(x1) + ", " + QString::number(y1) + ", " +
                             QString::number(x2) + ", " + QString::number(y2);

    QTableWidgetItem *newGeometryItem = new QTableWidgetItem();

    QTableWidgetItem *newColorItem = new QTableWidgetItem();

    QTableWidgetItem *newWidthItem = new QTableWidgetItem();

    QString styleItem = QVariant::fromValue(m_LineStyle).toString();
    QTableWidgetItem *newStyleItem = new QTableWidgetItem();

    newShapeItem->setData(Qt::DisplayRole, shapeItem);

    //пиктограммы для 1го столбца
    signShape ? newShapeItem->setIcon(QIcon(":/Images/Images/IconEllipse.ico")) :
                newShapeItem->setIcon(QIcon(":/Images/Images/IconRect.ico"));
//или так:
//    signShape ? newShapeItem->setData(Qt::DecorationRole,(QIcon(":/Images/Images/IconEllipse.ico"))) :
//                newShapeItem->setData(Qt::DecorationRole,(QIcon(":/Images/Images/IconRect.ico")));

    newGeometryItem->setData(Qt::DisplayRole, geometryString);
    newWidthItem->setData(Qt::DisplayRole, m_Width);
    newColorItem->setData(Qt::DecorationRole, m_Color);//пиктограмма цвета
    newColorItem->setData(Qt::DisplayRole, m_Color);//значение цвета
    newStyleItem->setData(Qt::DisplayRole, styleItem);

    uint colShape = 0;//столбцы по №
    uint colGeomt = 1;
    uint colColor = 4;
    uint colWidth = 3;
    uint colStyle = 2;

    ui->summTable->setItem(row, colShape, newShapeItem);
    ui->summTable->setItem(row, colGeomt, newGeometryItem);
    ui->summTable->setItem(row, colColor, newColorItem);
    ui->summTable->setItem(row, colWidth, newWidthItem);
    ui->summTable->setItem(row, colStyle, newStyleItem);
}


