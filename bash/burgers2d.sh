cd ..
make clean
make

./bin/burgers 1

python3 ./python/quiver.py
open ./results/inviscidBurgers2d_quiver.mp4

cd bash