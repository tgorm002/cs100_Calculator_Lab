#include "Iterator.hpp"
#include "base.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <stack>

//class Base;

using namespace std;

/* Sets up the iterator to start at the beginning of traversal */
    BinaryIterator::BinaryIterator(Base* b){
        self_ptr = b;
        curr = nullptr;
    }
    void BinaryIterator::first() {
        curr = self_ptr->get_left();
    }
    
    /* Move onto the next element */
    void BinaryIterator::next() {
        if(curr == self_ptr->get_left()) {
            curr = self_ptr->get_right();
            //cout << "hi" << endl;
        }
        // else if(curr == self_ptr) {
        //   curr = self_ptr->get_left();
        // }
        else {
            curr = nullptr;
        }
    }

    /* Returns if you have finished iterating through all elements */
    bool BinaryIterator::is_done() {
        if(curr == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    /* Return the element the iterator is currently at */
    Base* BinaryIterator::current() {
        return curr;
    }
    
    //---------------------------------------------------------------------------------------
    
  UnaryIterator::UnaryIterator(Base* b){
        self_ptr = b->get_left();
        curr = nullptr;
    }

    void UnaryIterator::first() {
        curr = self_ptr;//->get_left();
            
    }
    
    /* Move onto the next element */
    void UnaryIterator::next() {
        curr= nullptr;
        return;
    }

    /* Returns if you have finished iterating through all elements */
    bool UnaryIterator::is_done() {
        if(/*curr == self_ptr->get_left() ||*/ curr == nullptr){
            return true;
        }else{
            return false;
        }
    }

    /* Return the element the iterator is currently at */
    Base* UnaryIterator::current() {
        if(curr == nullptr) {
          return nullptr;
        }
        return curr;
    }
    
    //-------------------------------------------------------------------------------
    
    NullIterator::NullIterator(Base* b){
        self_ptr = b->get_left();
        curr = nullptr;
    }

     void NullIterator::first() {
        return;
    }
    
    /* Move onto the next element */
    void NullIterator::next() {
        return;
    }

    /* Returns if you have finished iterating through all elements */
    bool NullIterator::is_done() {
        return true;
    }

    /* Return the element the iterator is currently at */
    Base* NullIterator::current() {
        return NULL;
    }
    
    //-------------------------------------------------------------------------------------
    
    PreorderIterator::PreorderIterator(Base* b){
        self_ptr = b;
        root = nullptr;
    }

    void PreorderIterator::first() {
    // Empty the stack (just in case we had something leftover from another run). Create
    // an iterator for the Base* that was passed into the PreorderIterator constructor.
    // Initialize that iterator and push it onto the stack.
        //PreorderIterator(curr);
        while(!stackz.empty()) {//emptying stack
            stackz.pop();
        }
        iteratePtr = self_ptr->create_iterator();
  
        iteratePtr->first();
          
        stackz.push(iteratePtr);
        
    }

    void PreorderIterator::next() {
    // Create an iterator for the current() of the iterator on the top of the stack
    // Initialize the iterator and push it onto the stack. As long as the top iterator 
    // on the stack is_done, pop it off the stack and then advance whatever iterator is
    // now on top of the stack
        root = current();

        iteratePtr = stackz.top()->current()->create_iterator();

        iteratePtr->first();

        stackz.push(iteratePtr);
        
        while(!stackz.empty() && stackz.top()->is_done()) {
            stackz.pop();
            if(!stackz.empty()) {
              stackz.top()->next();
            }
            
        }
        
    }

    bool PreorderIterator::is_done() { // Return true if there are no more elements on the stack to iterate
        if(stackz.empty()) {
            return true;
        }
        return false;
    }
    
    Base* PreorderIterator::current() { // Return the current for the top iterator in the stack //WHY IS IT A BASE*
        root = stackz.top()->current();
        return root;
    }