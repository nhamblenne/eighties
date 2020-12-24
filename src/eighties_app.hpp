#ifndef EIGHTIES_EIGHTIES_APP_HPP
#define EIGHTIES_EIGHTIES_APP_HPP

/* =======================================================================
 * eighties_app.hpp.h
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <QApplication>

#include <future>

namespace eighties {

class eighties : public QApplication
{
    Q_OBJECT
public:
    eighties(int& argc, char** argv);
    eighties(eighties const&) = delete;
    eighties& operator=(eighties const&) = delete;
    ~eighties() noexcept override = default;

    template<typename F, typename... Ts>
    std::future<void> enqueue(F&&, Ts&&... args);

    static eighties* instance() {
        return dynamic_cast<eighties*>(QApplication::instance());
    }

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    std::mutex m_guard;
    std::vector<std::packaged_task<void()>> m_tasks;
};

template<typename F, typename... Ts>
std::future<void> eighties::enqueue(F&& fn, Ts&&... args)
{
    std::lock_guard guard(m_guard);
    std::packaged_task<void()> task([&](){ return fn(std::forward<Ts>(args)...);});
    auto result = task.get_future();
    m_tasks.push_back(std::move(task));
    return result;
}

}

#endif
