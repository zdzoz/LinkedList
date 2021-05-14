#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<assert.h>
template<typename Item>
class List {
public:

	List();

	List(const List<Item>& other);

	List<Item>& operator=(const List<Item>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Item &item);
	void	push_rear(const Item &item);
	void	insert(int index, const Item &item);

	Item	front() const;
	Item	rear() const;
	Item	get(int index) const;

	int		size() const;
	int		find(const Item &item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	remove(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	class Node;

	Node*	m_head;
	Node*	m_tail;

	int		m_size;
};


/* 
// List Implementation
*/

/* Node definition
*/
template<typename Item>
class List<Item>::Node {
public:
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
};



/* List default constructor
*/
template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {}


/* Copy constructor
*/
template<typename Item>
List<Item>::List(const List<Item>& other) {
	Node* h = other.m_head;

	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;

	while (h != nullptr) {
		//push_rear handles m_size
		this->push_rear(h->item);

		h = h->next;
	}
}

/* Overloaded assignment operator
*/
template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
	// self?
	if (this == &other) return *this;

	// clear
	Node* n = m_head;
	while (n != nullptr) {
		Node* d = n->next;
		delete n;
		n = d;
	}

	// reassign
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;

	// copy

	n = other.m_head;
	while (n != nullptr) {
		//push_rear handles m_size
		this->push_rear(n->item);

		n = n->next;
	}

	return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
	Node* n = m_head;
	while (n != nullptr) {
		Node* d = n->next;
		delete n;
		n = d;
	}
}

/* List print
*/
template<typename Item>
void List<Item>::print() const {
	Node* h = m_head;
	if (h != nullptr) {
		while (h->next != nullptr) {
			std::cout << h->item << " ";
			h = h->next;
		}
		std::cout << h->item << std::endl;
	}
}

/* List empty
*/
template<typename Item>
bool List<Item>::empty() const {
	return m_size == 0;
}

/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item &item) {
	Node* n = new Node;
	n->item = item;
	
	n->next = m_head;
	n->prev = nullptr;
	
	if (empty()) {
		m_tail = n;
	}
	else {
		m_head->prev = n;
	}
	
	m_head = n;

	m_size++;
}

/* List push_rear
*/
template<typename Item>
void List<Item>::push_rear(const Item &item) {
	if (m_size == 0) {
		push_front(item);
		return;
	}
	
	Node* n = new Node;
	n->item = item;

	n->next = nullptr;
	n->prev = m_tail;

	m_tail->next = n;
	m_tail = n;
	
	m_size++;
}

/* List insert
*/
template<typename Item>
void List<Item>::insert(int index, const Item &item) {
	if (index <= 0 || empty()) {
		push_front(item);
	}
	else if (index >= m_size) {
		push_rear(item);
	}
	else {
		Node* h = m_head;
		int count = 0;

		while (index != count) {
			count++;
			h = h->next;
		}

		Node* n = new Node;
		n->item = item;
		n->next = h;
		n->prev = h->prev;

		h->prev->next = n;
		h->prev = n;

		m_size++;
	}
}

/*  List front
*/
template<typename Item>
Item List<Item>::front() const {

	assert(m_head != nullptr);

	return m_head->item;
}

/* List rear
*/
template<typename Item>
Item List<Item>::rear() const {
	assert(m_tail != nullptr);

	return m_tail->item;
}

/* List get
//		returns the item at index
*/
template<typename Item>
Item List<Item>::get(int index) const {
	assert(index >= 0 && index < m_size);

	Node* h = m_head;
	int count = 0;

	while (count != index) {
		count++;
		h = h->next;
	}

	return h->item;
}

/* List size
*/
template<typename Item>
int List<Item>::size() const {
	return m_size;
}

/* List find
*/
template<typename Item>
int List<Item>::find(const Item &item) const {

	Node* h = m_head;
	int index = 0;

	while (h != nullptr) {
		if (h->item == item) return index;
		index++;
		h = h->next;
	}

	return -1;
}

/* List pop_front
*/
template<typename Item>
bool List<Item>::pop_front() {
	if (empty()) return false;

	Node* h = m_head;
	m_head = m_head->next;

	delete h;
	if (m_head != nullptr) m_head->prev = nullptr;

	m_size--;

	if (empty()) m_tail = nullptr;

	return true;
}

/* List pop_rear
*/
template<typename Item>
bool List<Item>::pop_rear() {
	if (empty()) return false;

	Node* t = m_tail;
	m_tail = m_tail->prev;

	delete t;
	if (m_tail != nullptr) m_tail->next = nullptr;

	m_size--;

	if (empty()) m_head = nullptr;

	return true;
}

/* List remove
*/
template<typename Item>
bool List<Item>::remove(int index) {
	if (empty() || index > m_size || index < 0) return false;

	if (index == 0) {
		pop_front();
	}
	else if (index == m_size-1) {
		pop_rear();
	}
	else {

		Node* n = m_head;
		int count = 0;

		while (count != index) {
			count++;
			n = n->next;
		}

		n->prev->next = n->next;
		n->next->prev = n->prev;

		delete n;
		m_size--;
	}

	return true;
}

#endif