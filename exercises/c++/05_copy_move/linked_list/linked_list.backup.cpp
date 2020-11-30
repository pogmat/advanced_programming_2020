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
		explicit node(const T& v, node* n=nullptr) : value{v}, next{n} {}
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

	template <typename UR>
	void _insert(UR&& v, const Insertion_method m) {
		switch (m) {
		case Insertion_method::push_front:
			push_front(std::forward<UR>(v));
			break;
		case Insertion_method::push_back:
			push_back(std::forward<UR>(v));
			break;
		default:
			std::cout << "Unknown option" << std::endl;
			break;
		}

		++_size;
	}
	
	template <typename UR>
	void push_front(UR&& v);

	template <typename UR>
	void push_back(UR&& v);
public:
	List() = default;
	~List() = default;

	std::size_t size() const {return _size;}
	void insert(const T& v, const Insertion_method m) {_insert(v, m);}
	void insert(T&& v, const Insertion_method m) {_insert(std::move(v), m);}

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
template <typename UR>
void List<T>::push_front(UR&& v)
{
	head.reset(new node{std::forward<UR>(v), head.release()});

	if (!_size)
		tail = head.get();
}

template <typename T>
template <typename UR>
void List<T>::push_back(UR&& v)
{
	if (_size) {
		tail->next.reset(new node{std::forward<UR>(v)});
		tail = tail->next.get();
	} else {
		push_front(std::forward<UR>(v)); // A lot of if's...	
	}
}

int main()
{
	List<int> l;
	int a{1};
	l.insert(a, Insertion_method::push_back);
	l.insert(2, Insertion_method::push_back);
	l.insert(3, Insertion_method::push_front);
	std::cout << l.size() << std::endl;
	std::cout << l << std::endl;

	return 0;
}
