// SPDX-License-Identifier: GPL-3.0-or-later

#include <gtest/gtest.h>

#include "libdsc/unordered_set.h"

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

class UnorderedSetTest : public ::testing::Test {
   protected:
    void SetUp() override {
        set = unordered_set_create(sizeof(char *), string_hash, string_compare);
        ASSERT_NE(set, nullptr);
    }

    void TearDown() override {
        if (set) {
            unordered_set_destroy(set);
        }
    }

    dsc_unordered_set_t *set;
};

TEST_F(UnorderedSetTest, Create) {
    EXPECT_EQ(unordered_set_size(set), 0);
    EXPECT_TRUE(unordered_set_empty(set));
}

TEST_F(UnorderedSetTest, InsertAndFind) {
    char const *element = "test";

    EXPECT_EQ(unordered_set_insert(set, &element), DSC_SUCCESS);
    EXPECT_EQ(unordered_set_size(set), 1);

    char const **found =
        static_cast<char const **>(unordered_set_find(set, &element));
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(*found, element);
}

TEST_F(UnorderedSetTest, InsertDuplicate) {
    char const *element = "test";

    EXPECT_EQ(unordered_set_insert(set, &element), DSC_SUCCESS);
    EXPECT_EQ(unordered_set_insert(set, &element), DSC_SUCCESS);
    EXPECT_EQ(unordered_set_size(set), 1);

    char const **found =
        static_cast<char const **>(unordered_set_find(set, &element));
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(*found, element);
}

TEST_F(UnorderedSetTest, Erase) {
    char const *element = "test";

    EXPECT_EQ(unordered_set_insert(set, &element), DSC_SUCCESS);
    EXPECT_EQ(unordered_set_erase(set, &element), DSC_SUCCESS);
    EXPECT_EQ(unordered_set_size(set), 0);
    EXPECT_EQ(unordered_set_find(set, &element), nullptr);
}

TEST_F(UnorderedSetTest, EraseNonExistent) {
    char const *element = "test";
    EXPECT_EQ(unordered_set_erase(set, &element), DSC_ERROR_NOT_FOUND);
}

TEST_F(UnorderedSetTest, Clear) {
    char const *element1 = "test1";
    char const *element2 = "test2";

    EXPECT_EQ(unordered_set_insert(set, &element1), DSC_SUCCESS);
    EXPECT_EQ(unordered_set_insert(set, &element2), DSC_SUCCESS);

    unordered_set_clear(set);
    EXPECT_EQ(unordered_set_size(set), 0);
    EXPECT_EQ(unordered_set_find(set, &element1), nullptr);
    EXPECT_EQ(unordered_set_find(set, &element2), nullptr);
}

TEST_F(UnorderedSetTest, Reserve) {
    EXPECT_EQ(unordered_set_reserve(set, 100), DSC_SUCCESS);

    char const *element = "test";
    EXPECT_EQ(unordered_set_insert(set, &element), DSC_SUCCESS);

    char const **found =
        static_cast<char const **>(unordered_set_find(set, &element));
    ASSERT_NE(found, nullptr);
    EXPECT_STREQ(*found, element);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
