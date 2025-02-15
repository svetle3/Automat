// automat.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include "Automat.h"


Automat::Automat(int nStates, int sState, std::set<int> fStates) : numStates(nStates), start(sState), finalStates(fStates)
{
	for (int i = 0; i < numStates; i++)
		states.insert(i);
	for (char c = '0'; c <= '9'; c++)
		alphabet.insert(c);
	for (char c = 'a'; c <= 'z'; c++)
		alphabet.insert(c);

}

int Automat::transition(int from, std::string str)
{
	int final = from; //start from the initial state and change after every transition
	for (int i = 0; i < str.length(); i++)
	{
		if (table.count(std::make_pair(final, str.at(i))) != 0)
		{
			final = table.at(std::make_pair(final, str.at(i)));
		}
		else
		{
			std::cout << "Error" << std::endl;
			return -1;
		}
	}
	return final;
}

bool Automat::member(std::string str)
{
	int check = transition(start, str);

	return (finalStates.count(check) != 0);
}

void Automat::insertState(bool isEnd)   //insert a state
{
	if (isEnd)
	{
		finalStates.insert(numStates);
	}
	states.insert(numStates++);
}

bool Automat::insertTransition(int begin, char str, int end) // insert transition
{
	if (states.count(begin) != 0 && alphabet.count(str) != 0 && states.count(end) != 0)
	{
		table.insert(std::pair<std::pair<int, char>, int>(std::pair<int, char>(begin, str), end));
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const Automat& Automat)
{
	out << "Alphabet: ";
	for (char c : Automat.alphabet)
	{
		out << c << " ";
	}
	out << std::endl;

	out << "States: ";
	for (int i : Automat.states)
	{
		out << i << " ";
	}
	out << std::endl;

	out << "Final states: ";
	for (int i : Automat.finalStates)
	{
		out << i << " ";
	}
	if (!Automat.finalStates.empty())
		out << "" << std::endl;

	for (int i : Automat.states)
	{
		out << "State " << i << std::endl;
		for (char c : Automat.alphabet)
		{
			if (Automat.table.count(std::make_pair(i, c)) != 0)
				out << "(" << i << "," << c << ") = " << Automat.table.at(std::make_pair(i, c)) << std::endl;
		}
	}
	return out;
}

Automat Automat::operator!()const
{
	Automat Automat(*this); // create new automat

	// change every non-final state to final and every final state to non-final
	for (int i = 0; i < Automat.numStates; i++)
	{
		if (finalStates.count(i) != 0)
		{
			Automat.finalStates.erase(i);
		}
		else
		{
			Automat.finalStates.insert(i);
		}
	}
	return Automat;
}
Automat Automat::operator*(const Automat& other) const //intersection
{
	return !(!(*this) + !other);
}

Automat Automat::operator+(const Automat& other)const  //union
{
	int resultnumStates = numStates * other.numStates; 	// multiply automat's tables
	int resultStart = start * other.numStates + other.start;
	Automat newAutomat(resultnumStates, resultStart, {});

	for (int i = 0; i < numStates; i++)
	{
		for (int j = 0; j < other.numStates; j++)
		{
			for (char x : alphabet)
			{
				int current = i * other.numStates + j;
				int firstTransition = 0;
				int secondTransition = 0;
				bool firstFlag = false;
				bool secondFlag = false;

				if (finalStates.count(i) != 0 || other.finalStates.count(j) != 0)
					newAutomat.finalStates.insert(current);

				if (table.count(std::make_pair(i, x)) != 0)
				{
					firstTransition = table.at(std::make_pair(i, x));
					firstFlag = true;
				}
				if (other.table.count(std::make_pair(j, x)) != 0)
				{
					secondTransition = other.table.at(std::make_pair(j, x));
					secondFlag = true;
				}
				if (firstFlag || secondFlag)
					newAutomat.insertTransition(current, x, firstTransition*other.numStates + secondTransition);
			}
		}
	}
	return newAutomat;
}

int Automat::get_numStates() const
{
	return numStates;
}

int Automat::get_startIndex() const
{
	return start;
}

bool Automat::setFinal(int index)
{
	if (states.count(index) != 0)
	{
		if (finalStates.count(index) == 0) //if state is already final
			finalStates.insert(index);
		return true;
	}
	else return false;
}

