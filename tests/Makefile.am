#
# automake Makefile.am for the PrBoom tests directory
#
#
# Process this file with automake to produce Makefile.in
#
#

# Build a library containing all the googletest features.
# This approach to building googletest directly in our build scripts is motivated, along with exact details on how to do this,
# in this README in the googletest souce code: https://github.com/google/googletest/tree/release-1.8.1/googletest#build
check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = $(srcdir)/googletest/googletest/src/gtest-all.cc
libgtest_la_CPPFLAGS = -isystem $(srcdir)/googletest/googletest/include -I$(srcdir)/googletest/googletest
libgtest_la_LDFLAGS = -pthread

# Build an example unit test suite, that leverages googletest, that runs when 'make check' is executed
check_PROGRAMS = unittests
unittests_SOURCES = test_example.cpp $(srcdir)/googletest/googletest/src/gtest_main.cc
unittests_LDADD = libgtest.la
unittests_CPPFLAGS = -isystem $(srcdir)/googletest/googletest/include -I$(srcdir)/googletest/googletest

TESTS = unittests
