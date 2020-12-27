//
//  printer.hpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-27.
//

#ifndef printer_hpp
#define printer_hpp

#include <stdio.h>
#include "animal.hpp"
#include <vector>
#include <string>
using namespace std;

class Printer
{
private:
    vector<vector<double>> strengthStorer;
    vector<vector<double>> foodFindingAbilityStorer;
    vector<vector<double>> friendlinessStorer;
    vector<vector<double>> sizeStorer;
    vector<vector<double>> beautyStorer;
    vector<vector<double>> longevityStorer;
    vector<vector<double>> healthStorer;
    vector<vector<double>> foodRequirementStorer;
    vector<int> children;
    vector<int> deathsFromStarvation;
    vector<int> deathsFromAge;
    vector<int> deathsFromFighting;
    vector<double> histogramBinSizes;
    vector<vector<double>> mean;
    vector<vector<double>> correlation;
    string path;
public:
    Printer(vector<double> histogramBinSizes, string path);
    void traitStore(vector<Animal> animals);
    void addChildren(int numOfChildren);
    void addDeathsFromStarvation(int numOfDeathsFromStarvation);
    void addDeathsFromAge(int numOfDeathsFromAge);
    void addDeathsFromFighting(int numOfDeathsFromFighting);
    vector<double> insert(vector<double> vec, double elem, int index);
    vector<double> add(vector<double> vec, int index);
    vector<double> fill(vector<double> vec, int index);
    void print();
};

#endif /* printer_hpp */
