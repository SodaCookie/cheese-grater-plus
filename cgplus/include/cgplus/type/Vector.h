#pragma once
#ifndef CG_VECTOR_H
#define CG_VECTOR_H

#include <iostream> // For printing
#include <memory> // For std::allocator
#include <stdexcept> // For runtime_exception
#include <algorithm> // For std::copy

template <typename T>
class Vector{
	public:
		Vector(int capacity = 0);
		void add_back(T value);
		void add_front(T value);
		void pop_back();
		void pop_front();
		void remove(T value);
		void remove(T value, bool (comparator)(T, T));
		void insert(T value, int index);

		T& get(int index);
		int get_size();
		int get_capacity();

		T& operator[] (int index);

	private:
		void allocate(int capacity);

		T *array;
		std::allocator<T> alloc;
		int size_;
		int capacity_;
};

template <typename T>
Vector<T>::Vector(int capacity) : capacity_(capacity), size_(0){
	if (capacity > 0){
		this->allocate(capacity);
	}
}

template <typename T>
void Vector<T>::allocate(int capacity){
	/**
	Allocates enough memory to hold "capacity" number of full
	objects T using the memory libraries default allocator.
	Then it will transfer and remove the previous allocation
	Everything is internally set: mutates array, capacity_*/
	T *new_array = new T[capacity];
	std::copy(array, array + capacity_, new_array);
	delete[] array;
    array = new_array;
	capacity_ = capacity;
}

template <typename T>
void Vector<T>::add_back(T value){
	/**
	Adds value to the back of the array and increasing size by 1.
	If size will be greater than capacity the vector will allocate
	twice the original capactity except for the vary start.
	*/
	if (size_ + 1 > capacity_){
		allocate(capacity_ ? capacity_ * 2 : 1);
	}
	array[size_] = value;
	size_++;
}

template <typename T>
void Vector<T>::add_front(T value){
	/**
	Adds value to the front of the array and increasing size by 1.
	If size will be greater than capacity the vector will allocate
	twice the original capactity except for the vary start.
	*/
	if (size_ + 1 > capacity_){
		allocate(capacity_ ? capacity_ * 2 : 1);
	}
	//std::copy(array, array + capacity_, array + 1);
	for (int i = size_; i > 0; i--){
		array[i] = array[i - 1];
	}
	array[0] = value;
	size_++;
}

template <typename T>
void Vector<T>::pop_back(){
	/**
	Removes the very last element. Destroying the element
	*/
	size_--;
	alloc.destroy(array + size_);
}

template <typename T>
void Vector<T>::pop_front(){
	/**
	Removes the very first element. Destroying the element.
	This also shift all elements by one and is not constant
	time.
	*/
	size_--;
	alloc.destroy(array);
	std::copy(array + 1, array + 1 + size_, array);
}

template <typename T>
void Vector<T>::remove(T value){
	/**
	Removes the first instance of value using the default
	boolean equals. This destroys the value. Value must have
	equality operator for its type.
	*/
	int cur = 0;
	while (cur < size_ || !(array[cur] == value)){
		cur++;
	}
	if (cur == size_){
		throw std::runtime_error("Value not found.");
	}
	alloc.destroy(array + cur);
	std::copy(array + cur + 1, array + size_, array + cur);
	size_--;
}

template <typename T>
void Vector<T>::remove(T value, bool (comparator)(T, T)){
	/**
	Removes the first instance of value using the given
	comparator. This destroys the value. Value must have
	equality operator for its type.
	*/
	int cur = 0;
	while (cur < size_ && !(comparator(value, array[cur]))){
		cur++;
	}
	if (cur == size_){
		throw std::runtime_error("Value not found.");
	}
	alloc.destroy(array + cur);
	std::copy(array + cur + 1, array + size_, array + cur);
	size_--;
}

template <typename T>
void Vector<T>::insert(T value, int index){
	/**
	Inserts the value at value and shifts all values down from
	that index.
	*/
	if (index > size_ || index < 0){
		throw std::length_error("Given index is out of range");
	}
	if (size_ + 1 > capacity_){
		allocate(capacity_ ? capacity_ * 2 : 1)	;
	}
	std::copy(array + index, array + size_, array + index + 1);
	array[index] = value;
	size_++;
}

template <typename T>
T& Vector<T>::get(int index){
	/**
	Returns a reference directly from the array.
	*/
	if (index >= size_ || index < 0){
		throw std::length_error("Given index is out of range");
	}
	return array[index];
}

template <typename T>
int Vector<T>::get_size(){
	/**
	Returns the current size of the vector.
	*/
	return size_;
}

template <typename T>
int Vector<T>::get_capacity(){
	/**
	Returns the current capacity of the vector. If additional
	objects are added to the vector then the capacity will
	increase in a non-linear fashion.
	*/
	return capacity_;
}

template <typename T>
T& Vector<T>::operator[] (int index){
	return this->get(index);
}

#endif