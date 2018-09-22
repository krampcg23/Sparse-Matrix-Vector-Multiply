#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <vector>
#include <ctime>
#include <omp.h>
#define LOWER 0.1
#define UPPER 4.9
#define NUMTHREADS 2

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

bool myfunction (Points i, Points j) { 
    if (i.getRow() == j.getRow()) { 
        return i.getCol() < j.getCol(); 
    } else { return i.getRow() < j.getRow();}
}

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

void readInput(string inputFile, boost::numeric::ublas::mapped_matrix<double> &Mat, boost::numeric::ublas::vector<double> &Vec, vector<Points> &myMat, vector<double> &myVec) {
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
            Mat(myRow, myCol) = randomN;
            myMat[counter].setRow(myRow); myMat[counter].setCol(myCol); myMat[counter].setVal(randomN);
            counter++;
        }
    }
    for (int i = 0; i < totalRow; i++) {
        double randomN;
        randomN = ((double) rand() / (double) RAND_MAX) * (UPPER - LOWER) + LOWER;
        Vec(i) = randomN;
        myVec[i] = randomN;
    }       
}


void compute(vector<Points> myMat, vector<double> myVec, vector<double> &myOut) {
    #pragma omp parallel num_threads(NUMTHREADS) shared(myOut)
    {
        #pragma omp for schedule(auto)
        for (int i = 0; i < myMat.size(); i+=4) {
            #pragma omp atomic
            myOut[myMat[i].getRow()] += myMat[i].getVal() * myVec[myMat[i].getCol()];
            myOut[myMat[i+1].getRow()] += myMat[i+1].getVal() * myVec[myMat[i+1].getCol()];
            myOut[myMat[i+2].getRow()] += myMat[i+2].getVal() * myVec[myMat[i+2].getCol()];
            myOut[myMat[i+3].getRow()] += myMat[i+3].getVal() * myVec[myMat[i+3].getCol()];
        }
    }

}

double checkForErrors(boost::numeric::ublas::vector<double> Out, vector<double> myOut) {
    double maxError = 0.0;
    assert(Out.size() == myOut.size());
    for (int i = 0; i < Out.size(); i++) {
        if (abs(Out(i) - myOut[i]) > maxError) {
            cout << Out(i) << " " << myOut[i] << endl;
            maxError = abs(Out(i) - myOut[i]);
        }
        assert(abs(Out(i) - myOut[i]) < 0.000001);
    }
    return maxError;
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        cerr << "Please add an input file" << endl;
        return 2;
    }

    clock_t start;
    double duration;

    string inputFile = argv[1];
    getSize(inputFile);

    start = clock();
    // Boost matrix and vectors
    boost::numeric::ublas::mapped_matrix<double> Mat(totalRow,totalCol);
    boost::numeric::ublas::vector<double> Vec(totalRow), Out(totalRow);
    // My implementation matrix and vectors
    vector<double> myVec, myOut;
    vector<Points> myMat;
    myVec.resize(totalRow);
    myMat.resize(elements);
    myOut.resize(totalRow);
    // Read in all the info and store
    readInput(inputFile, Mat, Vec, myMat, myVec);
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Time for reading in the file " << duration << endl;

    // Time the boost computation
    start = clock();
    boost::numeric::ublas::axpy_prod(Mat, Vec, Out, true);
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Time for execution using BOOST " << duration << endl;


    // Time my computation
    double start_time = omp_get_wtime();
    compute(myMat, myVec, myOut);
    double time = omp_get_wtime() - start_time;
    cout << "Time for execution using my implementation " << time << endl;

    cout << "My implementation was " << duration / durationImp << " times faster" << endl;

    // Check for errors
    double error = checkForErrors(Out, myOut);
    cout << "Maximum error found between the two outputs is " << error << endl;
}

