#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class fileReader
{
    public: 
        fileReader();
        
        void openFile();
        void printFile();
        int getCount();
        vector<int> getData(int _i);
        int getTarget(int _i);
        int getSize(int _i);

        void outputFile(vector <int> _Order, vector<int> _NoOrder);
    
    private:
        string line;
        vector <vector<int>> values;

};
#endif // FILEREADER_H