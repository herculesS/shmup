/*
 * GameObject.cpp
 *
 *  Created on: 17/05/2013
 *      Author: vitor
 */

#include "GameObject.h"

GameObject::GameObject(Shape* shape) {
	this->shape = shape;
}

GameObject::~GameObject() {
	delete (shape);
}
