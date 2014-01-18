
test $1 || exit 0
f=$1
g++ -o $f $f.cpp
grep '^>' $f.md|cut -b 2-|./$f && rm $f
