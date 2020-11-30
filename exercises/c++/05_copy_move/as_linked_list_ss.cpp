#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move

class S {
  int A;
  public:
  S(int a) : A{a} {}
  S(const S& c) : A{c.A} {std::cout << "S copied" << std::endl;}
  S(S&& m) : A{std::move(m.A)} {std::cout << "S moved" << std::endl;}
  S& operator=(const S&) = delete;
  S& operator=(S&&) = delete;
  friend std::ostream& operator<<(std::ostream& os, const S& s) {
    os << "S(" << s.A << ")";
    return os;
  }
};

enum class Method{push_back, push_front};


template <typename T>
class List{

  struct node{
    std::unique_ptr<node> next;
    T value;
    explicit node(const T& x): value{x} {std::cout << "l-value\n";}          // copy ctor of T
    node(const T& x, node* p): next{p}, value{x} {std::cout << "l-value\n";}

    explicit node(T&& x): value{std::move(x)} {std::cout << "r-value" << std::endl;}
    node(T&& x, node* p): next{p}, value{std::move(x)} {std::cout << "r-value" << std::endl;}

    // node(const node& x): value{x.value}{
    //   if(x.next)
    // 	next.reset(new node{*(x->next)});
    // }
    
    explicit node(const std::unique_ptr<node>& x): value{x->value}{
      if(x->next)
	next.reset(new node{x->next});
    }
  };
  
  std::unique_ptr<node> head;
  node* tail;
  std::size_t _size;

  // forwarding ref
  void push_front(T&& x){ // forwarding ref. not r-value
    // auto tmp = new node{x, head.release()};
    // head.reset(tmp);

    // auto tmp = new node{x,head};
    // head.release();
    // head.reset(tmp);
    head.reset(new node{std::move(x),head.release()});
    

  }


  void push_back(T&& x){
    auto _node = new node{std::move(x)};
    auto tmp = head.get();
    if(!tmp){ // if tmp == nullptr
      // our list is empty
      head.reset(_node);
      return;
    }
    
    while(tmp->next)  // while tmp->next.get() != nullptr
      tmp = tmp->next.get();

    tmp->next.reset(_node);
    
  }

public:
  List() = default;
  ~List() = default;


  List(List&&) = default;
  List& operator=(List&&) = default;
  
    
  List(const List& x): _size{x._size} {
    
    if(x.head)
      head.reset(new node{x.head});

  }

  
  List& operator=(const List& x) {
    head.reset();
    auto tmp = x; // copy ctor
    *this = std::move(tmp); // move assignment
    return *this;    
  }
  

  void insert(T x, const Method m) {
  switch(m){
  case Method::push_back:
    push_back(std::move(x)); 
    break;
  case Method::push_front:
    push_front(std::move(x));
    break;
  default:
    std::cerr << "unknown method" << std::endl;
    break;
  };
  ++_size;
  }


  
  friend
  std::ostream& operator<<(std::ostream& os, const List& x){
    auto tmp = x.head.get();
    os << "[" << x._size << "] ";
    while(tmp){
      os << tmp->value << " ";
      tmp = tmp->next.get();
    }
    os << std::endl;
    return os;
  }
  
};



template <typename T>
void my_swap(T& a, T& b){
  auto tmp = std::move(a);
  a = std::move(b); 
  b = std::move(tmp); 
}


int main(){
  List<S> l{};

  S a{4};
  S b{5};

  l.insert(a,Method::push_front);
  std::cout << std::endl;
  l.insert(std::move(b),Method::push_back);
  std::cout << std::endl;

  std::cout << l << std::endl;
  
 return 0;
}
