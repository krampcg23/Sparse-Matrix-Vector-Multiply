#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char* argv[]) {

    srand(time(NULL));
    int n = 5000;
    int input = 4000;
    ofstream out("matrix.txt");
    out << n << " " << n << " " << input <<  endl;

    for (int i = 0; i < input; i++) {
        int random = i+1;
        int random2 = rand() % (n - 5) + 2;
        if (i != input - 1) {
            out << random << " " << random2 << endl;
        } else {out << random << " " << random2;}
    }
    out.close();
}
