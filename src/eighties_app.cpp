/* =======================================================================
 * eighties_app.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties_app.hpp"

namespace eighties {

app::app(int& argc, char** argv)
    : QApplication(argc, argv)
{
    startTimer(0);
}

void app::timerEvent(QTimerEvent*)
{
    for (size_t i = 0;; ++i) {
        std::lock_guard guard(m_guard);
        if (i >= m_tasks.size()) {
            m_tasks.clear();
            return;
        }
        m_tasks[i]();
    }
}

}
