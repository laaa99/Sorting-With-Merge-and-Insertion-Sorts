/***********************************************************************
*
*	Merge Sort (and Insertion sort) Microassignment
*   Aaron S. Crandall, 2016
*
*   CptS 223
*	Lucy Tran
*	11-2-16
*	Implemented Merge and insertion sort
*/


#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>  // rand
#include <time.h>    // time for srand
#include <cmath>     // floor

using namespace std::chrono;
using namespace std;

enum SortType { doMergeSort, doInsertionSort, doBubbleSort };


/**********************************************************/
void showFirstNElements(vector<int> &data, int n)
{
	cout << data[0];
	for (int i = 1; i < n; i++)
	{
		cout << ", " << data[i];
	}
	cout << endl;
}


/**********************************************************/
bool are_VectorsIdentical(vector<int> &vecA, vector<int> &vecB)
{
	bool result = true;
	for (int i = 0; i < vecA.size(); i++)
	{
		if (vecA[i] != vecB[i])
		{
			result = false;
			return(result);
		}
	}
	return result;
}


/**********************************************************/

/*Implemented insertion: Starts with the second element until the last element - the element is compared with previous elements and swapped until it is in the right position*/
void executeInsertionSort(vector<int> &data)
{
	/*Initialize size of vector*/
	int size = data.size();

	/*Initialize incremented and decrement indexes*/
	int index = 1;
	int decIndex = 0;
	int tempIndex = 0;

	/*Initialize element temps*/
	int element = 0;
	int prevElement = 0;

	for (; index < size; index++) { //Loop through all numbers
		element = data[index]; //Element to be compared with previous elements
		tempIndex = index; //Changes during swapping

		for (decIndex = index - 1; decIndex >= 0; decIndex--) { //Loop to compare elements and swap
			prevElement = data[decIndex]; //Previous element

			if (element < prevElement) { //Swap here
				data[decIndex] = element;
				data[tempIndex] = prevElement;
				tempIndex--;
			}
		}
	}

}

/**********************************************************/

/*Merges the split vectors into a larger vector*/
void merge(vector<int> &data, vector<int> &temp1, vector<int> &temp2) {

	/*Clear original vector*/
	data.clear();

	/*Intialize indexes*/
	int temp1Index = 0;
	int temp2Index = 0;

	/*Initialize sizes*/
	int size1 = temp1.size();
	int size2 = temp2.size();

	/*Sort and merge*/
	while (temp1Index < size1 && temp2Index < size2) {
		/*Add smaller element to the original vector*/
		if (temp1[temp1Index] <= temp2[temp2Index]) {
			data.push_back(temp1[temp1Index]);
			temp1Index++;
		}
		else {
			data.push_back(temp2[temp2Index]);
			temp2Index++;
		}
	}

	/*Merge the rest if any*/
	while (temp1Index < size1) {
		data.push_back(temp1[temp1Index]);
		temp1Index++;
	}

	while (temp2Index < size2) {
		data.push_back(temp2[temp2Index]);
		temp2Index++;
	}

}

/*Implemented merge: Splits into smaller vectors, sorts them, merges them back into original vector*/
void executeMergeSort(vector<int> &data)
{
	/*Find the midpoint using the start and end indexes*/
	int index = 0;
	int size = data.size();
	int midpoint = floor((size) / 2);

	/*More than one element in vector, split, sort, merge*/
	if (size > 1) {
		/*Initialize temporary vectors*/
		vector<int> temp1;
		vector<int> temp2;

		/*Add elements to temporary vectors*/
		for (; index < midpoint; index++) {
			temp1.push_back(data[index]);
		}
		for (index = midpoint; index < size; index++) {
			temp2.push_back(data[index]);
		}

		/*Split into smaller vectors*/
		executeMergeSort(temp1);
		executeMergeSort(temp2);

		/*Merge*/
		merge(data, temp1, temp2);
	}
}

/**********************************************************/
void executeBubbleSort(vector<int> &data)
{
	cout << " [x] Doing Bubble Sort." << endl;
	int n = data.size();
	int swap = 0;
	for (int c = 0; c < (n - 1); c++)
	{
		for (int d = 0; d < n - c - 1; d++)
		{
			if (data[d] > data[d + 1])
			{
				swap = data[d];
				data[d] = data[d + 1];
				data[d + 1] = swap;
			}
		}
	}
}

/*****************************************************************************/
std::chrono::duration<double> do_Benchmark(SortType sortType, vector<int> &data)
{
	//set up clock variables
	std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
	start_time = std::chrono::system_clock::now();    // Grab starting time

	switch (sortType)
	{
	case doMergeSort: executeMergeSort(data); 			break;
	case doInsertionSort: executeInsertionSort(data);	break;
	case doBubbleSort: executeBubbleSort(data);		break;
	}

	end_time = std::chrono::system_clock::now();          // Grab end time

	return std::chrono::duration<double>(end_time - start_time);
}

/******************************************************************************/
int main(int argc, char *argv[])
{
	//generate large list of number
	srand(time(NULL));
	vector<int> merge_vector{};
	vector<int> insertion_vector{};
	vector<int> bubble_vector{};

	int curr_num = 0;
	for (int i = 0; i < 10000; i++)	//Creating 3 copies of the random series, 10000
	{
		curr_num = rand() % 100000;
		merge_vector.push_back(curr_num);
		insertion_vector.push_back(curr_num);
		bubble_vector.push_back(curr_num);
	}

	cout << " [x] Starting sorts and tests " << endl;
	cout << " *********************************************" << endl;

	cout << " [x] Doing Merge Sort." << endl;
	cout << " [x] Merge sort time: "
		<< do_Benchmark(doMergeSort, merge_vector).count() << " secs" << endl;

	cout << " [x] Doing Insertion Sort." << endl;
	cout << " [x] Insertion sort time: "
		<< do_Benchmark(doInsertionSort, insertion_vector).count() << " secs" << endl;

	cout << " [x] Bubble sort time: "
		<< do_Benchmark(doBubbleSort, bubble_vector).count() << " secs" << endl;

	cout << " *********************************************" << endl;
	cout << " [x] Resulting sorted array samples: " << endl;
	cout << " [x] Merge: "; showFirstNElements(merge_vector, 10);
	cout << " [x] Inser: "; showFirstNElements(insertion_vector, 10);
	cout << " [x] Bubbl: "; showFirstNElements(bubble_vector, 10);
	cout << " *********************************************" << endl;
	cout << " [x] Correct results? " << endl;
	if (are_VectorsIdentical(bubble_vector, merge_vector))
		cout << " [x] Merge Sort is: CORRECT " << endl;
	else
		cout << " [!] Merge Sort is: WRONG " << endl;

	if (are_VectorsIdentical(bubble_vector, insertion_vector))
		cout << " [x] Insertion Sort is: CORRECT " << endl;
	else
		cout << " [!] Insertion Sort is: WRONG " << endl;

	if (are_VectorsIdentical(bubble_vector, bubble_vector))
		cout << " [x] Bubble Sort is: CORRECT " << endl;
	else
		cout << " [!] Bubble Sort is: WRONG " << endl;


}
