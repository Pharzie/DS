/*
 * A Sequence ADT.
 * array: fixed length container with consecutive elements.
 * vector: container with consecutive elements.
 * list: linked nodes with little spatial locality.
 * 
 * Other variants are:
 * stack: FILO seq structure. Usually a singly linked list with a head pointer.
 * queue: FIFO seq structure. Usually a singly linked list with a head pointer and a tail pointer.
 * sorted list: a sorted linked list.
 * 
 * This is a abstract class.
 */

template<typename var>
class Sequence {
public:
	class Iterator {
	public:
		var& operator*();
		var* operator->();
		virtual Iterator& operator++() = 0;
		Iterator operator++(int);
		Iterator& operator+(size_t offset);
		virtual Iterator& operator--() = 0;
		Iterator operator--(int);
		Iterator& operator-(size_t offset);
		int operator-(Iterator const& other) const;
		bool operator==(Iterator const& other) const;
		bool operator!=(Iterator const& other) const;
		bool operator<(Iterator const& other) const;
		bool operator<=(Iterator const& other) const;
		bool operator>(Iterator const& other) const;
		bool operator>=(Iterator const& other) const;

		bool invalid() const;
	private:
		var* it;
	}

	class CIterator {
	public:
		var const& operator*();
		var const* operator->();
		virtual CIterator& operator++() = 0;
		CIterator operator++(int);
		CIterator& operator+(size_t offset);
		virtual CIterator& operator--() = 0;
		CIterator operator--(int);
		CIterator& operator-(size_t offset);
		bool operator==(CIterator const& other);
		bool operator!=(CIterator const& other);
	private:
		var const* it;
	}

	virtual size_t size() const = 0;
	bool empty() const;
	size_t max_size() const;

	virtual var peek() const = 0;
	var first() const;
	var last() const;
	virtual Sequence rest() const = 0;
	Iterator begin();
	CIterator cbegin() const;
	Iterator end();
	CIterator cend() const;
	
	virtual var& operator[](size_t idx);
	virtual var const& at(size_t idx) const;
	CIterator find(var elem) const;

	void push_front(var elem);
	void push_back(var elem);
	virtual void push(var elem) = 0;
	virtual void insert(Iterator pos, var elem) = 0;
	var pop_front();
	var pop_back();
	virtual var pop() = 0;
	virtual var remove(Iterator pos) = 0;

	bool operator==(Sequence const& other) const;
	bool operator!=(Sequence const& other) const;
	
	virtual Sequence& operator=(Sequence const& rhs) = 0;
	virtual Sequence& operator=(Sequence&& rhs) = 0;
	virtual void swap(Sequence const& other) = 0;
};

template<typename var>
using SeqIterator = typename Sequence<var>::Iterator;

template<typename var>
using SeqCIterator = typename Sequence<var>::CIterator;


// Some implementations.
// Sequence::Iterator
// Dereference.
template<typename var>
var& Sequence<var>::Iterator::operator*() {
	return *it;
}

// Get the pointer.
template<typename var>
var* Sequence<var>::Iterator::operator->() {
	return it;
}

// it++
template<typename var>
SeqIterator<var> Sequence<var>::operator++(int) {
	auto temp(*this);
	this->operator++();
	return temp;
}

// it + offset
template<typename var>
SeqIterator<var>& Sequence<var>::operator+(size_t offset) {
	int i = offset;
	while (i--) {
		if ((this->operator++()).invalid()) {
			return *this;
		}
	}
	return *this;
}

// it--
template<typename var>
SeqIterator<var> Sequence<var>::operator--(int) {
	auto temp(*this);
	this->operator--();
	return temp;
}

// it - offset
SeqIterator<var>& Sequence<var>::operator-(size_t offset) {
	int i = offset;
	while (i--) {
		if ((this->operator--()).invalid()) {
			return this;
		}
	}
	return *this;
}

template<typename var>
bool Sequence<var>::operator==(SeqIterator<var> const& other) const {
	return this->operator->() == other->();
}

template<typename var>
bool Sequence<var>::operator!=(SeqIterator<var> const& other) const {
	return !this->operator==(other):
}

template<typename var>
bool Sequence<var>::invalid() const {
	return it == nullptr;
}

// Sequence::CIterator
template<typename var>
var const& Sequence<var>::CIterator::operator*() {
	return *it;
}

template<typename var>
var* Sequence<var>::CIterator::operator->() {
	return it;
}

template<typename var>
SeqCIterator<var> Sequence<var>::operator++(int) {
	auto temp(*this);
	this->operator++();
	return temp;
}

template<typename var>
SeqCIterator<var>& Sequence<var>::operator+(size_t offset) {
	int i = offset;
	while (i--) {
		if ((this->operator++()).invalid()) {
			return *this;
		}
	}
	return *this;
}

template<typename var>
SeqCIterator<var> Sequence<var>::operator--(int) {
	auto temp(*this);
	this->operator--();
	return temp;
}

template<typename var>
SeqCIterator<var>& Sequence<var>::operator-(size_t offset) {
	int i = offset;
	while (i--) {
		if ((this->operator--()).invalid()) {
			return *this;
		}
	}
	return *this;
}

template<typename var>
bool Sequence<var>::operator==(SeqCIterator<var> const& other) const {
	return this->operator->() == other->();
}

template<typename var>
bool Sequence<var>::operator!=(SeqCIterator<var> const& other) const {
	return !this->operator==(other);
}

template<typename var>
bool Sequence<var>::invalid() const {
	return it == nullptr;
}

// Sequence.
template<typename var>
bool Sequence<var>::empty() const {
	return size() == 0;
}

template<typename var>
inline size_t max_size() const {
	return 1 << 20;
}

template<typename var>
var Sequence<var>::first() const {
	return this->at(0);
}

template<typename var>
var Sequence<var>::last() const {
	return this->at(size() - 1);
}

template<typename var>
SeqIterator<var> Sequence<var>::begin() {
	return SeqIterator<var>(&this->operator[0]);
}

template<typename var>
SeqCIterator<var> Sequence<var>::cbegin() const {
	return const_cast<var const&>(*this).begin();
}

template<typename var>
SeqIterator<var> Sequence<var>::end() {
	return SeqIterator<var>(nullptr);
}

template<typename var>
SeqCIterator<var> Sequence<var>::cend() const {
	return SeqCIterator<var>(nullptr);
}


template<typename var>
SeqCIterator<var> Sequence<var>::find(var elem) const {
	for (auto it = this->cbegin(); it != this->cend(); ++it) {
		if (*it == elem) {
			return it;
		}
	}
	return this->cend();
}

template<typename var>
void Sequence<var>::push_front(var elem) {
	this->insert(this->begin(), elem);
}

template<typename var>
void Sequence<var>::push_back(var elem) {
	this->insert(this->end(), elem);
}

template<typename var>
var pop_front() {
	return this->remove(this->begin());
}

template<typename var>
var pop_back() {
	return this->remove(this->begin() - 1);
}

template<typename var>
bool Sequence<var>::operator==(Sequence const& other) const {
	if (this->size() != other.size()) {
		return false;
	}

	auto it_1 = this->cbegin();
	auto it_2 = other.cbegin();

	while (it_1 != this->cend()) {
		if (*it_1 != *it_2) {
			return false;
		}
		++it_1;
		++it_2;
	}
	return true;
}

template<typename var>
bool Sequence<var>::operator!=(Sequence const& other) const {
	return !this->operator==(other);
}
