/* =======================================================================
 * window.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include "window_impl.hpp"

#include "eighties/color.hpp"
#include "eighties/point.hpp"
#include "eighties_app.hpp"
#include "canvas.hpp"
#include "scroll_area.hpp"

#include <QMainWindow>
#include <QCloseEvent>

namespace {

template <typename T, typename M, typename... Ps>
void forward(T* c, M fn, Ps&&... params)
{
    eighties::app::instance()->enqueue
        ([&]()
         {
             (c->*fn)(std::forward<Ps>(params)...);
         }).get();
}

}

namespace eighties {

window::window(window&&) noexcept = default;
window& window::operator=(window&&) noexcept = default;
window::~window()
{
    wait_for_close();
}

window::window(int width, int height)
{
    app::instance()->enqueue
        ([=]()
         {
             m_impl = std::make_unique<window_impl>(width, height);
         }).get();
}

window_impl::window_impl(int width, int height)
    : QMainWindow()
{
    setAttribute(Qt::WA_QuitOnClose, false);
    m_canvas = new canvas(this, width, height);
    m_scrollArea = new scroll_area(this);
    m_scrollArea->setBackgroundRole(QPalette::Midlight);
    m_scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_scrollArea->setWidget(m_canvas);
    setCentralWidget(m_scrollArea);
    resize(m_scrollArea->sizeHint());
    show();
}

window_impl::~window_impl() noexcept = default;

void window::wait_for_close() const
{
    m_impl->wait_for_close();
}

void window_impl::wait_for_close()
{
    std::unique_lock guard(m_guard);
    m_cond.wait(guard, [this]{return m_is_closed;});
}

void window::resize(int new_width, int new_height)
{
    forward(m_impl.get(), &window_impl::do_resize, new_width, new_height);
}

void window_impl::do_resize(int new_width, int new_height)
{
    m_canvas->resize(new_width, new_height);
    resize(m_scrollArea->sizeHint());
}

void window::hide()
{
    forward(m_impl.get(), &window_impl::do_hide);
}

void window_impl::do_hide()
{
    hide();
}

void window::show()
{
    forward(m_impl.get(), &window_impl::do_show);
}

void window_impl::do_show()
{
    if (status() == window::closed) {
        show();
    }
}

void window::close()
{
    forward(m_impl.get(), &window_impl::do_close);
}

void window_impl::do_close()
{
    close();
}

void window::clear()
{
    forward(m_impl->m_canvas, &canvas::do_clear);
}

void window::draw_circle(int xc, int yc, int r, color col)
{
    forward(m_impl->m_canvas, &canvas::do_draw_circle, xc, yc, r, col);
}

void window::draw_line(int xb, int yb, int xe, int ye, color col)
{
    forward(m_impl->m_canvas, &canvas::do_draw_line, xb, yb, xe, ye, col);
}

void window::draw_point(int x, int y, color col)
{
    forward(m_impl->m_canvas, &canvas::do_draw_point, x, y, col);
}

void window::draw_image(int x, int y, image const& im)
{
    forward(m_impl->m_canvas, &canvas::do_draw_image, x, y, im);
}

window::status_type window::status() const
{
    return m_impl->status();
}

window::status_type window_impl::status() const
{
    std::unique_lock guard(m_guard);
    if (m_is_closed) {
        return window::closed;
    } else {
        return window::opened;
    }
}

point window::current_cursor_position() const
{
    point result{ -1, -1 };
    app::app::instance()->enqueue
        ([&]()
         {
             result = m_impl->m_canvas->do_current_cursor_position();
         }).get();
    return result;
}

event window::get_event(bool wait)
{
    return m_impl->m_canvas->do_get_event(wait);
}

event window::get_event(std::string& text, bool wait)
{
    return m_impl->m_canvas->do_get_event(text, wait);
}

void window_impl::closeEvent(QCloseEvent* event)
{
    event->accept();
    std::unique_lock guard(m_guard);
    m_is_closed = true;
    m_cond.notify_all();
}

}
