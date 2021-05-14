
#define RUN0 //RUN1 RUN2 RUN3


#ifdef RUN0 

#include"list.h"
#include<iostream>

int main() {

	List<int> l; //List of integers

	l.push_front(5);
	l.push_rear(1);
	l.push_front(7);
	l.push_front(42);

	l.print(); // 2 Bob World Hello

	return 0;
}

#elif defined RUN1

#include"list.h"
#include<iostream>
#include<string>

int main() {

	List<std::string> l; //List of integers

	l.push_rear("Hello");
	l.push_front("World");
	l.push_front("Bob");
	l.push_front("2");

	l.print(); // 2 Bob World Hello
	std::cout << "Size: " << l.size() << std::endl;

	l.pop_rear();
	l.pop_front();
	//l.pop_front();
	l.pop_rear();
	l.print(); // 2 Bob World 

	std::cout << "Size: " << l.size() << std::endl;
	if (!l.empty()) {
		std::cout << l.front() << std::endl; // 2
		std::cout << l.rear() << std::endl;  // World
	}
	return 0;
}

#elif defined RUN2

#define MAKE_MEMBERS_PUBLIC
#include"list.h"
#include<assert.h>

//Unit test for push_front on initially empty list

int main() {

	// Step 1: Initial state
	List<int> l;


	// Step 2: Execute the function to test
	l.push_front(99);

	// Step 3: Verify what you expect to observe.
	assert(l.m_head != nullptr);
	assert(l.m_tail != nullptr);
	assert(l.m_size == 1);
	assert(l.m_head->prev == nullptr);
	assert(l.m_head->next == nullptr);
	assert(l.m_head->item == 99);


}


#else

#define MAKE_MEMBERS_PUBLIC
#include"list.h"
#include<assert.h>
#include<string>

//Unit test for push_font on initially non empty list

int main() {

	// Step 1: Initial state
	
	List<std::string>::Node* first = new List<std::string>::Node;
	List<std::string>::Node* second = new List<std::string>::Node;
	List<std::string>::Node* third = new List<std::string>::Node;

	// We have to manually linked everything together:
	first->item = "first";
	first->prev = nullptr;
	first->next = second;

	second->item = "second";
	second->prev = first;
	second->next = third;

	third->item = "third";
	third->prev = second;
	third->next = nullptr;

	// Now we create List object and inject the initial control state:
	List<std::string> l;
	l.m_head = first;
	l.m_tail = third;
	l.m_size = 3;

	// Step 2: Now with the list given a complete and correct starting state
	l.push_front("Zero");

	// Step 3: Verify:  Technically, we should examine all
	assert(l.m_size == 4);
	assert(l.m_head->prev == nullptr);
	assert(l.m_head == first->prev);
	assert(l.m_head->next == first);
	assert(l.m_head->item == "Zero");
	assert(l.m_tail == third);
}
#endif