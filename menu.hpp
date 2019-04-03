#ifndef __MENU_HPP__ 
#define __MENU_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "command.hpp"

using namespace std;


class Menu {
    private:
        int history_index; // Indexes which command was last executed, accounting for undo and redo functions
        vector<Command*> history; // Holds all the commands that have been executed until now

    public:
        Menu() { // Constructor which initializes the internal members
            history_index=0; //NOICE
        }

        string execute() { // Returns the string converted evaluation of the current command
            Command* nicole = get_command();
            return to_string(nicole->execute());
        }

        string stringify() { // Returns the stringified version of the current command
            Command* nicole = get_command();
            return nicole->stringify();
        }

        bool initialized() { // Returns if the history has an InitialCommand, which is necessary to start the calculation
            return history.size(); // supposed to work cuz ints can work as booleans. will be 0 if its not initialized and therefore return false
        }

        void add_command(Command* cmd) { // Adds a command to the history (does not execute it), this may require removal of some other commands depending on where history_index is
            if(history_index < history.size()) {
                history_index = history.size();
            }
            else if(history_index > history.size()){
                history_index = history.size();
            }
            history.push_back(cmd);
            history_index++;
            
            return;
        }

        Command* get_command() {  // Returns the command that the history_index is currently referring to
            return history.at(history_index-1);
        }

        void undo() {// Move back one command (does not execute it) if there is a command to undo
	    //if(history_index == 0) {
	//	cout << "cant do that my guy" << endl;
	  //  }
            if(initialized() == true) {
		if(history_index == 1) {
		    cout << "cant do that" << endl;
		}
		else{
                history_index--;//I THINK
		}    
            }
            return;
        }

        void redo() { // Moves forward one command (does not execute it) if there is a command to redo
            if(history_index < history.size()) {
                history_index++;// WE'LL START HERE YUH
            }
            return;
        }
};

#endif
