#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <ctime>
#include <omp.h>
#define LOWER 0.1
#define UPPER 4.9
#define NUMTHREADS 4

using namespace std;

struct Points {
    private:
    int row;
    int col;
    double val;
    
    public:
    Points() { }

    int getRow() {
        return row;
    }
    int getCol() {
        return col;
    }
    double getVal() {
        return val;
    }
    void setRow(int r) {
        row = r;
    }
    void setCol (int c) {
        col = c;
    }
    void setVal (double v) {
        val = v;
    }
};

int totalRow, totalCol, elements;

void getSize(string inputFile) {
    ifstream fin(inputFile);
    istringstream sin;
    string srow, scol, selements;

    if (fin.is_open()) {
        string line;
        while (!fin.eof()) {
            getline(fin, line);
            if (line[0] != '%') {
                sin.str(line);
                sin >> srow >> scol >> selements;
                break;
            }
        }
        totalRow = stoi(srow);
        totalCol = stoi(scol);
        elements = stoi(selements);
        sin.clear();
    }
}

void readInput(string inputFile, vector<Points> &myMat, vector<double> &myVec) {
    ifstream fin(inputFile);
    if (fin.is_open()) {
        string line;
        while(!fin.eof()) {
            getline(fin, line);
            if (line[0] != '%') { break; }
        }
        unsigned int counter = 0;
        while(!fin.eof()) {
            double randomN;
            string sRow, sCol;
            int myRow, myCol;
            istringstream sin;
            string line;
            getline(fin, line);
            if (line == "") { break; }
            sin.str(line);
            sin >> sRow >> sCol;
            myRow = stoi(sRow) - 1;
            myCol = stoi(sCol) - 1;
            randomN = ((double) rand() / (double) RAND_MAX) * (UPPER - LOWER) + LOWER;
            myMat[counter].setRow(myRow); myMat[counter].setCol(myCol); myMat[counter].setVal(randomN);
            counter++;
        }
    }
    for (int i = 0; i < totalRow; i++) {
        double randomN;
        randomN = ((double) rand() / (double) RAND_MAX) * (UPPER - LOWER) + LOWER;
        myVec[i] = randomN;
    }       
}

void compute(vector<Points> myMat, vector<double> myVec, vector<double> &myOut) {
    #pragma omp parallel num_threads(NUMTHREADS) shared(myOut)
    {
        #pragma omp for schedule(static, 5)
        for (int i = 0; i < myMat.size(); i+=2) {
            myOut[myMat[i].getRow()] += myMat[i].getVal() * myVec[myMat[i].getCol()];
            myOut[myMat[i+1].getRow()] += myMat[i+1].getVal() * myVec[myMat[i+1].getCol()];
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        cerr << "Please add an input file" << endl;
        return 2;
    }

    clock_t start;
    double duration;
    cout << endl;

    cout << "Deploying " << NUMTHREADS << " threads" << endl;
    cout << "---------------------------------" << endl;

    for (int i = 1; i < argc; i++) {
        cout << "Running for input " << i << " " << argv[i] << endl;
        cout << "+++++++++++++++++++++++++++++++++" << endl;
        string inputFile = argv[i];
        getSize(inputFile);

        start = clock();
        // My implementation matrix and vectors
        vector<double> myVec, myOut;
        vector<Points> myMat;
        myVec.resize(totalRow);
        myMat.resize(elements);
        myOut.resize(totalRow);

        // Read in all the info and store
        readInput(inputFile, myMat, myVec);
        duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
        cout << "Time for reading in the file " << duration << endl;

        // Time my computation
        start = clock();
        compute(myMat, myVec, myOut);
        duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
        cout << "Time for execution using my implementation " << duration << endl;
        cout << "=================================" << endl << endl;
    }
}

