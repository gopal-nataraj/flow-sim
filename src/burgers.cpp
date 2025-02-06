#include <cmath>
#include <cstring>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <omp.h>

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
        omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel for
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

int inviscidBurgers2d(const double* u_0yx,
                      const double* v_0yx,
                      const int& nt,
                      const int& ny,
                      const int& nx,
                      const double& dt,
                      const double& dy,
                      const double& dx,
                      const double& tol,
                      double* u,
                      double* v) {
    if ((nx<2)||(ny<2)||(nt<2)) return FAILURE;
    for (int i=0; i<nt; ++i) {
        std::memcpy(&u[i*ny*nx], u_0yx, ny*nx*sizeof(double));
        std::memcpy(&v[i*ny*nx], v_0yx, ny*nx*sizeof(double));
    }
    double* uOld = new double[nt*ny*nx];
    double* vOld = new double[nt*ny*nx];
    Eigen::Matrix2d A;
    Eigen::Vector2d b, x;
    double diff;
    do {
        std::memcpy(uOld, u, nt*ny*nx*sizeof(double));
        std::memcpy(vOld, v, nt*ny*nx*sizeof(double));
        omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel for
        for (int i=1; i<nt; ++i) {
            for (int j=1; j<ny; ++j) {
                for (int k=1; k<nx; ++k) {
                    A(0,0) = (1.0/dt + (2*uOld[i*ny*nx+j*nx+k]-uOld[i*ny*nx+j*nx+(k-1)])/dx
                              + vOld[i*ny*nx+j*nx+k]/dy);
                    A(0,1) = (uOld[i*ny*nx+j*nx+k]-uOld[i*ny*nx+(j-1)*nx+k])/dy;
                    A(1,0) = (vOld[i*ny*nx+j*nx+k]-vOld[i*ny*nx+j*nx+(k-1)])/dx;
                    A(1,1) = (1.0/dt + uOld[i*ny*nx+j*nx+k]/dx 
                              + (2*vOld[i*ny*nx+j*nx+k]-vOld[i*ny*nx+(j-1)*nx+k])/dy);
                    b(0) = (uOld[(i-1)*ny*nx+j*nx+k]/dt + pow(uOld[i*ny*nx+j*nx+k], 2.0)/dx
                            + uOld[i*ny*nx+j*nx+k]*vOld[i*ny*nx+j*nx+k]/dy);
                    b(1) = (vOld[(i-1)*ny*nx+j*nx+k]/dt + pow(vOld[i*ny*nx+j*nx+k], 2.0)/dy
                            + uOld[i*ny*nx+j*nx+k]*vOld[i*ny*nx+j*nx+k]/dx);
                    x = A.inverse() * b;
                    u[i*ny*nx+j*nx+k] = x(0);
                    v[i*ny*nx+j*nx+k] = x(1);
                }
            }
        }
        diff = 0.0;
        for (int i=0; i<nt; ++i) {
            for (int j=0; j<ny; ++j) {
                for (int k=0; k<nx; ++k) {
                    diff += std::abs(u[i*ny*nx+j*nx+k]-uOld[i*ny*nx+j*nx+k]);
                    diff += std::abs(v[i*ny*nx+j*nx+k]-vOld[i*ny*nx+j*nx+k]);
                }
            }
        }
        std::cout << diff << std::endl;
    } while (0); // (diff>tol);
    delete[] uOld;
    delete[] vOld;
    return SUCCESS;
}