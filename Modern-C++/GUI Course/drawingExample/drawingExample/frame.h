#ifndef FRAME_H
#define FRAME_H

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>
#include <QPaintEvent>

#include "color.h"
#include "matrix.h"

class Frame : public QFrame
{
    Q_OBJECT

public:
    Frame(QWidget* parent = nullptr);

protected:
    // There are many events available in a QWidget class
    // We can customize their behaviour by overriding them;
    void mousePressEvent(QMouseEvent *event) override; // called on a mouse click
    void paintEvent(QPaintEvent* event) override; // called when the window is repainted

private:
    Matrix<Color> m_colors = Matrix<Color>(5, 5, Color::RED);
};

#endif // FRAME_H
