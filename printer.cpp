//
//  printer.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-27.
//

#include "printer.hpp"
#include "animal.hpp"
#include <fstream>
using namespace std;

Printer::Printer(vector<double> histogramBinSizes, string path){
    this->histogramBinSizes = histogramBinSizes;
    this->path = path;
}
void Printer::traitStore(vector<Animal> animals){
    vector<double> strengthStorer;
    vector<double> foodFindingAbilityStorer;
    vector<double> friendlinessStorer;
    vector<double> sizeStorer;
    vector<double> beautyStorer;
    vector<double> longevityStorer;
    vector<double> healthStorer;
    vector<double> foodRequirementStorer;
    
    vector<double> sum(8,0.0);
    vector<vector<double>> covarianceSum(8,sum);
    vector<double> correlations;
    vector<double> mean = sum;
    int numOfAnimals = 0;
    for (Animal a : animals) {
        strengthStorer.push_back(a.getStrength());
        foodFindingAbilityStorer.push_back(a.getFoodFindingAbility());
        friendlinessStorer.push_back(a.getFriendliness());
        sizeStorer.push_back(a.getSize());
        beautyStorer.push_back(a.getBeauty());
        longevityStorer.push_back((double)a.getLongevity());
        healthStorer.push_back(a.getHealth());
        foodRequirementStorer.push_back(a.getFoodRequirement());
        numOfAnimals += 1;
        vector<double> sumTemp(8,0.0);
        vector<vector<double>> covarianceSumTemp(8,sumTemp);
        
        sumTemp[0] = a.getStrength();
        sumTemp[1] = a.getFoodFindingAbility();
        sumTemp[2] = a.getFriendliness();
        sumTemp[3] = a.getSize();
        sumTemp[4] = a.getBeauty();
        sumTemp[5] = a.getLongevity();
        sumTemp[6] = a.getHealth();
        sumTemp[7] = a.getFoodRequirement();
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                covarianceSumTemp[i][j] = sumTemp[i]*sumTemp[j];
            }
        }
        
        for (int i = 0; i < 8; i++) {
            sum[i] += sumTemp[i];
        }
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                covarianceSum[i][j] += covarianceSumTemp[i][j];
            }
        }
    }
    this->strengthStorer.push_back(strengthStorer);
    this->foodFindingAbilityStorer.push_back(foodFindingAbilityStorer);
    this->friendlinessStorer.push_back(friendlinessStorer);
    this->sizeStorer.push_back(sizeStorer);
    this->beautyStorer.push_back(beautyStorer);
    this->longevityStorer.push_back(longevityStorer);
    this->healthStorer.push_back(healthStorer);
    this->foodRequirementStorer.push_back(foodRequirementStorer);
    for (int i = 0; i < 8; i++) {
        mean[i] += sum[i]/numOfAnimals;
    }
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 8; j++) {
            correlations.push_back((covarianceSum[i][j]/numOfAnimals - mean[i]*mean[j])/(sqrt(covarianceSum[i][i]/numOfAnimals - mean[i]*mean[i])*sqrt(covarianceSum[j][j]/numOfAnimals - mean[j]*mean[j])));
        }
    }
    this->mean.push_back(mean);
    this->correlation.push_back(correlations);
};
void Printer::addChildren(int numOfChildren){
    this->children.push_back(numOfChildren);
};
void Printer::addDeathsFromStarvation(int numOfDeathsFromStarvation){
    this->deathsFromStarvation.push_back(numOfDeathsFromStarvation);
};
void Printer::addDeathsFromAge(int numOfDeathsFromAge){
    this->deathsFromAge.push_back(numOfDeathsFromAge);
};
void Printer::addDeathsFromFighting(int numOfDeathsFromFighting){
    this->deathsFromFighting.push_back(numOfDeathsFromFighting);
};
vector<double> Printer::insert(vector<double> vec, double elem, int index){
    if (index < vec.size()) {
        vec[index] = elem;
    }
    else{
        for (int i = (int)vec.size(); i < index; i++) {
            vec.push_back(0.0);
        }
        vec.push_back(elem);
    }
    return vec;
};
vector<double> Printer::add(vector<double> vec, int index){
    if (index < vec.size()) {
        vec[index] += 1;
    }
    else{
        for (int i = (int)vec.size(); i < index; i++) {
            vec.push_back(0.0);
        }
        vec.push_back(1.0);
    }
    return vec;
};
vector<double> Printer::fill(vector<double> vec, int index){
    if (index >= vec.size()) {
        for (int i = (int)vec.size(); i <= index; i++) {
            vec.push_back(0.0);
        }
    }
    return vec;
};

void Printer::print(){
    vector<vector<double>> histStrength;
    vector<vector<double>> histFoodFindingAbility;
    vector<vector<double>> histFriendliness;
    vector<vector<double>> histSize;
    vector<vector<double>> histBeauty;
    vector<vector<double>> histLongevity;
    vector<vector<double>> histHealth;
    vector<vector<double>> histFoodRequirement;
    
    vector<vector<vector<double>>> hists{histStrength, histFoodFindingAbility, histFriendliness, histSize, histBeauty, histLongevity, histHealth, histFoodRequirement};
    
    vector<string> traits{"strength", "foodFindingAbility", "friendliness", "size", "beauty", "longevity", "health", "foodRequirement"};
    
    vector<vector<vector<double>>> traitStorers{this->strengthStorer, this->foodFindingAbilityStorer, this->friendlinessStorer, this->sizeStorer, this->beautyStorer, this->longevityStorer, this->healthStorer};
    
    int maxIndex = -1;
    for (int i = 0; i < traits.size(); i++) {
        for (int j = 0; j < traitStorers[i].size(); j++) {
            for (int k = 0; traitStorers[i][j].size(); k++) {
                hists[i][j] = add(hists[i][j], (int)traitStorers[i][j][k]/this->histogramBinSizes[i]);
            }
            if (hists[i][j].size()-1>maxIndex) {
                maxIndex = (int)hists[i][j].size()-1;
            }
        }
        for (int j = 0; j < hists[i].size(); j++) {
            hists[i][j] = fill(hists[i][j], maxIndex);
        }
    }
    
    ofstream histogramFile;
    for (int i = 0; i < traits.size(); i++) {
        histogramFile.open(path + traits[i] + ".csv",ofstream::out);
        for (int j = 0; j < hists[i].size(); j++) {
            for (int k = 0; k < hists[i][j].size(); k++) {
                histogramFile << hists[i][j][k];
                if (k != hists[i][j].size() - 1) {
                    histogramFile << ", ";
                }
            }
            histogramFile << endl;
        }
        histogramFile.close();
    }
    
    vector<string> correlationTraits;
    for (int i = 0; i+1 < traits.size(); i++) {
        for (int j = i+1; j < traits.size(); j++) {
            correlationTraits.push_back(traits[i] + traits[j]);
        }
    }
    
    ofstream correlationFile;
    correlationFile.open(path + "correlations.csv",ofstream::out);
    for (int i = 0; i < correlationTraits.size(); i++) {
        correlationFile << correlationTraits[i];
        if(i != correlationTraits.size() - 1){
            correlationFile << ", ";
        }
    }
    correlationFile << endl;
    for (int j = 0; j < this->correlation[0].size(); j++) {
        for (int i = 0; i < this->correlation.size(); i++) {
            correlationFile << correlation[i][j];
            if(i != this->correlation.size() - 1){
                correlationFile << ", ";
            }
        }
        correlationFile << endl;
    }
    correlationFile.close();
    
    vector<string> otherData{"children", "deathsFromStarvation", "deathsFromAge", "deathsFromFighting"};
    
    ofstream dataFile;
    dataFile.open(path + "data.csv",ofstream::out);
    for (int i = 0; i < traits.size(); i++) {
        dataFile << traits[i] << ", ";
    }
    for (int i = 0; i < otherData.size(); i++) {
        dataFile << otherData[i] << ", ";
        if(i != otherData.size() - 1){
            correlationFile << ", ";
        }
    }
    dataFile << endl;
    for (int j = 0; j < this->correlation[0].size(); j++) {
        for (int i = 0; i < this->correlation.size(); i++) {
            dataFile << correlation[i][j] << ", ";
        }
        for (int i = 0; i < otherData.size(); i++) {
            dataFile << children[j] << ", ";
            dataFile << deathsFromStarvation[j] << ", ";
            dataFile << deathsFromAge[j] << ", ";
            dataFile << deathsFromFighting[j];
        }
        dataFile << endl;
    }
    dataFile.close();
};
