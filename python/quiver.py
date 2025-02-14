import matplotlib.pyplot as plt
import matplotlib.animation as anim
import numpy as np

def updateQuiver(frame, q):
    q.set_UVC(frame[0], frame[1])

def writeQuiver2d(filename, u, v, x, y, delay_ms, xticks, yticks):
    fig, ax = plt.subplots()
    quiverPlot = ax.quiver(x, y, u[0], v[0], pivot='mid')
    ax.set_aspect('equal')
    ax.set_xticks(xticks)
    ax.set_yticks(yticks)
    anim_kwargs = {
        'blit': False,
        'cache_frame_data': False,
        'fargs': (quiverPlot,),
        'frames': [(u[i], v[i]) for i in range(u.shape[0])],
        'interval': delay_ms,
    }   
    quiver_anim = anim.FuncAnimation(fig, updateQuiver, **anim_kwargs)
    quiver_anim.save(filename)

def writeInviscidBurgers2d():
    filepath_prefix = './results/inviscidBurgers2d_'
    u_suffix = 'u.txt'
    v_suffix = 'v.txt'
    quiver_suffix = 'quiver.mp4'
    ny = 64
    d = 2 # decimation factor
    playback = 0.4 # playback speedup factor
    u = np.loadtxt(filepath_prefix+u_suffix, delimiter=',')
    u.shape = (u.shape[0]//ny, ny, u.shape[1])
    v = np.loadtxt(filepath_prefix+v_suffix, delimiter=',')
    v.shape = (v.shape[0]//ny, ny, v.shape[1])
    x = np.linspace(-2.0, 2.0, u.shape[2]//d, endpoint=False)
    y = np.linspace(-2.0, 2.0, ny//d, endpoint=False)
    delay_ms = (2000.0-0.0)/(playback*u.shape[0])
    xticks = [-2.0, 0.0, 2.0]
    yticks = [-2.0, 0.0, 2.0]
    writeQuiver2d(filepath_prefix+quiver_suffix, u[:,::d,::d],
                  v[:,::d,::d], x, y, delay_ms, xticks, yticks)

def writeInviscidBurgers2dExplicit():
    filepath_prefix = './results/inviscidBurgers2dExplicit_'
    u_suffix = 'u.txt'
    v_suffix = 'v.txt'
    quiver_suffix = 'quiver.mp4'
    ny = 256
    d = 8 # decimation factor
    playback = 0.2 # playback speedup factor
    u = np.loadtxt(filepath_prefix+u_suffix, delimiter=',')
    u.shape = (u.shape[0]//ny, ny, u.shape[1])
    v = np.loadtxt(filepath_prefix+v_suffix, delimiter=',')
    v.shape = (v.shape[0]//ny, ny, v.shape[1])
    x = np.linspace(-2.0, 2.0, u.shape[2]//d, endpoint=False)
    y = np.linspace(-2.0, 2.0, ny//d, endpoint=False)
    delay_ms = (2000.0-0.0)/(playback*u.shape[0])
    xticks = [-2.0, 0.0, 2.0]
    yticks = [-2.0, 0.0, 2.0]
    writeQuiver2d(filepath_prefix+quiver_suffix, u[:,::d,::d],
                  v[:,::d,::d], x, y, delay_ms, xticks, yticks)

def main():
    writeInviscidBurgers2d()
    # writeInviscidBurgers2dExplicit()

if __name__ == '__main__':
    main()