#ifndef PATTERN_H
#define PATTERN_H

#include <QWidget>
#include <QPen>


class Pattern : public QWidget
{
    Q_OBJECT

    QPen patternPen;//перо должно соответствовать текущим установкам диалога

public:
    explicit Pattern(QWidget *parent = nullptr);


signals:
    // QPaintDevice interface
public:
    //QPaintEngine *paintEngine() const;//создался автоматом вместе с paintEvent по правой клавише на классе
                                        //генерирует ошибки!

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void slotChangePen(QPen);

};

#endif // PATTERN_H
