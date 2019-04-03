#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <iostream>
#include <vector>
#include <string>
//#include "menu.hpp"
#include "base.hpp"
#include "BaseFactory.hpp"

using namespace std;

class Command {
    protected:
        Base* root;
    
    public:
    
        Command() { this->root = nullptr; }
        double execute() { return root->evaluate(); }
        string stringify() { return root->stringify(); }
        Base* get_root() { return root; }
};

class InitialCommand : public Command{
    public:
        InitialCommand(Base* value) {
            root = value;
        }
};

class AddCommand : public Command{
    public:
        AddCommand(Command* lhs, Base* rhs) {
            root = new Add(lhs->get_root(), rhs);
        }
};

class SubCommand : public Command{
    public:
        SubCommand(Command* lhs, Base* rhs) {
            root = new Sub(lhs->get_root(), rhs);
        }
};

class MultCommand : public Command{
    public:
        MultCommand(Command* lhs, Base* rhs) {
            root = new Mult(lhs->get_root(), rhs);
        }
};

class DivCommand : public Command{
    public:
        DivCommand(Command* lhs, Base* rhs) {
            root = new Div(lhs->get_root(), rhs);
        }
};

class PowCommand : public Command{
    public:
        PowCommand(Command* lhs, Base* rhs) {
            root = new Pow(lhs->get_root(), rhs);
        }
    
};


#endif
