//
//  animal.hpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#ifndef animal_hpp
#define animal_hpp

#include <stdio.h>

class Animal
{
private:
    double strength;
    double foodFindingAbility;
    double friendliness;
    double size;
    bool sex; //True is male and False is female
    int age;
    double beauty;
    int longevity;
    double health;
    int location[2];
    double foodRequirement;
    double food;
    
public:
    Animal(double strength,
           double foodFindingAbility,
           double friendliness,
           double size,
           bool sex,
           int age,
           double beauty,
           int longevity,
           double health,
           int* location,
           double foodRequirement,
           double food);
    //    void setStrength(double strength);
    //    void setFoodFindingAbility(double foodFindingAbility);
    //    void setFriendliness(double friendliness);
    //    void setSize(double size);
    //    void setSex(bool sex);
    //    void setAge(int age);
    //    void setBeauty(double beauty);
    //    void setLongevity(int longevity);
    void setHealth(double health);
    void setLocation(int* location);
    void setFoodRequirement(double foodRequirement);
    
    double getStrength();
    double getFoodFindingAbility();
    double getFriendliness();
    double getSize();
    bool getSex();
    int getAge();
    double getBeauty();
    int getLongevity();
    double getHealth();
    int* getLocation();
    double getFoodRequirement();
    
    void eat(double food);
    void clearFood();
    double foodRequirementCalculate(double strength,
                                    double foodFindingAbility,
                                    double friendliness,
                                    double size,
                                    //bool sex,
                                    int age,
                                    double beauty,
                                    double health);
};

#endif /* animal_hpp */
