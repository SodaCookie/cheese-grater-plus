#pragma once
#ifndef _CG_NODE_H
#define _CG_NODE_H

#include <memory>
#include <iostream>

template <typename T>
class Node
{
	public:
		Node(T value, std::shared_ptr<Node<T>> next, std::shared_ptr<Node<T>> prev);
		Node(T value, std::shared_ptr<Node<T>> next);
		Node(T value);
		Node();
		~Node();

		// Methods
		T& get(void);
		void set(T value);
		void set_next(std::shared_ptr<Node<T>> next);
		void set_prev(std::shared_ptr<Node<T>> prev);
		std::shared_ptr<Node<T>> next(void);
		std::shared_ptr<Node<T>> prev(void);

	private:
		T _value;
		std::shared_ptr<Node<T>> _next;
		std::shared_ptr<Node<T>> _prev;
};

template <typename T>
Node<T>::Node(T value, std::shared_ptr<Node<T>> next, std::shared_ptr<Node<T>> prev) : _value(value), _next(next), _prev(prev){
}

template <typename T>
Node<T>::Node(T value, std::shared_ptr<Node<T>> next) : _value(value), _next(next){
}

template <typename T>
Node<T>::Node(T value) : _value(value){
	_next = std::shared_ptr<Node<T>>();
}

template <typename T>
Node<T>::Node(){
	_next = std::shared_ptr<Node<T>>();
}


template <typename T>
Node<T>::~Node()
{
}

template <typename T>
T& Node<T>::get(void){
	return _value;
}

template <typename T>
void Node<T>::set(T value){
	_value = value;
}

template <typename T>
void Node<T>::set_next(std::shared_ptr<Node<T>> next){
	_next = next;
}

template <typename T>
void Node<T>::set_prev(std::shared_ptr<Node<T>> prev){
	_prev = prev;
}

template <typename T>
std::shared_ptr<Node<T>> Node<T>::prev(void){
	return _prev;
}

template <typename T>
std::shared_ptr<Node<T>> Node<T>::next(void){
	return _next;
}

#endif
