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
#include "printer.hpp"
using namespace std;

World::World(int sizeWorld, int stepsPerDay, int ageWorld, int numOfAnimals, int foodSparseness, double foodSize, Printer printer){
    this->sizeWorld = sizeWorld;
    this->stepsPerDay = stepsPerDay;
    this->ageWorld = ageWorld;
    this->numOfAnimals = numOfAnimals;
    this->day = 0;
    this->step = 0;
    this->foodSparseness = foodSparseness;
    this->foodSize = foodSize;
    
    unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine eng(seed);
    srand(seed);
    normal_distribution<double> distribution(0.0,0.3);
    vector<Animal> animals;
    
    Life life;
    
    for (int i = 0; i < this->numOfAnimals; i++) {
        double strength = this->traitMean*exp(distribution(eng));
        double foodFindingAbility = this->traitMean*exp(distribution(eng));
        double friendliness = this->traitMean*exp(distribution(eng));
        double size = this->traitMean*exp(distribution(eng));
        bool sex = rand() % 2;
        int age = 0;
        double beauty = this->traitMean*exp(distribution(eng));
        int longevity = (int)this->traitMean*exp(distribution(eng));
        double health = this->traitMean*exp(distribution(eng));
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
    
    this->animals = animals;
    
    for (int i = 0; i < this->ageWorld; i++) {
        
        int childrenToday = 0;
        int deathsFromStarvationToday = 0;
        int deathsFromAgeToday = 0;
        int deathsFromFightingToday = 0;
        
        for (int j = 0; j < this->stepsPerDay; j++) {
            vector<vector<int>> locations;
            vector<vector<Animal>> animalsGroupedAfterLocation;
            for (vector<Animal>::iterator animalIt=this->animals.begin(); animalIt!=this->animals.end();animalIt++){
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
            
            vector<Animal> newAnimals;
            
            for (vector<vector<Animal>>::iterator animalsGroupedIt=animalsGroupedAfterLocation.begin();animalsGroupedIt!=animalsGroupedAfterLocation.end();animalsGroupedIt++) {
                vector<Animal> animalGroup = *animalsGroupedIt;
                if (animalGroup.size()>1) {
                    vector<vector<reference_wrapper<Animal>>> animalPairs;
                    for (vector<Animal>::iterator animalIt1=animalGroup.begin(); animalIt1+1!=animalGroup.end(); animalIt1++) {
                        for (vector<Animal>::iterator animalIt2=animalIt1+1; animalIt2!=animalGroup.end();animalIt2++) {
                            animalPairs.push_back(vector<reference_wrapper<Animal>> {*animalIt1,*animalIt2});
                        }
                    }
                    for (vector<vector<reference_wrapper<Animal>>>::iterator animalPairsIt=animalPairs.begin();animalPairsIt!=animalPairs.end();animalPairsIt++) {
                        reference_wrapper<Animal> a1 = (*animalPairsIt)[0];
                        reference_wrapper<Animal> a2 = (*animalPairsIt)[1];
                        if (!a1.get().getToDie() && !a2.get().getToDie()) {
                            if(life.canMate(a1.get(),a2.get())){
                                if (rand() % 100 > 30) {
                                    Animal c = life.mate(a1, a2);
                                    newAnimals.push_back(c);
                                    childrenToday += 1;
                                }
                            }
                            else{
                                if(a1.get().getFriendliness() < 15 || a2.get().getFriendliness() < 15){
                                    if(life.fight(a1.get(), a2.get())==1){
                                        a2.get().setFoodPrivelege(false);
                                        double damage = a1.get().getStrength()-a2.get().getStrength();
                                        double newHealth = a2.get().getHealth()-damage;
                                        if (newHealth <= 0.0) {
                                            a2.get().setToDie(true);
                                            deathsFromFightingToday += 1;
                                        }
                                        else{
                                            a2.get().setHealth(newHealth);
                                        }
                                    }
                                    else{
                                        a1.get().setFoodPrivelege(false);
                                        double damage = a2.get().getStrength()-a1.get().getStrength();
                                        double newHealth = a1.get().getHealth()-damage;
                                        if (newHealth <= 0.0) {
                                            a1.get().setToDie(true);
                                            deathsFromFightingToday += 1;
                                        }
                                        else{
                                            a1.get().setHealth(newHealth);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (animalGroup[0].getLocation()[0] % this->foodSparseness == 0 && animalGroup[0].getLocation()[1] % this->foodSparseness == 0) {
                        double totalFoodRequirement = 0.0;
                        double maxFoodFindingAbility = 0.0;
                        for (vector<Animal>::iterator animalIt=animalGroup.begin(); animalIt!=animalGroup.end();animalIt++) {
                            Animal a = *animalIt;
                            if (a.getFoodPrivelege() && a.getFood()<a.getFoodRequirement()) {
                                totalFoodRequirement += a.getFoodRequirement();
                                if (a.getFoodFindingAbility() > maxFoodFindingAbility) {
                                    maxFoodFindingAbility = a.getFoodFindingAbility();
                                }
                                
                            }
                        }
                        for (vector<Animal>::iterator animalIt=animalGroup.begin(); animalIt!=animalGroup.end();animalIt++) {
                            Animal a = *animalIt;
                            bool willEat = maxFoodFindingAbility > 10*exp(distribution(eng));
                            if (!a.getToDie()) {
                                if (a.getFoodPrivelege() && a.getFood()<a.getFoodRequirement() && willEat) {
                                    double foodToEat = max(a.getFoodRequirement()-a.getFood(),  foodSize*a.getFoodRequirement()/totalFoodRequirement);
                                    a.eat(foodToEat);
                                }
                                bool west = a.getLocation()[0] <= 0;
                                bool east = a.getLocation()[0] >= this->sizeWorld;
                                bool south = a.getLocation()[1] <= 0;
                                bool north = a.getLocation()[1] >= this->sizeWorld;
                                a.step(1-(int)east-(rand()%2)*(2-(int)east-(int)west),1-(int)north-(rand()%2)*(2-(int)north-(int)south));
                                a.setFoodPrivelege(true);
                                newAnimals.push_back(a);
                            }
                        }
                    }
                }
                if (animalGroup.size() == 1) {
                    Animal a = animalGroup[0];
                    if (a.getLocation()[0] % this->foodSparseness == 0 && a.getLocation()[1] % this->foodSparseness == 0 && a.getFood()<a.getFoodRequirement()) {
                        if (a.getFoodFindingAbility() > 10*exp(distribution(eng))) {
                            double foodToEat = max(a.getFoodRequirement()-a.getFood(),this->foodSize);
                            a.eat(foodToEat);
                        }
                    }
                    bool west = a.getLocation()[0] <= 0;
                    bool east = a.getLocation()[0] >= this->sizeWorld;
                    bool south = a.getLocation()[1] <= 0;
                    bool north = a.getLocation()[1] >= this->sizeWorld;
                    a.step(1-(int)east-(rand()%2)*(2-(int)east-(int)west),1-(int)north-(rand()%2)*(2-(int)north-(int)south));
                    newAnimals.push_back(a);
                }
            }
            this->animals = newAnimals;
        }
        for (vector<Animal>::iterator animalIt=this->animals.begin(); animalIt!=this->animals.end();animalIt++) {
            if (animalIt->getFoodRequirement()>animalIt->getFood() && !animalIt->getIsChild()) {
                this->animals.erase(animalIt--);
                deathsFromStarvationToday += 1;
            }
            else if(animalIt->getAge()>=animalIt->getLongevity()){
                this->animals.erase(animalIt--);
                deathsFromAgeToday += 1;
            }
            else {
                animalIt->setIsChild(false);
                animalIt->clearFood();
                animalIt->setAge(animalIt->getAge() + 1);
            }
        }
        
        printer.traitStore(this->animals);
        printer.addDeathsFromAge(deathsFromAgeToday);
        printer.addDeathsFromFighting(deathsFromFightingToday);
        printer.addDeathsFromStarvation(deathsFromStarvationToday);
        printer.addChildren(childrenToday);
    }

    printer.print();
    
}
