
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

#include "UI.h"
#include "str_util.h"

class App{
  UI view;
  public:
    App();
    void executeCommand(string cmd);
    void run();
    string executeCommandWhileLoggingOutput(string cmd);
  private:
    int parseCommand(string cmd);
};
