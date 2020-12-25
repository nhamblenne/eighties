/* =======================================================================
 * window.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include "window_impl.hpp"

#include "eighties/color.hpp"
#include "eighties_app.hpp"
#include "canvas.hpp"
#include "scroll_area.hpp"

#include <QMainWindow>
#include <QCloseEvent>

namespace {

template <typename T, typename M, typename... Ps>
void forward(T* c, M fn, Ps... params)
{
    eighties::eighties::instance()->enqueue
        ([=]()
         {
             (c->*fn)(params...);
         }).get();
}

}

namespace eighties {

window::window(window&&) noexcept = default;
window& window::operator=(window&&) noexcept = default;
window::~window() = default;

window::window(int width, int height)
{
    eighties::instance()->enqueue
        ([=]()
         {
             m_impl = std::make_unique<window_impl>(width, height);
         }).get();
}

window_impl::window_impl(int width, int height)
    : QMainWindow()
{
    m_canvas = new canvas(this, width, height);
    m_scrollArea = new scroll_area(this);
    m_scrollArea->setBackgroundRole(QPalette::Midlight);
    m_scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_scrollArea->setWidget(m_canvas);
    setCentralWidget(m_scrollArea);
    resize(m_scrollArea->sizeHint());
    show();
}

void window::wait_for_close() const
{
    m_impl->wait_for_close();
}

void window_impl::wait_for_close()
{
    std::unique_lock guard(m_guard);
    m_cond.wait(guard, [this]{return m_isClosed;});
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

void window::clear()
{
    forward(m_impl->m_canvas, &canvas::do_clear);
}

void window::circle(int xc, int yc, int r, color col)
{
    forward(m_impl->m_canvas, &canvas::do_circle, xc, yc, r, col);
}

void window::draw_line(int xb, int yb, int xe, int ye, color col)
{
    forward(m_impl->m_canvas, &canvas::do_draw_line, xb, yb, xe, ye, col);
}

void window::plot(int x, int y, color col)
{
    forward(m_impl->m_canvas, &canvas::do_plot, x, y, col);
}

void window_impl::closeEvent(QCloseEvent* event)
{
    event->accept();
    std::unique_lock guard(m_guard);
    m_isClosed = true;
    m_cond.notify_all();
}

}
