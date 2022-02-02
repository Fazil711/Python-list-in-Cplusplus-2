#include "../include/plist.h"
#include<iostream>

int main() {
	List<int> arr;
	arr.append(23);
	arr.append(45);
	arr.append(100);
	arr.append(3);
	arr.append(200);
	std::cout << arr;
	//arr.append(2);
	//arr.append(34);
	//std::cout << arr;
	std::cout << arr.index(200) << std::endl;
	arr.insert(5, 4000);
	arr.remove(100);
	std::cout << arr;
	std::cout << arr.len();
	std::cout << arr.count(23) << std::endl;
	std::cout << arr.sum() << std::endl;
	List<int> arr2;
	arr2.append(34);
	arr2.append(550);
	std::cout << arr2;
	arr.extend(arr2);
	std::cout << arr;
	arr.reverse();
	std::cout << arr;
	std::cout << pmax(arr) << " " << pmin(arr) << " " << plen(arr) << std::endl;
	arr.sort();
	arr.append(28);
	std::cout << arr;

	return 0;
}

/* 
Basically you can do 

arr.append();
arr.clear;
arr.pop();
arr.index(int index);
arr.sum();
arr.pmin();
arr.pmax();
arr.insert(int index, int value);
arr.extend(arr2);
arr.sort();
arr.count(int value);
arr.len();
arr.remove(int value);
arr.reverse();

pmax(arr);
pmin(arr);
plen(arr);
sum(arr);
*/
