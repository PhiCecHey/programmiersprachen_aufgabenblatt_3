#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) { return list_to_test.size_; }

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) { return list_to_test.first_; }

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) { return list_to_test.last_; }


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test case definitions for 

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//test case for clear()
TEST_CASE("clears list", "[list_clear]") {
	List<int> list{};
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);
	list.clear();
	bool empty = list.empty();
	int size = list.size();

	REQUIRE(empty == true);
	REQUIRE(size == 0);
	REQUIRE(nullptr == get_first_pointer(list));
	REQUIRE(nullptr == get_last_pointer(list));
}

TEST_CASE("copy construct list", "[list{list}]") {
	List<int> list{};
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);
	List<int> list2{ list };

	REQUIRE(get_first_pointer(list2)->value == 0);
	REQUIRE(get_first_pointer(list2)->next->value == 1);
	REQUIRE(get_last_pointer(list2)->value == 2);
}

TEST_CASE("unifying assignment operator =", "[operator=]") {
	List<int> list{};
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);
	List<int> list2 = list;

	REQUIRE(get_first_pointer(list2)->value == 0);
	REQUIRE(get_first_pointer(list2)->next->value == 1);
	REQUIRE(get_last_pointer(list2)->value == 2);
}

TEST_CASE("reverse list", "[list_reverse]") {
	List<int> list{};
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);
	list.reverse();

	REQUIRE(get_first_pointer(list)->value == 2);
	REQUIRE(get_first_pointer(list)->next->value == 1);
	REQUIRE(get_last_pointer(list)->value == 0);

	List<int> list3{};
	list.push_back(3);
	list.push_back(4);
	list.push_front(2);
	list.reverse();
	List<int> list4 = list;

	REQUIRE(get_first_pointer(list4)->value == 4);
	REQUIRE(get_first_pointer(list4)->next->value == 3);
	REQUIRE(get_last_pointer(list4)->value == 2);
}

TEST_CASE("list operator== and !=", "[list_== and !=]") {
	List<int> list{};
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);
	List<int> list3{};
	list3.push_back(-1);
	list3.push_back(-2);
	list3.push_back(-3);
	List<int> list2{ list };
	bool a = list == list2;
	bool b = list == list;
	bool c = list == list3;
	REQUIRE(a == true);
	REQUIRE(b == true);
	REQUIRE(c == false);
	a = list != list2;
	b = list != list;
	c = list != list3;
	REQUIRE(a == false);
	REQUIRE(b == false);
	REQUIRE(c == true);
}

//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
/*#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"*/


int main(int argc, char* argv[])
{

	List<int> list{};
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);
	/*
	list.pop_front();
	list.pop_front();
	list.pop_front();
	list.pop_front();

	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.pop_back();

	list.clear();
	
	List<int> list2{ list };
	list2.push_back(3);
	list2 = list;
	
	list.reverse();
	List<int> list3{};
	list3.push_back(-1);
	list3.push_back(-2);
	list3.push_back(-3);
	List<int> list4{list};
	bool comp = list == list4;
	comp = list == list;
	comp = list == list3;

	auto b = list.begin();
	auto e = list.end();
	bool c = b == e;
	c = b == list.begin();*/

	ListIterator<int> li = list.begin();
	//list.insert(li, 5);

	bool empty = list.empty();
	int size = list.size();


	int a = 5;

	return Catch::Session().run(argc, argv);
}




