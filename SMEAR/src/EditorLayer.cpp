#include "EditorLayer.h"

#include <imgui/imgui.h>

#include <vector>

#include "Panels/Panel.h"
#include "Panels/PianoPanel.h"

namespace SMEAR {
	EditorLayer::EditorLayer() : Newt::Layer("EditorLayer") {
		m_Panels.push_back(new PianoPanel());
	}

	void EditorLayer::OnAttach() {
		for (Panel* panel : m_Panels) {
			panel->OnAttach();
		}
	}

	void EditorLayer::OnDetach() {
		for (Panel* panel : m_Panels) {
			panel->OnDetach();
		}
	}

	void EditorLayer::OnAwake() {}

	void EditorLayer::OnUpdate(Newt::TimeStep ts) {
		Newt::RenderCommand::Clear();
	}

	void EditorLayer::OnImGuiRender() {
		for (Panel* panel : m_Panels) {
			panel->OnImGuiRender();
		}

		ImGui::Begin("Initial window");
		ImGui::Text("Hello world");
		ImGui::End();
	}
}