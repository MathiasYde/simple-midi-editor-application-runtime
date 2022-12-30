#pragma once

#include "Newt.h"

#include "Panels/Panel.h"

namespace SMEAR {
	class EditorLayer : public Newt::Layer {
	private:
		std::vector<Panel*> m_Panels;

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnAwake() override;
		virtual void OnUpdate(Newt::TimeStep ts) override;

		virtual void OnImGuiRender() override;
	};
}
