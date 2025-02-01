#include <gtest/gtest.h>
#include "BasicSSO.h"

TEST(Tests, ShortZeroString) {
    BasicSSO short_zero_string;
    EXPECT_EQ(short_zero_string.length(), 0);
    EXPECT_STREQ(short_zero_string.c_str(), "");
    EXPECT_EQ(sizeof(short_zero_string), 24);
    // All union and length together
}

TEST(Tests, ShortNonZeroString) {
    const char* str = "Hello";
    BasicSSO hello(str);
    EXPECT_EQ(hello.length(), 5);
    EXPECT_STREQ(hello.c_str(), str);
    EXPECT_EQ(sizeof(hello), 24);
}

// Copy one BasicSSO to another
TEST(Tests, CopyTestStack) {
    BasicSSO original("Original");
    BasicSSO copy;
    copy = original;
    EXPECT_EQ(copy.length(), original.length());
    EXPECT_STREQ(copy.c_str(), original.c_str());
}

// Copy one BasicSSO to another
TEST(Tests, CopyTestLarge) {
    BasicSSO original("Original-Test-For-Large-String");
    // This will throw an error if I use default member copy contructor
    // Or on address sanitiser
    BasicSSO copy(original);
    EXPECT_EQ(copy.length(), original.length());
    EXPECT_STREQ(copy.c_str(), original.c_str());
}

// Copy one BasicSSO to another
TEST(Tests, AssignmentTest) {
    BasicSSO original("Original-Test-For-Large-String");
    BasicSSO copy;
    // This will throw an error if I use default member copy contructor
    // Or on address sanitiser
    copy = original;
    EXPECT_EQ(copy.length(), original.length());
    EXPECT_STREQ(copy.c_str(), original.c_str());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
