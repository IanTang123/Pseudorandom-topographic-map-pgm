# Pseudorandom-topographic-map-pgm
**BASIC EXPLANATION**
algorithm that generates a pseudorandom topographic map based on a seed, it will receive the name of an txt file containing in order: N, seed, roughness, A, B, C, D; the map will be a square matrix with numbers between 0 and 255.
N will define the size of the 2d array, where matrix[size][size] = (2^n) + 1, in other words, the matrix will always be odd (to have a middle value more easily)
seed will be a random number that will be used in srand();
roughness will be used in a formula to define the variation, where sorteia(roughness) = (2*roughness) * (rand()/rand_max) - roughness;
A, B, C, D will be the value of the for corners of the matrix, A = top left, B = top right, C = bottom left, D = bottom right;

**HOW TO USE**
You need to insert the name of a txt file with N, seed, roughness, A, B, C, D in that order, the txt file can have as many lines you want, where every line will contain all the parameters and will create a whole new matrix. Every line will create a new txt containing the matrix in PGM format, you can just change the extension to .pgm if you want to see it
