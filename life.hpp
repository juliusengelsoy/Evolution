//
//  life.hpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#ifndef life_hpp
#define life_hpp

#include <stdio.h>
#include "animal.hpp"

class Life
{
public:
    Animal mate(Animal a1, Animal a2);
    int fight(Animal a1, Animal a2);
    bool canMate(Animal a1, Animal a2);
    double foodRequirementCalculate(double strength,
                                    double foodFindingAbility,
                                    double friendliness,
                                    double size,
                                    //bool sex,
                                    int age,
                                    double beauty,
                                    double health);
};
#endif /* life_hpp */
