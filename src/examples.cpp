#include <cmath>
#include <string>

#include "burgers.hpp"
#include "util.hpp"

int testInviscidBurgers1d(void) {
    int nt = 512;
    double dt = (4.0-0.0)/nt;
    int nx = 256;
    double xmin = -3.0;
    double dx = (3.0-xmin)/nx;
    double* u_0x = new double[nx];
    double x = xmin;
    for (int i=0; i<nx; ++i) {
        u_0x[i] = exp(-8.0*pow(x+1.0, 2.0)) + exp(-16.0*pow(x+2.0, 2.0));
        x += dx;
    }
    double tol = 0.001;
    double* u = new double[nt*nx];
    if (inviscidBurgers1d(u_0x, nt, nx, dt, dx, tol, u)!=SUCCESS)
        return FAILURE;
    std::string filename = "results/inviscidBurgers1d.txt";
    if (writeToFile2d(filename, nt, nx, u)!=SUCCESS)
        return FAILURE;
    delete[] u_0x;
    delete[] u;
    return SUCCESS;
}