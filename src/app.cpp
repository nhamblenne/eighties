/* =======================================================================
 * app.cpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/app.hpp"

#include "eighties_app.hpp"

#include <QWidget>

#include <future>

namespace eighties {

int user_thread(int argc, char** argv, int (*wrapped)(int, char**))
{
    int status = wrapped(argc, argv);
    QApplication::exit(0);
    return status;
}

int main(int argc, char* argv[], int (*wrapped)(int, char**))
{
    app app{argc, argv};
    auto future = std::async(std::launch::async, user_thread, argc, argv, wrapped);
    QApplication::exec();
    return future.get();
}

}