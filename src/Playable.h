/*
 * Playable.h
 *
 *  Created on: 09/06/2013
 *      Author: vitor
 */

#ifndef PLAYABLE_H_
#define PLAYABLE_H_

#include <string>

class Playable {
protected:
	std::string fileName;

public:
	Playable();
	virtual ~Playable();

	virtual void play(int n) = 0;
	virtual void stop() = 0;
};

#endif /* PLAYABLE_H_ */
