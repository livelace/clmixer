//
// Created by user on 10/8/21.
//

#include <gtest/gtest.h>
#include "helper.h"

TEST(HelperTestSuite, HumanSize)
{
    EXPECT_EQ(human_readable(1024),"1K");
}