#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <signal.h>
#include <cstdlib>
#include <unistd.h>
#include <util.h>
#include <sys/wait.h>

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
    vector<string> _targetscorelist;
    string _targetstring;
    vector<string> _targetvector;
    vector<string> do_string_split(char delimiter);

public:
    Displayer(vector<string> targetscorelist) : _targetscorelist{targetscorelist} {}
    Displayer(string targetstring) : _targetstring(targetstring) {}
    void assign_keys();
    // assigns up/down and enter keys
    void display();
    void inverserdisplay();
    void display_footline();
};

vector<string> Displayer::do_string_split(char delimiter){
    int startindex = 0;
    for (int i=0; i < _targetstring.size(); i++)
    {
        if (_targetstring[i] == delimiter)
        {
            string k = _targetstring.substr(startindex,i);
            k.erase(k.size(), 0);
            _targetvector.push_back(k);
            startindex == 0 ? startindex = i : startindex = i-1;
        }
    }
    return _targetvector;
}
void Displayer::display()
{
    _targetvector = do_string_split('\n');
    for (int i = 0 ; i < _targetvector.size();i++)
    {
        cout << _targetvector[i];
    }
    cout << "\n";
    display_footline();
};



void Displayer::display_footline()
{
    //needs imporvement to addjust to the window size)
    //window_refresh() -> gets length and width of the window. 
    cout << _targetvector.size() 
    << "/" 
    << _targetvector.size() 
    << " --------------------" << endl;
};



int main(int argc, char *argv[])
{

    string example = "apple\nbanana\ncherry\n";
    Displayer d(example);
    thread t1(&Displayer::display, &d);
    t1.join();
    
}