/// \file
// Range v3 library
//
//  Copyright Eric Niebler 2013-2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3
//

#ifndef RANGES_V3_DETAIL_CONFIG_HPP
#define RANGES_V3_DETAIL_CONFIG_HPP

#include <iosfwd>

#ifndef RANGES_ASSERT
# include <cassert>
# define RANGES_ASSERT assert
#endif

#ifndef RANGES_ENSURE_MSG
# include <exception>
# define RANGES_ENSURE_MSG(COND, MSG) \
    ((COND) ? void() : (RANGES_ASSERT(!(true && MSG)), std::terminate()))
#endif

#ifndef RANGES_ENSURE
# define RANGES_ENSURE(COND) \
    RANGES_ENSURE_MSG(COND, #COND)
#endif

#define RANGES_DECLTYPE_AUTO_RETURN(...)                        \
    -> decltype(__VA_ARGS__)                                    \
    { return (__VA_ARGS__); }                                   \
    /**/

#define RANGES_DECLTYPE_AUTO_RETURN_NOEXCEPT(...)               \
    noexcept(noexcept(decltype(__VA_ARGS__)(__VA_ARGS__))) ->   \
    decltype(__VA_ARGS__)                                       \
    { return (__VA_ARGS__); }                                   \
    /**/

// Non-portable forward declarations of standard containers
#ifdef _LIBCPP_VERSION
#define RANGES_BEGIN_NAMESPACE_STD _LIBCPP_BEGIN_NAMESPACE_STD
#define RANGES_END_NAMESPACE_STD _LIBCPP_END_NAMESPACE_STD
#else
#define RANGES_BEGIN_NAMESPACE_STD namespace std {
#define RANGES_END_NAMESPACE_STD }
#endif

#ifdef __clang__
#define RANGES_CXX_NO_VARIABLE_TEMPLATES !__has_feature(cxx_variable_templates)
#else
#define RANGES_CXX_NO_VARIABLE_TEMPLATES 1
#endif

#ifndef RANGES_THREAD_LOCAL
#if (defined(__clang__) && defined(__CYGWIN__)) || \
    (defined(__clang__) && defined(_LIBCPP_VERSION)) // BUGBUG avoid unresolved __cxa_thread_atexit
#define RANGES_STATIC_THREAD_LOCAL
#else
#define RANGES_STATIC_THREAD_LOCAL static thread_local
#endif
#endif

#if _MSC_VER >= 1900
#define WORKAROUND_SFINAE_UNIQUE
// mainly for T{} / T() where T is a type trait
#define WORKAROUND_SFINAE_CONSTEXPR
// more complex constexpr
#define WORKAROUND_SFINAE_CONSTEXPR_2
#define WORKAROUND_SFINAE_PARAMETERPACK
#define WORKAROUND_SFINAE_ALIAS_DECLTYPE
#define WORKAROUND_SFINAE_FUNCTION_DECLTYPE
// The same as WORKAROUND_204517
#define WORKAROUND_SFINAE_ALIAS_DEPENDENTEXPR
//#define WORKAROUND_LAMBDA_PREPARSING

// This requires __declspec(empty_bases)
#define WORKAROUND_EBO

#define WORKAROUND_PERMISSIVE

#ifdef WORKAROUND_PERMISSIVE
// fail only under /d1permissive
// alias template
#define WORKAROUND_207134
#endif

// /EHsc and noexcept
#define WORKAROUND_140392
// friend with different nested template parameter level
#define WORKAROUND_159890
// inheriting ctor (ParseQname)
#define WORKAROUND_206729
// name lookup
#define WORKAROUND_207089
// alias template + parser error
#define WORKAROUND_209577
// static data member in constexpr function
#define WORKAROUND_209653
// friend
#define WORKAROUND_213536
// pack expansion + alias
#define WORKAROUND_213933
// decltype in qname
#define WORKAROUND_214014
// pack expansion + base
#define WORKAROUND_214039
// using declaration + alias
#define WORKAROUND_214062
// dependent expression + template arguments used in nested class
#define WORKAROUND_215191
// nested pack expansion
//   found in test\view\zip.cpp
#define WORKAROUND_215598
#define WORKAROUND_215598_NOEXCEPT
// reference + ternary operator
#define WORKAROUND_215653
// friend + default template argument
#define WORKAROUND_216572

// replace.cpp (prevent indirect_move in adaptor_cursor from being specialized)
// variant.hpp (pack expansion doesn't happen for default argument)
#define WORKAROUND_DEFAULT_TEMPLATE_ARGUMENT

// dependent expression + noexcept operator
// also see bug 211850
#define WORKAROUND_NOEXCEPT_DEPENDENT
#define WORKAROUND_211850

#define WORKAROUND_CLASS_RVALUE_AS_LVALUE
#define WORKAROUND_TEMPLATE_STATIC_INITIALIZER
#define WORKAROUND_PACK_EXPANSION // nested alias template
#define WORKAROUND_CONSTEXPR_CXX14

#define NO_GCC_WARNING_PRAGMA

// Temporarily disabled tests
#define TEST_FAILURES

#define BUGFIX

#endif

#if _MSC_VER >= 1900
//#define RANGES_CXX_GREATER_THAN_11
#else
#if __cplusplus > 201103
#define RANGES_CXX_GREATER_THAN_11
#endif
#endif

#if __cplusplus > 201402
#define RANGES_CXX_GREATER_THAN_14
#endif

#ifndef RANGES_DISABLE_DEPRECATED_WARNINGS
#ifdef RANGES_CXX_GREATER_THAN_11
#define RANGES_DEPRECATED(MSG) [[deprecated(MSG)]]
#else
#if defined(__clang__) || defined(__GNUC__)
#define RANGES_DEPRECATED(MSG) __attribute__((deprecated(MSG)))
#elif defined(_MSC_VER)
#define RANGES_DEPRECATED(MSG) __declspec(deprecated(MSG))
#else
#define RANGES_DEPRECATED(MSG)
#endif
#endif
#else
#define RANGES_DEPRECATED(MSG)
#endif

// RANGES_CXX14_CONSTEXPR macro (see also BOOST_CXX14_CONSTEXPR)
// Note: constexpr implies inline, to retain the same visibility
// C++14 constexpr functions are inline in C++11
#ifdef RANGES_CXX_GREATER_THAN_11
#ifdef WORKAROUND_CONSTEXPR_CXX14
#define RANGES_CXX14_CONSTEXPR inline
#else
#define RANGES_CXX14_CONSTEXPR constexpr
#endif
#else
#define RANGES_CXX14_CONSTEXPR inline
#endif

// Workaround for https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70552
#if defined(__GNUC__) && !defined(__clang__) && \
    ((__GNUC__ == 4 && __GNUC_MINOR__ == 9 && __GNUC_PATCHLEVEL__ >= 4) || \
     (__GNUC__ == 5 && __GNUC_MINOR__ >= 3))
#define RANGES_GCC_BROKEN_CUSTPOINT inline
#else
#define RANGES_GCC_BROKEN_CUSTPOINT
#endif

#endif
