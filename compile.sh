rm "$1.out"
gcc -fopenmp "$1" -o "$1.out"
./"$1.out"