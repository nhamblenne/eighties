#ifndef EIGHTIES_CANVAS_HPP
#define EIGHTIES_CANVAS_HPP

/* =======================================================================
 * canvas.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/event.hpp"

#include <QWidget>
#include <QImage>

#include <deque>
#include <mutex>
#include <condition_variable>

namespace eighties {

class color;
class image;
class point;

class canvas: public QWidget
{
    Q_OBJECT
public:
    explicit canvas(QWidget* parent, int width, int height);
    canvas(canvas const&) = delete;
    canvas& operator=(canvas const&) = delete;
    ~canvas() noexcept override = default;

    void do_clear();
    void do_draw_circle(int xc, int yc, int r, color);
    void do_draw_line(int xb, int yb, int xe, int ye, color);
    void do_draw_point(int x, int y, color);
    void do_draw_image(int x, int y, image const&);
    point do_current_cursor_position() const;
    eighties::event do_get_event(bool wait);
    eighties::event do_get_event(std::string&, bool wait);

public:
    QVariant inputMethodQuery(Qt::InputMethodQuery query) const override;

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
    void inputMethodEvent(QInputMethodEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    QImage m_content;
    mutable std::mutex m_guard;
    std::condition_variable m_cond;
    std::deque<eighties::event> m_events;
    std::deque<std::string> m_strings;
};

}

#endif
