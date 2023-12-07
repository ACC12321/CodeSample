//
// CS104 Hashtable test suite
//

#include <gtest/gtest.h>

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <string>

#include "../Hashtable.h"

using namespace std;

TEST(HashTest, Hash_a)
{
	string input("a");
	unsigned long long hash = 261934300;
	Hashtable<int> hashtable11(true, 11);
	Hashtable<int> hashtable23(true, 23);
	EXPECT_EQ(hash % 11, hashtable11.hash(input));
	EXPECT_EQ(hash % 23, hashtable23.hash(input));
}

TEST(HashTest, Hash_test)
{
	string input("test");
	unsigned long long hash = 104207418043400;
	Hashtable<int> hashtable11(true, 11);
	Hashtable<int> hashtable23(true, 23);
	EXPECT_EQ(hash % 11, hashtable11.hash(input));
	EXPECT_EQ(hash % 23, hashtable23.hash(input));
}

TEST(HashTest, Hash_mediumlength)
{
	string input("mediumlength");
	unsigned long long hash = 232302162651600409;
	Hashtable<int> hashtable11(true, 11);
	Hashtable<int> hashtable23(true, 23);
	EXPECT_EQ(hash % 11, hashtable11.hash(input));
	EXPECT_EQ(hash % 23, hashtable23.hash(input));
}

TEST(HashTest, Hash_antidisestablishmentarianism)
{
	string input("antidisestablishmentarianism");
	unsigned long long hash = 321236178794688624;
	Hashtable<int> hashtable11(true, 11);
	Hashtable<int> hashtable23(true, 23);
	EXPECT_EQ(hash % 11, hashtable11.hash(input));
	EXPECT_EQ(hash % 23, hashtable23.hash(input));
}

TEST(HashTest, HashActuallyRandom)
{
	string k("antidisestablishmentarianism");
	vector<size_t> hash_values;
	for(int i = 0; i<3; i++){
		Hashtable<int> hashtable(false, 823117);
		hash_values.push_back(hashtable.hash(k));
		//wait for a second to ensure we get a different seed number
		//each run should produce different hash values.
		sleep(1);
	}
	set<size_t> hash_unique_vals(hash_values.begin(),hash_values.end());
	EXPECT_EQ(hash_values.size(),hash_unique_vals.size());
}

TEST(HashtableTest, ConstructionDestruction)
{
	Hashtable<int> hashtable1;
	Hashtable<string> hashtable2(false);
	Hashtable<double> hashtable3(true, 11);
}

TEST(HashtableTest, AddCheckCount_a)
{
	Hashtable<int> hashtable(true);
	hashtable.add("a", 1);
	EXPECT_EQ(1, hashtable.lookup("a"));

	stringstream ss;
	hashtable.reportAll(ss);
	EXPECT_EQ("a 1\n", ss.str());
}

TEST(HashtableTest, AddCheckCount_a_b_test)
{
	Hashtable<int> hashtable(true);
	hashtable.add("a", 1);
	hashtable.add("b", 2);
	hashtable.add("test", 3);
	EXPECT_EQ(1, hashtable.lookup("a"));
	EXPECT_EQ(2, hashtable.lookup("b"));
	EXPECT_EQ(3, hashtable.lookup("test"));
	
	stringstream ss;
	hashtable.reportAll(ss);
	EXPECT_EQ("a 1\nb 2\ntest 3\n", ss.str());
}

TEST(HashtableTest, ForceResize)
{
	Hashtable<int> hashtable(true);
	hashtable.add("a", 1);
	hashtable.add("b", 2);
	hashtable.add("c", 3);
	hashtable.add("d", 4);
	hashtable.add("e", 5);
	hashtable.add("f", 6);
	hashtable.add("g", 7);
	EXPECT_EQ(1, hashtable.lookup("a"));
	EXPECT_EQ(2, hashtable.lookup("b"));
	EXPECT_EQ(3, hashtable.lookup("c"));
	EXPECT_EQ(4, hashtable.lookup("d"));
	EXPECT_EQ(5, hashtable.lookup("e"));
	EXPECT_EQ(6, hashtable.lookup("f"));
	EXPECT_EQ(7, hashtable.lookup("g"));

	stringstream ss;
	string expected = "e 5\nd 4\nc 3\nb 2\ng 7\na 1\nf 6\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());
}

TEST(HashtableTest, Lookup_Nonexistent)
{
	//Make sure it doesn't crash
	Hashtable<int> hashtable(true);
	hashtable.lookup("a");
	hashtable.add("a", 1);
	hashtable.add("b", 2);
	hashtable.add("c", 3);
	hashtable.lookup("d");
	hashtable.lookup("e");
	hashtable.lookup("f");
}

TEST(HashtableTest, ProbingOneCollision)
{
	Hashtable<int> hashtable(true);

	vector<pair<string, int>> stringToHash = { {"a", 1}, {"l", 1} };
	//Check to make sure the hashtable hashes strings correctly to cause collisions
	for(auto stringHash : stringToHash) {
		EXPECT_EQ(stringHash.second, hashtable.hash(stringHash.first));
	}

	EXPECT_EQ(0, hashtable.add("a", 15));
	EXPECT_EQ(1, hashtable.add("l", 20));

	EXPECT_EQ(15, hashtable.lookup("a"));
	EXPECT_EQ(20, hashtable.lookup("l"));

	stringstream ss;
	string expected = "a 15\nl 20\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());
}


TEST(HashtableTest, ProbingOneCollisionTwoProbes)
{
	Hashtable<int> hashtable(true);

	vector<pair<string, int>> stringToHash = { {"a", 1}, {"b", 2}, {"l", 1} };
	//Check to make sure the hashtable hashes strings correctly to cause collisions
	for(auto stringHash : stringToHash) {
		EXPECT_EQ(stringHash.second, hashtable.hash(stringHash.first));
	}

	EXPECT_EQ(0, hashtable.add("a", 10));
	EXPECT_EQ(0, hashtable.add("b", 20));
	EXPECT_EQ(2, hashtable.add("l", 30));

	EXPECT_EQ(10, hashtable.lookup("a"));
	EXPECT_EQ(20, hashtable.lookup("b"));
	EXPECT_EQ(30, hashtable.lookup("l"));

	stringstream ss;
	string expected = "a 10\nb 20\nl 30\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());
}

TEST(HashtableTest, ProbingOneCollisionOneProbe)
{
	Hashtable<int> hashtable(true);

	vector<pair<string, int>> stringToHash = { {"a", 1}, {"b", 2}, {"l", 1} };
	//Check to make sure the hashtable hashes strings correctly to cause collisions
	for(auto stringHash : stringToHash) {
		EXPECT_EQ(stringHash.second, hashtable.hash(stringHash.first));
	}

	EXPECT_EQ(0, hashtable.add("a", 10));
	EXPECT_EQ(1, hashtable.add("l", 20));
	EXPECT_EQ(1, hashtable.add("b", 30));

	EXPECT_EQ(10, hashtable.lookup("a"));
	EXPECT_EQ(20, hashtable.lookup("l"));
	EXPECT_EQ(30, hashtable.lookup("b"));

	stringstream ss;
	string expected = "a 10\nl 20\nb 30\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());
}

TEST(HashtableTest, ProbingTwoCollisions)
{
	Hashtable<int> hashtable(true);

	vector<pair<string, int>> stringToHash = { {"a", 1}, {"l", 1}, {"w", 1} };
	//Check to make sure the hashtable hashes strings correctly to cause collisions
	for(auto stringHash : stringToHash) {
		EXPECT_EQ(stringHash.second, hashtable.hash(stringHash.first));
	}

	EXPECT_EQ(0, hashtable.add("a", 10));
	EXPECT_EQ(1, hashtable.add("l", 20));
	EXPECT_EQ(2, hashtable.add("w", 30));

	EXPECT_EQ(10, hashtable.lookup("a"));
	EXPECT_EQ(20, hashtable.lookup("l"));
	EXPECT_EQ(30, hashtable.lookup("w"));

	stringstream ss;
	string expected = "a 10\nl 20\nw 30\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());
}

TEST(HashtableTest, ResizingCorrectly)
{
	Hashtable<int> hashtable(true, 3);

	vector<pair<string, int>> stringToHash = { {"g", 1}, {"d", 1} };
	//Check to make sure the hashtable hashes strings correctly to cause collisions
	for(auto stringHash : stringToHash) {
		EXPECT_EQ(stringHash.second, hashtable.hash(stringHash.first));
	}

	EXPECT_EQ(0, hashtable.add("g", 10));
	EXPECT_EQ(0, hashtable.add("d", 20)); // Does not cause collision because table resizes
	EXPECT_EQ(4, hashtable.hash("d"));

	EXPECT_EQ(10, hashtable.lookup("g"));
	EXPECT_EQ(20, hashtable.lookup("d"));

	stringstream ss;
	string expected = "d 20\ng 10\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());
}

TEST(HashtableTest, OnlyCollisionsResizing)
{
	Hashtable<int> hashtable(true);

	vector<pair<string, int>> stringToHash = { {"ag", 1}, {"ar", 1}, {"bb", 1}, {"bm", 1}, {"bx", 1}, {"ch", 1}, {"cs", 1} };
	//Check to make sure the hashtable hashes strings correctly to cause collisions
	for(auto stringHash : stringToHash) {
		EXPECT_EQ(stringHash.second, hashtable.hash(stringHash.first));
	}

	EXPECT_EQ(0, hashtable.add("ag", 10));
	EXPECT_EQ(1, hashtable.add("ar", 20));
	EXPECT_EQ(2, hashtable.add("bb", 30));
	EXPECT_EQ(3, hashtable.add("bm", 40));
	EXPECT_EQ(4, hashtable.add("bx", 50));

	EXPECT_EQ(10, hashtable.lookup("ag"));
	EXPECT_EQ(20, hashtable.lookup("ar"));
	EXPECT_EQ(30, hashtable.lookup("bb"));
	EXPECT_EQ(40, hashtable.lookup("bm"));
	EXPECT_EQ(50, hashtable.lookup("bx"));

	stringstream ss;
	string expected = "ag 10\nar 20\nbb 30\nbx 50\nbm 40\n";
	hashtable.reportAll(ss);
	EXPECT_EQ(expected, ss.str());

	//Resize now
	EXPECT_EQ(0, hashtable.add("ch", 60)); 	//Resize on this call
	EXPECT_EQ(0, hashtable.add("cs", 70));

	EXPECT_EQ(10, hashtable.lookup("ag"));
	EXPECT_EQ(20, hashtable.lookup("ar"));
	EXPECT_EQ(30, hashtable.lookup("bb"));
	EXPECT_EQ(40, hashtable.lookup("bm"));
	EXPECT_EQ(50, hashtable.lookup("bx"));
	EXPECT_EQ(60, hashtable.lookup("ch"));
	EXPECT_EQ(70, hashtable.lookup("cs"));

	stringstream ss2;
	string expected2 = "ag 10\nar 20\nbb 30\nbm 40\nbx 50\nch 60\ncs 70\n";
	hashtable.reportAll(ss2);
	EXPECT_EQ(expected2, ss2.str());
}

string generateStringFromInt(int num) {
	string str = "aaaa";
	for(int i = str.size()-1 ; i >= 0; i--) {
		str[i] += num % 26;
		num /= 26;
	}
	return str;
}

TEST(HashtableTest, ResizingMultiple)
{
	Hashtable<int> hashtable(true);

	string input("a");
	unsigned long long hash = 261934300;

	//Check for resizing at correct times
	vector<int> sizes = {11, 23, 47, 97, 197, 397};
	vector<int> resizeSize = {6, 12, 24, 49, 99, 199};
	int currentSizeIndex = 0;
	for(int i = 0; i < 100; i++) {
		//Add value
		hashtable.add(generateStringFromInt(i), i);
		//Check to see if the table should resize
		if(i + 1 == resizeSize[currentSizeIndex]) {
			currentSizeIndex++;
		}
		//Check to make sure the hashtable resized by hashing a for the modulus value
		EXPECT_EQ(hash % sizes[currentSizeIndex], hashtable.hash("a"));
	}

	//Check to make sure all values still in hashtable
	for(int i = 0; i < 100; i++) {
		EXPECT_EQ(i, hashtable.lookup(generateStringFromInt(i)));
	}
}

TEST(HashtableTest, InsertStress)
{
	int NUM_INSERTS = 400000;

	Hashtable<int> hashtable(true);
	//Add values
	for(int i = 0; i < NUM_INSERTS; i++) {
		hashtable.add(generateStringFromInt(i), i);
	}
	//Check for values
	for(int i = 0; i < NUM_INSERTS; i++) {
		EXPECT_EQ(i, hashtable.lookup(generateStringFromInt(i)));
	}
}