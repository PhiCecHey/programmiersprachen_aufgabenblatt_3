#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>
//#include <stdexcept>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
	T         value = T{};
	ListNode* prev = nullptr;
	ListNode* next = nullptr;

	void swap(ListNode<T>* ln) {
		T val = this->value;
		this->value = ln->value;
		ln->value = val;
	}

};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
	using Self = ListIterator<T>;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;


	/* DESCRIPTION  operator*() */
	T& operator*()  const {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}
		return this->node->value;
	} //call *it

	/* DESCRIPTION  operator->() */
	T* operator->() const {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}
		return  &this->node->value;
	}  //call it->method() or it->member


	/* PREINCREMENT, call: ++it, advances one element forward */
	ListIterator<T>& operator++() {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}
		/*ListIterator li{};
		li.node = this->node;
		return li;*/
		return this->next();
	}

	/* POSTINCREMENT (signature distinguishes the iterators),
					  call:  it++, advances one element forward*/
	ListIterator<T> operator++(int) {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}
		/*ListIterator li{};
		li.node = this->node;
		return li;*/
		return this->next();
	}

	/* compares two ListIterators */
	bool operator==(ListIterator<T> const& x) const {
		// Iterators should be the same if they refer to the same node
		
		if (this->node != x.node) return false;
		return true;
	} // call it: == it
	
	/* returns the opposite of operator== */
	bool operator!=(ListIterator<T> const& x) const {
		return this->operator==(x);
	} // call it: != it

	/* Advances Iterator */
	ListIterator<T> next() const {
		if (nullptr != node) {
			return ListIterator{ node->next };
		}
		else {
			return ListIterator{ nullptr };
		}
	}


	ListNode <T>* node = nullptr;
};


template <typename T>
class List {
public:

	//friend declarations for testing the members   
	template <typename TEST_TYPE>
	friend size_t get_size(List<TEST_TYPE> const& list_to_test);
	template <typename TEST_TYPE>
	friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
	template <typename TEST_TYPE>
	friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

	using value_type = T;
	using pointer = T*;
	using const_pointer = T const*;
	using reference = T&;
	using const_reference = T const&;
	using iterator = ListIterator<T>;

	// not fully implemented yet

	/* standard constructor */
	//List() {}
	List() = default;

	/* copy constructor */
	List(List const& list) {
		ListNode<T>* temp = list.first_;
		for (; temp->next; temp = temp->next) {
			this->push_back(temp->value);
		}
		this->push_back(temp->value);
	}

	// test and implement:
	// TODO: Move-Konstruktor (Aufgabe 3.9)

	//TODO: Initializer-List Konstruktor (3.10 - Teil 1)
	/* ... */
	// test and implement:
	List(std::initializer_list<T> ini_list) {
		//not implemented yet
	}

	/* unifying assignment operator = */
	List& operator= (List const& list) {
		this->clear();
		ListNode<T>* temp = list.first_;
		for (; temp->next; temp = temp->next) {
			this->push_back(temp->value);
		}
		this->push_back(temp->value);
		return *this;
	}

	/* ... */
	bool operator==(List const& rhs) const
	{
		if (this->size_ != rhs.size_) return false;
		ListNode<T>* a = this->first_;
		ListNode<T>* b = rhs.first_;
		while (!compare(a, this->last_)) {
			if (a->value != b->value) return false;
			a = a->next;
			b = b->next;
		}
		if (a->value != b->value) return false;
		return true;
	}

	bool operator!=(List const& rhs) const
	{
		return !(this->operator==(rhs));
	}

	/* deletes list */
	~List() {
		this->clear();
		//TODO: delete list itself
	} //can not really be tested

	/* returns iterator begin */
	ListIterator<T> begin() {
		return ListIterator<T>{this->first_};
	}

	/* returns iterator begin */
	ListIterator<T> end() {
		return ListIterator<T>{nullptr};
	}

	/* removes all elements of the list */
	// test and implement:
	void clear() {
		while (!this->empty()) {
			this->pop_front();
		}
	}

	/* ... */
	//TODO: member function insert (Aufgabe 3.13)
	ListIterator<T>* insert(ListIterator<T> const& pos, T val) { 
		ListNode<T>* insert = new ListNode{ val, pos.node, pos.node.next };
		pos.node->next->prev = insert;
		pos.node->next = insert;
		ListIterator<T> li{};
		li.node = insert;
		//size_++;
		return &li;
	}

	/* ... */
	//TODO: member function erase (Aufgabe 3.14)

	/* reverses the elements */
	void reverse() {
		if (this->size_ < 2) return;
		
		ListNode<T>* lb = this->first_;
		ListNode<T>* rb = this->last_;
		while (!compare(lb, rb) && !(lb->next == rb)) {
			lb->swap(rb);
			lb = lb->next;
			rb = rb->prev;
		}
		if (lb->next == rb) {
			lb->swap(rb);
		}
	}

	/* adds element to the front of the list */
	void push_front(T const& element) {
		if (this->empty()) {
			this->first_ = new ListNode<T>{ element, nullptr, nullptr };
			this->last_ = this->first_;
		}
		else {
			this->first_->prev = new ListNode<T>{ element, nullptr, this->first_ };
			this->first_ = this->first_->prev;
		}
		this->size_++;
	}

	/* adds element to the back of the list */
	void push_back(T const& element) {
		if (this->empty()) {
			this->first_ = new ListNode<T>{ element, nullptr, nullptr };
			this->last_ = this->first_;
		}
		else {
			this->last_->next = new ListNode<T>{ element, this->last_, nullptr };
			this->last_ = this->last_->next;
		}
		this->size_++;
	}

	/* removes first element */
	void pop_front() {
		if (empty()) {
			throw "List is empty";
		}
		else {
			ListNode<T>* front = this->first_;
			if (this->size_ == 1) {
				this->first_ = nullptr;
				this->last_ = nullptr;
			}
			else {
				front->next->prev = nullptr;
				this->first_ = front->next;
				front->next = nullptr;
			}
			//TODO: delete front
			this->size_--;
		}
	}

	/* removes last element */
	void pop_back() {
		if (empty()) {
			throw "List is empty";
		}
		else {
			ListNode<T>* back = this->last_;
			if (this->size_ == 1) {
				this->first_ = nullptr;
				this->last_ = nullptr;
			}
			else {
				back->prev->next = nullptr;
				this->last_ = back->prev;
				back->prev = nullptr;
			}
			//TODO: delete back
			this->size_--;
		}
	}

	/* returns reference to the value of the first element */
	T& front() {
		if (empty()) {
			throw "List is empty";
		}
		return this->first_->value;
	}

	/* returns reference to the value of the last element */
	T& back() {
		if (empty()) {
			throw "List is empty";
		}
		return this->last_->value;
	}

	/* returns true if the list is empty */
	bool empty() const {
		return !this->first_;
	};


	/* returns size of the list */
	std::size_t size() const {
		return this->size_;
	};

	ListNode<T>* b() {
		return this->first_;
	}

	ListNode<T>* e() {
		return this->first_;
	}

	// list members
private:
	std::size_t size_ = 0;
	ListNode<T>* first_ = nullptr;
	ListNode<T>* last_ = nullptr;
};

/* returns a new list with the reversed order of the param list*/
template <typename T>
List<T>* reverse(List<T>* const list) {
	List<T>* list2 = new List<T>{list};
	list2->reverse();
	return list2;
}

/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)

template <typename T>
bool compare(ListNode<T>* p1, ListNode<T>* p2) {
	if (p1->value != p2->value) return false;
	else if (p1->prev != p2->prev) return false;
	else if (p1->next != p2->next) return false;
	else return true;
}

#endif // # define BUW_LIST_HPP
