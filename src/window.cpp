/* =======================================================================
 * window.cpp.c
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/window.hpp"
#include "window_impl.hpp"
#include "eighties_app.hpp"

#include <QMainWindow>
#include <QCloseEvent>
#include <iostream>

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
    m_canvas = new QWidget(this);
    m_canvas->resize(width, height);
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_scrollArea->setWidget(m_canvas);
    setCentralWidget(m_scrollArea);
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

void window_impl::closeEvent(QCloseEvent* event)
{
    event->accept();
    std::unique_lock guard(m_guard);
    m_isClosed = true;
    m_cond.notify_all();
}

}
