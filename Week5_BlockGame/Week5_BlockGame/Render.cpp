#include "Render.h"

void Render::OnDrawCall()
{
	while (!_renderQueue.empty())
	{
		auto obj = _renderQueue.back();
		_renderQueue.pop();
		Color color = obj.GetColor();
		
		glBegin(GL_POLYGON);
		glColor3f(color.Red, color.Green, color.Blue);
		
		for (auto vertex : obj.GetPolygon())
		{
			glVertex3f(vertex.X, vertex.Y, vertex.Z);
		}
		glEnd();
	}
}

void Render::AddRenderTarget(const IObject Target)
{
	_renderQueue.push(Target);
}
