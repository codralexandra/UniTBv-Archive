#include "frame.h"

#include <QBrush>
#include <QPainter>
#include <QPen>


Frame::Frame(QWidget* parent)
    : QFrame(parent)
{
    // Empty
}

void Frame::mousePressEvent(QMouseEvent *event) // check the documentation of this specific event subclass to see available methods
{
    const auto squareWidth = this->width() / m_colors.GetCols();  // square dimensions are dependent on the window dimensions
    const auto squareHeight = this->height() / m_colors.GetRows();

    std::size_t col = event->position().x() / squareWidth;
    std::size_t line = event->position().y() / squareHeight;

    ++m_colors[{line, col}];

    update(); // a call that queues up a request to redraw the window;
    // this is thread safe - can be called as many times as we want
}

// do not call this method manually;
// there is a system behind it to call it when necessary
void Frame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter{ this }; // this is the only place we can create/use a QPainter

    QPen pen; // controls the contour of the shape we are drawing
    pen.setColor(Qt::black);
    pen.setCapStyle(Qt::SquareCap);
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);
    pen.setJoinStyle(Qt::RoundJoin);

    painter.setPen(pen);

    QBrush brush; // customizez the interior of the shape we are drawing
    brush.setStyle(Qt::SolidPattern);


    const auto squareWidth = this->width() / m_colors.GetCols();
    const auto squareHeight = this->height() / m_colors.GetRows();

    auto position = std::make_pair(0u, 0u);
    auto& [line, col] = position;
    for (; line < m_colors.GetRows(); ++line)
    {
        for (col = 0u; col < m_colors.GetCols(); ++col)
        {
            brush.setColor(colorToQColor(m_colors[position]));
            painter.setBrush(brush);

            painter.drawRect( // there are many draw functions to use
                col * squareWidth,
                line * squareHeight,
                squareWidth,
                squareHeight
            );
        }
    }
}
