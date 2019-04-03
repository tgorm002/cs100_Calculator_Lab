#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
//#include "base.hpp"
#include <stack>
// #include "BaseFactory.hpp"
// #include "calculator.hpp"
// #include "command.hpp"
//#include "menu.hpp"
// #include "test.cpp"

class Base;

using namespace std;

class Iterator {
    protected:
      Base* self_ptr;

    public:
      Iterator() {};
      Iterator(Base* ptr) { this->self_ptr = ptr; }

      /* Sets up the iterator to start at the beginning of traversal */
      virtual void first() = 0;
      
      /* Move onto the next element */
      virtual void next() = 0;
  
      /* Returns if you have finished iterating through all elements */
      virtual bool is_done() = 0;

      /* Return the element the iterator is currently at */
      virtual Base* current() = 0;
};

class BinaryIterator : public Iterator {
    public:
        Base* curr;
        BinaryIterator() {self_ptr = nullptr; curr = nullptr;};
        BinaryIterator(Base* b);

        /* Sets up the iterator to start at the beginning of traversal */
        void first();
        
        /* Move onto the next element */
        void next();
    
        /* Returns if you have finished iterating through all elements */
        bool is_done();

        /* Return the element the iterator is currently at */
        Base* current();
};

class UnaryIterator : public Iterator {
    public:
        Base* curr;
        UnaryIterator() {self_ptr = nullptr;}
        UnaryIterator(Base* b);
        /* Sets up the iterator to start at the beginning of traversal */
        void first();
        
        /* Move onto the next element */
        void next();
    
        /* Returns if you have finished iterating through all elements */
        bool is_done();

        /* Return the element the iterator is currently at */
        Base* current();
};


class NullIterator : public Iterator {
    public:
        Base* curr;
        NullIterator() {self_ptr = nullptr;}
        NullIterator(Base* b);
        /* Sets up the iterator to start at the beginning of traversal */
        void first();
        
        /* Move onto the next element */
        void next();
    
        /* Returns if you have finished iterating through all elements */
        bool is_done();

        /* Return the element the iterator is currently at */
        Base* current();
};


class PreorderIterator : public Iterator{
    public:
        stack<Iterator*> stackz;
        Base* root;
        Iterator* iteratePtr;
        
        PreorderIterator() {self_ptr = nullptr;}

        PreorderIterator(Base* curr);
        
        void first();
    
        void next();
    
        bool is_done();
        
        Base* current();
        
};

#endif