#!/bin/bash
make; ./LifeGame
convert -delay 10 -scale 1000% ./images/*.pbm ./results/LifeGame_Result_$(cat suffix.txt).gif
echo "End."
rm -rf ./*.o ./LifeGame ./suffix.txt ./images/*.pbm
