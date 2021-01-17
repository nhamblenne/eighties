# eighties

A simple graphic library for C++ whose goal is to give me the same ease of
writing graphical programs in C++ on modern platforms that I had in the
eighties when I learned to program in basic on a [Dragon
32](https://en.wikipedia.org/wiki/Dragon_32/64) and a [ZX
Spectrum](https://en.wikipedia.org/wiki/ZX_Spectrum).

The documentation is
[here](https://nhamblenne.github.io/eighties/). Neither the documentation
nor the code is complete yet but I want to get early feedback and a guess
of interest. If there is a lack of them, the documentation will probably
never be done.

This is built over [Qt](https://www.qt.io/). The code is structured so that
not only other backends are possible but no information about the current
backend is leaked. I don't intend to write any, the use of Qt gives me
portability and allows me not to work on some tedious things like the support
of Unicode or of image formats.
