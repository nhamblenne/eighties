#ifndef EIGHTIES_CANVAS_HPP
#define EIGHTIES_CANVAS_HPP

/* =======================================================================
 * canvas.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <QWidget>
#include <QImage>

namespace eighties {

class color;

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget* parent, int width, int height);
    canvas(canvas const&) = delete;
    canvas& operator=(canvas const&) = delete;
    ~canvas() noexcept override = default;

    void do_clear();
    void do_circle(int xc, int yc, int r, color);
    void do_draw_line(int xb, int yb, int xe, int ye, color);
    void do_plot(int x, int y, color);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QImage m_content;
};

}

#endif
