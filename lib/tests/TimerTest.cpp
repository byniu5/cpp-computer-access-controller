#include <gtest/gtest.h>
#include "../../src/timer/Timer.h"

class TimerTest : public ::testing::Test {

};


TEST(TimerTest, GetCurrentTimeFloatReturnsValidValue) {
    float time = Timer::getCurrentTimeFloat();
    std::cout << std::endl << time << std::endl;

    EXPECT_GE(time, 0);
    EXPECT_LT(time, 2400);
}

TEST(TimerTest, isAllowedTimeValid) {
    EXPECT_TRUE(Timer::isAllowedTime(0, 2400));
}