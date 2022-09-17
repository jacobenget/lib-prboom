#include "gtest/gtest.h"

extern "C" {
#include "m_argv.h"
}

/*
  Unit tests for the M_CheckParm utility.
*/

template <int size> void setMyArg(char *(&argv)[size]) {
  myargc = size;
  myargv = argv;
}

TEST(CheckParmTest, CorrectlyFindsAllExistingArgs) {

  char *args[7] = {"executableName",           "-anOption", "aValue",
                   "anotherOptionWithoutDash", "a",         "b",
                   "has \n whitespace \t\n\t"};
  setMyArg(args);

  ASSERT_EQ(M_CheckParm("-anOption"), 1);
  ASSERT_EQ(M_CheckParm("aValue"), 2)
      << "M_CheckParm finds each and any arg, and doens't make a distintion of "
         "what they might mean";
  ASSERT_EQ(M_CheckParm("anotherOptionWithoutDash"), 3)
      << "Parameters do not have to start with with -";
  ASSERT_EQ(M_CheckParm("a"), 4);
  ASSERT_EQ(M_CheckParm("b"), 5);
  ASSERT_EQ(M_CheckParm("has \n whitespace \t\n\t"), 6)
      << "Parameters can have aribtrary whitespace in them";
}

TEST(CheckParmTest, OnlyFindsLastInstance) {
  char *args[6] = {"executableName", "a", "a", "b", "a", "b"};
  setMyArg(args);

  ASSERT_EQ(M_CheckParm("a"), 4)
      << "All instances of 'a' but the last one are ignored";
  ASSERT_EQ(M_CheckParm("b"), 5)
      << "All instances of 'b' but the last one are ignored";
}

TEST(CheckParmTest, ParameterNamesAreCaseInsensitive) {
  char *args[2] = {"executableName", "-anOption"};
  setMyArg(args);

  ASSERT_EQ(M_CheckParm("-AnOPTION"), 1);
  ASSERT_EQ(M_CheckParm("-anoption"), 1);
  ASSERT_EQ(M_CheckParm("-ANOPTION"), 1);
}

TEST(CheckParmTest, ZeroReturnedWhenParameterNotFound) {
  char *args[2] = {"executableName", "-anOption"};
  setMyArg(args);

  ASSERT_EQ(M_CheckParm("anOption"), 0);
  ASSERT_EQ(M_CheckParm("-somethingUnexpected"), 0);
}

TEST(CheckParmTest, ZeroReturnedWhenExecutableNameSearched) {
  char *args[2] = {"executableName", "-anOption"};
  setMyArg(args);

  ASSERT_EQ(M_CheckParm("executableName"), 0);
}
