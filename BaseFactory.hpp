#include <iostream>
#include "base.hpp"
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

//THIS IS A VIRTUAL CODE TEST
// ANOTHER VIRTUAL STUDIO TEST THAT BETTER WORK

class BaseFactory {
	public:
		BaseFactory() {};

        virtual Op* createOp(double value) = 0;
        virtual Rand* createRand() = 0;
};

class Precision : public BaseFactory {
	public:
	    
	    int decPlaces;
	    
	    Precision() {};
	    
		Op* createOp(double value){ 
			PrecisionOp* Trevor = new PrecisionOp(3, value);
            return Trevor;    
        }
        
        Rand* createRand() {
            PrecisionRand* Trevor = new PrecisionRand(3);
            return Trevor;
        }
};

class Scientific : public BaseFactory {
	public:
	    int decPlaces;
	    double randValue = rand()%100;
	    
	    Scientific() {}; //: decPlaces(decPlaces) {}
	    
	    Op* createOp(double value) { // maybe correct
	        SciOp* Trevor = new SciOp(3, value);
	        return Trevor;
	    }
	    
	    Rand* createRand() {
	        SciRand* Trevor = new SciRand(3);
	        return Trevor;
	    }
};

class Double : public BaseFactory {
	public:
	    double value;
	    double randValue = rand()%100;
	    stringstream sstream;
	    
	    Double() {};
	    
	    Op* createOp(double value) {
	        return new Op(value);
	    }
	    
	    Rand* createRand() {
	        Rand* Trevor = new Rand();
	        return Trevor;
	    }
};



