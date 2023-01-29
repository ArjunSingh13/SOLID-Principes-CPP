#pragma once
/*
	No client should be forced to depend on methods it does not use.	

	Standard Techniques to avoid this principle:

	1. Fat Interfaces : With lots of methods that are not too related to each other.
	2. Low Cohesion:  Example scanPhoto and fax in a printer class.
	3. Emplty Methods: Almost always sign of this principle.
*/
#include <iostream>

/*
BAD Implementation

There is a main class for all kinds of printers and then 3 subclasses for 3 different kind of printers. 
Issue is not all printers supports all features so some classes may have empty methods which can give
false idea of supporting the feature to user that can result in code failure.
*/
class Printer
{
public:

	virtual void print() = 0 {};
	virtual void getPrinterInfo() = 0 {};
	virtual void scan() = 0 {};
	virtual void scanPhoto() = 0 {};
	virtual void fax() = 0 {};
	virtual void internetFax() = 0 {};
};

class XeroxWorkCentre : public Printer
{
public:

	virtual void print() { std::cout << "Feature supported" << std::endl; };
	virtual void getPrinterInfo() { std::cout << "Feature supported" << std::endl; };
	virtual void scan() { std::cout << "Feature supported" << std::endl; };
	virtual void scanPhoto() { std::cout << "Feature supported" << std::endl; };
	virtual void fax() { std::cout << "Feature supported" << std::endl; };
	virtual void internetFax() { std::cout << "Feature supported" << std::endl; };
};

class hpPrinterScanner : public Printer
{
public:
	virtual void print() { std::cout << "Feature supported" << std::endl; };
	virtual void getPrinterInfo() { std::cout << "Feature supported" << std::endl; };
	virtual void scan() { std::cout << "Feature supported" << std::endl; };
	virtual void scanPhoto() { std::cout << "Feature supported" << std::endl; };
	virtual void fax() { std::cout << "Feature NOT supported" << std::endl; };
	virtual void internetFax() { std::cout << "Feature NOT supported" << std::endl; };
};

class cannonPrinter : public Printer
{
public:
	virtual void print() { std::cout << "Feature supported" << std::endl; };
	virtual void getPrinterInfo() { std::cout << "Feature supported" << std::endl; };
	virtual void scan() { std::cout << "Feature NOT supported" << std::endl; };
	virtual void scanPhoto() { std::cout << "Feature NOT supported" << std::endl; };
	virtual void fax() { std::cout << "Feature NOT supported" << std::endl; };
	virtual void internetFax() { std::cout << "Feature NOT supported" << std::endl; };
};

/*
	Good Implementation

	Now to not give use surprises of feature not supported for some of the features, we need to 
	"segregate" the features into multiple classes for the base class. so printer only inherit 
	features that it can support
*/
class iPrint
{
	virtual void print() = 0 {};
	virtual void getPrintInfo() = 0 {};
};

class iScan
{
	virtual void scan() = 0 {};
	virtual void scanPhoto() = 0 {};
};

class iFax
{
	virtual void fax() = 0 {};
	virtual void internetFax() = 0 {};
};

class XeroxWorkCentre : public iPrint, public iScan, public iFax
{
public:

	virtual void print() { std::cout << "Feature supported" << std::endl; };
	virtual void getPrinterInfo() { std::cout << "Feature supported" << std::endl; };
	virtual void scan() { std::cout << "Feature supported" << std::endl; };
	virtual void scanPhoto() { std::cout << "Feature supported" << std::endl; };
	virtual void fax() { std::cout << "Feature supported" << std::endl; };
	virtual void internetFax() { std::cout << "Feature supported" << std::endl; };
};

class hpPrinterScanner : public iPrint, public iScan
{
public:
	virtual void print() { std::cout << "Feature supported" << std::endl; };
	virtual void getPrinterInfo() { std::cout << "Feature supported" << std::endl; };
	virtual void scan() { std::cout << "Feature supported" << std::endl; };
	virtual void scanPhoto() { std::cout << "Feature supported" << std::endl; };
};

class cannonPrinter : public iPrint
{
public:
	virtual void print() { std::cout << "Feature supported" << std::endl; };
	virtual void getPrinterInfo() { std::cout << "Feature supported" << std::endl; };
};

