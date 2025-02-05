int inviscidBurgers1d(const double* u_0x,
                      const int& nt,
                      const int& nx,
                      const double& dt,
                      const double& dx,
                      const double& tol,
                      double* u);

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
                      double* v);