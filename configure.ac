# MIT License
#
# Copyright (c) 2023 Vincent Smeets

# Autoconf requirements

# AC_INIT(package, version, bug-report-address)
AC_INIT([dsmr-server], [0.1.0], [dsmr-server@vsmeets.nl])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/dsmr_server.cc])
AC_CONFIG_HEADERS([config.h])
LT_INIT
AM_INIT_AUTOMAKE

# information on the package
BOOST_REQUIRE([1.74])

# checks for programs
AC_PROG_CXX
AC_LANG([C++])

# checks for header files
BOOST_PROGRAM_OPTIONS
AC_CHECK_HEADERS([gtest/gtest.h], , [AC_MSG_ERROR([The required header is not available])])

# checks for libraries
AC_CHECK_CXXLIB([gtest_main], [], [main()])
AC_CHECK_CXXLIB([gtest], [#include <gtest/gtest.h>], [testing::InitGoogleTest()])

# checks for types

# checks for structures

# checks for compiler characteristics

# checks for library functions

# checks for system services

# AC_CONFIG_FILES([file…])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

# AC_OUTPUT
AC_OUTPUT
