#pragma once

#include <iostream>
using namespace std;

class Displayer
{
    /*
    The purpose is to display the
    results of the fuzzy find match
    The results are using forkpty
    when PID = 0;
    The results have to be
    - scrollable (assigns keys)
    - displayed bottom up !?
    */

private:
    int count;
    vector<int, string> _targetscorelist;
public:
    Displayer(vector<int, string> targetscorelist): 
        _targetscorelist{targetscorelist} {}
    void assign_keys() {}
        //assigns up/down and enter keys
    void display(){};
    void inverserdisplay(){};
};