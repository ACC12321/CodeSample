#include "Hashtable.h"

#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <cstdlib>
#include <random>
#include <map>

using namespace std;


//Helper function to generate random strings
string random(int length){

    /*I utilized the mt19937 generator rather than srand or rand because those are not fully random. 
    Although the mt19937 generator is not fully random as well, it is a better option than srand and rand.*/

    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);

    string randomString = "";

    for (int i = 0; i < length; ++i) {
        randomString += alphabet[dis(gen)];
    }

    return randomString;
}


int main(){
    //Testing the Birthday Paradox
    cout << "Testing the Birthday Paradox" << endl;

    double less = 0; //Number of times we insert 23 or less
    double more = 0;
    for(int i=0; i < 1500; ++i){

        //Size of 365 to represent 365 days in a year
        Hashtable<int> temp(true, 365); //creating a temp hashtable for each test
        int numElements = 0; //number of elements added
        //Generating random lowercase strings of size 28 to add
        string randomString = random(28);

        //runs while there is no probing (indicates nobody shares a birthday)
        int probes = 0;
        while(probes==0){
            probes = temp.add(randomString, 28); //adds the random string
            ++numElements; //increments the number of elements
            randomString = random(28); //generates a new random string
        }

        if(numElements <= 23){
            ++less; //if number of elements inserted is less than 23, increments the less counter
        }
        else{
            ++more; //else increments the greater counter
        }
                
    }

    //Printing out the results
    cout << "Percentage of times 23 or less things are inserted before there is a match: " << (less/1500) * 100 << endl;
    cout << "Percentage of times that 24 or more things are inserted before there is a match: " << (more/1500) * 100 << endl << endl << endl;

    cout << "Testing Ruining Quadratic Probing now" << endl;

    //Testing Ruining Quadratic Probing
    Hashtable<int> test2(true, 12); //set size to 12 (first non-prime after 11)
    vector<string> myDupes; //stores strings that will hash to the same index
    string testString = random(2); //stores the testString that other random strings must hash to the same index as


    //For loop that iterates 2000 times or until 5 things that hash to the same index as testString have been found
    for(int i=0; i < 2000; ++i){
        string randomString = random(2); //creating a random string

        //Exits early if 5 things that hash to the same index as testString have been found
        if((int)myDupes.size() > 5){
            break;
        }

        //Pushes back the string into my vector if it hashes to the same index as my testString
        if(test2.hash(randomString)==test2.hash(testString)){
            myDupes.push_back(randomString);
        }
        
    }

    //Printing out the list of items that hash to the same index
    cout << "This is the list of items that will hash to the same index as " << testString << ": " << endl;
    for(int i=0; i < (int)myDupes.size(); ++i){
        cout << myDupes[i] << endl;
    }

    //Adding them to the hashtable to attempt to ruin quadratic probing
    //Not everything will be added because there will be an infinite loop
    for(int i=0; i < (int)myDupes.size(); ++i){
        cout << "Attempting to add " << myDupes[i] << endl;
        test2.add(myDupes[i], 2);
    }

    //Printing what was actually added
    cout << endl << "Printing what actually was added to my hashtable: " << endl;
    test2.reportAll(cout);
    
    

    return 0;
}