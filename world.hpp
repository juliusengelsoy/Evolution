//
//  world.hpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <vector>
#include "animal.hpp"
#include "life.hpp"
using namespace std;

class World
{
private:
    int sizeWorld;
    int day;
    int numOfAnimals;
    vector<Animal> animals;
    int step;
    int stepsPerDay;
    int ageWorld;
    int foodSparseness;
    double foodSize;
    
public:
    World(int sizeWorld, int stepsPerDay, int ageWorld, int numOfAnimals, int foodSparseness, int foodSize);
    void randomStep(Animal a);
};

#endif /* world_hpp */
