#pragma once
/*
	Objects should be replacable with their sub types without affecting the correctness of the program.

	Example base class car and child class is hatchback car. Another example is base class bird and child
	class is Ostrich. Now here issue is birds can fly but ostrich cant

	Method 1: Breaking the heirarchy
	Method 2: Tell, Don't ask
*/

/*
*	BAD Design
	Imagine we have car class and then we make subclass racing car. Now there can be issue in their methods.
	lets say base class car has a function name getInteriorWidth but now racing car has different kind of interior.
	So it's method can be getCockpitWidth instead. now there can be issues
*/

#include <vector>
#include <iostream>

class car
{
public:
	virtual int getInteriorWidth(void) {};
};

class racingCar : public car
{
	//getInteriorWidth stays unimplemented but implements below function instead
	int getCockpitWidth() {}

};

void testCarClass(void)
{
	car* first = new car();
	car* second = new car();
	car* third = new racingCar(); // this should work according to Liskov substitution principle.

	std::vector<car> vecCar;

	vecCar.push_back(*first);
	vecCar.push_back(*second);
	vecCar.push_back(*third);

	// now here trying to print getInteriorWidth will cause error as racing car is missing 
	// definition of getInteriorWidth
}

/*
*	GOOD Design
* Method 1  Breaking with heirarchy
* 
	Solution to above problem is implementing first
	class as more generic which will be vehicle class with more generic method.

	Now using testCarClass with below classes will work just fine.
*/
class vehicle
{
public:
	virtual int getInteriorWidth(void) {}
};

class car: public vehicle
{
private:
	int interiorWidth;
public:
	virtual int getInteriorWidth(void) {
		return this->cockpitWidth();
	}

	int cockpitWidth(void)
	{
		return interiorWidth;
	}
};

class racingCar : public car
{
private:
	int cpWidth;
public:
	virtual int getInteriorWidth(void) {
		return this->cockpitWidth();
	}

	int cockpitWidth(void)
	{
		return cpWidth;
	}
};

/* 
	Second BAD Code
	Here we have example of discount on amazon products. first there are products and then in house products which has
	extra discount.
*/	

class product
{
protected:
	double discount;
public:
	int getDiscount() {}
};

class inHouseProduct : public product
{
private:
	double extraDiscount;
public:
	// here getDiscount method is not override

	float addExtraDiscount() {
		discount = discount * 1.5;
	}
};

void testProductClass(void)
{
	product* p1 = new product();
	product* p2 = new product();
	product* p3 = new inHouseProduct();

	std::vector<product> vecProduct;

	vecProduct.push_back(*p1);
	vecProduct.push_back(*p2);
	vecProduct.push_back(*p3);

	// here printing get discount should work fine as inHouseProduct has getDiscount implemented
	for (auto v : vecProduct)
	{
		// code to compare if v is equal to p3 then 
		// call applyExtraDiscount function
		// else call getDiscount function

		/*
			above if else condition is against LiskoveSubstitutionPrinciple as we are asking here.
			Need to follow tell, dont ask rule here which is getting rid of this if else.
		*/
}

/*
*	GOOD Design
	Soultion to second problem
*/
class product
{
protected:
	double discount;
public:
	virtual int getDiscount() {}
};

class inHouseProduct : public product
{
private:
	double extraDiscount;
public:
	virtual int getDiscount() override {
		this->addExtraDiscount();
		return discount;
	}

	float addExtraDiscount(){
		discount = discount * 1.5;
	}
};

void testProductClass(void)
{
	product* p1 = new product();
	product* p2 = new product();
	product* p3 = new inHouseProduct();

	std::vector<product> vecProduct;

	vecProduct.push_back(*p1);
	vecProduct.push_back(*p2);
	vecProduct.push_back(*p3);

	// here printing get discount should work fine as inHouseProduct has getDiscount implemented
}