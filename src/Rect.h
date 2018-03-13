/*
 * Rect.h
 *
 *  Created on: 30/05/2013
 *      Author: vitor
 */

#ifndef RECT_H_
#define RECT_H_

#include "Shape.h"
#include "Point.h"
#include "Vector2.h"
#include <algorithm>
#include <math.h>

class Rect: public Shape {
private:
	float w, h;
	float angleInDegrees; // Usado na colisão com eixos independentes

	// Pontos auxiliares pré-calculados para acelerar o cálculo da colisão
	Point rotatedTopLeft;
	Point rotatedTopRight;
	Point rotatedBottomRight;
	Point rotatedBottomLeft;

	// Vetores também pré-calculados
	Vector2 TLTRNormal; // Normal produzida a partir dos pontos Top Left->Top Right
	Vector2 TRBRNormal; // Normal produzida a partir dos pontos Top Right->Bottom Right

	void calculatePoints();
	float minProjection(Vector2 projectionAxis);
	float maxProjection(Vector2 projectionAxis);

public:
	Rect();
	Rect(float x, float y, float w, float h, float angleInDegrees = 0);
	Rect(Point center, float w, float h, float angleInDegrees = 0);
	virtual ~Rect();

	Shape::TYPE getType() {
		return Shape::RECTANGLE;
	}

	bool collidesWith(Rect other);

	float getH() const {
		return h;
	}

	void setH(float h);

	float getW() const {
		return w;
	}

	void setW(float w);

	void setX(float x);

	void setY(float y);

	float getX() {
		return center.getX();
	}

	float getY() {
		return center.getY();
	}

	void setCenter(Point position);

	float getAngleInDegrees() const {
		return angleInDegrees;
	}

	void setAngleInDegrees(float angleInDegrees);

	const Vector2& getTLTRNormal() const {
		return TLTRNormal;
	}

	const Vector2& getTRBRNormal() const {
		return TRBRNormal;
	}
};

#endif /* RECT_H_ */
