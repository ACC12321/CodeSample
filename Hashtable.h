#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <cstdlib>

template<typename T>
class Hashtable
{
public:

	Hashtable(bool debug = false, unsigned int size = 11);

	~Hashtable();

	int add(std::string k, const T& val);

	const T& lookup(std::string k) const;

	void reportAll(std::ostream& out) const;

	int hash(std::string k) const;

private:

	std::pair<std::string, T>** myTable; //Array of to pointers of pairs (hashtable)

	unsigned int tableSize; //size of the hash table

	unsigned int numElements; //number of elements

	void resize(); //resize function

	long long r[5] = {0}; //stores 5 random numbers

	bool _debug; //stores debug

	int resizeArr[17]={11, 23, 47, 97, 197, 397, 797, 
	1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 
	411527, 823117}; //array that stores the necessary resize sizes

	T garbageT; //Temporarily made to return a garbage variable for nonexistent lookup	
	 
};

/*Function Implementations*/

//Constructor
template <typename T>
Hashtable<T>::Hashtable(bool debug, unsigned int size){
	tableSize = size; //setting table size
	numElements=0; //initializing to zero elements
	_debug = debug; //setting the debug value

	//allocating tableSize numbers of memory into heap for myTable
	myTable = new std::pair<std::string, T>*[tableSize];

	//Setting every element in my table to nullptr
	for(int i=0; i < (int)tableSize; ++i){
		myTable[i]=nullptr;
	}

	//if debug is false, construct 5 random numbers for the hash function
	if(debug==false){
		for(int i=0; i < 5; ++i){
			r[i] = rand() % (tableSize);
		}
	}
	else{
		//if debug is true sets the 5 random numbers for the hash function
		r[0]=983132572;
		r[1]=1468777056;
		r[2]=552714139;
		r[3]=984953261;
		r[4]=261934300;
	}
}

//Deconstructor
template <typename T>
Hashtable<T>::~Hashtable(){
	//Deallocate old array
	
	//Iterates through and deletes every pointer
	for(unsigned int i=0; i < tableSize; ++i){
		delete myTable[i];
	}

	//Deletes the array
	delete [] myTable;

}

//Add Function
template <typename T>
int Hashtable<T>::add(std::string k, const T& val){
	//Checks to see if the element that is going to be added will take the load factor over 0.5
	if( ( (double)(numElements+1) / (tableSize) ) > 0.5){
		resize(); //calls resize
	}

	int numProbes = 0; //stores number of probes
	int tempIndex = hash(k); //stores index of hashed string k
	
	//Checks if there is no initial collision, returns 0 for zero probes needed
	if(myTable[tempIndex]==nullptr){
			//creates a pointer to a new pair of the passed in k and val
			myTable[tempIndex] = new std::pair<std::string, T>(k, val);
			++numElements; //increments number of elements
			return 0; //returns 0
	}
	
	/*Quadratic probing while loop, ends when an empty spot is found*/
	while( (myTable[tempIndex+(int)pow(numProbes, 2) % (int)tableSize]!=nullptr) ){

		//Guard statement that indicates if an infinite loop has been entered
		if(numProbes == 50000000){
			std::cout << "Entered an infinite loop for my test" << std::endl;
			return numProbes;
		}

		++numProbes; //increments number of probes
	}

	//Creates a pointer to a new pair at the quadratically probed index
	myTable[tempIndex+(int)pow(numProbes, 2) % (int)tableSize] = new std::pair<std::string, T>(k, val);
	++numElements; //increments number of elements
	
	return numProbes; //returns number of probes
}

//Lookup Function
template <typename T>
const T& Hashtable<T>::lookup(std::string k) const{

	int tempIndex = hash(k); //stores the hashed index of k at tempIndex

	//Handles nonexistent lookup at first index
	if(myTable[tempIndex]==nullptr){
		return garbageT;
	}
	
	
	int iter = 0; //iterator for quadratic probing

	//Iterates quadratically until element is found or all possible indices have been checked
	while( (tempIndex+(int)pow(iter, 2) % (int)tableSize) < (int)tableSize && iter < (int)numElements){

		//if the key is found
		if(myTable[tempIndex+(int)pow(iter,2) % (int)tableSize]->first == k){
			return myTable[tempIndex+(int)pow(iter, 2) % (int)tableSize]->second; //returns value
		}

		++iter; //iterates the probe
	}
	
	return garbageT; //returns garbage variable if element is nonexistent
}

//ReportAll Function
template <typename T>
void Hashtable<T>::reportAll(std::ostream& out) const{

	//loops through the hashtable
	for(int i=0; i < (int)tableSize; ++i){
		//Continue if there is nothing at the index 
		if(myTable[i]==nullptr){
			continue;
		}

		//Prints out in the required format
		out << myTable[i]->first << " " << myTable[i]->second << std::endl;
	}
}

//Hash Function
template <typename T>
int Hashtable<T>::hash(std::string k) const{

	int iter = k.size()-1; //iterator to loop through the string, set to last char in the string

	long long w[5]={0}; //Stores all the w values, initializes to 0
	int wIter = 4; //iterates through w array

	//While the iterator is in bounds of the string
	while(iter >= 0){
		//array that stores all the a values
		long long tempa[6]={0}; //Initialized to 0 at first to avoid any issues

		//iterates for 6 characters in the string each iteration of the while loop
		for(int i=0; i < 6; ++i){
			//prevents any out of bounds accessing
			if(iter < 0){
				break;
			}

			//calculation for a value
			tempa[6-i-1] = (int)k[iter]-96;
			
			--iter; //decrementing k string iterator
		}

		//formula calculation for w values
		w[wIter]=((long long)pow(27, 5)*tempa[0]) + ((long long)pow(27, 4)*tempa[1]) + ((long long)pow(27, 3)*tempa[2]) + ((long long)pow(27, 2)*tempa[3]) + (27*tempa[4]) + (tempa[5]);
		--wIter; //decrementing wIter
	}


	//calculating the hash index
	long long index = ( (r[0]*w[0]) + (r[1]*w[1]) + (r[2]*w[2]) + (r[3]*w[3]) + (r[4]*w[4]) ) % tableSize;

	return static_cast<int>(index); //returns index 
}

//Resize Function
template <typename T>
void Hashtable<T>::resize(){

	int newSize; //Int to store the new size of the table
	int iter = 0; //Determine what the next jump in size is from resizeArr

	//Runs while the value at resizeArr is less than or equal to the current tableSize
	while(resizeArr[iter]<=(int)tableSize){
		++iter;
	}

	newSize = resizeArr[iter]; //Sets newSize to the next value in the sequence of possible sizes (hardcoded in the resize array)

	//Rehash all values in the old array
	std::pair<std::string, T>** temp = myTable; //stores old table in a temp pointer 
	myTable = new std::pair<std::string, T>*[newSize]; //allocates new table of newSize at myTable
	
	//Initializes the newly resized myTable to all nullpointers (indicating empty indices)
	for(int i=0; i < (int)newSize; ++i){
		myTable[i]=nullptr;
	}

	//Creates new random numbers for the hash function if debug is false
	if(_debug==false){
		for(int i=0; i < 5; ++i){
			r[i] = rand() % (newSize); //uses the newSize for the random numbers
		}
	}

	int tempSize = tableSize; //storing tableSize in a temp variable for future iteration 
	tableSize = newSize; //updating tableSize
	numElements = 0; //resets numElements

	//iterates through old array and rehashes into the new array
	for(int i=0; i < (int)tempSize; ++i){

		//continues if the index is empty
		if(temp[i]==nullptr){
			continue;
		}

		add(temp[i]->first, temp[i]->second); //adds to the new hashtable
	}


	//Deallocate old array
	for(int i=0; i < (int)tempSize; ++i){
		delete temp[i];
	}

	delete [] temp;
}

#endif
