clang++ -std=c++14 -O3 -Wall -march=native src/Main.cpp -o readqr `pkg-config --cflags --libs zbar` `pkg-config --cflags --libs opencv`
