#include "IObject.h"

void IObject::Translate(GLfloat X , GLfloat Y , GLfloat Z)
{
	for (auto& vertex : _polygon)
	{
		vertex.X += X;
		vertex.Y += Y;
		vertex.Z += Z;
	}
}

std::vector<Vertex> IObject::GetPolygon()
{
	return _polygon;
}

Color IObject::GetColor()
{
	return _color;
}
