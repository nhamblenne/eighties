/* =======================================================================
 * scroll_area.hpp.h
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#ifndef EIGHTIES_SCROLL_AREA_HPP
#define EIGHTIES_SCROLL_AREA_HPP

#include <QScrollArea>

namespace eighties {

class scroll_area: public QScrollArea
{
    Q_OBJECT
public:
    explicit scroll_area(QWidget* parent);
    scroll_area(scroll_area const&) = delete;
    scroll_area& operator=(scroll_area const&) = delete;
    ~scroll_area() noexcept override = default;

    QSize sizeHint() const override;
};

}

#endif //EIGHTIES_SCROLL_AREA_HPP
