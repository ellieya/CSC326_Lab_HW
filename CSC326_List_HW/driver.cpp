#include <iostream>
#include <fstream>
#include <cassert>
#include "ArrayQueue.h"

using namespace std;

void sort_list(ArrayQueue<int> &target);
void print_list(ArrayQueue<int> target);
template <typename s> int get_array_length(s target[]);

int main() {

	ArrayQueue<int> sample_list;
	ifstream input_file;
	int temp;
	
	input_file.open("input_file.txt");

	assert(!input_file.fail());

	while (!input_file.eof()) {
		input_file >> temp;
		sample_list.enqueue(temp);
	}

	print_list(sample_list);
	sort_list(sample_list);
	print_list(sample_list);

	return 0;
}

void sort_list(ArrayQueue<int> &target) {
	ArrayQueue<int> holder = target; //Used to hold target's data in order to avoid modification of target
	int holder_array[50];
	int i = 0;
	int sorted = 0; //# of already sorted that will also serve as index of working object
	int working_element;
	int array_length;

	//Store all values of ArrayQueue into a temporary array.
	//Affecting the ArrayQueue in this instance should have no effect on the actual ArrayQueue.
	while (!holder.isEmpty()) {
		try {
		holder_array[i] = holder.peekFront();
		holder.dequeue();
		i++;
		}
		catch (PrecondViolatedExcep error) {
			cout << error.what();
		}
	}
	
	 array_length = get_array_length<int>(holder_array);
	
	//Sort process
	while (sorted < array_length) { //Keep going until sorted == array_length
		
		//Initalize working_element and working_element_i with the current element in working index
		working_element = sorted;

		//Go through entire thing and look for lower
		for (i = sorted; i < array_length; i++) {
			if (holder_array[working_element] > holder_array[i]) {
				working_element = i;
			}
		}

		//Swap the location if not equal to sorted
		if (sorted != working_element) {
			swap(holder_array[working_element], holder_array[sorted]);
		}

		//Change sorted
		sorted++;
	}


	//Clean out holder
	holder = ArrayQueue<int>();

	//Update holder with new data
	for (i = 0; i < array_length; i++) {
		holder.enqueue(holder_array[i]);
	}

	//Update target
	target = holder;
}

void print_list(ArrayQueue<int> target) {
	int holder_array[50];
	int i = 0;

	//Transfer queue data into array
	while (!target.isEmpty()) {
		try {
			holder_array[i] = target.peekFront();
			target.dequeue();
			i++;
		}
		catch (PrecondViolatedExcep error) {
			cout << error.what();
		}
	}

	//Print all data
	for (i = 0; i < sizeof(holder_array) / sizeof(*holder_array); i++) {
		cout << holder_array[i] << endl;
	}

}

//The fact that this is a template may be messing up the calculation
template <typename s>
int get_array_length(s target[]) {
	int test = sizeof(target);
	int test2 = sizeof(*target);
	return ( sizeof(target) / sizeof(*target) );
}