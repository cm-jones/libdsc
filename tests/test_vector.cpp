// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "libdsc/vector.h"

class VectorTest : public ::testing::Test {
   protected:
    void SetUp() override { vec = vector_create(sizeof(int)); }

    void TearDown() override { vector_destroy(vec); }

    dsc_vector *vec;
};

TEST_F(VectorTest, Create) {
    ASSERT_NE(vec, nullptr);
    EXPECT_EQ(vector_size(vec), 0);
    EXPECT_TRUE(vector_empty(vec));
}

TEST_F(VectorTest, PushBack) {
    int value = 42;
    EXPECT_EQ(vector_push_back(vec, &value), DSC_ERROR_OK);
    EXPECT_EQ(vector_size(vec), 1);
    EXPECT_FALSE(vector_empty(vec));

    int *stored = static_cast<int *>(vector_at(vec, 0));
    ASSERT_NE(stored, nullptr);
    EXPECT_EQ(*stored, 42);
}

TEST_F(VectorTest, PopBack) {
    int value = 42;
    vector_push_back(vec, &value);
    EXPECT_EQ(vector_pop_back(vec), DSC_ERROR_OK);
    EXPECT_EQ(vector_size(vec), 0);
    EXPECT_TRUE(vector_empty(vec));
}

TEST_F(VectorTest, Insert) {
    int values[] = {1, 2, 3};
    vector_push_back(vec, &values[0]);
    vector_push_back(vec, &values[2]);

    EXPECT_EQ(vector_insert(vec, 1, &values[1]), DSC_ERROR_OK);
    EXPECT_EQ(vector_size(vec), 3);

    int *stored = static_cast<int *>(vector_at(vec, 1));
    ASSERT_NE(stored, nullptr);
    EXPECT_EQ(*stored, 2);
}

TEST_F(VectorTest, Erase) {
    int values[] = {1, 2, 3};
    vector_push_back(vec, &values[0]);
    vector_push_back(vec, &values[1]);
    vector_push_back(vec, &values[2]);

    EXPECT_EQ(vector_erase(vec, 1), DSC_ERROR_OK);
    EXPECT_EQ(vector_size(vec), 2);

    int *first = static_cast<int *>(vector_at(vec, 0));
    int *second = static_cast<int *>(vector_at(vec, 1));
    EXPECT_EQ(*first, 1);
    EXPECT_EQ(*second, 3);
}

TEST_F(VectorTest, Resize) {
    int value = 42;
    EXPECT_EQ(vector_resize(vec, 5), DSC_ERROR_OK);
    EXPECT_EQ(vector_size(vec), 5);

    for (size_t i = 0; i < 5; ++i) {
        vector_push_back(vec, &value);
    }

    EXPECT_EQ(vector_size(vec), 10);
}

TEST_F(VectorTest, Reserve) {
    EXPECT_EQ(vector_reserve(vec, 100), DSC_ERROR_OK);
    EXPECT_EQ(vector_capacity(vec), 100);
    EXPECT_EQ(vector_size(vec), 0);
}

TEST_F(VectorTest, ShrinkToFit) {
    int value = 42;
    vector_reserve(vec, 100);
    vector_push_back(vec, &value);

    EXPECT_EQ(vector_shrink_to_fit(vec), DSC_ERROR_OK);
    EXPECT_EQ(vector_capacity(vec), 1);
    EXPECT_EQ(vector_size(vec), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
