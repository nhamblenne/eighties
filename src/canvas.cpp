/* =======================================================================
 * canvas.cpp.cc
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "canvas.hpp"

#include <QPainter>
#include <QPaintEvent>

namespace eighties {

canvas::canvas(QWidget* parent, int width, int height)
    : QWidget(parent),
      m_content(width, height, QImage::Format_RGB32)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setBackgroundRole(QPalette::Background);
    resize(width, height);
    m_content.fill(QColor(255, 255, 255));
}

void canvas::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, m_content, dirtyRect);
}

void canvas::resizeEvent(QResizeEvent* event)
{
    QImage newImage(size(), QImage::Format_RGB32);
    newImage.fill(QColor(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), m_content);
    m_content = newImage;
    QWidget::resizeEvent(event);
    update();
}

}