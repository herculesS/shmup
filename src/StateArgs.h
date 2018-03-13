/*
 * StateArgs.h
 *
 *  Created on: 08/06/2013
 *      Author: vitor
 */

#ifndef STATEARGS_H_
#define STATEARGS_H_

#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>

class StateArgs {
private:
	std::vector<std::vector<std::string> > arguments;

public:
	StateArgs();
	StateArgs(std::vector<std::string> arguments);
	StateArgs(std::vector<std::vector<std::string> > arguments);

	std::string getArg(int pos);
	std::string getArg(int i, int j);
	std::vector<std::string> getLineArgs(int pos);
	std::vector<std::vector<std::string> > getAllArgs();
	bool isEmpty();
	int getSize();
	int getSize(int pos);
	void setArg(int pos, std::string argument);
	void setLineArgs(int pos, std::vector<std::string> argument);
	void setArg(int i, int j, std::string argument);
	int getArgCount();
	void swapLines(int i, int j);

	void addLineArg(std::vector<std::string> argument);
	void addArg(int pos, std::string argument);

	void eraseLineArg(int index);

	void printArguments();

	virtual ~StateArgs();
};

#endif /* STATEARGS_H_ */
