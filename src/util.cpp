#include <fstream>
#include <string>

#include "util.hpp"

int writeToFile2d(const std::string& filename,
                  const int& nt,
                  const int& nx,
                  const double* u) {
    std::ofstream file(filename);
    for (int i=0; i<nt; ++i) {
        for (int j=0; j<nx; ++j) {
            file << u[i*nx+j] << ", ";
        }
        file << std::endl;
    }
    file.close();
    return SUCCESS;
}