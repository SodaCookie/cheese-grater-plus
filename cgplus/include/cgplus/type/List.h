#pragma once
#ifndef _CG_LIST_H
#define _CG_LIST_H

#include <memory>
#include <stdexcept>
#include "cgplus/type/Node.h"

template <typename T>
class List{
	public:
		List();
		void add_back(T value);
		void add_front(T value);
		T pop_back(void);
		T pop_front(void);
		void remove(T value);
		void remove(T value, bool (comparator)(T, T));
		void insert(T value, int index);

		T& get(int index);
		int get_size();
		std::shared_ptr<Node<T>> get_head(void);
		std::shared_ptr<Node<T>> get_tail(void);

		T& operator[] (int index);

	private:
		std::shared_ptr<Node<T>> head;
		std::shared_ptr<Node<T>> tail;
		int size;
};

template <typename T>
List<T>::List(){
	size = 0;
}

template <typename T>
void List<T>::add_back(T value){
	std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node<T>(value));
	if (size == 0){
		head = node;
		tail = node;
	}
	else{
		tail->set_next(node);
		node->set_prev(tail);
		tail = node;
	}
	size++;
}

template <typename T>
void List<T>::add_front(T value){
	std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node<T>(value));
	if (size == 0){
		head = node;
		tail = node;
	}
	else{
		head->set_prev(node);
		node->set_next(head);
		head = node;
	}
	size++;
}

template <typename T>
T List<T>::pop_back(void){
	if (size == 0){
		throw std::length_error("List is empty");
	}
	std::shared_ptr<Node<T>> node = tail;
	tail = tail->prev();
	tail->next().reset();
	node->prev().reset();
	size--;
	return node->get();
}

template <typename T>
T List<T>::pop_front(void){
	if (size == 0){
		throw std::length_error("List is empty");
	}
	std::shared_ptr<Node<T>> node = head;
	head = head->next();
	head->prev().reset();
	node->next().reset();
	size--;
	return node->get();
}

template <typename T>
void List<T>::remove(T value, bool (comparator)(T, T)){
	std::shared_ptr<Node<T>> node = head;
	std::shared_ptr<Node<T>> tmp;
	while (node){
		if (comparator(node->get(), value)){
			break;
		}
		node = node->next();
	}
	if (node){
		tmp = node->prev();
		tmp->set_next(node->next());
		node->next()->set_prev(tmp);
		size--;
	}
	else{
		throw std::runtime_error("Value not found.");
	}
}

template <typename T>
void List<T>::remove(T value){
	std::shared_ptr<Node<T>> node = head;
	std::shared_ptr<Node<T>> tmp;
	while (node){
		if (node->get() == value){
			break;
		}
		node = node->next();
	}
	if (node){
		tmp = node->prev();
		tmp->set_next(node->next());
		node->next()->set_prev(tmp);
		size--;
	}
	else{
		throw std::runtime_error("Value not found.");
	}
}

template <typename T>
void List<T>::insert(T value, int index){
	if (index > size || index < 0){
		throw std::length_error("Given index is out of range");
	}
	else if (index == size){
		this->add_back(value);
	}
	else{
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node<T>(value));
		std::shared_ptr<Node<T>> cur = head;
		std::shared_ptr<Node<T>> tmp;
		while (index > 0){
			cur = cur->next();
			index--;
		}
		tmp = cur->prev();
		tmp->set_next(node);
		cur->set_prev(node);
		node->set_next(cur);
		node->set_prev(tmp);
		size++;
	}
}

template <typename T>
T& List<T>::get(int index){
	if (index >= size || index < 0){
		throw std::length_error("Given index is out of range");
	}
	std::shared_ptr<Node<T>> cur = head;
	while (index > 0){
		cur = cur->next();
		index--;
	}
	return cur->get();
}

template <typename T>
int List<T>::get_size(void){
	return size;
}

template <typename T>
std::shared_ptr<Node<T>> List<T>::get_head(void){
	return head;
}

template <typename T>
std::shared_ptr<Node<T>> List<T>::get_tail(void){
	return tail;
}

template <typename T>
T& List<T>::operator[] (int index){
	return this->get(index);
}

#endif