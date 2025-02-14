cd ..
make clean
make

./bin/burgers 2

python3 ./python/quiver.py
open ./results/inviscidBurgers2dExplicit_quiver.mp4

cd bash
