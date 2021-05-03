#include "gtest/gtest.h"
#include "../lib/lab08/inc/hash_table.h"
#include "../lib/lab08/src/sorts.cpp"
#include "../lib/lab06/inc/doubly_linked_list.h"
#include <random>
#include<algorithm>

std::string gen_random();

class Lab08Fixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        max_size = 2000;

        rng = std::mt19937(rd());    // random-number engine used (Mersenne-Twister in this case)
        uni = std::uniform_int_distribution<int>(0, 99999999); // guaranteed unbiased

        // Get random values
        for (int i = 0; i < max_size; i++) {
            values.push_back(uni(rng));
        }
        for (int i = 0; i < max_size; i++) {
            string_values.push_back(gen_random());
        }
    }

    virtual void TearDown() {
    }

public:
    std::vector<int> values;
    std::vector<std::string> string_values;
    std::uniform_int_distribution<int> uni;
    std::random_device rd;
    std::mt19937 rng;

    int max_size;
};

TEST_F(Lab08Fixture, insertTest) {
    // Linear
    lab8::hash_table tablel('l');
    // Quadratic
    lab8::hash_table tableq('q');
    // Double Hash
    lab8::hash_table tabled('d');

    // Testing valid inserts on an empty linear probing table.
    for (int i = 0; i < max_size; i++) {
        EXPECT_TRUE(tablel.insert(string_values[i], values[i]));
        EXPECT_TRUE(tableq.insert(string_values[i], values[i]));
        EXPECT_TRUE(tabled.insert(string_values[i], values[i]));
    }

    // Testing inserting same keys on the now filled table
    for (int i = 0; i < max_size; i++) {
        EXPECT_FALSE(tablel.insert(string_values[i], values[i]));
        EXPECT_FALSE(tableq.insert(string_values[i], values[i]));
        EXPECT_FALSE(tabled.insert(string_values[i], values[i]));
    }
}

TEST_F(Lab08Fixture, inTableTest) {
    // Linear
    lab8::hash_table tablel('l');
    // Quadratic
    lab8::hash_table tableq('q');
    // Double Hash
    lab8::hash_table tabled('d');

    // Testing invalid in_table calls on an empty linear probing table
    for (int i = 0; i < max_size; i++) {
        EXPECT_FALSE(tablel.in_table(string_values[i]));
        EXPECT_FALSE(tableq.in_table(string_values[i]));
        EXPECT_FALSE(tabled.in_table(string_values[i]));
    }

    // inserting keys to table
    for (int i = 0; i < max_size; i++) {
        EXPECT_TRUE(tablel.insert(string_values[i], values[i]));
        EXPECT_TRUE(tableq.insert(string_values[i], values[i]));
        EXPECT_TRUE(tabled.insert(string_values[i], values[i]));
    }

    // retesting now valid in_table calls on a filled linear probing table
    for (int i = 0; i < max_size; i++) {
        EXPECT_TRUE(tablel.in_table(string_values[i]));
        EXPECT_TRUE(tableq.in_table(string_values[i]));
        EXPECT_TRUE(tabled.in_table(string_values[i]));
    }
}


TEST_F(Lab08Fixture, getTest) {
    // Linear
    lab8::hash_table tablel('l');
    // Quadratic
    lab8::hash_table tableq('q');
    // Double Hash
    lab8::hash_table tabled('d');

    // Empty Table, so we expect throw on every query
    for (int i = 0; i < max_size; i++) {
        EXPECT_ANY_THROW(tablel.get(string_values[i]));
        EXPECT_ANY_THROW(tableq.get(string_values[i]));
        EXPECT_ANY_THROW(tabled.get(string_values[i]));
    }

    // Fill table
    for (int i = 0; i < max_size; i++) {
        tablel.insert(string_values[i], values[i]);
        tableq.insert(string_values[i], values[i]);
        tabled.insert(string_values[i], values[i]);
    }

    // Filled table, so expect values returned now
    for (int i = 0; i < max_size; i++) {
        EXPECT_EQ(tablel.get(string_values[i]), values[i]);
        EXPECT_EQ(tableq.get(string_values[i]), values[i]);
        EXPECT_EQ(tabled.get(string_values[i]), values[i]);
    }
}

TEST_F(Lab08Fixture, removeTest) {
    // Linear
    lab8::hash_table tablel('l');
    // Quadratic
    lab8::hash_table tableq('q');
    // Double Hash
    lab8::hash_table tabled('d');

    // Fill table
    for (int i = 0; i < max_size; i++) {
        tablel.insert(string_values[i], values[i]);
        tableq.insert(string_values[i], values[i]);
        tabled.insert(string_values[i], values[i]);
    }

    // Filled table, so expect values returned now
    for (int i = 0; i < max_size; i++) {
        EXPECT_EQ(tablel.get(string_values[i]), values[i]);
        EXPECT_EQ(tableq.get(string_values[i]), values[i]);
        EXPECT_EQ(tabled.get(string_values[i]), values[i]);
    }

    // Remove all values from table
    for (int i = 0; i < max_size; i++) {
        tablel.remove(string_values[i]);
        tableq.remove(string_values[i]);
        tabled.remove(string_values[i]);
    }

    // Empty Table, so we expect throw on every query
    for (int i = 0; i < max_size; i++) {
        EXPECT_ANY_THROW(tablel.get(string_values[i]));
        EXPECT_ANY_THROW(tableq.get(string_values[i]));
        EXPECT_ANY_THROW(tabled.get(string_values[i]));
    }
}


TEST_F(Lab08Fixture, updateTest) {
    // Linear
    lab8::hash_table tablel('l');
    // Quadratic
    lab8::hash_table tableq('q');
    // Double Hash
    lab8::hash_table tabled('d');

    // Fill table
    for (int i = 0; i < max_size; i++) {
        tablel.insert(string_values[i], values[i]);
        tableq.insert(string_values[i], values[i]);
        tabled.insert(string_values[i], values[i]);
    }

    // Filled table, so expect values returned now
    for (int i = 0; i < max_size; i++) {
        EXPECT_EQ(tablel.get(string_values[i]), values[i]);
        EXPECT_EQ(tableq.get(string_values[i]), values[i]);
        EXPECT_EQ(tabled.get(string_values[i]), values[i]);
    }

    std::vector<int> offsets;
    offsets.reserve(max_size);
    for (int i = 0; i < max_size; i++) {
        offsets.push_back(uni(rng));
    }

    // Fill table
    for (int i = 0; i < max_size; i++) {
        tablel.update(string_values[i], values[i] + offsets[i]);
        tableq.update(string_values[i], values[i] + offsets[i]);
        tabled.update(string_values[i], values[i] + offsets[i]);
    }

    // Expect updated values
    for (int i = 0; i < max_size; i++) {
        EXPECT_EQ(tablel.get(string_values[i]), values[i] + offsets[i]);
        EXPECT_EQ(tableq.get(string_values[i]), values[i] + offsets[i]);
        EXPECT_EQ(tabled.get(string_values[i]), values[i] + offsets[i]);
    }
}

class Lab08SortsFixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        test_numbers=std::vector<int>({12,8,14,15,18,16,17,19,22,20,4,10,9,13,11,5,7,6,2,1,3});
    }

public:
    std::vector <int> test_numbers;

};

TEST_F(Lab08SortsFixture, quik_sortTests) {
    lab6::doubly_linked_list *to_sort;
    to_sort = new lab6::doubly_linked_list(test_numbers);
    lab6::quicksort(*to_sort, 0, test_numbers.size()-1);
    std::sort (test_numbers.begin(), test_numbers.end());

    for (int i = 0; i < test_numbers.size(); i++) {
        EXPECT_EQ(test_numbers[i],to_sort->get_data(i));
    }
}

TEST_F(Lab08SortsFixture, merge_sortTests) {
    lab6::doubly_linked_list *to_sort;
    to_sort = new lab6::doubly_linked_list(test_numbers);
    lab6::mergesort(*to_sort);
    std::sort (test_numbers.begin(), test_numbers.end());

    for (int i = 0; i < test_numbers.size(); i++) {
        EXPECT_EQ(test_numbers[i],to_sort->get_data(i));
    }
}

std::string gen_random() {
    int len = 20;
    char s[20];
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (char & i : s) {
        i = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
    return std::string(s);
}