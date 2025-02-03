#include <cmath>
#include <cstring>
#include <iostream>

#include "burgers.hpp"
#include "util.hpp"

int inviscidBurgers1d(const double* u_0x,
                      const int& nt,
                      const int& nx,
                      const double& dt,
                      const double& dx,
                      const double& tol,
                      double* u) {
    if ((nx<2)||(nt<2)) return FAILURE;
    for (int i=0; i<nt; ++i) {
        std::memcpy(&u[i*nx], u_0x, nx*sizeof(double));
    }
    double* uOld = new double[nt*nx];
    double udiff;
    do {
        std::memcpy(uOld, u, nt*nx*sizeof(double));
        for (int i=1; i<nt; ++i) {
            for (int j=1; j<nx; ++j) {
                u[i*nx+j] = ((dx*uOld[(i-1)*nx+j]+dt*pow(uOld[i*nx+j],2.0))/
                             (dx+dt*(2.0*uOld[i*nx+j]-uOld[i*nx+(j-1)])));
            }
        }
        udiff = 0.0;
        for (int i=0; i<nt; ++i) {
            for (int j=0; j<nx; ++j) {
                udiff += std::abs(u[i*nx+j]-uOld[i*nx+j]);
            }
        }
        std::cout << udiff << "\n";
    } while (udiff>tol);
    delete[] uOld;
    return SUCCESS;
}