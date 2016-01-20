#include "cgplus/type/Node.h"
#include "gtest/gtest.h"
#include <memory>
#include <iostream>
#include <typeinfo>

class NodeTest : public ::testing::Test{
	protected:
		std::shared_ptr<Node<int>> n2 = std::make_shared<Node<int>>(Node<int>(15));
		std::shared_ptr<Node<int>> n1 = std::make_shared<Node<int>>(Node<int>(10, n2));
		std::shared_ptr<Node<int>> n0 = std::make_shared<Node<int>>(Node<int>(5, n1));
};

TEST_F(NodeTest, test_node_construtor_value){
	std::shared_ptr<Node<int>> n = std::make_shared<Node<int>>(Node<int>(10));
	EXPECT_EQ(10, n->get());
}

TEST_F(NodeTest, test_node_construtor_value_next){
	std::shared_ptr<Node<int>> t = std::make_shared<Node<int>>(Node<int>(10));
	std::shared_ptr<Node<int>> t2 = std::make_shared<Node<int>>(Node<int>(20, t));
	EXPECT_EQ(10, t2->next()->get());
}

TEST_F(NodeTest, test_node_construtor_value_next_prev){
	std::shared_ptr<Node<int>> t = std::make_shared<Node<int>>(Node<int>(10));
	std::shared_ptr<Node<int>> t2 = std::make_shared<Node<int>>(Node<int>(20, t));
	std::shared_ptr<Node<int>> t3 = std::make_shared<Node<int>>(Node<int>(30, t, t2));
	EXPECT_EQ(10, t3->next()->get());
	EXPECT_EQ(20, t3->prev()->get());
}

TEST_F(NodeTest, test_type_check_node){
	Node<int> node {};
	EXPECT_STREQ(typeid(node.get()).name(), "int");
}

TEST_F(NodeTest, test_get_node){
	EXPECT_EQ(5, n0->get());
}

TEST_F(NodeTest, test_next_node){
	EXPECT_EQ(10, n0->next()->get());
}

TEST_F(NodeTest, test_set_node){
	n0->set(100);
	EXPECT_EQ(100, n0->get());
}

TEST_F(NodeTest, test_set_next_node){
	n0->set_next(n2);
	EXPECT_EQ(15, n0->next()->get());
}
