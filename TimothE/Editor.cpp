#include "Editor.h"
#include "ImGuiManager.h"
#include "Texture2D.h"

#include "misc/cpp/imgui_stdlib.h"
#include "misc/cpp/imgui_stdlib.cpp"

vector<string> Console::output = vector<string>();

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

	//Creates the screen shader for the framebuffer
	_pScreenShader = new Shader("fbVert.vs", "fbFrag.fs");

	//Creates the editor framebuffer
	_pEditorFramebuffer = new Framebuffer(_pScreenShader, quadVertices);
}

Editor::~Editor()
{
	delete _pEditorFramebuffer;
	delete _pScreenShader;
	delete _pWindow;
	delete _pEditorFramebuffer;
	delete _pScreenShader;
	delete _pScreenShader;
	delete _pSelectedGameObject;
	delete _pCurrentScene;
}

void Editor::EditorLoop(Scene* currentScene, float dt, bool& editorMode, bool& paused)
{
	EditorStartRender();

	EditorRender();

	//Handle unbinding the editor frame buffer and drawing it's contents
	_pEditorFramebuffer->UnbindFramebuffer();
	glDisable(GL_DEPTH_TEST);
	_pEditorFramebuffer->DrawFramebuffer();

	//Render Here
	ImGuiManager::ImGuiNewFrame();
	_pCurrentScene = currentScene;
	EditorImGui();
	ImGUISwitchRender(editorMode, paused);
	ImGuiManager::ImGuiEndFrame();

	EditorEndRender();

	if(!paused)
		EditorUpdate(dt);
}

void Editor::EditorImGui()
{
	static bool changeObject = false;

	{
		ImGui::Begin("Notes");

		string notes;
		ImGui::InputTextMultiline("Notes", &notes, ImVec2(300.0f, 600.0f), 0, 0);

		ImGui::End();
	}

	//Inspector
	{
		ImGui::Begin("Inspector");

		if (_pSelectedGameObject != nullptr)
		{
			// text box to change name
			{
				static string text = _pSelectedGameObject->GetName();
				if (changeObject)
				{
					text = _pSelectedGameObject->GetName();
				}
				if (ImGui::InputText("##ChangeObjectName", &text, ImGuiInputTextFlags_CharsNoBlank))
				{
					_pSelectedGameObject->SetName(text);
				}
			}

			// select object type
			if (ImGui::CollapsingHeader("Object Type"))
			{
				int index = (int)_pSelectedGameObject->GetType();
				if (ImGui::RadioButton("Player", &index, 0))
				{
					_pSelectedGameObject->SetType(ObjectType::Player);
				}
				if (ImGui::RadioButton("Enemy", &index, 1))
				{
					_pSelectedGameObject->SetType(ObjectType::Enemy);
				}
				if (ImGui::RadioButton("NPC", &index, 2))
				{
					_pSelectedGameObject->SetType(ObjectType::NPC);
				}
				if (ImGui::RadioButton("PickUp", &index, 3))
				{
					_pSelectedGameObject->SetType(ObjectType::PickUp);
				}
			}

			for(Component* c : _pSelectedGameObject->GetComponents())
			{
				c->EditorUI();
				if (c->GetType() != Component::Transform_Type)
				{
					if (ImGui::Button(("Delete component##" + to_string(c->GetType())).c_str()))
					{
						_pSelectedGameObject->RemoveComponent(c);
					}
				}
			}
			
			// add component
			if (ImGui::CollapsingHeader("AddComponent"))
			{
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
					static string texPath = "lenna3.jpg";
					if (ImGui::Button("Texture"))
					{
						if (_pSelectedGameObject->GetTexture() == nullptr)
						{
							_pSelectedGameObject->AddComponent(new Texture2D(), Component::Types::Transform_Type);
							_pSelectedGameObject->LoadTexture((char*)texPath.c_str(), "Linear");
						}
					}
					ImGui::SameLine();

					ImGui::InputText("##texturepath", &texPath);
				}
			}
		}

		ImGui::End();
	}

	//Hierarchy
	{
		ImGui::Begin("Hierarchy");

		if (ImGui::CollapsingHeader("Add GameObject"))
		{
			static string name = "New GameObject";

			ImGui::InputText("##NewGameObjectName", &name, ImGuiInputTextFlags_CharsNoBlank);
			static ObjectType tag = ObjectType::Player;
			if (ImGui::CollapsingHeader("Object type"))
			{
				static int tagIndex = 0;
				if (ImGui::RadioButton("Player", &tagIndex, 0))
				{
					tag = ObjectType::Player;
				}
				if (ImGui::RadioButton("Enemy", &tagIndex, 1))
				{
					tag = ObjectType::Enemy;
				}
				if (ImGui::RadioButton("NPC", &tagIndex, 2))
				{
					tag = ObjectType::NPC;
				}
				if (ImGui::RadioButton("PickUp", &tagIndex, 3))
				{
					tag = ObjectType::PickUp;
				}
			}
			if (ImGui::Button("Add Object"))
			{
				GameObject* obj = new GameObject(name, tag);
				_pCurrentScene->AddGameObject(obj);
				Console::Print("Object added: " + name);
				name = "New GameObject";
			}
		}

		changeObject = false;

		// index of the selected object
		static int index = 0;
		// get vector of objects from the current scene
		vector<GameObject*> objects = _pCurrentScene->GetGameObjects();
		if (!objects.empty())
		{
			for (int i = 0; i < objects.size(); i++)
			{
				// create a radio button for each of the objects
				// '##' is to add a unique ID for ImGui when labels are the same
				ImGui::RadioButton((objects[i]->GetName() + "##" + objects[i]->GetUID()).c_str(), &index, i); ImGui::SameLine();
				if (ImGui::Button(("Delete object##" + objects[i]->GetUID()).c_str()))
				{
					Console::Print("Deleted " + objects[i]->GetName());
					// add button next to object button that removes game object
					_pCurrentScene->RemoveGameObject(objects[i]);
					_pSelectedGameObject = nullptr;

					if (i <= index)
					{
						if (index > 0)
							index--;
					}

					// update objects and take 1 from i (because the object at the current index was removed)
					objects = _pCurrentScene->GetGameObjects();
					i--;
				}
			}
			// set selected object to the object that the user has selected. does nothing currently.
			if (!objects.empty())
			{
				if (_pSelectedGameObject != objects[index])
				{
					_pSelectedGameObject = objects[index];
					changeObject = true;
				}
			}
			else
				_pSelectedGameObject = nullptr;
		}
		ImGui::End();
	}

	//Console
	{
		ImGui::Begin("Console");

		static int oldSize = 0;
		// get output from console class
		vector<string> consoleOut = Console::GetConsoleOutput();
		for (string s : consoleOut)
		{
			ImGui::Text(s.c_str());
			if (consoleOut.size() > oldSize)
			{
				ImGui::SetScrollY(ImGui::GetScrollMaxY());
				oldSize = consoleOut.size();
			}
		}

		ImGui::End();
	}

	//Content Browser
	{
		ImGui::Begin("Content Browser");

		ImGui::End();
	}

	//ImGui::ShowDemoWindow();
}

void Editor::EditorStartRender()
{
	_pEditorFramebuffer->BindFramebuffer();
	glEnable(GL_DEPTH_TEST);
	_pWindow->SetWindowColour(0.5f, 0.5f, 0.1f, 1.0f);
	_pEditorFramebuffer->BindShader();
}

void Editor::ImGUISwitchRender(bool& editorMode, bool& paused)
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
	//float width = ImGui::GetWindowSize().x;
	//ImGui::SetCursorPosX((width - 30.0f) * 0.5f); // sets play and pause button to centre of window
	if (ImGui::Button("Play", ImVec2(50.0f, 30.0f)))
	{
		paused = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause", ImVec2(50.0f, 30.0f)))
	{
		paused = true;
	}
	ImGui::SameLine();
	//resets game build
	if (ImGui::Button("Stop", ImVec2(50.0f, 30.0f)))
	{
		_pCurrentScene = new Scene("Test scene");
		paused = true;
	}
	ImGui::SameLine();
	ImGui::Text(("Paused: " + to_string(paused)).c_str());
	ImGui::End();
}

void Editor::EditorRender()
{

}

void Editor::EditorEndRender()
{
	_pWindow->SwapBuffers();
}

void Editor::EditorUpdate(float dt)
{
	_pCurrentScene->Update(dt);
}

void Console::Print(string message)
{
	output.push_back(message);

	// TODO: maybe add a way to remove old messages after size exceeded max size to reduce memory usage for unneeded messages
}