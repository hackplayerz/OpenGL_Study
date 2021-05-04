#pragma once
#include "IObject.h"
#include <queue>

/**
 * @class Render
 * @brief 렌더 객체.
 * @details 화면에 그리는 행위는 이 객체가 당담.
 */
class Render
{
private:
	std::queue<IObject> _renderQueue; ///< 순서대로 렌더링 하기위한 큐.
public:
	/** Display callback method*/
	void OnDrawCall();
	/** 렌더링할 객체를 렌더큐에 넣는다. */
	void AddRenderTarget(IObject Target);
};

