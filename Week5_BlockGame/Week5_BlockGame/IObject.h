#pragma once
#include <glut.h>
#include <vector>

/**
 * @struct Vertex
 * @brief 폴리곤의 꼭짓점 데이터.
 */
struct Vertex
{
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
};

/**
 * @struct Color
 * @brief 폴리곤의 색상 데이터.
 */
struct Color
{
	GLfloat Red;
	GLfloat Green;
	GLfloat Blue;
};

/**
 * @brief 화면에 그려질 객체 인터페이스.
 */
class IObject
{
public:
	IObject() = default;
	virtual ~IObject() = default;
protected:
	Color _color; ///< 색상.
	std::vector<Vertex> _polygon; ///< 객체의 폴리곤.

public:
	/** Member getter.  */
	std::vector<Vertex> GetPolygon();
	Color GetColor();

public:
	/** @brief 객체의 위치를 이동해주는 메서드.*/
	void Translate(GLfloat X,GLfloat Y, GLfloat Z);
};