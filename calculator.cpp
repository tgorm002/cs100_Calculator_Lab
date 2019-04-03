#include <iostream>
#include <vector>
#include <stdlib.h>
#include "menu.hpp"
//#include "Iterator.hpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;


bool is_integer(const string& s) {
    if(s.empty()) {
        return false ;
    }
    char* p;
    strtol(s.c_str(), &p, 10) ;
    return (*p == 0) ;
}


BaseFactory* generate_factory() {
    cout << "The following operators are available" << endl;
    cout << "\t\"d\": double" << endl;
    cout << "\t\"s\": scientific" << endl;
    cout << "\t\"p\": precision" << endl;
    cout << "Please enter one of the above choices: ";

    string input = "";
    getline(cin, input);

    if(input.substr(0,1) == "d") {
        return new Double();
    }
    else if(input.substr(0,1) == "s") {
        return new Scientific();
    } 
    else if(input.substr(0,1) == "p") {
        return new Precision();
    }
    return nullptr;
}


Command* parse_command_input(Command* lhs, BaseFactory* factory, string in) {
    
    if(is_integer(in.substr(2))) {
        int val = atoi((in.substr(2)).c_str());
        switch(in.substr(0,1).c_str()[0]) {
        case '+':
            return new AddCommand(lhs, factory->createOp(val));
            break;
        case '-':
            return new SubCommand(lhs, factory->createOp(val));
            break;
        case '*':
            return new MultCommand(lhs, factory->createOp(val));
            break;
        case '/':
            return new DivCommand(lhs, factory->createOp(val));
            break;
        case '^':
            return new PowCommand(lhs, factory->createOp(val));
            break;
        default:
            return nullptr;
        }
    }
    
    else if(in.substr(2,1) == "?") {
        switch(in.substr(0,1).c_str()[0]) {
        case '+':
            return new AddCommand(lhs, factory->createRand());
            break;
        case '-':
            return new SubCommand(lhs, factory->createRand());
            break;
        case '*':
            return new MultCommand(lhs, factory->createRand());
            break;
        case '/':
            return new DivCommand(lhs, factory->createRand());
            break;
        case '^':
            return new PowCommand(lhs, factory->createRand());
            break;
        default:
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

int main() {

    
    Menu* menu = new Menu();
    string input = "";

    
    BaseFactory* factory = generate_factory();
    if(factory == nullptr) {
        cout << "Invalid choice, exiting..." << endl;
        input = "exit";
    }

    while(input != "exit") {
        cout << "Choose a Menu Command: ";
        getline(cin, input);

        if(input == "exit") {
            cout << "Exiting..." << endl;
            break;
        }
        else if(input == "redo") {
            cout << "Redoing command, current command is..." << endl;
            menu->redo();
        }
        else if(input == "undo") {
            cout << "Undoing command, current command is..." << endl;
            menu->undo();
        } else {
            
            
            if(!menu->initialized()) {
                if(is_integer(input)) {
                    menu->add_command(new InitialCommand(factory->createOp(atoi(input.c_str()))));
                }
                else if(input.substr(0,1) == "?") {
                    menu->add_command(new InitialCommand(factory->createRand()));
                } else {
                    cout << "Invalid Command" << endl;
                }
            
            } else {
                Command* cmd = parse_command_input(menu->get_command(), factory, input);
                if(cmd == nullptr) {
                    cout << "Invalid commmand, current command is..." << endl;
                } else {
                    menu->add_command(cmd);
                }
            }
        }

        
        if(!menu->initialized()) {
            cout << "Empty" << endl;
        } else {
            cout << menu->stringify() << " = " << menu->execute() << endl;
        }
    }
    delete menu;
    delete factory;
}
