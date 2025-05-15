// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "libdsc/unordered_map.h"

// Hash function for strings
static size_t string_hash(void const *key) {
    char const *str = static_cast<char const *>(key);
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Compare function for strings
static int string_compare(void const *a, void const *b) {
    return strcmp(static_cast<char const *>(a), static_cast<char const *>(b));
}

class UnorderedMapTest : public ::testing::Test {
   protected:
    void SetUp() override {
        map = unordered_map_create(sizeof(char *), sizeof(int), string_hash,
                                   string_compare);
        ASSERT_NE(map, nullptr);
    }

    void TearDown() override {
        if (map) {
            unordered_map_destroy(map);
        }
    }

    dsc_unordered_map *map;
};

TEST_F(UnorderedMapTest, Create) {
    EXPECT_EQ(unordered_map_size(map), 0);
    EXPECT_TRUE(unordered_map_empty(map));
}

TEST_F(UnorderedMapTest, InsertAndFind) {
    char const *key = "test";
    int value = 42;

    EXPECT_EQ(unordered_map_insert(map, &key, &value), DSC_SUCCESS);
    EXPECT_EQ(unordered_map_size(map), 1);

    int *found = static_cast<int *>(unordered_map_find(map, &key));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, value);
}

TEST_F(UnorderedMapTest, InsertDuplicate) {
    char const *key = "test";
    int value1 = 42;
    int value2 = 43;

    EXPECT_EQ(unordered_map_insert(map, &key, &value1), DSC_SUCCESS);
    EXPECT_EQ(unordered_map_insert(map, &key, &value2), DSC_SUCCESS);
    EXPECT_EQ(unordered_map_size(map), 1);

    int *found = static_cast<int *>(unordered_map_find(map, &key));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, value2);
}

TEST_F(UnorderedMapTest, Erase) {
    char const *key = "test";
    int value = 42;

    EXPECT_EQ(unordered_map_insert(map, &key, &value), DSC_SUCCESS);
    EXPECT_EQ(unordered_map_erase(map, &key), DSC_SUCCESS);
    EXPECT_EQ(unordered_map_size(map), 0);
    EXPECT_EQ(unordered_map_find(map, &key), nullptr);
}

TEST_F(UnorderedMapTest, EraseNonExistent) {
    char const *key = "test";
    EXPECT_EQ(unordered_map_erase(map, &key), DSC_ERROR_NOT_FOUND);
}

TEST_F(UnorderedMapTest, Clear) {
    char const *key1 = "test1";
    char const *key2 = "test2";
    int value1 = 42;
    int value2 = 43;

    EXPECT_EQ(unordered_map_insert(map, &key1, &value1), DSC_SUCCESS);
    EXPECT_EQ(unordered_map_insert(map, &key2, &value2), DSC_SUCCESS);

    unordered_map_clear(map);
    EXPECT_EQ(unordered_map_size(map), 0);
    EXPECT_EQ(unordered_map_find(map, &key1), nullptr);
    EXPECT_EQ(unordered_map_find(map, &key2), nullptr);
}

TEST_F(UnorderedMapTest, Reserve) {
    EXPECT_EQ(unordered_map_reserve(map, 100), DSC_SUCCESS);

    char const *key = "test";
    int value = 42;
    EXPECT_EQ(unordered_map_insert(map, &key, &value), DSC_SUCCESS);

    int *found = static_cast<int *>(unordered_map_find(map, &key));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, value);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
