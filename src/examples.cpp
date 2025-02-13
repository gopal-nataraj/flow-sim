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
        u_0x[i] = exp(-8.0*pow(x+1.0, 2.0)) + 1.5*exp(-16.0*pow(x+2.0, 2.0));
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

int testInviscidBurgers2d(void) {
    int nt = 512;
    int ny = 64;
    int nx = 64;
    double dt = (2.0-0.0)/nt;
    double ymin = -2.0;
    double dy = (2.0-ymin)/ny;
    double xmin = -2.0;
    double dx = (2.0-xmin)/nx;
    double* u_0yx = new double[ny*nx];
    double* v_0yx = new double[ny*nx];
    double y = ymin + dy/2.0;
    double x;
    for (int i=0; i<ny; ++i) {
        x = xmin + dx/2.0;
        for (int j=0; j<nx; ++j) {
            u_0yx[i*nx+j] = 1.0;
            if ((-1.0<x)&&(x<0.0)&&(-1.0<y)&&(y<0.0)) {
                u_0yx[i*nx+j] += 1.0;
            }
            v_0yx[i*nx+j] = u_0yx[i*nx+j];
            x += dx;
        }
        y += dy;
    }
    double tol = 0.001;
    double* u = new double[nt*ny*nx];
    double* v = new double[nt*ny*nx];
    if (inviscidBurgers2d(u_0yx, v_0yx, nt, ny, nx, dt, dy, dx, tol, u, v)!=SUCCESS)
        return FAILURE;
    if (writeToFile3d("results/inviscidBurgers2d_u.txt", nt, ny, nx, u)!=SUCCESS)
        return FAILURE;
    if (writeToFile3d("results/inviscidBurgers2d_v.txt", nt, ny, nx, v)!=SUCCESS)
        return FAILURE;
    delete[] u_0yx;
    delete[] v_0yx;
    delete[] u;
    delete[] v;
    return SUCCESS;
}

int testInviscidBurgers2dExplicit(void) {
    int nt = 1024;
    int ny = 256;
    int nx = 256;
    double dt = (2.0-0.0)/nt;
    double ymin = -2.0;
    double dy = (2.0-ymin)/ny;
    double xmin = -2.0;
    double dx = (2.0-xmin)/nx;
    double* u_0yx = new double[ny*nx];
    double* v_0yx = new double[ny*nx];
    double y = ymin + dy/2.0;
    double x;
    for (int i=0; i<ny; ++i) {
        x = xmin + dx/2.0;
        for (int j=0; j<nx; ++j) {
            u_0yx[i*nx+j] = -y*exp(-(x*x+y*y));
            v_0yx[i*nx+j] = +x*exp(-(x*x+y*y));
            x += dx;
        }
        y += dy;
    }
    double* u = new double[nt*ny*nx];
    double* v = new double[nt*ny*nx];
    if (inviscidBurgers2dExplicit(u_0yx, v_0yx, nt, ny, nx, dt, dy, dx, u, v)!=SUCCESS)
        return FAILURE;
    if (writeToFile3d("results/inviscidBurgers2dExplicit_u.txt", nt, ny, nx, u)!=SUCCESS)
        return FAILURE;
    if (writeToFile3d("results/inviscidBurgers2dExplicit_v.txt", nt, ny, nx, v)!=SUCCESS)
        return FAILURE;
    delete[] u_0yx;
    delete[] v_0yx;
    delete[] u;
    delete[] v;
    return SUCCESS;
}