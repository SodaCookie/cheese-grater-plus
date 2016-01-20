#include "cgplus/type/List.h"
#include "gtest/gtest.h"
#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <typeinfo>

class ListTest : public ::testing::Test{
protected:
	List<int> list;
	List<std::string> slist;
};

TEST_F(ListTest, test_list_get_head){
	list.add_back(20);
	list.add_back(10);
	EXPECT_EQ(20, list.get_head()->get());
}

TEST_F(ListTest, test_list_get_tail){
	list.add_back(20);
	list.add_back(10);
	EXPECT_EQ(10, list.get_tail()->get());
}

TEST_F(ListTest, test_list_add_back){
	list.add_back(20);
	list.add_back(10);
	EXPECT_EQ(10, list.get_tail()->get());
}

TEST_F(ListTest, test_list_add_front){
	list.add_front(10);
	list.add_front(20);
	EXPECT_EQ(20, list.get_head()->get());
}

TEST_F(ListTest, test_list_remove_no_comparator){
	list.add_back(10);
	list.add_back(20);
	list.add_back(30);
	list.remove(20);
	EXPECT_EQ(30, list.get_head()->next()->get());
}

TEST_F(ListTest, test_list_remove_comparator){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	slist.remove("World", [](std::string a, std::string b) -> bool{
		return (a.compare(b) == 0);
	});
	ASSERT_STREQ("Foo", slist.get_head()->next()->get().c_str());
}

TEST_F(ListTest, test_list_remove_error){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_THROW(
		slist.remove("Bar", [](std::string a, std::string b) -> bool{
		return (a.compare(b) == 0);
	}), std::runtime_error);
}

TEST_F(ListTest, test_list_get){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_STREQ("World", slist.get(1).c_str());
}

TEST_F(ListTest, test_list_get_error_over){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_THROW(slist.get(3), std::length_error);
}

TEST_F(ListTest, test_list_get_error_negative){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_THROW(slist.get(-1), std::length_error);
}

TEST_F(ListTest, test_list_get_subscript){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_STREQ("World", slist[1].c_str());
}

TEST_F(ListTest, test_list_set_subscript){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	slist[1] = "Bar";
	ASSERT_STREQ("Bar", slist[1].c_str());
}

TEST_F(ListTest, test_list_insert_middle){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	slist.insert("Bar", 2);
	ASSERT_STREQ("Bar", slist[2].c_str());
}

TEST_F(ListTest, test_list_insert_end){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	slist.insert("Bar", 3);
	ASSERT_STREQ("Bar", slist[3].c_str());
}

TEST_F(ListTest, test_list_insert_length_error){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_THROW(slist.insert("Bar", 4); , std::length_error);
}

TEST_F(ListTest, test_list_pop_back){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_STREQ("Foo", slist.pop_back().c_str());
}

TEST_F(ListTest, test_list_pop_front){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	ASSERT_STREQ("Hello", slist.pop_front().c_str());
}

TEST_F(ListTest, test_list_size){
	slist.add_back("Hello");
	slist.add_back("World");
	slist.add_back("Foo");
	EXPECT_EQ(3, slist.get_size());
	slist.pop_back();
	EXPECT_EQ(2, slist.get_size());
	slist.insert("Bar", 2);
	EXPECT_EQ(3, slist.get_size());
	slist.remove("World", [](std::string a, std::string b) -> bool{
		return (a.compare(b) == 0);
	});
	EXPECT_EQ(2, slist.get_size());
}