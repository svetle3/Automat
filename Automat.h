#pragma once
#include <iostream> 
#include <map>		
#include <set>		
#include <string>

class Automat
{
private:
	int numStates; //int from 0 to numStates
	int start; // start state

	std::set<int> states;
	std::set<char> alphabet;
	std::set<int> finalStates; //subset of {0, , numStates-1}
	std::map<std::pair<int, char>, int> table;

	int transition(int, std::string);//takes string and returns the state after finishing

public:
	Automat(int nStates = 1, int sState = 0, std::set<int> fStates = {});
	
	bool member(std::string);//checks if word is from tha language
	void insertState(bool); //insert a state
	bool insertTransition(int, char, int);// insert a transition
	
	Automat operator+(const Automat&)const;// union
	Automat operator*(const Automat&)const;// intersection
	Automat operator!()const ;

	int get_numStates() const;//number of states
	int get_startIndex() const;//start index
	bool setFinal(int); //checks if argument is a valid state index

	friend std::ostream& operator<<(std::ostream&, const Automat&);
};