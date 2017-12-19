Range-V3-VS2015
===============

This is a fork of [Eric Niebler's range-v3 library](https://github.com/ericniebler/range-v3) from late 2015 with extensive (and somewhat invasive) workarounds to support the Visual C++ compiler as released in Microsoft Visual Studio 2015. As MSVC becomes more conforming throughout the VS2017 series, it is our hope that this separate fork will become unnecessary and that it will be possible for upstream range-v3 to support MSVC directly. Given that goal, there is little motivation for diverging development in this fork. (Note that despite the "VS2015" in the title, this library is intended to work with VS2017 as well.)

Please post any problems you have with this codebase in the [Github issues forum](https://github.com/Microsoft/Range-V3-VS2015/issues) and not in the upstream range-v3 forum. There's no need to bother the range-v3 maintainers with issues and/or bugs in this two-year-old code that may have already been fixed upstream.

About (excerpted from [the upstream README](https://github.com/ericniebler/range-v3/blob/master/README.md)):
------

Why does C++ need another range library? Simply put, the existing solutions haven't kept up with the rapid evolution of C++. Range v3 is a library for the future C++. Not only does it work well with today's C++ -- move semantics, lambdas, automatically deduced types and all -- it also anticipates tomorrow's C++ with Concepts Lite.

Range v3 forms the basis of a proposal to add range support to the standard library ([N4128: Ranges for the Standard Library](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4128.html)). It also will be the reference implementation for an upcoming Technical Specification. These are the first steps toward turning ranges into an international standard.

Documentation:
--------------

Check out the (woefully incomplete) documentation [here](https://microsoft.github.io/Range-V3-VS2015/).

License:
--------

Most of the source code is under the Boost Software License. Parts are taken from Alex Stepanov's Elements of Programming, LLVM's libc++, and from the SGI STL. Please see the attached LICENSE.txt for the full text of all licenses.
