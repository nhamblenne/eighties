/* =======================================================================
 * scroll_area.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "scroll_area.hpp"

#include <QScrollBar>

namespace eighties {

scroll_area::scroll_area(QWidget* parent)
    : QScrollArea(parent)
{}

QSize scroll_area::sizeHint() const
{
    int f = 2 * frameWidth();
    QSize sz(f, f);
    if (widget()) {
        auto widgetSize = widgetResizable() ? widget()->sizeHint() : widget()->size();
        sz += widgetSize;
    } else {
        int h = fontMetrics().height();
        sz += QSize(12 * h, 8 * h);
    }
    if (verticalScrollBarPolicy() == Qt::ScrollBarAlwaysOn)
        sz.setWidth(sz.width() + verticalScrollBar()->sizeHint().width());
    if (horizontalScrollBarPolicy() == Qt::ScrollBarAlwaysOn)
        sz.setHeight(sz.height() + horizontalScrollBar()->sizeHint().height());
    return sz;
}

}