#include <initializer_list>

#include "seq.hpp"

/*
 * An Array ADT.
 * 
 * Size is fixed and is one of the template argument.
 * 
 * Implement most interface of std::array.
 */

template<typename var, size_t size>
class Array : Sequence<var> {
public:
	class ArrayIterator : Iterator {
		SeqIterator<var>& operator++() override;
		SeqIterator<var>& operator--() override;
	}
	Array();
	Array(std::initializer_list<var> list);
	Array(var val);

	var* data();

	void fill(var val);

private:
	size_t _size;
	var* _data;
}

// Implementations of Array Iterator.
template<typename var, size_t size>
template<typename v = var>
SeqIterator<v>& Array<var, size>::operator++() {
	
}

// Implementations of Array.
// Ctor.
template<typename var, size_t size>
Array<var, size>::Array() {
	_size = size;
	_data = new var[size];
}

// e.g.
// Array<int, 10> arr = {1, 2, 3, 4, 5}; -> {1, 2, 3, 4, 5, 0, 0, 0, 0, 0}
template<typename var, size_t size>
Array<var, size>::Array(std::initializer_list<var> list) : Array() {
	auto it_1 = this->begin();
	auto it_2 = list.begin();

	while (it_1 != this->end() && it_2 != list.end()) {
		*it_1 = *it_2;
		++it_1;
		++it_2;
	}

	if (it_2 == list.end()) {
		while (it_1 != this->end()) {
			*it_1 = var();
			++it_1;
		}
	}
}

template<typename var, size_t size>
Array<var, size>::Array(var val) : Array() {
	this->fill(val);
}

template<typename var, size_t size>
void Array<var, size>::fill(var val) {
	for (auto it = this->begin(); it != this->end(); ++it) {
		*it = val;
	}
}

