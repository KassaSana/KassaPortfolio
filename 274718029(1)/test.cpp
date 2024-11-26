/*
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <src/avltree.h>
#include <fstream>
#include <iostream>
using namespace std;

TEST_CASE("Test Invalid Commands", "[1]") {
AVLTree GatorAVLTree;
ofstream outputFile("output.txt");
streambuf* coutBuffer = cout.rdbuf();
cout.rdbuf(outputFile.rdbuf());
GatorAVLTree.insert("Invalid Name", "1234567");
GatorAVLTree.insert("Invalid123", "12345678");
GatorAVLTree.search("NonExistentID");
GatorAVLTree.remove("ABCDEFGH");

GatorAVLTree.search("Random Name");
cout.rdbuf(coutBuffer);
outputFile.close();

ifstream generatedFile("output.txt");
string actualOutput((istreambuf_iterator<char>(generatedFile)), istreambuf_iterator<char>());

string expectedOutput = "unsuccessful\n"
                             "unsuccessful\n"
                             "unsuccessful\n"
                             "unsuccessful\n"
                             "unsuccessful\n";

REQUIRE(expectedOutput.size() == actualOutput.size());
REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Edge Cases", "[2]") {
AVLTree GatorAVLTree;

ofstream outputFile("output.txt");
streambuf* coutBuffer = cout.rdbuf();
cout.rdbuf(outputFile.rdbuf());

GatorAVLTree.insert("First", "12345678");
GatorAVLTree.remove("87654321");
GatorAVLTree.insert("First", "12345678");
GatorAVLTree.insert("Second", "22345678");
GatorAVLTree.insert("Third", "32345678");

cout.rdbuf(coutBuffer);
outputFile.close();

ifstream generatedFile("output.txt");
string actualOutput((istreambuf_iterator<char>(generatedFile)), istreambuf_iterator<char>());

string expectedOutput = "successful\n"
                             "unsuccessful\n"
                             "unsuccessful\n"
                             "successful\n"
                             "successful\n";

REQUIRE(expectedOutput.size() == actualOutput.size());
REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("All Rotation Cases", "[3]") {
AVLTree GatorAVLTree;

ofstream outputFile("output.txt");
streambuf* coutBuffer = cout.rdbuf();
cout.rdbuf(outputFile.rdbuf());

GatorAVLTree.insert("Left Rotation", "33333333");
GatorAVLTree.insert("Right Child", "44444444");
GatorAVLTree.insert("Right Rotation", "22222222");
GatorAVLTree.insert("Left Right", "11111111");
GatorAVLTree.insert("Mid Child", "00000000");
GatorAVLTree.insert("Right Left", "66666666");
GatorAVLTree.insert("Mid Right", "55555555");

cout.rdbuf(coutBuffer);
outputFile.close();

ifstream generatedFile("output.txt");
string actualOutput((istreambuf_iterator<char>(generatedFile)), istreambuf_iterator<char>());

string expectedOutput = "successful\n"
                             "successful\n"
                             "successful\n"
                             "successful\n"
                             "successful\n"
                             "successful\n";

REQUIRE(expectedOutput.size() == actualOutput.size());
REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Deletion Cases", "[4]") {
AVLTree GatorAVLTree;

ofstream outputFile("output.txt");
streambuf* coutBuffer = cout.rdbuf();
cout.rdbuf(outputFile.rdbuf());

GatorAVLTree.insert("Node A", "11111111");
GatorAVLTree.insert("Node B", "22222222");
GatorAVLTree.insert("Node C", "33333333");
GatorAVLTree.insert("Node D", "44444444");

GatorAVLTree.remove("44444444");
GatorAVLTree.remove("33333333");
GatorAVLTree.remove("22222222");

cout.rdbuf(coutBuffer);
outputFile.close();

ifstream generatedFile("output.txt");
string actualOutput((istreambuf_iterator<char>(generatedFile)), istreambuf_iterator<char>());

string expectedOutput = "successful\n"
                             "successful\n"
                             "successful\n"
                             "successful\n"
                             "successful\n"
                             "successful\n";

REQUIRE(expectedOutput.size() == actualOutput.size());
REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("Insert 100 nodes and remove 10 random nodes", "[5]") {
AVLTree GatorAVLTree;

ofstream outputFile("output.txt");
streambuf* coutBuffer = cout.rdbuf();
cout.rdbuf(outputFile.rdbuf());

for (int i = 1; i <= 100; ++i) {
GatorAVLTree.insert("Node " + to_string(i), to_string(10000000 + i));
}

for (int i = 1; i <= 10; ++i) {
GatorAVLTree.remove(to_string(10000000 + (i * 10)));
}

GatorAVLTree.printInorder();

cout.rdbuf(coutBuffer);
outputFile.close();

ifstream generatedFile("output.txt");
string actualOutput((istreambuf_iterator<char>(generatedFile)), istreambuf_iterator<char>());

string expectedOutput = "successful\n"
                             "successful\n"
                             "successful\n";

REQUIRE(actualOutput.size() > 0);
REQUIRE(1 == 1);
}
*/