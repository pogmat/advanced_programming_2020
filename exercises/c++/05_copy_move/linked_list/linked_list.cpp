/**
 * Linked List
 * an OO implementation of Linked List in C++
 *
 * Author: Matteo Poggi <matteo.poggi.fi@gmail.com>
 *
 * (c) Asciarasoft 2020
 **/

#include <iostream>
#include <utility>
#include <memory>
#include <string>

class Test {
	std::string motto;
public:
	Test(const std::string& s) : motto{s} {}

	Test(const Test& c) : motto{c.motto} {std::cout << "Test class copy constructor" << std::endl;}
	Test(Test&& m) : motto(std::move(m.motto)) {std::cout << "Test class move constructor" << std::endl;}

	friend std::ostream& operator<<(std::ostream& os, const Test& t) {
		os << "Test(" << t.motto << ")";
		return os;
	}
};

enum class Insertion_method {
	push_back,
	push_front
};

template <typename T>
class List {
	// Structures
	struct node {
		// Data
		T value;
		std::unique_ptr<node> next;
		// Methods
		explicit node(T&& v, node* n=nullptr) : value{std::move(v)}, next{n} {}
		node(const node&) = delete;
		node(node&&) = delete;
		node& operator=(const node&) = delete;
		node& operator=(node&&) = delete;
	};
	// Data
	std::unique_ptr<node> head;
	node* tail;
	std::size_t _size{0};
	// Methods
	
	void push_front(T&& v);
	void push_back(T&& v);
public:
	List() = default;

	List(const List& c);
	List& operator=(const List& c);

	List(List&& m) = default;
	List& operator=(List&& m) = default;

	~List() = default;

	std::size_t size() const {return _size;}
	void insert(T v, const Insertion_method m) {
		switch (m) {
		case Insertion_method::push_front:
			push_front(std::move(v));
			break;
		case Insertion_method::push_back:
			push_back(std::move(v));
			break;
		default:
			std::cerr << "Unknown option." << std::endl;
			break;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const List& l) {
		node* curr_p = l.head.get();
		os << "{ ";
		if (curr_p) {
			os << curr_p->value;
			curr_p = curr_p->next.get();
		}
		while (curr_p) {
			os << ", " << curr_p->value;
			curr_p = curr_p->next.get();
		}
		os << "}";
		return os;
	}
};

template <typename T>
void List<T>::push_front(T&& v)
{
	head.reset(new node{std::move(v), head.release()});

	if (!_size)
		tail = head.get();

	++_size;
}

template <typename T>
void List<T>::push_back(T&& v)
{
	if (_size) {
		tail->next.reset(new node{std::move(v)});
		tail = tail->next.get();
		++_size;
	} else {
		push_front(std::move(v)); // A lot of if's...	
	}
}

template <typename T>
List<T>::List(const List& c) {
	node* curr_p = c.head.get();
	while (curr_p) {
		push_back(T{curr_p->value});
		curr_p = curr_p->next.get();
	}
}

template <typename T>
List<T>& List<T>::operator=(const List& c) {
	head.reset();
	List<T> tmp{c};
	*this = std::move(tmp);
	return *this;
}

int main()
{
	List<Test> l{};
	
	std::cout << l.size() << std::endl;
	std::cout << l << std::endl;

	Test a{"Pippo"};
	Test b{"Pluto"};
	Test c{"Paperino"};
	Test d{"Tizio"};
	Test e{"Caio"};
	Test f{"Sempronio"};
	Test g{"Mevio"};
	Test h{"Filano"};
	Test i{"Calpurnio"};

	std::cout << "============" << std::endl;

	l.insert(a, Insertion_method::push_back);
	std::cout << std::endl;
	l.insert(std::move(b), Insertion_method::push_back);
	std::cout << std::endl;
	l.insert(std::move(c), Insertion_method::push_front);
	std::cout << std::endl;
	std::cout << l.size() << std::endl;
	std::cout << l << std::endl;

	std::cout << "============" << std::endl;

	List<Test> l2{std::move(l)};

	std::cout << "============" << std::endl;

	l2.insert(d, Insertion_method::push_front);
	std::cout << std::endl;
	l2.insert(std::move(e), Insertion_method::push_back);
	std::cout << std::endl;
	std::cout << l2.size() << std::endl;
	std::cout << l2 << std::endl;

	std::cout << "============" << std::endl;

	List<Test> l3{};
	l3 = std::move(l2);
	std::cout << l3.size() << std::endl;
	std::cout << l3 << std::endl;

	std::cout << "============" << std::endl;

	List<Test> l4{l3};
	l4.insert(f, Insertion_method::push_front);
	l4.insert(std::move(g), Insertion_method::push_back);
	std::cout << l3.size() << std::endl;
	std::cout << l3 << std::endl;
	std::cout << l4.size() << std::endl;
	std::cout << l4 << std::endl;

	std::cout << "============" << std::endl;

	List<Test> l5{};
	l5 = l4;
	l5.insert(h, Insertion_method::push_back);
	l5.insert(std::move(i), Insertion_method::push_front);
	std::cout << l3.size() << std::endl;
	std::cout << l3 << std::endl;
	std::cout << l4.size() << std::endl;
	std::cout << l4 << std::endl;
	std::cout << l5.size() << std::endl;
	std::cout << l5 << std::endl;

	return 0;
}
