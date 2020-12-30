#ifndef EIGHTIES_EIGHTIES_APP_HPP
#define EIGHTIES_EIGHTIES_APP_HPP

/* =======================================================================
 * eighties_app.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include <QApplication>

#include <future>

namespace eighties {

class app : public QApplication
{
    Q_OBJECT
public:
    app(int& argc, char** argv);
    app(app const&) = delete;
    app& operator=(app const&) = delete;
    ~app() noexcept override = default;

    template<typename F, typename... Ts>
    std::future<void> enqueue(F&&, Ts&&... args);

    static app* instance() {
        return dynamic_cast<app*>(QApplication::instance());
    }

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    std::mutex m_guard;
    std::vector<std::packaged_task<void()>> m_tasks;
};

template<typename F, typename... Ts>
std::future<void> app::enqueue(F&& fn, Ts&&... args)
{
    std::lock_guard guard(m_guard);
    std::packaged_task<void()> task([&](){ return fn(std::forward<Ts>(args)...);});
    auto result = task.get_future();
    m_tasks.push_back(std::move(task));
    return result;
}

}

#endif
