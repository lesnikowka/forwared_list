#pragma once
#include <iostream>

template <class T>
class list {
	struct node {
		T elem;
		node* next;
		
		node() : elem(T()), next(nullptr) {}

		node(T elem_, node* ptr = nullptr) : elem(elem_), next(ptr) {}
	};

	node* first = nullptr;

	size_t node_distance(node* lnode, node* rnode) {
		node* tmp = lnode;
		size_t distance = 0;
		while (tmp != rnode) {
			distance++;
			tmp = tmp->next;
		}
		return distance;
	}

	node* before_medium_node(node* lnode, node* rnode) {
		node* tmp = lnode;
		for (int i = 0; i < node_distance(lnode, rnode) / 2 - 1; i++) 
			tmp = tmp->next;
		return tmp;
	}

	void merge(node* before_start, node* end) {
		node* medium = before_medium_node(before_start->next, end)->next;
		node* lpart = before_start->next, * rpart = medium, * new_list = new node, * current = new_list;

		while (lpart != medium || rpart != end) {
			if (rpart == end || (lpart != medium && lpart->elem <= rpart->elem)) {
				current->next = lpart;
				lpart = lpart->next;
			}
			else{
				current->next = rpart;
				rpart = rpart->next;
			}
			current = current->next;
		}

		before_start->next = new_list->next;
		current->next = end;
		delete new_list;
	}


	void mergesort(node* before_start, node* end) {
		if (node_distance(before_start->next, end) > 2) {
			mergesort(before_start, before_medium_node(before_start->next, end)->next);
			mergesort(before_medium_node(before_start->next, end), end);
		}

		if(node_distance(before_start->next, end) > 1) merge(before_start, end);
	}

public:

	class iterator {
		node* ptr;
		friend class list;
	public:

		iterator() : ptr(nullptr) {}
		iterator(node* ptr_) {
			ptr = ptr_;
		}
		T& operator*() {
			return ptr->elem;
		}
		iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(*this);
			ptr = ptr->next;
			return tmp;
		}
		iterator operator+(size_t value) {
			iterator tmp(*this);
			for (size_t i = 0; i < value; i++) {
				tmp.ptr = tmp.ptr->next;
			}
			return tmp;
		}
		bool operator!=(const iterator& it) const {
			return ptr != it.ptr;
		}
		bool operator==(const iterator& it) const {
			return !operator!=(it);
		}
	};

	size_t size() const {
		return count;
	}

	iterator begin(){
		return iterator(first);
	}

	iterator end() const {
		return iterator(nullptr);
	}

	size_t count() {
		node* tmp = first;
		size_t count = 0;
		while (tmp) {
			count++;
			tmp = tmp->next;
		}
		return count;
	}

	bool empty() {
		return !first;
	}

	list() = default;

	list(size_t count, T value = 0) {
		if (!count) {
			first = nullptr;
		}
		else {
			node* tmp = new node(value);
			first = tmp;
			for (int i = 1; i < count; i++) {
				tmp->next = new node(value);
				tmp = tmp->next;
			}
		}
	}

	list(const list<T>& l) {
		if (l.first) {
			first = new node(l.first->elem);
			node* tmp1 = first;
			node* tmp2 = l.first;
			while (tmp2->next) {
				tmp1->next = new node(tmp2->next->elem);
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
		}
	}

	list(list<T>&& l) {
		first = nullptr;
		std::swap(first, l.first);
	}

	~list() {
		if (first) {
			node* tmp = first;
			node* tmp2;
			while (tmp->next) {
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
		}
	}

	const list<T>& operator=(const list<T>& l) {
		if (this != &l) {
			if(!empty()) clear();
			if (l.first) {
				first = new node(l.first->elem);
				node* tmp1 = first;
				node* tmp2 = l.first;
				while (tmp2->next) {
					tmp1->next = new node(tmp2->next->elem);
					tmp1 = tmp1->next;
					tmp2 = tmp2->next;
				}
			}
		}
		return *this;
	}

	const list<T>& operator=(list<T>&& l) {
		std::swap(first, l.first);
	}

	void insert_after(iterator previous_it, T value) {
		if (empty()) throw std::exception("list is empty");

		node* tmp = new node(value, previous_it.ptr->next);
		previous_it.ptr->next = tmp;
	}

	void erase_after(iterator previous_it) {
		if (empty()) throw std::exception("list is empty");
		else if (!previous_it.ptr->next) throw std::exception("next element are not exist");

		node* tmp = previous_it.ptr->next;
		previous_it.ptr->next = previous_it.ptr->next->next;
		delete tmp;
	}

	void push_front(const T& value) {
		node* new_element = new node(value, first);
		first = new_element;
	}

	void pop_front() {
		if (empty()) throw std::exception("list is empty");

		node* tmp = first->next;
		delete first;
		first = tmp;
	}

	void clear() {
		if (empty()) throw std::exception("list is empty");

		node* tmp = first;
		node* tmp2;
		while (tmp->next) {
			tmp2 = tmp->next;
			delete tmp;
			tmp = tmp2;
		}
		first = nullptr;
	}

	void print() {
		for (auto i : *this) std::cout << i << " ";
		std::cout << std::endl;
	}

	void sort() {
		node* before_first = new node(T(), first);
		mergesort(before_first, nullptr);
		first = before_first->next;
		delete before_first;
	}

};