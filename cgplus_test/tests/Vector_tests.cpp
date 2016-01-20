#include "cgplus/type/Vector.h"
#include "gtest/gtest.h"
#include <string>
#include <memory>
#include <iostream>


class VectorTest : public ::testing::Test{
protected:
	Vector<int> int_vector;
	Vector<std::string> string_vector;
};

TEST_F(VectorTest, test_vector_add_back){
	int_vector.add_back(10);
	int_vector.add_back(20);
	int_vector.add_back(30);
	ASSERT_EQ(10, int_vector[0]);
	ASSERT_EQ(20, int_vector[1]);
	ASSERT_EQ(30, int_vector[2]);

	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Peace");
	EXPECT_STREQ("Hello", string_vector[0].c_str());
	EXPECT_STREQ("World", string_vector[1].c_str());
	EXPECT_STREQ("Peace", string_vector[2].c_str());
}

TEST_F(VectorTest, test_vector_add_front){
	int_vector.add_front(10);
	int_vector.add_front(20);
	int_vector.add_front(30);
	ASSERT_EQ(30, int_vector[0]);
	ASSERT_EQ(20, int_vector[1]);
	ASSERT_EQ(10, int_vector[2]);

	string_vector.add_front("Hello");
	string_vector.add_front("World");
	string_vector.add_front("Peace");
	EXPECT_STREQ("Peace", string_vector[0].c_str());
	EXPECT_STREQ("World", string_vector[1].c_str());
	EXPECT_STREQ("Hello", string_vector[2].c_str());
}

TEST_F(VectorTest, test_vector_get){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	ASSERT_STREQ("World", string_vector.get(1).c_str());
}

TEST_F(VectorTest, test_vector_get_error_over){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	ASSERT_THROW(string_vector.get(3), std::length_error);
}

TEST_F(VectorTest, test_vector_get_error_negative){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	ASSERT_THROW(string_vector.get(-1), std::length_error);
}

TEST_F(VectorTest, test_vector_get_size){
	int_vector.add_back(10);
	ASSERT_EQ(1, int_vector.get_size());
	int_vector.add_back(20);
	ASSERT_EQ(2, int_vector.get_size());
	int_vector.add_back(30);
	ASSERT_EQ(3, int_vector.get_size());
}

TEST_F(VectorTest, test_vector_pop_back){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Peace");
	string_vector.pop_back();
	EXPECT_STREQ("World", string_vector[string_vector.get_size() - 1].c_str());
	string_vector.pop_back();
	EXPECT_STREQ("Hello", string_vector[string_vector.get_size() - 1].c_str());
}

TEST_F(VectorTest, test_vector_pop_front){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Peace");
	string_vector.pop_front();
	EXPECT_STREQ("World", string_vector[0].c_str());
	string_vector.pop_front();
	EXPECT_STREQ("Peace", string_vector[0].c_str());
}

TEST_F(VectorTest, test_vector_remove_comparator){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	string_vector.remove("World", [](std::string a, std::string b) -> bool{
		return (a.compare(b) == 0);
	});
	ASSERT_STREQ("Foo", string_vector[1].c_str());
}

TEST_F(VectorTest, test_vector_remove_error){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	ASSERT_THROW(
		string_vector.remove("Bar", [](std::string a, std::string b) -> bool{
		return (a.compare(b) == 0);
	}), std::runtime_error);
}

TEST_F(VectorTest, test_vector_insert_middle){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	string_vector.insert("Bar", 2);
	ASSERT_STREQ("Bar", string_vector[2].c_str());
}

TEST_F(VectorTest, test_vector_insert_end){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	string_vector.insert("Bar", 3);
	ASSERT_STREQ("Bar", string_vector[3].c_str());
}

TEST_F(VectorTest, test_vector_insert_length_error){
	string_vector.add_back("Hello");
	string_vector.add_back("World");
	string_vector.add_back("Foo");
	ASSERT_THROW(string_vector.insert("Bar", 4); , std::length_error);
}