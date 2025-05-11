// SPDX-License-Identifier: GPL-3.0-or-later

#include "libdsc/queue.h"

#include <gtest/gtest.h>

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        queue = queue_create(sizeof(int));
        ASSERT_NE(queue, nullptr);
    }

    void TearDown() override {
        if (queue) {
            queue_destroy(queue);
        }
    }

    dsc_queue_t* queue;
};

TEST_F(QueueTest, Create) {
    EXPECT_EQ(queue_size(queue), 0);
    EXPECT_TRUE(queue_empty(queue));
}

TEST_F(QueueTest, PushAndPop) {
    int value = 42;
    EXPECT_EQ(queue_push(queue, &value), DSC_SUCCESS);
    EXPECT_EQ(queue_size(queue), 1);
    
    int* front = static_cast<int*>(queue_front(queue));
    ASSERT_NE(front, nullptr);
    EXPECT_EQ(*front, value);
    
    EXPECT_EQ(queue_pop(queue), DSC_SUCCESS);
    EXPECT_EQ(queue_size(queue), 0);
    EXPECT_TRUE(queue_empty(queue));
}

TEST_F(QueueTest, PushMultiple) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        EXPECT_EQ(queue_push(queue, &value), DSC_SUCCESS);
    }
    EXPECT_EQ(queue_size(queue), 5);
    
    for (int value : values) {
        int* front = static_cast<int*>(queue_front(queue));
        ASSERT_NE(front, nullptr);
        EXPECT_EQ(*front, value);
        EXPECT_EQ(queue_pop(queue), DSC_SUCCESS);
    }
    EXPECT_TRUE(queue_empty(queue));
}

TEST_F(QueueTest, PopEmpty) {
    EXPECT_EQ(queue_pop(queue), DSC_ERROR_EMPTY);
}

TEST_F(QueueTest, FrontBack) {
    int values[] = {1, 2, 3};
    for (int value : values) {
        EXPECT_EQ(queue_push(queue, &value), DSC_SUCCESS);
    }
    
    int* front = static_cast<int*>(queue_front(queue));
    ASSERT_NE(front, nullptr);
    EXPECT_EQ(*front, 1);
    
    int* back = static_cast<int*>(queue_back(queue));
    ASSERT_NE(back, nullptr);
    EXPECT_EQ(*back, 3);
}

TEST_F(QueueTest, Clear) {
    int values[] = {1, 2, 3, 4, 5};
    for (int value : values) {
        EXPECT_EQ(queue_push(queue, &value), DSC_SUCCESS);
    }
    
    queue_clear(queue);
    EXPECT_EQ(queue_size(queue), 0);
    EXPECT_TRUE(queue_empty(queue));
}

TEST_F(QueueTest, Reserve) {
    EXPECT_EQ(queue_reserve(queue, 100), DSC_SUCCESS);
    
    int value = 42;
    EXPECT_EQ(queue_push(queue, &value), DSC_SUCCESS);
    
    int* front = static_cast<int*>(queue_front(queue));
    ASSERT_NE(front, nullptr);
    EXPECT_EQ(*front, value);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
