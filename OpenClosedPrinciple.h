#pragma once
/*
	"Software components should be closed for modification, but open for extension." 

	Adding new features/behavior should not result in modifying existing code.

	Example : Creating an IO block with software stack of Ethernet/IP protocol. Now 
	this IO block can be a part of various applications. Such as multiple conveying 
	belts and HMI all connected to IO block. Here IO block is closed to modification 
	but was open for extension.
*/

/*
*	BAD Design
	below three classes is bad example as it does not follow open close concept. we have two classes one for each
	health and vehicle customers and now when we want to calculate discount we had to add function overloading.
	but what if now company wants to sell home insurance as well then we will have again modify class
	insuranceDiscountCalculator.
*/
class healthInsuranceCustomerProfile
{
	bool bLoyalCustomer;
public:

	healthInsuranceCustomerProfile(bool flag) : bLoyalCustomer{ flag }
	{}

	bool isLoyalCustomer(void)
	{
		if (bLoyalCustomer) return true;
		else return false;
	}
};

class vehicleInsuranceCustomerProfile
{
	bool bLoyalCustomer;
public:

	vehicleInsuranceCustomerProfile(bool flag) : bLoyalCustomer{ flag }
	{}

	bool isLoyalCustomer(void)
	{
		if (bLoyalCustomer) return true;
		else return false;
	}
};
class insuranceDiscountCalculator
{
public:
	int calculateDiscountPercent(healthInsuranceCustomerProfile customerObj)
	{
		if (customerObj.isLoyalCustomer()) return 20;
		else return 0;
	}
	int calculateDiscountPercent(vehicleInsuranceCustomerProfile customerObj)
	{
		if (customerObj.isLoyalCustomer()) return 20;
		else return 0;
	}
};

/* 
	GOOD Design

Good Example that follows open close concept, here first we will take benefit 
of inheritance, abstract class and polymorphism.

here class iDiscountCalculator's method calculateDiscountPercent is having customerProfile 
which is base class as param so any inherited class including vehicle , house, health 
insurance can be called.
*/
class customerProfile
{
public:
	virtual bool isLoyalCustomer(void) = 0;
};

// vehicle insurance
class vInsuranceCustomerProfile : public customerProfile
{
	bool bLoyalCustomer;
public:

	vInsuranceCustomerProfile(bool flag) : bLoyalCustomer{ flag }
	{}

	virtual bool isLoyalCustomer(void) override
	{
		if (bLoyalCustomer) return true;
		else return false;
	}
};

// house insurance
class hInsuranceCustomerProfile : public customerProfile
{
	bool bLoyalCustomer;
public:

	hInsuranceCustomerProfile(bool flag) : bLoyalCustomer{ flag }
	{}

	virtual bool isLoyalCustomer(void) override
	{
		if (bLoyalCustomer) return true;
		else return false;
	}
};

// Insurance discount calculator
class iDiscountCalculator
{
public:
	int calculateDiscountPercent(customerProfile customerObj)
	{
		if (customerObj.isLoyalCustomer()) return 20;
		else return 0;
	}
};