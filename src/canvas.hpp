/* =======================================================================
 * canvas.hpp.h
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#ifndef EIGHTIES_CANVAS_HPP
#define EIGHTIES_CANVAS_HPP

#include <QWidget>
#include <QImage>

namespace eighties {

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget* parent, int width, int height);
    canvas(canvas const&) = delete;
    canvas& operator=(canvas const&) = delete;
    ~canvas() noexcept override = default;

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QImage m_content;
};

}

#endif //EIGHTIES_CANVAS_HPP
