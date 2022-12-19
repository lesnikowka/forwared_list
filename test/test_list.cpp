#include <gtest.h>
#include "list.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


class list_fixture : public ::testing::Test{
protected:
	list<int> l, l1, l2, l3;
	std::vector<int> v;
	bool flag = true;
};

TEST_F(list_fixture, can_push_front_and_pop_front_in_order) {
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	l.push_front(3);
	l.push_front(2);
	l.push_front(1);


	for (auto i : v) {
		flag = i == l.front();
		l.pop_front();
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_push_front_and_pop_front_not_in_order) {
	l.push_front(1);
	l.pop_front();
	l.push_front(2);

	flag = l.front() == 2;

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, list_is_empty_after_pop_fronts) {
	l.push_front(1);
	l.push_front(2);

	l.pop_front();
	l.pop_front();

	EXPECT_TRUE(l.empty());
}

TEST_F(list_fixture, list_is_empty_after_clear) {
	l.push_front(1);
	l.push_front(2);

	l.clear();

	EXPECT_TRUE(l.empty());
}

TEST_F(list_fixture, iterators_is_working) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	int i = 0;
	for (auto it : l) {
		flag = it == v[i];
		++i;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_sort_list) {
	std::srand(0);
	int val;
	for (int i = 0; i < 10000; i++) {
		val = std::rand();
		v.push_back(val);
		l.push_front(val);
	}

	std::sort(v.begin(), v.end());
	l.sort();

	int i = 0;
	for (auto it : l) {
		flag = it == v[i];
		++i;
	}

	EXPECT_TRUE(flag);
}