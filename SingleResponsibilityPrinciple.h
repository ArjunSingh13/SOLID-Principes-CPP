#pragma once
#include <iostream>
/*
	Every Software Component should have one and only one reason to change. Aim for high cohesion and loose coupling.

	Cohesion: Degree to which the various parts of a software component are related. (Ideally should only be upto some extent).
	Example various kind of trash are segregated into recycle, organic and waste. Here different kind, color and material of plastic
	is added into recycle. So they all are cohesive to each other. The reason is lessser the responsibilites a class has higher the chance of having
	higher cohesion as elements of class/module are highly related to each other.

	Coupling: Level of inter dependency between various software components. Example two trains , first use 1.4 m rail track and other
	use 1.6m rail track. which means a train is tightly coupled to its track. It can be good for trains but not a good thing for
	software.
*/

/* 
	BAD Design

square and squareUI are the example of cohesion.
* If we add square and squareUI methods in same class then cohesion will be 
less but now classes are divided into two where square class' responsibility 
is to manage measurements of square and squareUI is for rendering images of
square.
*/
class square
{
	int side = 10;

public:

	square(int side): side{side}
	{	}

	int calcArea(void) {
		return side * side;
	}

	int calcPerim(void)
	{
		return 4 * side;
	}
};

class squareUI {
	
	bool isHighResolution;
public:

	squareUI(bool isHighResolution) : isHighResolution{ isHighResolution }
	{}

	void draw(void) {
		if(isHighResolution){}
		else{}
	}

	void rotate(int degree) {
		// rotate picture to provided degree

	}
};

/* 
*	GOOD Design
* 
* student and studentRepository class' are example of loose coupling. student class is not dependent on database and only
* on incoming get input so its loose coupling.
* 
* Only reason for change will be setting student information. So nothing 
* related to database
*/
class student
{
	int studentId;
	std::string address;
	std::string name;

public:
	int getStudentId(void)
	{
		return studentId;
	}

	void setStudentId(int studentId) {
		this->studentId = studentId;
	}
	// more getters and setters will go here

};

/*
 only reason to change here is to store data in a database so only 
 database can change here.
*/
class studentRepository
{
	student studentId;
public:
	void save(student studentObj)
	{
		// here we pass that same studentObj that was created for 
		// getters and setters.

		// depending on what kind of storage we use we can implement
		// here to store the student object  
	}
};