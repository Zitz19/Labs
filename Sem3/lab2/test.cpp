#include <gtest/gtest.h>
#include "class.h"

TEST(MyFirstTest, test1)
{
    Line L1 = Line();
    Line L2 = Line(5);

    ASSERT_EQ(1, L2.f(0));
    ASSERT_EQ(std::numeric_limits<double>::infinity(), L2.f(5));
    ASSERT_EQ(0, L2.f(-5));
    ASSERT_EQ(5, L2.r(0));
    ASSERT_EQ(std::numeric_limits<double>::infinity(), L2.r(90));

    //ASSERT_EQ(std::numeric_limits<double>::quiet_NaN(), L2.f(10));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}