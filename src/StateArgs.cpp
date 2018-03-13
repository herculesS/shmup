/*
 * StateArgs.cpp
 *
 *  Created on: 08/06/2013
 *      Author: vitor
 */

#include "StateArgs.h"

StateArgs::StateArgs() {
}

StateArgs::StateArgs(std::vector<std::string> arguments) {
	this->arguments.push_back(arguments);
}

StateArgs::StateArgs(std::vector<std::vector<std::string> > arguments) {
	this->arguments = arguments;
}

StateArgs::~StateArgs() {
	// TODO Auto-generated destructor stub
}

int StateArgs::getArgCount() {
	return arguments[0].size();
}

std::string StateArgs::getArg(int pos) {
	return arguments[0].at(pos);
}

std::string StateArgs::getArg(int i, int j) {
	return arguments[i].at(j);
}

std::vector<std::string> StateArgs::getLineArgs(int pos) {
	return arguments[pos];
}

std::vector<std::vector<std::string> > StateArgs::getAllArgs() {
	return arguments;
}

int StateArgs::getSize() {
	return arguments.size();
}

int StateArgs::getSize(int pos) {
	return arguments[pos].size();
}

bool StateArgs::isEmpty() {
	return arguments.empty();
}

void StateArgs::setArg(int pos, std::string argument) {
	arguments[0][pos] = argument;
}

void StateArgs::setArg(int i, int j, std::string argument) {
	arguments[i][j] = argument;
}

void StateArgs::setLineArgs(int pos, std::vector<std::string> argument) {
	arguments[pos] = argument;
}

void StateArgs::addLineArg(std::vector<std::string> argument) {
	arguments.push_back(argument);
}

void StateArgs::addArg(int pos, std::string argument) {
	arguments[pos].push_back(argument);
}

void StateArgs::swapLines(int i, int j) {
	std::swap(arguments[i], arguments[j]);
}

void StateArgs::eraseLineArg(int index) {
	arguments.erase(arguments.begin() + index);
}

void StateArgs::printArguments() {
	for (unsigned int i = 0; i < arguments.size(); i++) {
		for (unsigned int j = 0; j < arguments[i].size(); i++) {
			printf("%s ", arguments[i][j].c_str());
		}
		printf("\n");
	}
}
