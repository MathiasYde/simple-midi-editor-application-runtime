#include "EditorLayer.h"
#include <imgui/imgui.h>

namespace SMEAR {
	EditorLayer::EditorLayer() : Layer("EditorLayer") {}

	void EditorLayer::OnAttach() {}
	void EditorLayer::OnDetach() {}

	void EditorLayer::OnAwake() {}

	void EditorLayer::OnUpdate(TimeStep ts) {
		RenderCommand::Clear();
	}

	void EditorLayer::OnImGuiRender() {
		ImGui::Begin("Initial window");

		ImGui::Text("Hello world");

		ImGui::End();
	}
}