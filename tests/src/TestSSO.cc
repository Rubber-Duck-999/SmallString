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
    BasicSSO copy(original);
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

// Assign one BasicSSO to another
TEST(Tests, DuplicateTest) {
    BasicSSO original("Original-Test-For-Large-String");
    BasicSSO duplicate;
    duplicate = original;
    EXPECT_EQ(duplicate.length(), original.length());
    EXPECT_STREQ(duplicate.c_str(), original.c_str());
}

// Move one BasicSSO contents to another
TEST(Tests, MoveTest) {
    BasicSSO original("Original");
    BasicSSO moved = std::move(original);
    EXPECT_EQ(moved.length(), 8);
    EXPECT_EQ(original.length(), 0);
}

// Add assignment operator
TEST(Tests, AddAsssignmentCStr) {
    const char* str = "Original";
    BasicSSO original(str);
    EXPECT_EQ(original.length(), 8);
    EXPECT_STREQ(original.c_str(), str);
    // Now add +
    const char* addition = "+";
    original += addition;
    EXPECT_EQ(original.length(), 9);
    EXPECT_STREQ(original.c_str(), "Original+");
}

// Add assignment operator long
TEST(Tests, AddAsssignmentCStrLong) {
    const char* str = "Original-On-The-Heap";
    BasicSSO original(str);
    EXPECT_EQ(original.length(), 20);
    EXPECT_STREQ(original.c_str(), str);
    // Now add +
    const char* addition = "+";
    original += addition;
    EXPECT_EQ(original.length(), 21);
    EXPECT_STREQ(original.c_str(), "Original-On-The-Heap+");
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
