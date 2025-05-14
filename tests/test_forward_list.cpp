// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "libdsc/forward_list.h"

class ForwardListTest : public ::testing::Test {
   protected:
    void SetUp() override { list = forward_list_create(sizeof(int)); }

    void TearDown() override { forward_list_destroy(list); }

    dsc_forward_list_t *list;
};

TEST_F(ForwardListTest, Create) {
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(forward_list_size(list), 0);
    EXPECT_TRUE(forward_list_empty(list));
}

TEST_F(ForwardListTest, PushFrontAndPopFront) {
    int value = 42;
    EXPECT_EQ(forward_list_push_front(list, &value), DSC_SUCCESS);
    EXPECT_EQ(forward_list_size(list), 1);
    EXPECT_FALSE(forward_list_empty(list));

    int *front = (int *)forward_list_front(list);
    EXPECT_NE(front, nullptr);
    EXPECT_EQ(*front, 42);

    EXPECT_EQ(forward_list_pop_front(list), DSC_SUCCESS);
    EXPECT_EQ(forward_list_size(list), 0);
    EXPECT_TRUE(forward_list_empty(list));
}

TEST_F(ForwardListTest, PushMultiple) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        EXPECT_EQ(forward_list_push_front(list, &value), DSC_SUCCESS);
    }

    EXPECT_EQ(forward_list_size(list), 5);

    // Values should be in reverse order (5, 4, 3, 2, 1)
    int expected = 5;
    forward_list_node_t *current = forward_list_begin(list);
    while (current) {
        int *value = (int *)current->data;
        EXPECT_EQ(*value, expected--);
        current = current->next;
    }
}

TEST_F(ForwardListTest, PopFrontEmpty) {
    EXPECT_EQ(forward_list_pop_front(list), DSC_ERROR_EMPTY);
}

TEST_F(ForwardListTest, FrontEmpty) {
    EXPECT_EQ(forward_list_front(list), nullptr);
}

TEST_F(ForwardListTest, InsertAfter) {
    int values[] = {1, 2, 3};
    for (int value : values) {
        EXPECT_EQ(forward_list_push_front(list, &value), DSC_SUCCESS);
    }

    // List is now: 3 -> 2 -> 1
    forward_list_node_t *pos = forward_list_begin(list);
    int value = 42;
    EXPECT_EQ(forward_list_insert_after(list, pos, &value), DSC_SUCCESS);
    // List should be: 3 -> 42 -> 2 -> 1

    pos = forward_list_begin(list);
    EXPECT_EQ(*(int *)pos->data, 3);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 42);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 2);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 1);
}

TEST_F(ForwardListTest, EraseAfter) {
    int values[] = {1, 2, 3, 4};
    for (int value : values) {
        EXPECT_EQ(forward_list_push_front(list, &value), DSC_SUCCESS);
    }

    // List is now: 4 -> 3 -> 2 -> 1
    forward_list_node_t *pos = forward_list_begin(list);
    EXPECT_EQ(forward_list_erase_after(list, pos), DSC_SUCCESS);
    // List should be: 4 -> 2 -> 1

    pos = forward_list_begin(list);
    EXPECT_EQ(*(int *)pos->data, 4);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 2);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 1);
}

TEST_F(ForwardListTest, Clear) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        forward_list_push_front(list, &value);
    }

    EXPECT_EQ(forward_list_size(list), 5);
    forward_list_clear(list);
    EXPECT_EQ(forward_list_size(list), 0);
    EXPECT_TRUE(forward_list_empty(list));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
