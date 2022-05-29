#ifndef BINHEAP_AKOS
#define BINHEAP_AKOS

#define MAXLEN 10000

template<class T>
class MinHeap {

	const int MAX_LEN = MAXLEN;
	int size;
	T* arr;


public:
	void deleteLastNode();
	void insertNode(T node);

	//Konstruktorok
	MinHeap();									//Letrehoz egy ures minimum kupacot
	MinHeap(int inputSize, T* inputArr);		//Letrehoz egy minimum kupacot a  megadott tomb elemeivel

	//Destruktor	
	~MinHeap();									//Torli az adott kupacot

	//Muveletek				
	void push(T elem);							//Beilleszti a kapott elemet a kupacba,
	void pop();									//Kiveszi a kupacbol a legnagyobb kulcsu elemet
	T front();									//Visszateriti a kupac legnagyobb kulcsu elemet, de nem torli ki a kupacbol
	void decreaseKey(T newValue, int index);	//Csokkenti az adott indexu elem erteket, ezzel kozelebb kerul a sorban a gyoker elemhez
	void heapifyUp(int index);					//Helyrehozza a kupactulajdonsagot az adott indexu elemtol a gyokerig
	void heapifyDown(int index);				//Helyrehozza a kupactulajdonsagot az adott indexu elemtol a levelig
	void heapSort();							//Minden elemet csokkeno sorrendbe rendez

	//Getters
	T at(int index);							//Visszateriti az adott indexu elem kulcsat		
	int getSize();								//Visszateriti a kuapc elemeinek a szamat
private:
	int leftChild(int parent);					//Visszateriti az adott indexu elem  bal gyerekenek az indexet
	int rightChild(int parent);					//Visszateriti az adott indexu elem jobb gyerekenek az indexet
	int parent(int child);						//Visszateriti az adott indexu elem szulojenek az indexet
public:
	//kiirato muveltek 
	void printArray();							//Megjeleniti a kepernyon a kupac elemeit tomb (szamsorozat) formajaban

	//egyebv seged, metodusok
	bool isEmplty();							//Igazat terit vissza ha a kupac ures, hamisat ha nem
	void swap(T& node1, T& node2);				//Kicsereli a kupac 2 elemenek (node1 es node2) a kulcsait
	void reverse();								//Megforditja a kupac tombjet

	//Kivetelek
	class IndexOutOfBounds {};					//Hibas, nem letezo index kivetel
	class EmpltyHeap {};						//Ures kupaccal valo muvelet eseten fellepo kivetel
	class FullHeap {};							//Tele kupaccal valo muvelet eseten fellepo kivetel
};

#include "binaris_kupac.cpp"

#endif // !BINHEAP_AKOS