#include "gtest/gtest.h"

/*
    This file is just an example set of unit tests, which accomplish nothing other than demonstrating the most basic usage of googletest.
*/

TEST(CategoryTest, SpecificTest)
{
    ASSERT_EQ(0, 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
