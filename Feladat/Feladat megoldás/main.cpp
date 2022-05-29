#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <math.h>
#include <cfloat>
#include "binaris_kupac.h"

#define INF DBL_MAX

using namespace std;

//Eukledeszi algoritmus: 2 sikbeli pont kozotti tavolsagot hataroz meg
double calcDist(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void printAnswer(double r, int maxR, string outFile) {
	ofstream out(outFile);
	if (r <= maxR) {
		out << "Lehets�ges" << "\n" << r;
	}
	else {
		out << "Nem lehets�ges";
	}
}

void readInput(MinHeap<double>& houses, MinHeap<double>& towers, int& towerHeight, int& maxRadius, string inputFile) {
	int sizeOfHouses;
	int sizeOfTowers;

	ifstream in(inputFile);
	if (!in) {
		perror("Nem sikerult megnyitni a bementi allomanyt!");
	}

	in >> towerHeight >> maxRadius;
	in >> sizeOfHouses;
	double housePos;
	for (int i = 0; i < sizeOfHouses; i++) {
		in >> housePos;
		houses.push(housePos);
	}

	in >> sizeOfTowers;
	double towerPos;
	for (int i = 0; i < sizeOfTowers; i++) {
		in >> towerPos;
		towers.push(towerPos);
	}
}

double calculateMinRadius(MinHeap<double>& houses, MinHeap<double>& towers, const int& towerHeight) {
	//beillesztek 2 tornyot, +vegtelen es -vegtelen poziciokra, hogy minden hazat be tudjak rakni 2 torony koze
	towers.push(INF);
	towers.push(-INF);

	houses.heapSort();			
	towers.heapSort();

	double radius = 0.0;

	//minden hazra megkeresem a legkozelebbi tornyot
	int towerPos = 1;
	for (int i = 0; i < houses.getSize(); i++) {
		double house = houses.at(i);
		while (towers.at(towerPos) < house) {
			//mivel a hazak es a tornyok is rendezve vannak, igy biztos vagyok benne, hogy a kovetkezo haz, csak a jelenlegi 2 torony kozott van, vagy elorebb, de semmikepp sem olyan pozicion ahol mar voltunk
			towerPos++;										
		}
		//meghatarozzuk a melyik torony van kozelebb
		double minDist = min(calcDist(house, 1, towers.at(towerPos - 1), towerHeight), calcDist(towers.at(towerPos), towerHeight, house, 1));

		//a minimum radius a legnagyobb tavolsag lesz egy haz es egy torony kozott
		radius = max(radius, minDist);
	}

	return radius;
}

int main() {
	int towerHeight;					//tornyok magassaga
	int maxRadius;						//tornyok maximalis radiusa
	MinHeap<double> houses;				//hazak pozicioi
	MinHeap<double> towers;				//tornyok pozicioi

	readInput(houses, towers, towerHeight,maxRadius, "be5.txt");
	double r = 0.0;
	try {
		r = calculateMinRadius(houses, towers, towerHeight);
	}
	catch (MinHeap<double>::IndexOutOfBounds) {
		cout << "Hibas indexre probalt hivatkozni!\n";
	}
	catch (MinHeap<double>::FullHeap) {
		cout << "A Kupac tele van!\n";
	}
	catch (MinHeap<double>::EmpltyHeap) {
		cout << "Ures kupacbol probalt torolni elemet!\n";
	}

	printAnswer(r,maxRadius, "ki5.txt");

	return 0;
}