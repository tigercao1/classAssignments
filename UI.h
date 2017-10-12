

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

class App;

class UI {
  App * owner;
	public:
  	UI();
  	void setOwner(App * aUIOwner);
  	void output(string msg);
  	void run();
  private:
    // string operation(string cmd);
    int parseCommand(string cmd);
    void log_show (vector<string> someLoggedCommands);
    void log_save (vector<string> someLoggedCommands, string cmd);
    int help();
    int readFile(string cmd);
};
