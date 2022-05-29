#include "binaris_kupac.h"
#include <iostream>

template<class T>
MinHeap<T>::MinHeap() {
	this->size = 0;
	this->arr = NULL;
}

template<class T>
MinHeap<T>::MinHeap(int inputSize, T* inputArr) {
	//lefoglalok kello memoriat
	arr = new T[inputSize];
	size = inputSize;

	//atmasolom az elemeket
	for (int i = 0; i < size; i++) {
		arr[i] = inputArr[i];
	}

	//kupacositok minden nem level elemet
	for (int i = size / 2; i >= 0; i--) {
		heapifyDown(i);
	}
}

template<class T>
MinHeap<T>::~MinHeap() {
	delete[] arr;
}

template<class T>
void MinHeap<T>::insertNode(T node) {
	//lemasolom a kupacot egy segedtombbe
	T* tmpArr = new T[size + 1];
	for (int i = 0; i < size; i++) {
		tmpArr[i] = this->arr[i];
	}

	//az uj beillesztett elem a sor vegere kerul
	tmpArr[size] = node;

	//ujrameretezem a kupac altal hasznalt tombot
	this->arr = new T[size + 1];

	//visszamasolom az elemeket
	for (int i = 0; i < size + 1; i++) {
		this->arr[i] = tmpArr[i];
	}

	//felszabaditom a segedtombot
	delete[] tmpArr;

	//frissitem a meretet
	size++;
}

template<class T>
void MinHeap<T>::push(T elem) {
	if (this->size == MAX_LEN) {
		throw FullHeap();
	}

	//beillesztem az uj elemet a sor vegere
	insertNode(elem);

	//visszaallitom az kupactulajdonsagot, ha az uj elem elrontotta
	this->heapifyUp(size - 1);
}

template<class T>
void MinHeap<T>::deleteLastNode() {
	//kitorli a legutolso elemet a kupacbol

	if (this->size < 1) {
		throw EmpltyHeap();
	}
	else {
		//atmasolok n-1 elemet egy segettombbe
		T* tempArr = new T[size - 1];
		for (int i = 0; i < size - 1; i++) {
			tempArr[i] = this->arr[i];
		}

		//ujrafoglalok csokkentett helyet a kupac tombjenek
		this->arr = new T[size - 1];

		//visszamasolom az ertekeket az kupac tombjebe
		for (int i = 0; i < size - 1; i++) {
			this->arr[i] = tempArr[i];
		}

		this->size--;
	}
}

template<class T>
void MinHeap<T>::pop() {
	//vizsgalom ha van-e torolheto elem
	if (size == 0) {
		throw EmpltyHeap();
	}

	//a gyokeret kicserelem az utolso levellel
	this->swap(arr[0], arr[size - 1]);
	deleteLastNode();

	//visszaallitom a kupactulajdonsagot
	heapifyDown(0);
}

template<class T>
T MinHeap<T>::front() {
	//ha nem ures a kupac, akkor visszateriti a legkissebb kulcsu elemet
	if (isEmplty())
	{
		throw EmpltyHeap();
	}
	return arr[0];
}

template<class T>
void MinHeap<T>::decreaseKey(T newValue, int index) {
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	//az adott indexu elem kap egy uj erteket
	this->arr[index] = newValue;

	//ha ez elrontotta a kupactulajdonsagot akkor a heapifyUp(kupacol) muvelette visszaallitom
	this->heapifyUp(index);
}

template<class T>
void MinHeap<T>::heapifyUp(int index) {
	//ha helyesek az indexek es, romlott a kupactulajdonsag, akkor cserelem a szulot a gyerekkel, ugyanezt a szulore is elvegzem
	if (index >= 0 && this->parent(index) >= 0 && arr[this->parent(index)] > arr[index]) {
		this->swap(arr[index], arr[parent(index)]);
		this->heapifyUp(parent(index));
	}
}

template<class T>
void MinHeap<T>::heapifyDown(int index) {
	int child = leftChild(index);
	int child1 = rightChild(index);
	if (child >= 0 && child1 >= 0 && arr[child] > arr[child1]) {
		child = child1;
	}

	//ha helyesek az indexek es, romlott a kupactulajdonsag, akkor cserelem a szulot a gyerekkel, ugyanezt a gyerekre is elvegzem
	if (child > 0 && arr[index] > arr[child]) {
		this->swap(this->arr[index], this->arr[child]);
		this->heapifyDown(child);
	}
}

template<class T>
void MinHeap<T>::heapSort() {
	//a heapsort egy olyan kupacca alkitja a jelenlegi kupacot, amelyben minden elem rendezve vagy
	//vegrehajt egy kupacrendezest a kupac elemein, helyben rendez

	int savedSize = size;
	while (size > 1) {
		swap(arr[0], arr[size - 1]);
		size--;
		heapifyDown(0);
	}
	size = savedSize;

	//a fenti rendezes egy csokkeno rendezest ad, de mivel szeretnenk egy novekvo sorrendbeli rendezettseget, igy ezt megforditom
	reverse();
}

template<class T>
T MinHeap<T>::at(int index) {
	//hivatkozni lehet konstans idoben a kupac egy elemere az indexen keresztul
	if (index < 0 || index >= size)throw IndexOutOfBounds();
	return arr[index];
}

template<class T>
int MinHeap<T>::leftChild(int index) {
	int childPos = 2 * index + 1;
	if (childPos < this->size) {
		return childPos;
	}
	else {
		return -1;
	}
}

template<class T>
int MinHeap<T>::rightChild(int index) {
	int childPos = 2 * index + 2;
	if (childPos < this->size) {
		return childPos;
	}
	else {
		return -1;
	}
}

template<class T>
int MinHeap<T>::parent(int index) {
	int parentPos = (index - 1) / 2;
	if (index == 0) {
		return -1;
	}
	else {
		return parentPos;
	}
}

template<class T>
void MinHeap<T>::printArray() {
	std::cout << "[";
	if (this->size == 1) {
		std::cout << arr[0];
	}
	else {
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << " ";
		}
	}
	std::cout << "]\n";
}

template<class T>
bool MinHeap<T>::isEmplty() {
	return this->size == 0;
}

template<class T>
int MinHeap<T>::getSize() {
	return this->size;
}

template<class T>
void MinHeap<T>::swap(T& node1, T& node2) {
	T temp = node1;
	node1 = node2;
	node2 = temp;
}

template<class T>
void MinHeap<T>::reverse() {
	int left = 0;
	int right = size - 1;

	while (left < right) {
		swap(arr[left], arr[right]);
		left++;
		right--;
	}
}
