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
#define phi0 0.8     // Packing fraction
#define phi_max 1.0 // Maximum packing fraction
#define dphi 1e-3

void init_config(double (*x)[dim], double *a, double *phi, double *L) {
    *phi = phi0;
    *L = sqrt(M_PI * (a1 * a1 * N1 + a2 * a2 * N2) / (*phi)); // Calculate box size based on packing fraction
    cout << "Box size L = " << *L << endl;

    for (int i = 0; i < N1+N2; ++i) {
        for (int j = 0; j < dim; ++j) {
            x[i][j] = (double)rand() / RAND_MAX * (*L); // Initialize coordinates
        }
    }

    for (int i = 0; i < N1; ++i) {
        a[i] = a1; // Set radius for first type of particles
    }
    for (int i = N1; i < N1 + N2; ++i) {
        a[i] = a2; // Set radius for second type of particles
    }
}

void LE_boundary(double (*x)[dim], double *a, double *L) {
    // This function would handle periodic boundary conditions
    
}

void EoM(double (*x)[dim], double *a, double *L) {
    // This function would contain the equations of motion for the particles
    // For now, it is left empty as a placeholder
}

void qs_compression(double (*x)[dim], double *a, double *phi, double *L, double *p, double *txy) {
    // This function would handle the compression of the system
    for (int i = 0; i < N1 + N2; ++i) {
        for (int j = 0; j < dim; ++j) {
            x[i][j] *= (*p); // Scale positions based on pressure
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

void output_energy(double U, double p, double txy, double phi) {
    ofstream outfile("energy.dat", ios::app);
    if (!outfile) {
        cout << "Error opening file for output." << endl;
        return;
    }
    outfile << phi << "\t" << U << "\t" << p << "\t" << txy << endl;
    outfile.close();
}

int main(){
    double x[N1+N2][dim], a[N1+N2], f[N1+N2][dim]; // Particle positions, radii, and forces
    double phi, L, U, p, txy; // Box size based on packing fraction

    // initialize configuration
    init_config(x, a, &phi, &L);

    // compression
    for(phi = phi0; phi < phi_max; phi += dphi)
    {
        qs_compression(x, a, &phi, &L, &p, &txy);
        output_energy(U, p, txy, phi);
    }

    // output configuration to file
    output_config(x, a);


    return 0;
}