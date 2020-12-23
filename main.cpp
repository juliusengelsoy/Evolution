//
//  main.cpp
//  Evolution
//
//  Created by Julius Engelsöy on 2020-12-20.
//

#include <iostream>
#include <vector>
#include <random>
using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> vect{1,2,3,4};
    vector<vector<int>> pairs;
    for (vector<int>::iterator it1=vect.begin(); it1+1!=vect.end(); it1++) {
        for (vector<int>::iterator it2=it1+1; it2!=vect.end();it2++) {
            pairs.push_back(vector<int> {*it1,*it2});
        }
    }
    for (int i = 0; i < pairs.size(); i++) {
        cout << "(" << pairs[i][0] << ", " << pairs[i][1] << ")" << endl;
    }
    //cout << "Hello World!" << endl;
    return 0;
}
