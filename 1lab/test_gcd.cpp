#include <gtest/gtest.h>
#include "gcd.h"

TEST(GCDTest, PositiveNumbers) {
    EXPECT_EQ(gcd(48, 18), 6);
    EXPECT_EQ(gcd(101, 103), 1);
}

TEST(GCDTest, ZeroInput) {
    EXPECT_EQ(gcd(0, 10), 10);
    EXPECT_EQ(gcd(10, 0), 10);
}

TEST(GCDTest, BothZero) {
    EXPECT_EQ(gcd(0, 0), 0);
}

TEST(GCDTest, NegativeNumbers) {
    EXPECT_EQ(gcd(-48, -18), 6);
    EXPECT_EQ(gcd(-48, 18), 6);
}
