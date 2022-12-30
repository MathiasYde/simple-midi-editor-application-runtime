#pragma once

#include "Newt.h"
using namespace Newt;

namespace SMEAR {
	class EditorLayer : public Layer {
	private:
		std::vector<Panel*> m_Panels;

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnAwake() override;
		virtual void OnUpdate(TimeStep ts) override;

		virtual void OnImGuiRender() override;
	};
}
