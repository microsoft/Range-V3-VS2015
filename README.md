Range-V3-VS2105
===============

This is a fork of [Eric Niebler's range-v3 library](https://github.com/ericniebler/range-v3) with extensive (and somewhat invasive) workarounds to support the Visual C++ compiler as released in Microsoft Visual Studio 2015. Our intent is to evolve both this fork and upstream range-v3 toward each other by upstreaming less invasive workarounds and removing those that become unnecessary as the compiler evolves to be more standard conformant. We expect that some time in the Visual Studio "15" time frame, [the two streams will merge](https://www.youtube.com/watch?v=jyaLZHiJJnE) and Visual C++ users will be well-served by unmodified upstream range-v3. This fork will then exist only to provide support for VS2015 users.

About (excerpted from [the upstream README](https://github.com/ericniebler/range-v3/blob/master/README.md)):
------

Why does C++ need another range library? Simply put, the existing solutions haven't kept up with the rapid evolution of C++. Range v3 is a library for the future C++. Not only does it work well with today's C++ -- move semantics, lambdas, automatically deduced types and all -- it also anticipates tomorrow's C++ with Concepts Lite.

Range v3 forms the basis of a proposal to add range support to the standard library ([N4128: Ranges for the Standard Library](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4128.html)). It also will be the reference implementation for an upcoming Technical Specification. These are the first steps toward turning ranges into an international standard.

Documentation:
--------------

Check out the (woefully incomplete) documentation [here](https://ericniebler.github.io/range-v3/).

License:
--------

Most of the source code is under the Boost Software License. Parts are taken from Alex Stepanov's Elements of Programming, LLVM's libc++, and from the SGI STL. Please see the attached LICENSE.txt for the full text of all licenses.
