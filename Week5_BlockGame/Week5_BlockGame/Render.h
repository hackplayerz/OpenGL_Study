#pragma once
#include "IObject.h"
#include <queue>

/**
 * @class Render
 * @brief ���� ��ü.
 * @details ȭ�鿡 �׸��� ������ �� ��ü�� ���.
 */
class Render
{
private:
	std::queue<IObject> _renderQueue; ///< ������� ������ �ϱ����� ť.
public:
	/** Display callback method*/
	void OnDrawCall();
	/** �������� ��ü�� ����ť�� �ִ´�. */
	void AddRenderTarget(IObject Target);
};

