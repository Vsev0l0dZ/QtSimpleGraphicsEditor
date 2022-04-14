#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "myscene.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    int patternWidth;

    QColor patternColor;

    Qt::PenStyle patternStyle;

public:
    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog();

    int getPatternWidth() const;
    void setPatternWidth(const int value);

    QColor getPatternColor() const;
    void setPatternColor(const QColor &value);

    Qt::PenStyle getPatternStyle() const;
    void setPatternStyle(const Qt::PenStyle &value);

    void setColorToSliders();

public slots:
    void slotSomebodyChanged();

signals:
    void signalChangePattern(QPen);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
