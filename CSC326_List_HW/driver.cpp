#include <iostream>
#include <fstream>
#include <cassert>
#include "LinkedList.h"


void print_list(LinkedList<int> list);
void sort_list(LinkedList<int>& list);

using namespace std;


int main() {

	LinkedList<int> list;

	ifstream input_file;
	int temp;

	input_file.open("input_file.txt");

	assert(!input_file.fail());

	while (!input_file.eof()) {
		input_file >> temp;
		list.insert(list.getLength() + 1, temp);
	}

	print_list(list);
	cout << endl;
	sort_list(list);
	print_list(list);

	system("pause");
	return 0;
}

void print_list(LinkedList<int> list) {
	for (int i = 1; i <= list.getLength(); i++) {
		try {
			cout << list.getEntry(i) << endl;
		}
		catch (PrecondViolatedExcep error) {
			cout << error.what() << endl;
		}
	}

}

void sort_list(LinkedList<int>& list) {

	int i;
	int sorted = 1; //# of already sorted that will also serve as index of working object
	int working_element;
	int array_length;
	int temp;

	while (sorted < list.getLength()) { //Keep going until sorted == array_length

		//Initalize working_element and working_element_i with the current element in working index
		working_element = sorted;

		//Go through entire thing and look for lower
		for (i = sorted; i <= list.getLength(); i++) {
			try {
				if (list.getEntry(working_element) > list.getEntry(i)) {
					working_element = i;
				}
			}
			catch (PrecondViolatedExcep error) {
				cout << error.what() << endl;
			}
		}

		//Swap the location if not equal to sorted
		if (sorted != working_element) {

			//Swap entry at sorted with entry at working element
			try {
				temp = list.getEntry(sorted);
			}
			catch (PrecondViolatedExcep error) {
				cout << error.what() << endl;
			}
			list.replace(sorted, list.getEntry(working_element));
			list.replace(working_element, temp);

		}

		//Change sorted
		sorted++;
	}
}