#ifndef EIGHTIES_APP_HPP
#define EIGHTIES_APP_HPP

/* =======================================================================
 * app.hpp
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

namespace eighties {

/// initialize eighties and call wrapped.  Arguments used by eighties are
/// removed and not passed to wrapped.  wrapped is called in another thead as
/// some systems limit handling some things that eighties has to do to the main
/// thead.
/// This function is usually not needed as the usual way of writing an eighties
/// program is to provide an `emain` instead of a `main`.
int main(int argc, char* argv[], int (*wrapped)(int, char**));

}

#endif
