//
//  animal.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#include "animal.hpp"

Animal::Animal(double strength,
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
               double food){
    this->strength = strength;
    this->foodFindingAbility = foodFindingAbility;
    this->friendliness = friendliness;
    this->size = size;
    this->sex = sex;
    this->age = age;
    this->beauty = beauty;
    this->longevity = longevity;
    this->health = health;
    this->location[0] = location[0];
    this->location[1] = location[1];
    this->foodRequirement = foodRequirement;
    this->food = food;
}
//void Animal::setStrength(double strength){
//    this->strength = strength;
//}
//void Animal::setFoodFindingAbility(double foodFindingAbility){
//    this->foodFindingAbility = foodFindingAbility;
//}
//void Animal::setFriendliness(double friendliness){
//    this->friendliness = friendliness;
//}
//void Animal::setSize(double size){
//    this->size = size;
//}
//void Animal::setSex(bool sex){
//    this->sex = sex;
//}
//void Animal::setAge(int age){
//    this->age = age;
//}
//void Animal::setBeauty(double beauty){
//    this->beauty = beauty;
//}
//void Animal::setLongevity(int longevity){
//    this->longevity = longevity;
//}
void Animal::setHealth(double health){
    this->health = health;
}
void Animal::setLocation(int* location){
    this->location[0] = location[0];
    this->location[1] = location[1];
}
void Animal::setFoodRequirement(double foodRequirement){
    this->foodRequirement = foodRequirement;
}
void Animal::eat(double food){
    this->food += food;
}
void Animal::clearFood(){
    this->food = 0.0;
}

double Animal::getStrength(){
    return this->strength;
}
double Animal::getFoodFindingAbility(){
    return this->foodFindingAbility;
}
double Animal::getFriendliness(){
    return this->friendliness;
}
double Animal::getSize(){
    return this->size;
}
bool Animal::getSex(){
    return this->sex;
}
int Animal::getAge(){
    return this->age;
}
double Animal::getBeauty(){
    return this->beauty;
}
int Animal::getLongevity(){
    return this->longevity;
}
double Animal::getHealth(){
    return this->health;
}
int* Animal::getLocation(){
    return this->location;
}
double Animal::getFoodRequirement(){
    return this->foodRequirement;
}

double Animal::foodRequirementCalculate(double strength,
                       double foodFindingAbility,
                       double friendliness,
                       double size,
                       //bool sex,
                       int age,
                       double beauty,
                       double health){
    return (strength + foodFindingAbility + friendliness + size + beauty - health - age);//*(1+0.2*(double)sex);
}
