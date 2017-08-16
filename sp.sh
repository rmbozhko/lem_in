./gen $(( $RANDOM % 10 + 1)) $(( $RANDOM % 10 + 5)) > tests/test2 && clear && make re  && ./lem-in < tests/test2
#./lem-in.dms < tests/test2
