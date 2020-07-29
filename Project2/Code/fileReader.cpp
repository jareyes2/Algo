#include "fileReader.h"
#include <iostream>

fileReader::fileReader()
{
    openFile();
    //printFile();
}

// Opens the input file and stores each line into a vector
// That vector is stored in a vector of vectors
void fileReader::openFile (){
    ifstream inputFile ("intput.txt");

    while (getline(inputFile, line))
    {
        stringstream inStream (line);
        vector<int> tmpVect;
        int tmp;
        while (inStream >> tmp)
        {
            tmpVect.push_back(tmp);
        }
        values.push_back(tmpVect);
    }
    
    inputFile.close();
}

void fileReader::printFile() // Used for debugging
{
    for (vector<int> x : values)
    {
        for (int y : x)
        {
            cout << y << " ";
        }
        cout << "\n";
    }
}
// Returns the first integer of input file, which is the total number of 
// arrays to be processed
int fileReader::getCount() {return values.front().front(); }

// Returns the data array of integers used in the recursion 
vector<int> fileReader::getData(int _i) { return values[_i + 1]; }

// Returns the target integer
int fileReader::getTarget (int _i) { return values[_i][0]; }

// Returns the n value size
int fileReader::getSize (int _i) { return values[_i][1]; }

// Writes the values after the dynamic programming to an output file
void fileReader::outputFile (vector<int> _Order, vector<int> _NoOrder)
{
    ofstream outputFile("output.txt");
    for (int i = 0; i < getCount(); i++)
    {
         outputFile << _Order[i] << " " << _NoOrder[i] << "\n";
    }
}