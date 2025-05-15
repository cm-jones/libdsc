// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "libdsc/list.h"

class ListTest : public ::testing::Test {
   protected:
    void SetUp() override { list = list_create(sizeof(int)); }

    void TearDown() override { list_destroy(list); }

    dsc_list *list;
};

TEST_F(ListTest, Create) {
    EXPECT_NE(list, nullptr);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_TRUE(list_empty(list));
}

TEST_F(ListTest, PushFrontAndPopFront) {
    int value = 42;
    EXPECT_EQ(list_push_front(list, &value), DSC_SUCCESS);
    EXPECT_EQ(list_size(list), 1);
    EXPECT_FALSE(list_empty(list));

    int *front = (int *)list_front(list);
    EXPECT_NE(front, nullptr);
    EXPECT_EQ(*front, 42);

    EXPECT_EQ(list_pop_front(list), DSC_SUCCESS);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_TRUE(list_empty(list));
}

TEST_F(ListTest, PushBackAndPopBack) {
    int value = 42;
    EXPECT_EQ(list_push_back(list, &value), DSC_SUCCESS);
    EXPECT_EQ(list_size(list), 1);
    EXPECT_FALSE(list_empty(list));

    int *back = (int *)list_back(list);
    EXPECT_NE(back, nullptr);
    EXPECT_EQ(*back, 42);

    EXPECT_EQ(list_pop_back(list), DSC_SUCCESS);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_TRUE(list_empty(list));
}

TEST_F(ListTest, PushMultiple) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        EXPECT_EQ(list_push_back(list, &value), DSC_SUCCESS);
    }

    EXPECT_EQ(list_size(list), 5);

    // Values should be in order (1, 2, 3, 4, 5)
    int expected = 1;
    list_node_t *current = list_begin(list);
    while (current) {
        int *value = (int *)current->data;
        EXPECT_EQ(*value, expected++);
        current = current->next;
    }

    // Test reverse iteration
    expected = 5;
    current = list_rbegin(list);
    while (current) {
        int *value = (int *)current->data;
        EXPECT_EQ(*value, expected--);
        current = current->prev;
    }
}

TEST_F(ListTest, PopFrontEmpty) {
    EXPECT_EQ(list_pop_front(list), DSC_ERROR_EMPTY);
}

TEST_F(ListTest, PopBackEmpty) {
    EXPECT_EQ(list_pop_back(list), DSC_ERROR_EMPTY);
}

TEST_F(ListTest, FrontEmpty) { EXPECT_EQ(list_front(list), nullptr); }

TEST_F(ListTest, BackEmpty) { EXPECT_EQ(list_back(list), nullptr); }

TEST_F(ListTest, Insert) {
    int values[] = {1, 2, 3};
    for (int value : values) {
        EXPECT_EQ(list_push_back(list, &value), DSC_SUCCESS);
    }

    // List is now: 1 -> 2 -> 3
    list_node_t *pos = list_begin(list);
    int value = 42;
    EXPECT_EQ(list_insert(list, pos, &value), DSC_SUCCESS);
    // List should be: 42 -> 1 -> 2 -> 3

    pos = list_begin(list);
    EXPECT_EQ(*(int *)pos->data, 42);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 1);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 2);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 3);
}

TEST_F(ListTest, Erase) {
    int values[] = {1, 2, 3, 4};
    for (int value : values) {
        EXPECT_EQ(list_push_back(list, &value), DSC_SUCCESS);
    }

    // List is now: 1 -> 2 -> 3 -> 4
    list_node_t *pos = list_begin(list);
    pos = pos->next;  // Move to 2
    EXPECT_EQ(list_erase(list, pos), DSC_SUCCESS);
    // List should be: 1 -> 3 -> 4

    pos = list_begin(list);
    EXPECT_EQ(*(int *)pos->data, 1);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 3);
    pos = pos->next;
    EXPECT_EQ(*(int *)pos->data, 4);
}

TEST_F(ListTest, Clear) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        list_push_back(list, &value);
    }

    EXPECT_EQ(list_size(list), 5);
    list_clear(list);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_TRUE(list_empty(list));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
