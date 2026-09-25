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

void execute_forktty(void (*func)())
{
    struct winsize window{};
    window.ws_row = 40;
    window.ws_col = 100;
    /*
    The forkpty() function combines openpty(), fork(), and login_tty() to creates a new process operating in a pseudo-tty.
    */

    int primary_fd;
    pid_t pid = forkpty(&primary_fd,
                        nullptr, // Replica device
                        nullptr, // Default terminal settings
                        &window);
    int exitstatus;
    switch (pid)
    {
    case -1:
        perror("forkpty failed");
        exit(130);
    case 0:
        func();
        cout << "Print something" << endl;
        exit(0);
    default:
        char buffer[4096];
        ssize_t count;
        while ((count = read(primary_fd, buffer, sizeof(buffer))) > 0)
        {
             write(STDOUT_FILENO, buffer, count);
        }

        close(primary_fd);

        if (waitpid(pid, &exitstatus, 0) == -1)
        {
            perror("waitpid");
        }

        else if (WIFEXITED(exitstatus))
        {
            printf("child exited normally with status %d\n",
                   WEXITSTATUS(exitstatus));
        }
        else if (WIFSIGNALED(exitstatus))
        {
            printf("child was killed by signal %d\n",
                   WTERMSIG(exitstatus));
        }
    }
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
    // thread t1(&Displayer::display, &d);
    // t1.join();


}