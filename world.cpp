//
//  world.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#include "world.hpp"
#include <stdio.h>
#include <algorithm>
#include <vector>
#include "animal.hpp"
#include "life.hpp"
#include <random>
using namespace std;

World::World(int sizeWorld, int stepsPerDay, int ageWorld, int numOfAnimals, int foodSparseness, int foodSize){
    this->sizeWorld = sizeWorld;
    this->stepsPerDay = stepsPerDay;
    this->ageWorld = ageWorld;
    this->numOfAnimals = numOfAnimals;
    this->day = 1;
    this->step = 0;
    this->foodSparseness = foodSparseness;
    this->foodSize = foodSize;
    
    default_random_engine eng;
    normal_distribution<double> distribution(0.0,0.3);
    vector<Animal> animals;
    
    Life life;
    
    for (int i = 0; i < this->numOfAnimals; i++) {
        double strength = 10*exp(distribution(eng));
        double foodFindingAbility = 10*exp(distribution(eng));
        double friendliness = 10*exp(distribution(eng));
        double size = 10*exp(distribution(eng));
        bool sex = rand() % 2;
        int age = 0;
        double beauty = 10*exp(distribution(eng));
        int longevity = (int)100*exp(distribution(eng));
        double health = 10*exp(distribution(eng));
        vector<int> location{ rand() % this->sizeWorld, rand() % this->sizeWorld };
        double foodRequirement = life.foodRequirementCalculate(strength, foodFindingAbility, friendliness, size, age, beauty, health);
        double food = 0.0;
        Animal a(strength,
                 foodFindingAbility,
                 friendliness,
                 size,
                 sex,
                 age,
                 beauty,
                 longevity,
                 health,
                 location,
                 foodRequirement,
                 food);
        animals.push_back(a);
    }
    
    for (int i = 0; i < this->ageWorld; i++) {
        for (vector<Animal>::iterator it=animals.begin(); it!=animals.end();it++){
            if(it->getAge()==it->getLongevity())
                animals.erase(it--);
        }
        
        for (int j = 0; j < this->stepsPerDay; j++) {
            vector<vector<int>> locations;
            vector<vector<Animal>> animalsGroupedAfterLocation;
            for (vector<Animal>::iterator animalIt=animals.begin(); animalIt!=animals.end();animalIt++){
                vector<vector<int>>::iterator locationIt = find(locations.begin(), locations.end(), animalIt->getLocation());
                if(locationIt != locations.end()){
                    animalsGroupedAfterLocation[locationIt-locations.begin()].push_back(*animalIt);
                }
                else{
                    locations.push_back(*locationIt);
                    vector<Animal> animalGroup;
                    animalGroup.push_back(*animalIt);
                    animalsGroupedAfterLocation.push_back(animalGroup);
                }
            }
            for (vector<vector<Animal>>::iterator animalsGroupedIt=animalsGroupedAfterLocation.begin();animalsGroupedIt!=animalsGroupedAfterLocation.end();animalsGroupedIt++) {
                if (animalsGroupedIt->size()>1) {
                    vector<vector<Animal>> animalPairs;
                    for (vector<Animal>::iterator animalIt1=animalsGroupedIt->begin(); animalIt1+1!=animalsGroupedIt->end();animalIt1++) {
                        for (vector<Animal>::iterator animalIt2=animalIt1+1; animalIt2!=animals.end();animalIt2++) {
                            animalPairs.push_back(vector<Animal> {*animalIt1,*animalIt2});
                        }
                    }
                    for (vector<vector<Animal>>::iterator animalPairsIt=animalPairs.begin();animalPairsIt!=animalPairs.end();animalPairsIt++) {
                        Animal a1 = (*animalPairsIt)[0];
                        Animal a2 = (*animalPairsIt)[1];
                        if(life.canMate(a1,a2)){
                            if (rand() % 100 > 30) {
                                Animal c = life.mate(a1, a2);
                                animals.push_back(c);
                            }
                        }
                        else{
                            if(a1.getFriendliness() < 15 || a2.getFriendliness() < 15){
                                if(life.fight(a1, a2)==1){
                                    double damage = a1.getStrength()-a2.getStrength();
                                    double newHealth = a2.getHealth()-damage;
                                    if (newHealth <= 0.0) {
                                        animals.erase(remove(animals.begin(), animals.end(), a2), animals.end());
                                    }
                                    else{
                                        vector<Animal>::iterator an = find(animals.begin(), animals.end(), a2);
                                        an->setHealth(an->getHealth()-damage);
                                    }
                                }
                                else{
                                    double damage = a2.getStrength()-a1.getStrength();
                                    double newHealth = a1.getHealth()-damage;
                                    if (newHealth <= 0.0) {
                                        animals.erase(remove(animals.begin(), animals.end(), a1), animals.end());
                                    }
                                    else{
                                        vector<Animal>::iterator an = find(animals.begin(), animals.end(), a1);
                                        an->setHealth(an->getHealth()-damage);
                                    }
                                }
                            }
                        }
                    }
                }
                if (animalsGroupedIt->size() == 1) {
                    Animal a = (*animalsGroupedIt)[0];
                    if (a.getLocation()[0] % this->foodSparseness == 0 && a.getLocation()[1] % this->foodSparseness == 0) {
                        double foodToEat = max(a.getFoodRequirement(),this->foodSize);
                        a.eat(foodToEat);
                    }
                }
            }
        }
        
    }
    
    
}
