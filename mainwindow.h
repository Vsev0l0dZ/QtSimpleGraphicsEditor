#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myscene.h"
#include <QActionGroup>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QActionGroup *pactionGroup;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
     void changeCurrentShape(ShapeType shapeType);

private slots:

    void on_actionRectangle_triggered();

    void on_actionEllipse_triggered();

    void slotAddItem(ShapeType signShape, QRectF newRect,
                     QColor m_Color, uint m_Width, Qt::PenStyle m_LineStyle);


private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
