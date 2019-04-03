#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <cmath>
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Iterator.hpp"
#include "visitor.hpp"

class Iterator;
class NullIterator;
class BinaryIterator;
class UnaryIterator;
class CountVisitor;


using namespace std;

class Base {
    public:
        
        Base() { };

        virtual double evaluate() = 0;
        virtual string stringify() = 0;
        
        virtual Base* get_left() = 0;
        virtual Base* get_right() = 0;
        virtual Iterator* create_iterator() = 0;
        virtual void accept(CountVisitor*) = 0; 
};

class Op : public Base{
        public:
                double value;
                Base* left;
                Base* right;
                
                Op(double value) {
                        this->value = value;
                }
                double evaluate(){
                        return value;
                }
                string stringify() {
                        return to_string(value);
                }
                Base* get_left() {
                        return NULL;
                }
                Base* get_right(){
                        return NULL;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new NullIterator(this);
                        return iterate;
                }
                void accept(CountVisitor* ptr) {
                        //cout << "got to op visitor" << endl;
                        ptr->visit_op();
                }
};

class Rand : public Base{
        public:
                double value;// = rand() % 100;
                Rand() {
                        srand(time(0));
                        value = rand()%100;
                }                
                double evaluate() {
                        return value;
                }
                
                string stringify(){
                        return to_string(value);
                }
                Base* get_left() {
                        return NULL;
                }
                Base* get_right(){
                        return NULL;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new NullIterator(this);
                        return iterate;
                }
                void accept(CountVisitor* ptr) {
                        ptr->visit_rand();
                }
};



class Mult : public Base{
        public:
                Base *left;
                Base *right;

                double leftVal;
                double rightVal;

                string combined;

                Mult(Base *l, Base *r) {
                        left = l;
                        right = r;
                        leftVal = left->evaluate();
                        rightVal = right->evaluate();
                }

                double evaluate() {
                        return leftVal*rightVal;
                }

                string stringify() {
                        combined =  to_string(leftVal) +  "*" +  to_string(rightVal);
                        return combined;
                }
                
                Base* get_left() {
                        return left;
                }
                Base* get_right(){
                        return right;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new BinaryIterator(this);
                        return iterate;
                }
                void accept(CountVisitor* ptr) {
                        ptr->visit_mult();
                }
};

class Div : public Base{
        public:
                Base *left;
                Base *right;

                double leftVal;
                double rightVal;

                string combined;

                Div(Base *l, Base *r) {
                        left = l;
                        right = r;
                        leftVal = left->evaluate();
                        rightVal = right->evaluate();
                }

                double evaluate() {
                        return leftVal/rightVal;
                }

                Base* get_left() {
                        return left;
                }
                Base* get_right(){
                        return right;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new BinaryIterator(this);
                        return iterate;
                }
                string stringify() {
                        combined =  to_string(leftVal) + "/" + to_string(rightVal);
                        return combined;
                }
                void accept(CountVisitor* ptr) {
                        ptr->visit_div();
                }
};

class Add : public Base{
        public:
                Base *left;
                Base *right;

                double leftVal;
                double rightVal;

                string combined;

               Add(Base *l, Base*r) {
                        left = l;
                        right = r;
                        leftVal = left->evaluate();
                        rightVal = right->evaluate();
                }

                double evaluate() {
                        return leftVal+rightVal;
                }

                Base* get_left() {
                        return left;
                }
                Base* get_right(){
                        return right;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new BinaryIterator(this);
                        return iterate;
                }
                string stringify() {
                        combined =  to_string(leftVal) +  "+" +  to_string(rightVal);
                        return combined;
                }
                void accept(CountVisitor* ptr) {
                        ptr->visit_add();
                }
};

class Sub : public Base{
        public:
                Base *left;
                Base *right;

                double leftVal;
                double rightVal;

                string combined;

                Sub(Base *l, Base *r) {
                        left = l;
                        right = r;
                        leftVal = left->evaluate();
                        rightVal = right->evaluate();
                }

                double evaluate() {

                        return leftVal - rightVal;
                }

                Base* get_left() {
                        return left;
                }
                Base* get_right(){
                        return right;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new BinaryIterator(this);
                        return iterate;
                }
                string stringify() {
                        combined =  to_string(leftVal) +  "-" +  to_string(rightVal);
                        return combined;
                }
                void accept(CountVisitor* ptr) {
                        ptr->visit_sub();
                }

};

class Pow : public Base{
        public:
                Base *left;
                Base *right;

                double leftVal;
                double rightVal;

                string combined;

                Pow(Base *l, Base *r) { //should be the same as all the other ones for the constructor
                        left = l;
                        right = r;
                        leftVal = left->evaluate();
                        rightVal = right->evaluate();
                }

                Base* get_left() {
                        return left;
                }
                Base* get_right(){
                        return right;
                }
                Iterator* create_iterator() {
                        Iterator* iterate = new BinaryIterator(this);
                        return iterate;
                }
                
                double evaluate() { //this bad boy could be different
                        return pow(leftVal, rightVal); //yes
                }

                string stringify() {
                        combined =  to_string(leftVal) +  "^(" +  to_string(rightVal) +  ")";
                }
                void accept(CountVisitor* ptr) {
                        ptr->visit_pow();
                }
};

class Trunc : public Base {
    public:
        
        double value;
        Base* left;
        
        Trunc(Base* val){
            left = val;
            value = val->evaluate();
        }
        double evaluate(){
            return value; //"report its evaluation() value as its stringify() return rather than the full expression"
        }
        
        string stringify() {
            return to_string(value);
        }
    
        Base* get_left() {
                return left;
        }
        Base* get_right(){
                return NULL;
        }
        Iterator* create_iterator() {
                Iterator* iterate = new UnaryIterator(this);
                return iterate;
        }
        void accept(CountVisitor* ptr) {
                ptr->visit_trunc();
        }
};

class Paren : public Base {
    public:
        double value; 
        Base* nicole;   // 10 out of 10 variable naming
        
        
        
        Paren(Base* val) {
            value = val->evaluate();
            nicole = val;
        }
        
        double evaluate() {
            return value;
        }
        
        string stringify() {
            return "(" + nicole->stringify() + ")";
        }
        
        Base* get_left() {
                return nicole;
        }
        Base* get_right(){
                return NULL;
        }
        Iterator* create_iterator() {
                Iterator* iterate = new UnaryIterator(this);
                return iterate;
        }  
        void accept(CountVisitor* ptr) {
                ptr->visit_paren();
        }
};

class Ceil : public Base { 
    public:
        
        double number;
        double result;
        double value;
        
        Base* left;
        
        Ceil(Base* val) { 
                left = val;
                value = val->evaluate();
        }
        
        double evaluate() { 
            number = value;
            result = ceil(number);
            return result;
        }
    
        string stringify() {
            number = value;
            result = ceil(number);
            return to_string(result);
        }
        
        Base* get_left() {
                return left;
        }
        Base* get_right(){
                return NULL;
        }
        Iterator* create_iterator() {
                Iterator* iterate = new UnaryIterator(this);
                return iterate;
        }
        void accept(CountVisitor* ptr) {
                ptr->visit_ceil();
        }
    
};

class Floor : public Base { 
    public:
    
        double number;
        double result;
        double value;
        Base* left;
        
        Floor(Base* val) {
                left = val;
                value = val->evaluate();
        }
        
        double evaluate() {
            number = value;
            result = floor(number);
            return result;
        }
        
        string stringify() {
            double number = value;
            double result = floor(number);
            return to_string(result);
        }
        
        Base* get_left() {
                return left;
        }
        Base* get_right(){
                return NULL;
        }
        Iterator* create_iterator() {
                Iterator* iterate = new UnaryIterator(this);
                return iterate;
        }
        void accept(CountVisitor* ptr) {
                ptr->visit_floor();
        }
    
};

class Abs : public Base { //what it sounds like it would be
    public:
        
        double value;
        double number;
        double result;
        Base* left;
        
        Abs(Base* val) {
                left = val;
                value = val->evaluate();
        }
        
        double evaluate() {
            number = value;
            double result = abs(number);
            return result;
        }
        
        string stringify(){
            number = value;
            result = abs(number);
            return to_string(result);
        }
        
        Base* get_left() {
                return left;
        }
        Base* get_right(){
                return NULL;
        }
        Iterator* create_iterator() {
                Iterator* iterate = new UnaryIterator(this);
                return iterate;
        }
        void accept(CountVisitor* ptr) {
                ptr->visit_abs();
        }
    
};

class PrecisionOp : public Op{
        public:
                int decPlaces; //variable determines how many decimal places the precision will be set to
                double number;
                
                PrecisionOp(int decPlaces, double value) : decPlaces(decPlaces), Op(value){};

                string stringify(){//functions turns value into a string then returns it
                        stringstream sstream;
                        sstream << fixed << setprecision(decPlaces) << Op::value;
                        return sstream.str();   //might need to do to_string
                }
};    

class PrecisionRand : public Rand{
        public:
                int decPlaces; //variable determines how many decimal places the precision will be set to
                
                PrecisionRand(int decPlaces): decPlaces(decPlaces) {};
                
                string stringify(){
                        stringstream sstream;
                        sstream << fixed << setprecision(decPlaces) << Rand::value;
                        return sstream.str();
                }
};

class SciOp : public Op{
        public:
                int decPlaces; 
                
                SciOp(int decPlaces, double value) : decPlaces(decPlaces), Op(value){}
                
                string stringify() {
                        stringstream sstream;
                        sstream << fixed << setprecision(decPlaces) << scientific <<Op::value;
                        return sstream.str();
                }
                
};

class SciRand : public Rand{
        public:
                int decPlaces; 
                 
                
                SciRand(int decPlaces) : decPlaces(decPlaces) {}
                
                string stringify() {
                        stringstream sstream;
                        sstream << fixed << setprecision(decPlaces) << scientific <<Rand::value;
                        return sstream.str();
                }
                
                
};

#endif //__BASE_HPP__