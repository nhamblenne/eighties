/* =======================================================================
 * canvas.cpp.cc
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "canvas.hpp"

#include <QPainter>

namespace eighties {

canvas::canvas(QWidget* parent)
    : QWidget(parent)
{
    //setAttribute(Qt::WA_OpaquePaintEvent);
}

QSize canvas::sizeHint() const
{
    return size();
}

QSize canvas::minimumSizeHint() const
{
    return size();
}

void canvas::paintEvent(QPaintEvent*)
{
    QPainter painter{this};
    painter.drawLine(1, 1, size().width()-1, 1);
    painter.drawLine(1, 1, 1, size().height()-1);
    painter.drawLine(1, size().height()-1, size().width()-1, size().height()-1);
    painter.drawLine(size().width()-1, 1, size().width()-1, size().height()-1);
}

}