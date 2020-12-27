//
//  main.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "printer.hpp"
#include "world.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    vector<double> binSizes(8, 1.0);
    Printer printer(binSizes, "/Users/Julius/Documents/Evolution/Evolution/Evolution/");
    World world(100, //sizeWorld
                10, //stepsPerDay
                100, //ageWorld
                100, //numOfAnimals
                10, //foodSparseness
                10.0, //foodSize
                printer);
    return 0;
}
