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

		//TODO: remaining implementation of derefenciation of 
		//      iterator using operator* (Aufgabe 3.12 - Teil 1)

	} //call *it

	/* DESCRIPTION  operator->() */
	T* operator->() const {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}

		//TODO: remaining implementation of derefenciation of 
		//      iterator using operator-> (Aufgabe 3.12 - Teil 2)
	}  //call it->method() or it->member


	/* PREINCREMENT, call: ++it, advances one element forward */
	ListIterator<T>& operator++() {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}

		//TODO: Implement Postincrement-Operation for Iterator
		//      (Aufgabe 3.12 - Teil 3)

	}

	/* POSTINCREMENT (signature distinguishes the iterators),
					  call:  it++, advances one element forward*/
	ListIterator<T> operator++(int) {
		if (nullptr == node) {
			throw "Iterator does not point to valid node";
		}

		//TODO: Implement Postincrement-Operation for Iterator
		//      (Aufgabe 3.12 - Teil 4)

	}


	/* ... */
	bool operator==(ListIterator<T> const& x) const {
		//TODO: Implement Equality-Operation for Iterator
		//      (Aufgabe 3.12 - Teil 5)
		// Iterators should be the same if they refer to the same node
		return false;
	} // call it: == it

	/* ... */
	bool operator!=(ListIterator<T> const& x) const {
		//TODO: Implement Inequality-Operation for Iterator  
		//      (Aufgabe 3.12 - Teil 6)
		// Reuse operator==
		return false;
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

	// test and implement:
	//TODO: Copy-Konstruktor using Deep-Copy semantics (Aufgabe 3.5)

	// test and implement:
	// TODO: Move-Konstruktor (Aufgabe 3.9)

	//TODO: Initializer-List Konstruktor (3.10 - Teil 1)
	/* ... */
	// test and implement:
	List(std::initializer_list<T> ini_list) {
		//not implemented yet
	}

	/* ... */
	// test and implement:
	//TODO: (unifying) Assignment operator (Aufgabe 3.6)

	/* ... */
	// test and implement:

	bool operator==(List const& rhs) const
	{
		//TODO: operator== (Aufgabe 3.8)
	}

	bool operator!=(List const& rhs) const
	{
		//TODO: operator!= (Aufgabe 3.8)
		// make use of operator==
	}

	/* ... */
	~List() {
		//TODO: Implement via clear-Method (Aufgabe 3.4)
	} //can not really be tested

	/* ... */
	ListIterator<T> begin() {
		//TODO: begin-Method returning an Iterator to the 
		//      first element in the List (Aufgabe 3.11)
		return {};
	}

	/* ... */
	ListIterator<T> end() {
		//TODO: end-Method returning an Iterator to element after (!) 
		//      the last element in the List (Aufgabe 3.11)
		return {};
	}

	/* ... */
	// test and implement:
	//TODO: clear()-Method (Aufgabe 3.4)


	/* ... */
	//TODO: member function insert (Aufgabe 3.13)

	/* ... */
	//TODO: member function insert (Aufgabe 3.14)

	/* ... */

	//TODO: member function reverse (Aufgabe 3.7 - Teil 1)


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
		/*
		if (this->empty()) {
			return 0;
		}
		ListNode<T>* temp = this->first_;
		std::size_t count = 1;
		while (temp != this->last_) {
			temp = temp->next;
			count++;
		}
		if (!temp->next) {
			std::cout << "FEHLER bei size()";
			return count;
		}
		temp = temp->next;
		count++;
		return count;*/
		return this->size_;
	};


	// list members
private:
	std::size_t size_ = 0;
	ListNode<T>* first_ = nullptr;
	ListNode<T>* last_ = nullptr;
};

/* ... */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)

/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP
