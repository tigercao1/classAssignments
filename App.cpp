#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#include "App.h"

//App.cpp
App::App(){
	view.setOwner(this);
}
void App::executeCommand(string cmd){
	//do execution stuff
	int command = parseCommand(cmd);

	if (command != -1){
		view.output("Executing: " + cmd);
	}
}

string App::executeCommandWhileLoggingOutput(string cmd){
	int command = parseCommand(cmd);

	if (command != -1){
		view.output("Executing: " + cmd);
		return "Executing: " + cmd;
	}
	return "";
}

// vector<string> v logging(const string cmd, const int condition){
// 	vector<string> loggedCommands;
// 	if (condition == 40){
// 		loggedCommands.clear();
// 	}
// 	loggedCommands << cmd;
// 	return loggedCommands;
// }

// void log_save(const string fileName, vector<string> cmds){
// 	ofstream logfile(fileName, ofstream::out);
// 	for (unsigned int i = 0; i < cmds.size(); i++){
// 		logfile << cmds[i] << endl;
// 	}
// 	logfile.close();
// }

/* Application Commands
return 1x for commands after add
return 2x for commands after delete
return 3x for commands after display
*/
int App::parseCommand(const string cmd){
	stringstream stringStream (cmd);
	vector<string> words;
	string temp;
	int recording = 0;
	int song = 1;
	int track = 2;
	int user = 3;
	int playlist = 4;
	int playlist_track = 5;

	while (getline(stringStream, temp, ' ')){
		words.push_back(temp);
	}

	view.output("Parsed Command");
	for (unsigned int i = 0; i < words.size(); i++){
		view.output(words[i]);
	}

	if (words[0] == "add"){
		if (words[1] == "-r"){ // Recording - 0
			return 10+recording;
		} else if (words[1] == "-s") { // Song - 1
			return 10+song;
		} else if (words[1] == "-t") { // Track - 2
			return 10+track;
		} else if (words[1] == "-u"){ // User - 3
			return 10+user;
		} else if (words[1] == "-p"){ // Playlist - 4
			return 10+playlist;
		} else if (words[1] == "-l"){ // Playlist track - 5
			return 10+playlist_track;
		}
		return 16; // Able to prompt user for additional command
	} else if (words[0] == "delete"){
		if (words[1] == "-r"){ // Recording - 0
			return 20+recording;
		} else if (words[1] == "-s") { // Song - 1
			return 20+song;
		} else if (words[1] == "-t") { // Track - 2
			return 20+track;
		} else if (words[1] == "-u"){ // User - 3
			return 20+user;
		} else if (words[1] == "-p"){ // Playlist - 4
			return 20+playlist;
		} else if (words[1] == "-l"){ // Playlist track - 5
			return 20+playlist_track;
		}
		return 26; // Able to prompt user for additional command
	} else if (words[0] == "display"){
		if (words[1] == "-r"){ // Recording - 0
			return 30+recording;
		} else if (words[1] == "-s") { // Song - 1
			return 30+song;
		} else if (words[1] == "-t") { // Track - 2
			return 30+track;
		} else if (words[1] == "-u"){ // User - 3
			return 30+user;
		} else if (words[1] == "-p"){ // Playlist - 4
			return 30+playlist;
		}
		return 36; // Able to prompt user for additional command
	}
	// else if (words[0] == ".log"){
	// 	if (words[1] == "clear"){
	// 		return 40;
	// 	} else if (words[1] == "start") {
	// 		return 41;
	// 	} else if (words[1] == "start_output") {
	// 		return 42;
	// 	} else if (words[1] == "start_both"){
	// 		return 43;
	// 	} else if (words[1] == "stop"){
	// 		return 44;
	// 	} else if (words[1] == "save"){
	// 		if (words[2] != ""){
	// 			return 45;
	// 		}
	// 	}
	// } else if (words[0] == ".read"){
	// 	if (words[2] != ""){
	// 		return 50;
	// 	}
	// }

	view.output("Error: Invalid Command");
	return -1;

}

void App::run(){
	view.run();
}
