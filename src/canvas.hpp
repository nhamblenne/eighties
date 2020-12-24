/* =======================================================================
 * canvas.hpp.h
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#ifndef EIGHTIES_CANVAS_HPP
#define EIGHTIES_CANVAS_HPP

#include <QWidget>

namespace eighties {

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget* parent);
    canvas(canvas const&) = delete;
    canvas& operator=(canvas const&) = delete;
    ~canvas() noexcept override = default;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent*) override;
};

}

#endif //EIGHTIES_CANVAS_HPP
