#include <gtest/gtest.h>
#include <cmath>
#include "class.h"

TEST(MyFirstTest, test1)
{
    Line L1 = Line();
    Line L2 = Line(5);
    
    ASSERT_NEAR(0, L2.f(0), 0.1);
    ASSERT_EQ(std::numeric_limits<double>::infinity(), L2.f(5));
    ASSERT_NEAR(0, L2.f(-5), 0.1);
    ASSERT_NEAR(5, L2.r(0), 0.1);
    ASSERT_EQ(std::numeric_limits<double>::infinity(), L2.r(90));
    ASSERT_NEAR(5.0 / cos(mns::PI / 4.0), L2.R_zp(), 0.1);
    ASSERT_NEAR(pow(5.0, 2.0) * (2.0 - mns::PI / 2.0), L2.S1(), 0.1);
    ASSERT_NEAR(pow(5.0, 3.0) * mns::PI * (2 * log(2.0) - 4.0 / 3.0), L2.V1(), 0.1);
    ASSERT_NEAR(pow(5.0, 2.0) * (2.0 + mns::PI / 2.0), L2.S2(), 0.1);

    //ASSERT_NEAR(std::numeric_limits<double>::quiet_NaN(), L2.f(10)); //nan != nan for some reason
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
