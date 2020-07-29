#include "sums.h"

sums::sums()
{
    fileReader input;
    processSums(input);

    // Sends the two solution vectors to the fileReader class.
    // There they are written to the output file
    input.outputFile(OrderSolutions, NoOrderSolutions);
}


// Calls the wrapper functions for  order matters and order doesn't matter and stores the result into
// a vector for each that holds the solutions
void sums::processSums(fileReader _input)
{
    for (int i = 1; i < (_input.getCount()*2)+1; i+=2)
    {
        OrderSolutions.push_back(orderMattersWrapper(_input.getData(i), _input.getTarget(i), _input.getSize(i)));
        NoOrderSolutions.push_back(orderDoesntMatterWrapper(_input.getData(i), _input.getTarget(i), _input.getSize(i)) );
    }
}

// Dynamically allocates an array based on the target value
// Used for memoization
int sums::orderMattersWrapper(vector<int> _data, int _t, int _n) 
{
    int* orderTable = new int[_t+1]; 
    int numOM;
    // Initializes the array to 0
    for (int i = 0; i <= _t; i++) 
    {
        orderTable[i] = 0;
    }

    numOM = orderMatterMemo(orderTable, _data, _t, _n);
    delete orderTable;
    return numOM;
}

// Returns the number of sums given the data, target and size
int sums::orderMatterMemo(int* &_oT, vector<int> _data, int _t, int _n)
{
    int total = 0;
    
    // Memo Check
    if(_oT[_t] > 0)
    {
        return _oT[_t];
    }
    
    // Base Case
    if (_t == 0){
       _oT[0] = 1;
       return _oT[_t];
    }
    
    else if (_t < 0){
        return 0;
    }

    // Recursion
    else 
    {
        for (int i =0 ; i < _n; i++){
            if((_t-_data[i]) < 0) continue;
            total += orderMatterMemo(_oT, _data, _t-_data[i], _n);
           _oT[_t] = total;
        } 
    }
    return _oT[_t];

}


// Dynamically allocates a 2D array based on _n for row & _t for column 
// Used for memoization
int sums::orderDoesntMatterWrapper(vector<int> _data, int _t, int _n)
{
    int** noOrderTable = new int*[_n];
    for(int i = 0; i < _n; i++)
    {
        noOrderTable[i] = new int[_t+1];
    }

    int sumODM;

    // Initializes all values to 0s
    for (int i = 0; i < _n; i++)
    {
        for(int j = 0; j <= _t; j++)
        {
            noOrderTable[i][j] = 0;
        }
    }

    // Initializes the first column to all 1s
    for(int i = 0; i<_n; i++){
       noOrderTable[i][0] = 1;
   }

    sumODM = orderDoesntMatterMemo(noOrderTable, _data, _t, _n, 0);
    delete noOrderTable;
    return sumODM;
}

int sums::orderDoesntMatterMemo(int** &_nOT, vector<int> _data, int _t, int _n, int _x)
{
    
    if (_t == 0){
        return _nOT[_x][_t];
    }
    //base case 
    if (_t < 0){
        return 0;
    }
    
    if(_nOT[_x][_t] > 0){
        return _nOT[_x][_t];
    }

    // recursion    
    for (int i = _x; i < _n ; i++){
        _nOT[_x][_t] += orderDoesntMatterMemo(_nOT, _data, _t-_data[i],_n,i); 
    } 
    return _nOT[_x][_t];
}


