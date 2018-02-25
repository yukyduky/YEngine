#pragma once
#ifndef IDLIST_H
#define IDLIST_H

#include "IDHandler.h"
#include <vector>

template<class T>
class idlist
{
private:
	IDHandler m_IDs;
	std::vector<typename T> m_Container;
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
	return m_IDs.peekNextID();
}

template<class T>
inline idlist<T>::idlist() : m_IDs()
{
}

template<class T>
inline idlist<T>::idlist(const size_t size) : m_IDs()
{
	this->resize(size);
}

template<class T>
inline void idlist<T>::push(typename T element)
{
	size_t id = m_IDs.getNewID();

	if (id == m_Container.size()) {
		m_Container.push_back(element);
	}
	else {
		m_Container[id] = element;
	}
}

template<class T>
inline void idlist<T>::remove(const size_t& id)
{
	m_IDs.remove(id);
}

template<class T>
inline void idlist<T>::remove(std::list<size_t>::const_iterator it)
{
	m_IDs.remove(it);
}

template<class T>
inline void idlist<T>::resize(const size_t size)
{
	if (size > m_Container.size()) {
		m_IDs.resize(size);
		m_Container.resize(size);
	}
}

template<class T>
inline const size_t & idlist<T>::capacity()
{
	return m_Container.capacity();
}

template<class T>
inline void idlist<T>::clear()
{
	m_Container.clear();
	m_IDs.clear();
}

template<class T>
inline bool idlist<T>::getElement(const size_t& id, typename T& element)
{
	bool elementFound = false;
	std::list<size_t>::const_iterator it;
	if (m_IDs.idInUse(id)) {
		elementFound = true;
		element = m_Container[*it];
	}
	return elementFound;
}

template<class T>
inline bool idlist<T>::empty()
{
	return m_IDs.empty();
}

template<class T>
inline std::list<size_t>::const_iterator idlist<T>::begin() const
{
	return m_IDs.begin();
}

template<class T>
inline std::list<size_t>::const_iterator idlist<T>::end() const
{
	return m_IDs.end();
}

template<class T>
inline std::list<size_t>::const_reverse_iterator idlist<T>::rbegin() const
{
	return this->rbegin();
}

template<class T>
inline std::list<size_t>::const_reverse_iterator idlist<T>::rend() const
{
	return m_IDs.rend();
}

template<class T>
inline T& idlist<T>::operator[](std::list<size_t>::const_iterator it)
{
	return m_Container[*it];
}

#endif
