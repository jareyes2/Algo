#ifndef SUMS_H
#define SUMS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "fileReader.h"

class sums
{
    public:
        sums();
        
        void processSums(fileReader _input);
        void emptySolutioons();

        int orderMattersWrapper(vector<int> _data, int _t, int _n);
        int orderMatterMemo(int* &_oT, vector<int> _data, int _t, int _n);

        int orderDoesntMatterWrapper(vector<int> _data, int _t, int _n);
        int orderDoesntMatterMemo(int** &_nOT, vector<int> _data, int _t, int _n, int _x);        

    private:
        vector<int> OrderSolutions;
        vector<int> NoOrderSolutions;
};
#endif // SUMS_H