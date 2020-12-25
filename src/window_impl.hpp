#ifndef EIGHTIES_WINDOW_IMPL_HPP
#define EIGHTIES_WINDOW_IMPL_HPP

/* =======================================================================
 * window_impl.hpp.h
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <QMainWindow>
#include <mutex>
#include <condition_variable>

class QScrollArea;

namespace eighties {

class canvas;
class scroll_area;

class window_impl : QMainWindow
{
    Q_OBJECT
public:
    window_impl(int width, int height);
    window_impl(window_impl const&) = delete;
    window_impl& operator=(window_impl const&) = delete;
    ~window_impl() noexcept override = default;

    void wait_for_close();
    void do_resize(int new_width, int new_height);

protected:
    void closeEvent(QCloseEvent*) override;

private:
    std::mutex m_guard;
    std::condition_variable m_cond;
    bool m_isClosed{false};
    scroll_area* m_scrollArea{nullptr};
    canvas* m_canvas{nullptr};
};

}

#endif
