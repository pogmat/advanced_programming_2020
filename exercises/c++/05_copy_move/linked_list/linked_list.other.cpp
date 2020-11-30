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
#include <type_traits>

class S {
	int a;
public:
	S(int a) : a{a} {}
	S(const S& c) : a{c.a} {std::cout << "S copied" << std::endl;}
	S(S&& m) : a{std::move(m.a)} {std::cout << "S moved" << std::endl;}

	friend std::ostream& operator<<(std::ostream& os, const S& s) {
		os << "S(" << s.a << ")";
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
		//explicit node(const T& v, node* n=nullptr) : value{v}, next{n} {}
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
			std::cerr << "Unknown option" << std::endl;
			break;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const List& l) {
		node* curr_p = l.head.get();
		os << "{ ";
		if (l._size) {
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
}

template <typename T>
void List<T>::push_back(T&& v)
{
	if (_size) {
		tail->next.reset(new node{std::move(v)});
		tail = tail->next.get();
	} else {
		push_front(std::move(v)); // A lot of if's...	
	}
}

int main()
{
	List<S> l;
	S a{1};
	S b{2};
	S c{3};
	l.insert(a, Insertion_method::push_back);
	l.insert(std::move(b), Insertion_method::push_back);
	l.insert(std::move(c), Insertion_method::push_front);
	std::cout << l.size() << std::endl;
	std::cout << l << std::endl;

	return 0;
}
