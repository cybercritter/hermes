#include <gtest/gtest.h>

TEST(NewTest, test1)
{
    EXPECT_NE(true, false);
}

TEST(NewTest2, test2)
{
    EXPECT_TRUE(false);
}

TEST(SuiteName, TestName) {
    
}

class SuiteName : public ::testing::Test {
    
};
