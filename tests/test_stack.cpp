// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "libdsc/stack.h"

class StackTest : public ::testing::Test {
   protected:
    void SetUp() override { stack = stack_create(sizeof(int)); }

    void TearDown() override { stack_destroy(stack); }

    dsc_stack *stack;
};

TEST_F(StackTest, Create) {
    EXPECT_NE(stack, nullptr);
    EXPECT_EQ(stack_size(stack), 0);
    EXPECT_TRUE(stack_empty(stack));
}

TEST_F(StackTest, PushAndPop) {
    int value = 42;
    EXPECT_EQ(stack_push(stack, &value), DSC_ERROR_OK);
    EXPECT_EQ(stack_size(stack), 1);
    EXPECT_FALSE(stack_empty(stack));

    int *top = static_cast<int *>(dsc_stackop(stack));
    EXPECT_NE(top, nullptr);
    EXPECT_EQ(*top, 42);

    EXPECT_EQ(stack_pop(stack), DSC_ERROR_OK);
    EXPECT_EQ(stack_size(stack), 0);
    EXPECT_TRUE(stack_empty(stack));
}

TEST_F(StackTest, PushMultiple) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        EXPECT_EQ(stack_push(stack, &value), DSC_ERROR_OK);
    }

    EXPECT_EQ(stack_size(stack), 5);

    for (int i = 4; i >= 0; i--) {
        int *top = static_cast<int *>(dsc_stackop(stack));
        EXPECT_NE(top, nullptr);
        EXPECT_EQ(*top, values[i]);
        EXPECT_EQ(stack_pop(stack), DSC_ERROR_OK);
    }

    EXPECT_TRUE(stack_empty(stack));
}

TEST_F(StackTest, PopEmpty) { EXPECT_EQ(stack_pop(stack), DSC_ERROR_EMPTY); }

TEST_F(StackTest, TopEmpty) { EXPECT_EQ(dsc_stackop(stack), nullptr); }

TEST_F(StackTest, Clear) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        stack_push(stack, &value);
    }

    EXPECT_EQ(stack_size(stack), 5);
    stack_clear(stack);
    EXPECT_EQ(stack_size(stack), 0);
    EXPECT_TRUE(stack_empty(stack));
}

TEST_F(StackTest, Reserve) {
    EXPECT_EQ(stack_reserve(stack, 100), DSC_ERROR_OK);

    int values[100];
    for (size_t i = 0; i < 100; ++i) {
        values[i] = i;
        EXPECT_EQ(stack_push(stack, &values[i]), DSC_ERROR_OK);
    }

    EXPECT_EQ(stack_size(stack), 100);

    for (int i = 99; i >= 0; i--) {
        int *top = static_cast<int *>(dsc_stackop(stack));
        EXPECT_NE(top, nullptr);
        EXPECT_EQ(*top, values[i]);
        EXPECT_EQ(stack_pop(stack), DSC_ERROR_OK);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
