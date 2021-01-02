#ifndef EIGHTIES_APP_HPP
#define EIGHTIES_APP_HPP

/* =======================================================================
 * app.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

namespace eighties {

/// initialize eighties and call wrapped.  Arguments used by
/// eighties are removed and not passed to wrapped.
int main(int argc, char* argv[], int (*wrapped)(int, char**));

}

#endif
