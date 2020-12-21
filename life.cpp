//
//  life.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

//#include <stdlib.h>
#include "life.hpp"
#include "animal.hpp"
#include <random>
using namespace std;

Animal* Life::mate(Animal a1, Animal a2){
    default_random_engine eng;
    normal_distribution<double> distribution(0.0,0.1);
    Animal* c = new Animal(((a1.getStrength()+a2.getStrength())/2)*exp(distribution(eng)),
                              ((a1.getFoodFindingAbility()+a2.getFoodFindingAbility())/2)*exp(distribution(eng)),
                              ((a1.getFriendliness()+a2.getFriendliness())/2)*exp(distribution(eng)),
                              ((a1.getSize()+a2.getSize())/2)*exp(distribution(eng)),
                              rand() % 2,
                              0,
                              ((a1.getBeauty()+a2.getBeauty())/2)*exp(distribution(eng)),
                              (int)((a1.getLongevity()+a2.getLongevity())/2)*exp(distribution(eng)),
                              ((a1.getHealth()+a2.getHealth())/2)*exp(distribution(eng)),
                               a1.getLocation(),
                               0.0,
                               0.0);
    c->setFoodRequirement(c->foodRequirementCalculate(c->getStrength(),
                                                   c->getFoodFindingAbility(),
                                                   c->getFriendliness(),
                                                   c->getSize(),
                                                   //c->getSex(),
                                                   c->getAge(),
                                                   c->getBeauty(),
                                                   c->getHealth()));
    return c;
}

int Life::fight(Animal a1, Animal a2){
    default_random_engine eng;
    normal_distribution<double> distribution(2*(a1.getStrength()-a2.getStrength())/(a1.getStrength()+a2.getStrength()),0.1);
    if (distribution(eng)>0) {
        return 1;
    }
    return 2;
}
