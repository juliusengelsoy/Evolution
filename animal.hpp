//
//  animal.hpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#ifndef animal_hpp
#define animal_hpp

#include <vector>
#include <stdio.h>
using namespace std;

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
    vector<int> location;
    double foodRequirement;
    double food;
    bool foodPrivelege = true;
    bool toDie = false;
    
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
           vector<int> location,
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
    void setLocation(vector<int> location);
    void setFoodRequirement(double foodRequirement);
    void setFoodPrivelege(bool priv);
    void setToDie(bool die);
    
    double getStrength() const;
    double getFoodFindingAbility() const;
    double getFriendliness() const;
    double getSize() const;
    bool getSex() const;
    int getAge() const;
    double getBeauty() const;
    int getLongevity() const;
    double getHealth() const;
    vector<int> getLocation() const;
    double getFoodRequirement() const;
    double getFood() const;
    bool getFoodPrivelege() const;
    bool getToDie() const;
    
    void eat(double food);
    void clearFood();
    void step(int dx, int dy);
    
    bool operator== (const Animal& other) const;
    
};

#endif /* animal_hpp */
