#pragma once
#ifndef IDLIST_H
#define IDLIST_H

#include "IDHandler.h"
#include <vector>

template<class T>
class idlist
{
private:
	IDHandler ids;
	std::vector<typename T> container;
public:
	idlist();
	idlist(const size_t size);

	void push(typename T element);
	void remove(const size_t& id);
	void remove(std::list<size_t>::const_iterator it);
	void resize(const size_t size);
	const size_t& capacity();
	void clear();
	bool getElement(const size_t& id, typename T& element);
	bool empty();
	const size_t& peekNextID();

	std::list<size_t>::const_iterator begin() const;
	std::list<size_t>::const_iterator end() const;
	std::list<size_t>::const_reverse_iterator rbegin() const;
	std::list<size_t>::const_reverse_iterator rend() const;

	T& operator[](std::list<size_t>::const_iterator it);
};

template<class T>
const size_t& idlist<T>::peekNextID()
{
	return this->ids.peekNextID();
}

template<class T>
inline idlist<T>::idlist() : ids()
{
}

template<class T>
inline idlist<T>::idlist(const size_t size) : ids()
{
	this->resize(size);
}

template<class T>
inline void idlist<T>::push(typename T element)
{
	size_t id = this->ids.getNewID();

	if (id == this->container.size()) {
		this->container.push_back(element);
	}
	else {
		this->container[id] = element;
	}
}

template<class T>
inline void idlist<T>::remove(const size_t& id)
{
	this->ids.remove(id);
}

template<class T>
inline void idlist<T>::remove(std::list<size_t>::const_iterator it)
{
	this->ids.remove(it);
}

template<class T>
inline void idlist<T>::resize(const size_t size)
{
	if (size > this->container.size()) {
		this->ids.resize(size);
		this->container.resize(size);
	}
}

template<class T>
inline const size_t & idlist<T>::capacity()
{
	return this->container.capacity();
}

template<class T>
inline void idlist<T>::clear()
{
	this->container.clear();
	this->ids.clear();
}

template<class T>
inline bool idlist<T>::getElement(const size_t& id, typename T& element)
{
	bool elementFound = false;
	std::list<size_t>::const_iterator it;
	if (ids.idInUse(id)) {
		elementFound = true;
		element = this->container[*it];
	}
	return elementFound;
}

template<class T>
inline bool idlist<T>::empty()
{
	return this->ids.empty();
}

template<class T>
inline std::list<size_t>::const_iterator idlist<T>::begin() const
{
	return this->ids.begin();
}

template<class T>
inline std::list<size_t>::const_iterator idlist<T>::end() const
{
	return this->ids.end();
}

template<class T>
inline std::list<size_t>::const_reverse_iterator idlist<T>::rbegin() const
{
	return this->rbegin();
}

template<class T>
inline std::list<size_t>::const_reverse_iterator idlist<T>::rend() const
{
	return this->ids.rend();
}

template<class T>
inline T& idlist<T>::operator[](std::list<size_t>::const_iterator it)
{
	return this->container[*it];
}

#endif
