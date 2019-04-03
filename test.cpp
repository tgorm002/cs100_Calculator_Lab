#include "menu.hpp"
#include "Iterator.hpp"
#include "visitor.hpp"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

TEST(oneTest, Everything) {
    Base* op1 = new Add( new Rand(), new Trunc(new Op(1.432)));
	Base* op2 = new Sub( new Abs(op1), new Floor(new Op(1.432)));
	Base* op3 = new Mult( new Ceil(new Op(5.5)), new Pow(new Op(2), new Op(2)));
	Base* op4 = new Div( new Rand(), op3);
	
	Base* dummy = new Add(op2,op4);
	CountVisitor *cv = new CountVisitor();
	PreorderIterator *pi = new PreorderIterator(dummy);
    pi->first();
	while(pi->is_done() == false){
        //cout << pi->current()->evaluate() << endl;
	    pi->current()->accept(cv);
	    pi->next();
	}
	
	EXPECT_EQ(cv->add_count(), 1);
	EXPECT_EQ(cv->op_count(),5);
	EXPECT_EQ(cv->trunc_count(),1);
	EXPECT_EQ(cv->abs_count(),1);
	EXPECT_EQ(cv->div_count(),1);
	EXPECT_EQ(cv->sub_count(),1);
	EXPECT_EQ(cv->pow_count(),1);
	EXPECT_EQ(cv->ceil_count(),1);
	EXPECT_EQ(cv->floor_count(),1);
	EXPECT_EQ(cv->rand_count(),2);
	EXPECT_EQ(cv->paren_count(),0);
}

TEST(oneOp, simple) {
    Base* op1 = new Op(5);
    Base* op2 = new Op(4);
    Base* dummy = new Add(op1,op2);
	CountVisitor *cv = new CountVisitor();
	PreorderIterator *pi = new PreorderIterator(dummy);
    pi->first();
    pi->current()->accept(cv);
    EXPECT_EQ(cv->op_count(),1);
}

TEST(ParenOp, ehhh) {
    Base* op1 = new Add( new Rand(), new Trunc(new Op(1.432)));
	Base* op2 = new Sub( new Paren(new Op(5)), new Floor(new Op(1.432)));

    Base* dummy = new Add(op1,op2);
	CountVisitor *cv = new CountVisitor();
	PreorderIterator *pi = new PreorderIterator(dummy);
    pi->first();
	while(pi->is_done() == false){
        //cout << pi->current()->evaluate() << endl;
	    pi->current()->accept(cv);
	    pi->next();
	}

    EXPECT_EQ(cv->add_count(), 1);
	EXPECT_EQ(cv->op_count(),3);
	EXPECT_EQ(cv->trunc_count(),1);
	EXPECT_EQ(cv->abs_count(),0);
	EXPECT_EQ(cv->div_count(),0);
	EXPECT_EQ(cv->sub_count(),1);
	EXPECT_EQ(cv->pow_count(),0);
	EXPECT_EQ(cv->ceil_count(),0);
	EXPECT_EQ(cv->floor_count(),1);
	EXPECT_EQ(cv->rand_count(),1);
	EXPECT_EQ(cv->paren_count(),1);
}

// TEST(IteratorTest, UnoChildo) {
//     Base* firstCommand = new Op(69);
//     Iterator* Trevor = firstCommand->create_iterator();
//     EXPECT_EQ(firstCommand->get_left(), nullptr);
//     EXPECT_EQ(firstCommand->get_right(), nullptr);
//     Trevor->first();
//     EXPECT_EQ(Trevor->current(), nullptr); 
//     Trevor->next();
//     EXPECT_EQ(Trevor->current(), nullptr);
//     EXPECT_TRUE(Trevor->is_done());
// }

// TEST(IteratorTest, DosEquis) {
//     Base* firstCommand = new Abs(new Op(-69));
//     Iterator* JasonDerulo = firstCommand->create_iterator();
//     EXPECT_EQ(firstCommand->get_left()->evaluate(), -69);
//     EXPECT_EQ(firstCommand->get_right(), nullptr);
//     JasonDerulo->first();
//     JasonDerulo->next();
//     EXPECT_EQ(JasonDerulo->current(), nullptr);
//     EXPECT_TRUE(JasonDerulo->is_done());
// }

// TEST(IteratorTest, TresAmigos) {
//     Base* op1 = new Op(5);
//     Base* op2 = new Op(1);
//     Base* firstCommand = new Add(new Op(5), new Op(1)); 
//     //cout << "1" << endl;
//     Iterator* Batman = firstCommand->create_iterator();
//     //cout << "2" << endl;
//     EXPECT_EQ(firstCommand->get_left()->evaluate(), 5);
//     //cout << "3" << endl;
//     EXPECT_EQ(firstCommand->get_right()->evaluate(), 1);
//     //cout << "4" << endl;
//     Batman->first();
//     //cout << "5" << endl;
//     EXPECT_EQ(Batman->current()->evaluate(), 5);
//     //cout << "6" << endl;
//     Batman->next();
//     //cout << "7" << endl;
//     EXPECT_EQ(Batman->current()->evaluate(), op2->evaluate());
//     //cout << "8" << endl;
//     Batman->next();
//     EXPECT_TRUE(Batman->is_done());
//     //cout << "9" << endl;
// }

// TEST(IteratorTest, PreorderTest) {
// 	Base* op1 = new Op(3);
// 	Base* op2 = new Op(4);
//     //cout << "1" << endl;
// 	Mult* multiplier = new Mult(op1,op2);
//     //cout << "2" << endl;
// 	Add* addTemp = new Add(multiplier, op2);
//     //cout << "3" << endl;
// 	PreorderIterator* temp = new PreorderIterator(addTemp);
//     //cout << "4" << endl;
// 	temp->first();
//     //cout << "5" << endl;
// 	//cout << temp->current()->get_left()->evaluate() << endl;
//     //cout << "6" << endl;
// 	EXPECT_EQ(temp->current()->get_left()->evaluate(), op1->evaluate());
//     //cout << "7" << endl;
// 	temp->next();
//     //cout << "8" << endl;
// 	EXPECT_EQ(temp->current()->evaluate(), 3);
//     //cout << "9" << endl;
//     temp->next();
//     EXPECT_EQ(temp->current()->evaluate(), 4);
//     temp->next();
//     //cout << "10" << endl;
//     EXPECT_EQ(temp->current()->evaluate(), 4);
//     temp->next();
//     //cout << "12" << endl;
//     EXPECT_TRUE(temp->is_done());
    
// }

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



