//
// Created by Nikitos on 24.06.18.
//

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>

#include "my_circular_buffer.h"
#include "gtest/gtest.h"

template<typename T>
bool check(T &a, T &b) {
    return a == b;
}

template<typename T>
bool check(std::vector<T> &v1, my_circular_buffer<T> &v2) {
    int j = 0;
    for (T i : v2) {
        if (v1[j] != i)
            return false;
        ++j;
    }
    return true;
}

TEST(correctness, two_plus_two){
    my_circular_buffer<int> a(4);
    my_circular_buffer<int> b(8);
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.pop_front();
    b.insert(b.begin(), 10);

    EXPECT_EQ(a[2], b[2]);
}

TEST(correctness, start_empty) {
    my_circular_buffer<int> s;
    EXPECT_EQ(s.empty(), true);
}


TEST(correctness, push_back_one) {
    my_circular_buffer<int> s(1);
    s.push_back(1);
    std::vector<int> v = {1};
    EXPECT_EQ(check<int>(s[0], v[0]), true);
}

TEST(correctness, push_front_one) {
    my_circular_buffer<int> s(1);
    s.push_front(1);
    std::vector<int> v = {1};
    EXPECT_EQ(check<int>(s[0], v[0]), true);
}

TEST(correctness, push_back_one_circl) {
    my_circular_buffer<int> s(1);
    s.push_back(2);
    s.push_back(1);
    std::vector<int> v = {1};
    EXPECT_EQ(check<int>(s[1], v[0]), true);
}

TEST(correctness, push_front_one_circl) {
    my_circular_buffer<int> s(1);
    s.push_front(2);
    s.push_front(1);
    std::vector<int> v = {1};
    EXPECT_EQ(check<int>(s[0], v[0]), true);
}

TEST(correctness, merge_push_one_circl) {
    my_circular_buffer<int> s(1);
    s.push_front(2);
    s.push_back(1);
    std::vector<int> v = {1};
    EXPECT_EQ(check<int>(s[1], v[0]), true);
}


TEST(correctness, many_push_back_one_circl) {
    my_circular_buffer<int> s(8);
    std::vector<int> v;
    for (int i = 0; i < 8; i++) {
        s.push_back(i);
        v.push_back(i);
    }
    EXPECT_EQ(check(v, s), true);
}

TEST(correctness, many_push_front_one_circl) {
    my_circular_buffer<int> s(8);
    std::vector<int> v;
    for (int i = 0; i < 8; i++) {
        s.push_front(i);
        v.push_back(7 - i);
    }
    EXPECT_EQ(check(v, s), true);
}

TEST(correctness, clear) {
    my_circular_buffer<int> s(8);
    std::vector<int> v;
    for (int i = 0; i < 8; i++) {
        s.push_back(i);
    }
    s.clear();
    EXPECT_EQ(s.empty(), true);
    for (int i = 0; i < 8; i++) {
        s.push_front(i);
    }
    s.clear();
    EXPECT_EQ(s.empty(), true);
}

TEST(correctness, pop_back) {
    my_circular_buffer<int> s(8);
    std::vector<int> v;
    for (int i = 0; i < 8; i++) {
        s.push_back(i);
    }
    s.clear();
    EXPECT_EQ(s.empty(), true);
    for (int i = 0; i < 8; i++) {
        s.push_front(i);
    }
    s.clear();
    EXPECT_EQ(s.empty(), true);
}

TEST(correctness, erase) {
    my_circular_buffer<int> s;
    s.push_back(1);
    s.erase(s.begin());
    EXPECT_EQ(s.empty(), true);
}

TEST(correctness, insert) {
    my_circular_buffer<int> s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);
    s.insert(s.begin() + 2, 5);
//    print(s);
    std::vector<int> v = {1, 2, 5, 3, 4};
    EXPECT_EQ(check(v, s), true);
}

TEST(correctness, insert1) {
    my_circular_buffer<int> s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);
    s.insert(s.begin() + 3, 5);
//    print(s);
    std::vector<int> v = {1, 2, 3, 5, 4};
    EXPECT_EQ(check(v, s), true);
}

TEST(correctness, insert_erase) {
    my_circular_buffer<int> s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);
    s.erase(s.insert(s.begin() + 3, 5));
//    print(s);
    std::vector<int> v = {1, 2, 3, 4};
    EXPECT_EQ(check(v, s), true);
}

TEST(correctness, insert_erase1) {
    my_circular_buffer<int> s;
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);
    s.insert(s.erase(s.insert(s.begin() + 3, 5)), 5);
//    print(s);
    std::vector<int> v = {1, 2, 3, 5, 4};
    EXPECT_EQ(check(v, s), true);
}

TEST(correctness, size_after_clear) {
    my_circular_buffer <int> s;
    s.push_back(3);
    s.push_front(10);
    EXPECT_EQ(s.size(), 2);
    s.clear();
    EXPECT_EQ(s.size(), 0);
}

TEST(correctness, iterator_empty_deque) {
    my_circular_buffer <int> s;
    EXPECT_EQ(s.begin() == s.end(), true);
}

TEST(correctness, swap_my_deq) {
    my_circular_buffer<int> a;
    my_circular_buffer<int> b;
    a.push_back(1);
    a.push_back(100);
    b.push_front(-1);

    std::vector<int> v_a = {1, 100};
    std::vector<int> v_b = {-1};
    EXPECT_TRUE(check(v_a, a));
    EXPECT_TRUE(check(v_b, b));
    swap(a, b);
    swap(v_a, v_b);
    EXPECT_TRUE(check(v_a, a));
    EXPECT_TRUE(check(v_b, b));
}

TEST(correctness, erase_end_iter) {
    my_circular_buffer<int> a(2);
    a.push_back(2);
    auto it = a.erase(a.begin());
    EXPECT_TRUE(it == a.end());
}