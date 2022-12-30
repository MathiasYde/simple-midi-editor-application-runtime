#pragma once

class Panel {
public:
	virtual void OnAttach() {}
	virtual void OnDetach() {}

	virtual void OnImGuiRender() {}
};