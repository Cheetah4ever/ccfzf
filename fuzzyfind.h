#pragma once

#include <iostream>
#include <string>

//Purpose Naive FuzzySearch:
using namespace std;
class FuzzyV1{

    private:
    int _matchscore = 0;
    string _target;
    string _searchquery;
    vector<int, string> _scorelist; 
    public:
    FuzzyV1(
        string searchquery, 
        bool ignoreupppercase = true): 
        _searchquery{searchquery} {}
    void do_string_compare(string target);
    //sets _target
    //calculates character match score/100 if perfect match
    //appends to _scorelist
    void store_score_target_list(){};
};

