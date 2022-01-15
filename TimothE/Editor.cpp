#include "Editor.h"
#include "ImGuiManager.h"

Editor::Editor(Window* pWindow)
	: _pWindow(pWindow)
{
	// vertex attributes for a quad that fills the editor screen space in Normalized Device Coordinates.
	float* quadVertices = new float[24] {
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

		if (_pSelectedGameObject != nullptr)
		{
			{
				static string text = _pSelectedGameObject->GetName();
				ImGui::InputText("Name", (char*)&text, 128);
				_pSelectedGameObject->SetName(text);
			}

			// transform component
			ImGui::Text("Transform");

			if (_pSelectedGameObject->GetTransform() != nullptr)
			{
				// get the position
				float* pos = new float[2]{ _pSelectedGameObject->GetTransform()->GetPosition()->_x, _pSelectedGameObject->GetTransform()->GetPosition()->_y };
				// create boxes to set the position
				ImGui::InputFloat2("Position", pos);
				// set the position on the game object
				_pSelectedGameObject->GetTransform()->SetPosition(pos[0], pos[1]);

				float* rot = new float[2]{ _pSelectedGameObject->GetTransform()->GetXrotation(), _pSelectedGameObject->GetTransform()->GetYrotation() };
				ImGui::InputFloat2("Rotation", rot);
				_pSelectedGameObject->GetTransform()->SetXrotation(rot[0]);
				_pSelectedGameObject->GetTransform()->SetYrotation(rot[1]);

				float* scale = new float[2]{ _pSelectedGameObject->GetTransform()->GetXrotation(), _pSelectedGameObject->GetTransform()->GetYrotation() };
				ImGui::InputFloat2("Scale", scale);
				_pSelectedGameObject->GetTransform()->SetXScale(scale[0]);
				_pSelectedGameObject->GetTransform()->SetYScale(scale[1]);
			}
			
			ImGui::Spacing();
			if (ImGui::CollapsingHeader("AddComponent"))
			{
				if (ImGui::CollapsingHeader("Transform"))
				{
					if (ImGui::Button("Transform"))
					{
						if (_pSelectedGameObject->GetTransform() == nullptr)
						{
							_pSelectedGameObject->AddComponent(new Transform(), Component::Types::Transform_Type);
						}
					}
				}
				if (ImGui::CollapsingHeader("Sound System"))
				{
					if (ImGui::Button("Sound"))
					{

					}
				}
				if (ImGui::CollapsingHeader("Colliders"))
				{
					if (ImGui::Button("Box Collider"))
					{

					}
					if (ImGui::Button("Circle Collider"))
					{

					}
				}
				if (ImGui::CollapsingHeader("AI"))
				{
					if (ImGui::Button("Pathfinding"))
					{

					}
					if (ImGui::Button("GOAP"))
					{

					}
				}
				if (ImGui::CollapsingHeader("Graphics"))
				{
					if (ImGui::Button("Texture"))
					{

					}
				}
			}
		}

		ImGui::End();
	}

	//Hierarchy
	{
		ImGui::Begin("Hierarchy");
		// index of the selected object
		static int index = 0;
		// get vector of objects from the current scene
		vector<GameObject*> objects = currentScene->GetGameObjects();
		if (!objects.empty())
		{
			for (int i = 0; i < objects.size(); i++)
			{
				// create a radio button for each of the objects
				ImGui::RadioButton(objects[i]->GetName().c_str(), &index, i); ImGui::SameLine();
				if (ImGui::Button("Delete object"))
				{
					// add button next to object button that removes game object
					currentScene->RemoveGameObject(objects[i]);
					_pSelectedGameObject = nullptr;
					// update objects and take 1 from i (because the object at the current index was removed)
					objects = currentScene->GetGameObjects();
					i--;
				}
			}
			// set selected object to the object that the user has selected. does nothing currently.
			if (!objects.empty())
				_pSelectedGameObject = objects[index];
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
