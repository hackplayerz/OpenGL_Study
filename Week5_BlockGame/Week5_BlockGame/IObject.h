#pragma once
#include <glut.h>
#include <vector>

/**
 * @struct Vertex
 * @brief �������� ������ ������.
 */
struct Vertex
{
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
};

/**
 * @struct Color
 * @brief �������� ���� ������.
 */
struct Color
{
	GLfloat Red;
	GLfloat Green;
	GLfloat Blue;
};

/**
 * @brief ȭ�鿡 �׷��� ��ü �������̽�.
 */
class IObject
{
public:
	IObject() = default;
	virtual ~IObject() = default;
protected:
	Color _color; ///< ����.
	std::vector<Vertex> _polygon; ///< ��ü�� ������.

public:
	/** Member getter.  */
	std::vector<Vertex> GetPolygon();
	Color GetColor();

public:
	/** @brief ��ü�� ��ġ�� �̵����ִ� �޼���.*/
	void Translate(GLfloat X,GLfloat Y, GLfloat Z);
};