// The most simple C++ program to demonstrate jammed system
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <random>
using namespace std;

#define dim 2
#define N1 50
#define N2 50
#define a1 1.0
#define a2 1.4
#define phi 0.8     // Packing fraction

void init_config(double (*x)[dim], double *a, double *L) {
    for (int i = 0; i < N1; ++i) {
        a[i] = a1; // Set radius for first type of particles
    }
    for (int i = N1; i < N1 + N2; ++i) {
        a[i] = a2; // Set radius for second type of particles
    }

    *L = sqrt(M_PI * (a1 * a1 * N1 + a2 * a2 * N2) / phi); // Calculate box size based on packing fraction
    cout << "Box size L = " << *L << endl;

    for (int i = 0; i < N1+N2; ++i) {
        for (int j = 0; j < dim; ++j) {
            x[i][j] = (double)rand() / RAND_MAX * (*L); // Initialize coordinates
        }
    }
}

void output_config(double (*x)[dim], double *a) {
    ofstream outfile("config.dat");
    if (!outfile) {
        cout << "Error opening file for output." << endl;
        return;
    }
    for(int i = 0; i < N1 + N2; ++i) {
        outfile << i+1 << "\t" << a[i] << "\t" << x[i][0] << "\t" << x[i][1] << endl;
    }
    outfile.close();
    cout << "Configuration is saved to config.txt" << endl;
}

int main(){
    double L; // Box size based on packing fraction
    double x[N1+N2][dim], a[N1+N2];

    // initialize configuration
    init_config(x, a, &L);

    // output configuration to file
    output_config(x, a);


    return 0;
}