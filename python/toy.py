import matplotlib.pyplot as plt
import numpy as np

# solves u' + u**2 = 0, u[0] = u0
def nonlinear1d(u0, xvals, tol=0.001):
    u = u0 * np.ones(len(xvals))
    dx = xvals[1:] - xvals[:-1]
    udiff = np.Inf
    while udiff>tol:
        uGuess = u.copy()
        for i in np.arange(len(xvals)-1, 0, -1):
            u[i] = (uGuess[i-1]+uGuess[i]**2*dx[i-1])/(1+2*dx[i-1]*uGuess[i])
        udiff = np.sum(np.abs(u-uGuess))
    return u

def testNonlinear1d():
    u0 = 2.0
    xvals = np.linspace(0.0, 1.0, 128)
    u = nonlinear1d(u0, xvals)
    uexact = 1.0/(xvals+(1/u0))
    plt.plot(xvals, u)
    plt.plot(xvals, uexact)
    plt.legend(['numerical', 'exact'])
    plt.show()
    
def main():
    testNonlinear1d()
    
if __name__ == '__main__':
    main()
