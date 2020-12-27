//
//  animal.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#include "animal.hpp"
#include <vector>
using namespace std;

Animal::Animal(double strength,
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
    this->location = location;
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
void Animal::setAge(int age){
    this->age = age;
}
//void Animal::setBeauty(double beauty){
//    this->beauty = beauty;
//}
//void Animal::setLongevity(int longevity){
//    this->longevity = longevity;
//}
void Animal::setHealth(double health){
    this->health = health;
}
void Animal::setLocation(vector<int> location){
    this->location = location;
}
void Animal::setFoodRequirement(double foodRequirement){
    this->foodRequirement = foodRequirement;
}
void Animal::setFoodPrivelege(bool priv){
    this->foodPrivelege = priv;
}
void Animal::setToDie(bool die){
    this->toDie = die;
}
void Animal::setIsChild(bool ch){
    this->isChild = ch;
}

double Animal::getStrength() const{
    return this->strength;
}
double Animal::getFoodFindingAbility() const{
    return this->foodFindingAbility;
}
double Animal::getFriendliness() const{
    return this->friendliness;
}
double Animal::getSize() const{
    return this->size;
}
bool Animal::getSex() const{
    return this->sex;
}
int Animal::getAge() const{
    return this->age;
}
double Animal::getBeauty() const{
    return this->beauty;
}
int Animal::getLongevity() const{
    return this->longevity;
}
double Animal::getHealth() const{
    return this->health;
}
vector<int> Animal::getLocation() const{
    return this->location;
}
double Animal::getFoodRequirement() const{
    return this->foodRequirement;
}
double Animal::getFood() const{
    return this->food;
}
bool Animal::getFoodPrivelege() const{
    return this->foodPrivelege;
}
bool Animal::getToDie() const{
    return this->toDie;
}
bool Animal::getIsChild() const{
    return this->isChild;
}

void Animal::eat(double food){
    this->food += food;
}
void Animal::clearFood(){
    this->food = 0.0;
}
void Animal::step(int dx, int dy){
    this->location[0] += dx;
    this->location[1] += dy;
}

bool Animal::operator==(const Animal& other) const {
    return (this->age == other.getAge()
            && this->beauty == other.getBeauty()
            && this->sex == other.getSex()
            && this->foodFindingAbility == other.getFoodFindingAbility()
            && this->friendliness == other.getFriendliness()
            && this->food == other.getFood()
            && this->foodRequirement == other.getFoodRequirement()
            && this->health == other.getHealth()
            && this->location == other.getLocation()
            && this->longevity == other.getLongevity()
            && this->size == other.getSize()
            && this->strength == other.getStrength()
            && this->foodPrivelege == other.getFoodPrivelege()
            && this->toDie == other.getToDie());
}

