#pragma once
#include<ostream>
#include<iostream>
#include<algorithm>
#ifndef PLIST_H
#define PLIST_H

template<class T>
class List {
private:
	const uint32_t RUN = 32;
	uint32_t capacity;
	uint32_t size;
	T* Array;
	void _insertion_sort(T* Arr, int left, int right);
	void _merge_sort(T* Arr, int l, int m, int r);
	void _tim_sort(T* Arr, int s);
public:
	List();
	~List();

	//User methods
	void append(T value);
	void clear();
	void insert(uint32_t index, T value);
	void remove(T value);
	void extend(const List<T>& clist);
	void reverse();
	void sort();
	uint32_t index(T value);
	uint32_t len();
	uint32_t count(T value);
	T pop();
	T sum();
	T pmin();
	T pmax();

	T& operator [] (uint32_t index);
	bool operator == (const List<T>& rhs) const;
	bool operator != (const List<T>& rhs) const;
	List<T>& operator = (const List<T>& clist);
	List<T>& operator * (const uint32_t value);
	List<T>& operator + (const List<T>& clist) const;

	template<typename U>
	friend std::ostream& operator << (std::ostream& ostr, const List<U>& clist);

	template<typename U>
	friend U pmax(const List<U>& clist);

	template<typename U>
	friend U pmin(const List<U>& clist);

	template<typename U>
	friend uint32_t plen(const List<U>& clist);

	template<typename U>
	friend U sum(const List<U>& clist);
};

template<class T>
T& List<T>::operator[](uint32_t index) {
	return Array[index];
}

template<class T>
bool List<T>::operator==(const List<T>& rhs) const {
	if (size != rhs.size) {
		return false;
	}
	else {
		for (uint32_t i = 0; i < size; i++) {
			if (Array[i] != rhs[i]) {
				return false;
			}
		}
	}
	return true;
}

template<class T>
bool List<T>::operator!=(const List<T>& rhs) const {
	return !(*this == rhs);
}

template<typename T>
std::ostream& operator << (std::ostream& ostr, const List<T>& clist) {
	for (uint32_t i = 0; i < clist.size; i++) {
		ostr << clist.Array[i] << " ";
	}
	ostr << std::endl;
	return ostr;
}

template<class T>
List<T>& List<T>::operator * (const uint32_t value) {
	List<T> temp;
	for (uint32_t i = 0; i < value; ++i) {
		temp.extend(*this);
	}
	*this = temp;
	return *this;
}

template<class T>
List<T>& List<T>::operator = (const List<T>& clist) {
	if (clist.size > size) {
		delete[] Array;
		capacity = clist.size + 5;
		Array = new T[capacity];
	}
	
	for (uint32_t i = 0; i < clist.size; ++i) {
		Array[i] = clist.Array[i];
	}
	size = clist.size;

	return *this;
}

template<class T>
List<T>& List<T>::operator+(const List<T>& clist) const{
	List<T> temp;
	temp.extend(*this);
	temp.extend(clist);
	return temp;
}

template<typename T>
T pmax(const List<T>& clist) {
	T maxelement = INT_MIN;
	if (clist.size == 0) {
		return -1;
	}
	else {
		for (uint32_t i = 0; i < clist.size; i++) {
			if (clist.Array[i] > maxelement) {
				maxelement = clist.Array[i];
			}
		}
		return maxelement;
	}
}

template<typename T>
T pmin(const List<T>& clist) {
	T minelement = INT_MAX;
	if (clist.size == 0) {
		return -1;
	}
	else {
		for (uint32_t i = 0; i < clist.size; i++) {
			if (clist.Array[i] < minelement) {
				minelement = clist.Array[i];
			}
		}
		return minelement;
	}
}

template<typename T>
uint32_t plen(const List<T>& clist) {
	return clist.size;
}

template<class T>
void List<T>::_insertion_sort(T* Arr, int left, int right) {
	for (int i = left + 1; i <= right; i++) {
		T temp;
		temp = Arr[i];
		int j = i - 1;
		while (j >= left && Arr[j] > temp) {
			Arr[j + 1] = Arr[j];
			j--;
		}
		Arr[j + 1] = temp;
	}
}

template<class T>
void List<T>::_merge_sort(T* Arr, int l, int m, int r) {
	int len1 = m - l + 1, len2 = r - m;
	T* left = new T[len1];
	T* right = new T[len2];
	for (int i = 0; i < len1; i++)
		left[i] = Arr[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = Arr[m + 1 + i];
	int i = 0;
	int j = 0;
	int k = l;

	while (i < len1 && j < len2)
	{
		if (left[i] <= right[j])
		{
			Arr[k] = left[i];
			i++;
		}
		else
		{
			Arr[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < len1)
	{
		Arr[k] = left[i];
		k++;
		i++;
	}

	while (j < len2)
	{
		Arr[k] = right[j];
		k++;
		j++;
	}
}

template<class T>
void List<T>::_tim_sort(T* Arr, int n) {
	for (int i = 0; i < n; i += RUN)
		_insertion_sort(Arr, i, std::min((i + 31), (n - 1)));

	for (int sz = RUN; sz < n; sz = 2 * sz)
	{
		for (int left = 0; left < n; left += 2 * sz)
		{
			int mid = left + sz - 1;
			int right = std::min((left + 2 * sz - 1), (n - 1));
			_merge_sort(Arr, left, mid, right);
		}
	}
}

template<typename T>
T sum(const List<T>& clist) {
	T summation = 0;
	for (uint32_t i = 0; i < clist.size; ++i) {
		summation += clist.Array[i];
	}
	return summation;
}

template<class T>
List<T>::List() : capacity(5), size(0), Array(new T[capacity]) {
	//Nothing
}

template<class T>
List<T>::~List() {
	delete[] Array;
}

template<class T>
void List<T>::append(T value) {
	if (size < capacity) {
		Array[size] = value;
		++size;
	}
	else {
		capacity *= 2;
		T* temp = new T[capacity];
		for (uint32_t i = 0; i < size; ++i) {
			temp[i] = Array[i];
		}
		temp[size] = value;
		++size;
		delete[] Array;
		Array = temp;
	}
}

template<class T>
void List<T>::clear() {
	delete[] Array;
	capacity = 5;
	T* temp = new T[capacity];
	size = 0;
	Array = temp;
}

template<class T>
uint32_t List<T>::index(T value) {
	uint32_t ide = 0;
	for (uint32_t i = 0; i < size; i++) {
		if (Array[i] == value) {
			ide = i;
			break;
		}
	}
	return ide;
}

template<class T>
void List<T>::insert(uint32_t index, T value) {
	if (index < 0 || index > size) {
		std::cout << "Invalid index." << std::endl;
	}
	if (size != capacity) {
		for (uint32_t i = size; i > index; i--) {
			Array[i] = Array[i - 1];
		}
		Array[index] = value;
		++size;
	}
	else {
		capacity *= 2;
		T* temp = new T[capacity];
		for (uint32_t i = 0; i < size; ++i) {
			temp[i] = Array[i];
		}
		delete[] Array;
		Array = temp;
		insert(index, value);
	}
}

template<class T>
void List<T>::remove(T value) {
	for (uint32_t i = 0; i < size; i++) {
		if (Array[i] == value) {
			for (uint32_t j = i; j < size - 1; j++) {
				Array[j] = Array[j + 1];
			}
			break;
		}
	}
	--size;
}

template<class T>
void List<T>::extend(const List<T>& clist) {

	for (uint32_t i = 0; i < clist.size; i++) {
		this->append(clist.Array[i]);
	}
}

template<class T>
uint32_t List<T>::len() {
	return size;
}

template<class T>
uint32_t List<T>::count(T value) {
	uint32_t cnt = 0;
	for (uint32_t i = 0; i < size; i++) {
		if (Array[i] == value) {
			cnt++;
		}
	}
	return cnt;
}

template<class T>
T List<T>::pop() {
	T temp = Array[size];
	--size;
	return temp;
}

template<class T>
T List<T>::sum() {
	T summation = 0;
	for (uint32_t i = 0; i < size; i++) {
		summation += Array[i];
	}
	return summation;
}

template<class T>
void List<T>::reverse() {
	T* head = Array;
	T* end = Array + size - 1;
	for (uint32_t i = 0; i < size; i++) {
		if (head < end) {
			T temp = *end;
			*end = *head;
			*head = temp;
		}
		head++;
		end--;
	}
}

template<class T>
void List<T>::sort() {
	_tim_sort(Array, size);
}

template<class T>
T List<T>::pmin() {
	T temp = INT_MAX;
	for (uint32_t i = 0; i < size; i++) {
		if (temp > Array[i]) {
			temp = Array[i];
		}
	}
	return temp;
}

template<class T>
T List<T>::pmax() {
	T temp = INT_MIN;
	for (uint32_t i = 0; i < size; i++) {
		if (temp < Array[i]) {
			temp = Array[i];
		}
	}
	return temp;
}

#endif // !PLIST_H
