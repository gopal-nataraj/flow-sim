#include <string>

#define FAILURE 1
#define SUCCESS 0

int writeToFile2d(const std::string& filename,
                  const int& nt,
                  const int& nx,
                  const double* u);

int writeToFile3d(const std::string& filename,
                  const int& nt,
                  const int& ny,
                  const int& nx,
                  const double* u);