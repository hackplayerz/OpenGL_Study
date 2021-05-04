#pragma once
#include "IObject.h"

class Projectile : public IObject
{
public:
	GLfloat bx;
	GLfloat by;
	GLfloat xdiff;
	GLfloat ydiff;
	Projectile(GLfloat, GLfloat, GLfloat, GLfloat);
};

