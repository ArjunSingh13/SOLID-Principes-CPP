#pragma once
/*
*   Dependency Inversion Principle:
	High-level modules should not depend on low-level modules. Both should depend on abstractions.
	Abstractions should not depend on details. Details should depend on abstraction.

	Dependency Injection: To do
	Inversion of Control: To do
*/
#include <iostream>

/*
	BAD Design

	Issue with below design is higher layer lets say store is dependent on lower layer Stripe. and according
	to principle both should depend on abstraction. Lets say if we want to change our payment gateway from 
	stripe to google pay that will result in change in store class itself which is not what we want.
*/
class googlePay
{
public:
	void makePayment(int amount) {
		std::cout << "payment under process with fee of 3%" << std::endl;
	}
};

class stripe
{
public:
	void makePayment(int amount) {
		std::cout << "payment under process with fee of 5%" << std::endl;
	}
};

class store
{
private:
	stripe stripeObj;
	int bikePrice = 100;
	int helmetPrice = 10;
public:

	store(stripe stripeObj) {
		this->stripeObj = stripeObj;
	}

	void purchaseBike(int qty)
	{
		stripeObj.makePayment(qty * bikePrice);
	}
};

/*
	Good Design:
	To fix above issue we need to make our higher layer which has class store and lower layer which is stripe
	or google pay both dependent on an abstraction. For good architecture we should never be dependent on 
	concrete classes when we are developing a project.

	As googlePay has cheaper fees than Stipe so in below example we dont need to make change in design of our 
	Store class and we can use any gateway as we like. 

	So in below example dependency inversion is followed as both classes are dependent on Abstract class and we
	call it dependency inversion because before

	Store Class ----> stripe gateway

	Now : 

	Store Class ----> Payment gateway <------ stripe gateway
*/

class paymentGateway
{
public:
	virtual void makePayment(int amount) = 0 {}
};

class googlePay : public paymentGateway
{
public:
	virtual void makePayment(int amount) override {
		std::cout << "payment under process with fee of 3%" << std::endl;
	}
};

class stripe : public paymentGateway
{
public:
	virtual void makePayment(int amount) override {
		std::cout << "payment under process with fee of 5%" << std::endl;
	}
};

class store
{
private:
	paymentGateway* paymentObj;
	int bikePrice = 100;
	int helmetPrice = 10;
public:


	store(paymentGateway* paymentObj) {
		this->paymentObj = paymentObj;
	}

	void purchaseBike(int qty)
	{
		paymentObj->makePayment(qty * bikePrice);
	}
};

/*
	 this is a test function and for convenience its definition is left
	 in header file
*/
void testPayment(void)
{
	paymentGateway* pObj = new googlePay();
	store sObj(pObj);

	// should result in calling googlePay gateway
	sObj.purchaseBike(2);

}