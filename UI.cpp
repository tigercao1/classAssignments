//#include "UI.h"
#include "App.h"
#include "str_util.h"

using namespace std;

UI::UI(){

}

void UI::setOwner(App * anApp){
		owner = anApp;
}

void UI::run(){
  cout << "Welcome to myTunes! Enter command below or '.help' to open the help menu!" << endl;
  string input = "";
	vector<string> loggedCommands;
	/*
	Log on/off switch
	read on/off switch
	*/
	bool isLogInput = false;
	bool isLogOutput = false;
	bool isRead = false;

  // Infinitely taking in commands unless .quit is entered
  while (input.compare(".quit") != 0) {
    cout << "myTunes - Enter commands or .quit ";
		int command = -1;
		string inputBuffer;
		input = "";
		getline(cin, inputBuffer);
		// Check if command is comment
		if (!StrUtil::isComment(inputBuffer)){
			input = inputBuffer;
			inputBuffer = "";
		}
		if (input != ""){
			command = parseCommand(input);
		}

		// 20 - ".read"
		if (command == 20){
			isRead = true;
		}

		// Condition for logging inputs/outputs
		if (isLogInput && !isLogOutput) {
			// Log inputs
			loggedCommands.push_back(input);
		} else if (isLogOutput && !isLogInput) {
			string outputs = owner->executeCommandWhileLoggingOutput(input);
			if (outputs != ""){
				// Log outputs
				loggedCommands.push_back(outputs);
			}
		} else if (isLogOutput && isLogInput) {
			string outputs = owner->executeCommandWhileLoggingOutput(input);
			if (outputs != ""){
				// Log inputs
				loggedCommands.push_back(input);
				// Log outputs
				loggedCommands.push_back(outputs);
			}
		}
		// Condition if read
		if (isRead) {
			stringstream stringStream (input);
			vector<string> words;
			string temp;
			while (getline(stringStream, temp, ' ')){
				words.push_back(temp);
			}
			ifstream readFile(words[1], ofstream::in);
			if (!readFile){
				output("Error: Could not open file " + words[1]);
			} else {
				while (getline(readFile, inputBuffer)){
					if (!StrUtil::isComment(inputBuffer) && inputBuffer != " "){
						input = inputBuffer;
					} else if (StrUtil::isComment(inputBuffer) && inputBuffer != " ") {
						output(inputBuffer);
					}
					int commandWhileLogging = -1;
					if (input != "")
						commandWhileLogging=parseCommand(input);
					//output("Here");
					if (isLogInput && !isLogOutput) {
						loggedCommands.push_back(input);
					} else if (isLogOutput && !isLogInput) {
						string outputs = owner->executeCommandWhileLoggingOutput(input);
						if (outputs != ""){
							loggedCommands.push_back(outputs);
						}
					} else if (isLogOutput && isLogInput) {
						string outputs = owner->executeCommandWhileLoggingOutput(input);
						if (outputs != ""){
							loggedCommands.push_back(input);
							loggedCommands.push_back(outputs);
						}
					}

					// 12 - .log start
					if (commandWhileLogging == 12) {
						isLogInput = true;
						isLogOutput = false;
						// 15 - .log stop
					} else if (commandWhileLogging == 15){
						isLogInput = false;
						isLogOutput = false;
						// 13 - .log start_output
					} else if (commandWhileLogging == 13){
						isLogInput=false;
						isLogOutput = true;
						// 14 - .log start_both
					} else if (commandWhileLogging == 14){
						isLogInput = true;
						isLogOutput = true;
						// 17 - .log show
					} else if (commandWhileLogging == 17) {
						log_show(loggedCommands);
						// 16 - .log save
					} else if (commandWhileLogging == 16) {
						log_save(loggedCommands, input);
						// 11 - .log clear
					} else if (commandWhileLogging == 11) {
						loggedCommands.clear();
						// 0 - .help
					} else if (commandWhileLogging == 0) {
						help();
					}
					// if (commandWhileLogging == 15 || input.compare(".quit") == 0 ){
					// 	// .log stop
					// 	break;
					// } else if (commandWhileLogging == 17) {
					// 	// .log show
					// 	//output("Inside");
					// 	log_show(loggedCommands);
					// } else if (commandWhileLogging == 11) {
					// 	// .log clear
					// 	loggedCommands.clear();
					// } else if (commandWhileLogging == 0) {
					// 	help();
					// } else if (commandWhileLogging == 16) {
					// 	log_save(loggedCommands, input);
					// }
					if (input.compare("") != 0 && input.compare(".quit") != 0 && !(commandWhileLogging >= 0))
			    	owner->executeCommand(input);
				}

			}
			readFile.close();
			isRead = false;
		}


		if (command == 12) {
			isLogInput = true;
			isLogOutput = false;
		} else if (command == 15){
			isLogInput = false;
			isLogOutput = false;
		} else if (command == 13){
			isLogInput=false;
			isLogOutput = true;
		} else if (command == 14){
			isLogInput = true;
			isLogOutput = true;
		} else if (command == 17) {
			log_show(loggedCommands);
		} else if (command == 16) {
			log_save(loggedCommands, input);
		} else if (command == 11) {
			loggedCommands.clear();
		} else if (command == 0) {
			help();
		}
		if (input != "" && input != ".quit" && command == -1 && isLogInput && !(isLogInput&&isLogOutput) && !isLogOutput){

			owner->executeCommand(input);
		}
		if (input == ".quit"){
			output("Ending Session.............");
		}
  }
}

// Show logged commands
void UI::log_show (vector<string> someLoggedCommands){
	cout << "Log============================================" << endl;
	for (unsigned int i = 0; i < someLoggedCommands.size(); i++){
		cout << someLoggedCommands[i] << endl;
	}
	cout << "===============================================" << endl;
}

void UI::log_save (vector<string> someLoggedCommands, string cmd){
	stringstream stringStream (cmd);
	vector<string> words;
	string temp;
	while (getline(stringStream, temp, ' ')){
		words.push_back(temp);
	}
	ofstream logfile(words[2], ofstream::out);
	for (unsigned int i = 0; i < someLoggedCommands.size(); i++){
		logfile << someLoggedCommands[i] << endl;
	}
	logfile.close();
}

int UI::help(){
	ifstream helpFile("help.txt", ifstream::in);
	string inputFromFile = "";
	if (!helpFile){
		cout << "Error: Could not find help.txt" << endl;
		return 0;
	}

	while(getline(helpFile, inputFromFile)){
		cout << inputFromFile << endl;
	}
	helpFile.close();
	return 1;
}

/* UI Commands
return 0 for help commands
return 1x for log commands
return 2x for read commands
*/
int UI::parseCommand(string cmd){
	stringstream stringStream (cmd);
	vector<string> words;
	string temp;
	while (getline(stringStream, temp, ' ')){
		words.push_back(temp);
	}
	if (words[0] == ".log" || words[0] == ".read" || words[0] == ".help"){
		output("Parsed Command");
		for (unsigned int i = 0; i < words.size(); i++){
			output(words[i]);
		}
	}
	if (words[0] == ".help"){
		return 0;
	} else if (words[0] == ".log"){
		if (words[1] == "clear"){
			return 11;
		} else if (words[1] == "start") {
			return 12;
		} else if (words[1] == "start_output") {
			return 13;
		} else if (words[1] == "start_both"){
			return 14;
		} else if (words[1] == "stop"){
			return 15;
		} else if (words[1] == "save"){
			if (words[2] != ""){
				return 16;
			}
		} else if (words[1] == "show"){
			//output("return 17");
			return 17;
		}
		return 10;
	} else if (words[0] == ".read"){
		if (words[1] != ""){
			return 20;
		}
	}
	return -1;
}

void UI::output(string message){
		//output a messsage to user on the UI screen
		cout << message << endl;
}
