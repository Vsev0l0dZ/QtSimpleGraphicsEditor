#include "dialog.h"
#include "ui_dialog.h"


int Dialog::getPatternWidth() const
{
    return patternWidth;
}

void Dialog::setPatternWidth(const int value)
{
    patternWidth = value;
}

QColor Dialog::getPatternColor() const
{
    return patternColor;
}

void Dialog::setPatternColor(const QColor &value)
{
    patternColor = value;
}

Qt::PenStyle Dialog::getPatternStyle() const
{
    return patternStyle;
}

void Dialog::setPatternStyle(const Qt::PenStyle &value)
{
    patternStyle = value;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    MyScene *dialogScene = new MyScene();

    //задаю spinBox образца текущую толщину Pen
    ui->spinBox_Width->setValue(dialogScene->getPenWidth());

    patternColor = MyScene::getPenColor();
    //void QColor::getRgb(int *r, int *g, int *b, int *a = nullptr) const
    int r, g, b;
    patternColor.getRgb(&r, &g, &b);

    //компоненты текущего цвета на слайдеры при первом запуске
    ui->slider_Red->setValue(r);
    ui->slider_Green->setValue(g);
    ui->slider_Blue->setValue(b);

    //выпадающее меню comboBox:
    ui->comboBox_Style->insertItem(0, "Nothing");
    ui->comboBox_Style->insertItem(1, "SolidLine");
    ui->comboBox_Style->insertItem(2, "DashLine");
    ui->comboBox_Style->insertItem(3, "DotLine");
    ui->comboBox_Style->insertItem(4, "DashDotLine");
    ui->comboBox_Style->insertItem(5, "DashDotDotLine");
    //ui->comboBox_Style->insertItem(6, "CustomDashLine");

    //установка текущего стиля линии:
    ui->comboBox_Style->setCurrentIndex(dialogScene->getPenLineStyle());

    //сигнал от каждого элемента управления соединяется со вспомогательным слотом:

    QObject::connect(ui->spinBox_Width, SIGNAL(valueChanged(int)), this, SLOT(slotSomebodyChanged()));

    QObject::connect(ui->slider_Red, SIGNAL(valueChanged(int)), this, SLOT(slotSomebodyChanged()));
    QObject::connect(ui->slider_Green, SIGNAL(valueChanged(int)), this, SLOT(slotSomebodyChanged()));
    QObject::connect(ui->slider_Blue, SIGNAL(valueChanged(int)), this, SLOT(slotSomebodyChanged()));

    QObject::connect(ui->comboBox_Style, SIGNAL(activated(int)), this, SLOT(slotSomebodyChanged()));

    QObject::connect(this, SIGNAL(signalChangePattern(QPen)), ui->widget_Sample, SLOT(slotChangePen(QPen)));
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::slotSomebodyChanged()
{
    //из элементов управления получаю текущие значения, из которых формирую перо:
    patternWidth = ui->spinBox_Width->value();//толщина

    int patternRed = ui->slider_Red->value();
    int patternGreen = ui->slider_Green->value();
    int patternBlue = ui->slider_Blue->value();

    patternColor = QColor(patternRed, patternGreen, patternBlue, 255);

    patternStyle = static_cast<Qt::PenStyle>(ui->comboBox_Style->currentIndex());

    QPen newPen;
    newPen.setColor(patternColor);
    newPen.setWidth(patternWidth);
    newPen.setStyle(patternStyle);

    emit signalChangePattern(newPen);//эмитирую сигнал образцу, чтобы он принял изменения и перерисовался
                                    //т.е., сработал слот void Pattern::slotChangePen(QPen newPen)
}

void Dialog::setColorToSliders()
{
    QColor currentColor;
    currentColor = MyScene::getPenColor();

    int r, g, b;
    currentColor.getRgb(&r, &g, &b);

    ui->slider_Red->setValue(r);
    ui->slider_Green->setValue(g);
    ui->slider_Blue->setValue(b);
}
