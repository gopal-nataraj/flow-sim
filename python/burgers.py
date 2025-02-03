import numpy as np

# solves u_t + u*u_x = 0
def inviscidBurgers1d(u_x0, x, t, tol=0.001):
    u = np.tile(u_x0, (len(t), 1)).T
    dx = x[1]-x[0]
    dt = t[1]-t[0]
    udiff = np.Inf
    while udiff>tol:
        uGuess = u.copy()
        for i in range(1, len(x)):
            for j in range(1, len(t)):
                u[i,j] = ((dx*uGuess[i,j-1] + dt*uGuess[i,j]**2)/
                          (dx + dt*(2*uGuess[i,j]-uGuess[i-1,j])))
        udiff = np.sum(np.abs(u-uGuess))
        print(udiff)
    return u

def testInviscidBurgers1d():
    x = np.linspace(-3.0, 3.0, 256, endpoint=False)
    u_x0 = np.exp(-8.0*(x+1.0)**2) + 1.5*np.exp(-16.0*(x+2.0)**2)
    t = np.linspace(0.0, 4.0, 512, endpoint=False)
    u = inviscidBurgers1d(u_x0, x, t)
    filename = '../results/inviscidBurgers1d.npz'
    np.savez(filename, x=x, t=t, u=u)
    
def main():
    testInviscidBurgers1d()
    
if __name__ == '__main__':
    main()
