#include "Editor.h"
#include "ImGuiManager.h"

Editor::Editor(Window* pWindow)
	: _pWindow(pWindow)
{
	// vertex attributes for a quad that fills the editor screen space in Normalized Device Coordinates.
	float* quadVertices = new float[24]{
		// positions   // texCoords
		-0.65f,  -0.6f,  0.0f, 0.0f,
		-0.65f,   0.82f,	0.0f, 1.0f,
		 0.6f,   0.82f,	1.0f, 1.0f,

		 0.6f,  -0.6f,  1.0f, 0.0f,
		-0.65f,  -0.6f,	0.0f, 0.0f,
		 0.6f,   0.82f,   1.0f, 1.0f
	};

	//Creates a large enough allocation to hold any notes we might have
	_pNotesBuffer = new char[16348];

	//Creates the screen shader for the framebuffer
	_pScreenShader = new Shader("fbVert.vs", "fbFrag.fs");

	//Creates the editor framebuffer
	_pEditorFramebuffer = new Framebuffer(_pScreenShader, quadVertices);
}

Editor::~Editor()
{
	delete _pEditorFramebuffer;
	delete _pScreenShader;
	delete _pNotesBuffer;
}

void Editor::EditorLoop(Scene* currentScene, float dt, bool& editorMode)
{
	EditorStartRender();

	EditorRender();

	//Handle unbinding the editor frame buffer and drawing it's contents
	_pEditorFramebuffer->UnbindFramebuffer();
	glDisable(GL_DEPTH_TEST);
	_pEditorFramebuffer->DrawFramebuffer();

	//Render Here
	ImGuiManager::ImGuiNewFrame();
	EditorImGui(currentScene);
	ImGUISwitchRender(editorMode);
	ImGuiManager::ImGuiEndFrame();


	EditorEndRender();

	EditorUpdate(currentScene, dt);
}

void Editor::EditorImGui(Scene* currentScene)
{
	{
		ImGui::Begin("Notes");

		ImGui::InputTextMultiline("Notes:", _pNotesBuffer, 16384, ImVec2(300.0f, 600.0f), 0, 0, _pNotesBuffer);

		ImGui::End();
	}

	//Inspector
	{
		ImGui::Begin("Inspector");

		if(_pSelectedGameObject != nullptr)
			_pSelectedGameObject->DisplayInEditor();

		ImGui::End();
	}

	//Hierarchy
	{
		ImGui::Begin("Hierarchy");

		bool openMenu = ImGui::Button("New Object");
		if (openMenu) {
			ImGui::OpenPopup("Create Objects");
		}
		if (ImGui::BeginPopup("Create Objects")) {
			if (ImGui::MenuItem("New GameObject")) {
				GameObject* obj = currentScene->AddGameObject(new GameObject("New Object"));
				_pSelectedGameObject = obj;
			}

			ImGui::EndPopup();
		}

		static int index = 0;
		vector<GameObject*> objects = currentScene->GetGameObjects();
		if (!objects.empty())
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (ImGui::RadioButton(objects[i]->GetName().c_str(), &index, i)) {
					std::cout << "Set I" << std::endl;
					//index = i;
					_pSelectedGameObject = objects[i];
				}
				ImGui::SameLine();
				if (ImGui::Button("Delete object"))
				{
					if (objects[i] == _pSelectedGameObject) _pSelectedGameObject = nullptr;
					currentScene->RemoveGameObject(objects[i]);
					objects = currentScene->GetGameObjects();
				}
			}
			if (!objects.empty())
				GameObject* selectedObject = objects[index];
		}
		ImGui::End();
	}

	//Console
	{
		ImGui::Begin("Console");

		ImGui::End();
	}

	//Content Browser
	{
		ImGui::Begin("Content Browser");

		ImGui::End();
	}

	ImGui::ShowDemoWindow();
}

void Editor::EditorStartRender()
{
	_pEditorFramebuffer->BindFramebuffer();
	glEnable(GL_DEPTH_TEST);
	_pWindow->SetWindowColour(0.5f, 0.5f, 0.1f, 1.0f);
	_pEditorFramebuffer->BindShader();
}

void Editor::ImGUISwitchRender(bool& editorMode)
{
	{
		ImGui::Begin("Application Mode");

		if (ImGui::Button("Editor", ImVec2(100.0f, 30.0f))) {
			editorMode = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Game", ImVec2(100.0f, 30.0f))) {
			editorMode = false;
		}
		ImGui::SameLine();
		ImGui::End();
	}
}

void Editor::EditorRender()
{

}

void Editor::EditorEndRender()
{
	_pWindow->SwapBuffers();
}

void Editor::EditorUpdate(Scene* currentScene, float dt)
{
	currentScene->Update(dt);
}
