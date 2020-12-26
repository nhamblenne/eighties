/* =======================================================================
 * canvas.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "canvas.hpp"

#include "eighties/color.hpp"
#include "eighties/point.hpp"

#include "image_impl.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QWindow>

namespace {

inline QColor toQColor(eighties::color col)
{
    return QColor(col.r, col.g, col.b, col.a);
}

}

namespace eighties {

canvas::canvas(QWidget* parent, int width, int height)
    : QWidget(parent),
      m_content(width, height, QImage::Format_RGB32)
{
    //setAttribute(Qt::WA_OpaquePaintEvent);
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

void canvas::do_clear()
{
    m_content.fill(QColor(255, 255, 255));
    update();
}

void canvas::do_draw_circle(int xc, int yc, int r, color col)
{
    QPainter painter(&m_content);
    painter.setPen(toQColor(col));
    painter.drawEllipse(QPoint(xc, yc), r, r);
    update(xc-r, yc-r, 2*r, 2*r);
}

void canvas::do_draw_line(int xb, int yb, int xe, int ye, color col)
{
    QPainter painter(&m_content);
    painter.setPen(toQColor(col));
    painter.drawLine(xb, yb, xe, ye);
    update(xb, yb, xe-xb+1, ye-yb+1);
}

void canvas::do_draw_point(int x, int y, color col)
{
    QPainter painter(&m_content);
    painter.setPen(toQColor(col));
    painter.drawPoint(x, y);
    update(x, y, 1, 1);
}

void canvas::do_draw_image(int x, int y, image const& im)
{
    QPainter painter(&m_content);
    auto image_size = get_impl(im)->get_image().size();
    painter.drawImage(QPoint(x, y), get_impl(im)->get_image(),
                      QRect(QPoint(0, 0), image_size));
    update(QRect(QPoint(x, y), image_size));
}

point canvas::do_current_cursor_position() const
{
    QWindow* win = window()->windowHandle();
    if (win == nullptr) {
        return { -1, -1 };
    }
    QScreen* scr = win->screen();
    if (scr == nullptr) {
        return { -1, -1 };
    }
    QPoint pos = QCursor::pos(scr);
    pos = mapFromGlobal(pos);
    return { pos.x(), pos.y() };
}

}