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

TEST_F(list_fixture, size_return_correct_value_if_list_is_empty_after_creating) {
	flag = l.size() == 0;

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, size_return_correct_value_if_list_is_empty_after_pop) {
	l.push_front(1);
	l.pop_front();

	flag = l.size() == 0;

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, size_return_correct_value_if_list_is_empty_after_clear) {
	l.push_front(1);
	l.clear();

	flag = l.size() == 0;

	EXPECT_TRUE(flag);
}

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
		if (it != v[i])
			flag = false;
		++i;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_sort_list) {
	std::srand(0);
	int val;
	for (int i = 0; i < 1000; i++) {
		val = std::rand();
		v.push_back(val);
		l.push_front(val);
	}

	std::sort(v.begin(), v.end());
	l.sort();

	int i = 0;
	for (auto it : l) {
		if (it != v[i])
			flag = false;
		++i;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_insert_after) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	v.push_back(3);
	v.push_back(2);
	v.push_back(4);
	v.push_back(1);

	auto it = ++l.begin();

	l.insert_after(it, 4);

	int i = 0;
	for (auto it : l) {
		if (it != v[i])
			flag = false;
		++i;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_insert_on_tail) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	v.push_back(3);
	v.push_back(2);
	v.push_back(1);
	v.push_back(4);

	auto it = ++++l.begin();

	l.insert_after(it, 4);

	int i = 0;
	for (auto it : l) {
		if (it != v[i])
			flag = false;
		++i;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_erase_after) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	v.push_back(3);
	v.push_back(2);

	auto it = ++l.begin();

	l.erase_after(it);

	int i = 0;
	for (auto it : l) {
		if (it != v[i])
			flag = false;
		++i;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, throw_if_insert_after_end) {
	l.push_front(1);
	l.push_front(2);

	ASSERT_ANY_THROW(l.insert_after(l.end(), 1));
}

TEST_F(list_fixture, can_copy_list) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	list<int> l4 = l;

	auto it1 = l.begin();
	for (auto it2 : l4) {
		if (it2 != *it1)
			flag = false;
		++it1;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_move_list_constructor) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	l2.push_front(1);
	l2.push_front(2);
	l2.push_front(3);

	list<int> l4 = std::move(l2);

	auto it1 = l.begin();
	for (auto it2 : l4) {
		if (it2 != *it1)
			flag = false;
		++it1;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_assign_list) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	l3 = l;

	auto it1 = l.begin();
	for (auto it2 : l3) {
		if (it2 != *it1)
			flag = false;
		++it1;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, can_move_list_operator) {
	l.push_front(1);
	l.push_front(2);
	l.push_front(3);

	l2.push_front(1);
	l2.push_front(2);
	l2.push_front(3);

	l3 = std::move(l2);

	auto it1 = l.begin();
	for (auto it2 : l3) {
		if (it2 != *it1)
			flag = false;
		++it1;
	}

	EXPECT_TRUE(flag);
}

TEST_F(list_fixture, no_throw_if_sort_empty_list) {
	ASSERT_NO_THROW(l.sort());
}

//TEST_F(list_fixture)

//TEST_F(list_fixture)

//TEST_F(list_fixture)

//TEST_F(list_fixture)

//TEST_F(list_fixture)

//TEST_F(list_fixture)

