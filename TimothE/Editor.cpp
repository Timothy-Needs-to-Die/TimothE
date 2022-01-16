#include "Editor.h"
#include "ImGuiManager.h"
#include "Texture2D.h"

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
	EditorImGui(currentScene);
	ImGUISwitchRender(editorMode, paused);
	ImGuiManager::ImGuiEndFrame();

	EditorEndRender();

	if(!paused)
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
			// text box to change name
			{
				static string text = _pSelectedGameObject->GetName();
				ImGui::InputText(" ", (char*)&text, 128);
				_pSelectedGameObject->SetName(text);
			}

			// select object type
			if (ImGui::CollapsingHeader("Object Type"))
			{
				static int consoletest = 0;
				Console::Print("test output " + to_string(consoletest++));

				static int index = (int)_pSelectedGameObject->GetType();
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

			// transform component
			if (_pSelectedGameObject->GetTransform() != nullptr)
			{
				ImGui::Text("Transform");

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
			
			// add component
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

		// bugs: having a name of 19 or more characters crashes
		// adding an object after another is deleted causes the first to come back? needs further testing
		if (ImGui::CollapsingHeader("Add GameObject"))
		{
			static string name = "Name";
			ImGui::InputText(" ", (char*)&name, 128);
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
				Texture2D* t = new Texture2D();
				t->Load("lenna3.jpg", "linear");

				GameObject* obj = new GameObject(name, tag, t);
				currentScene->AddGameObject(obj);
				Console::Print("Object added: " + name);
			}
		}

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
				if (ImGui::Button(("Delete object##" + to_string(i)).c_str()))
				{
					Console::Print("Deleted " + objects[i]->GetName());
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
	if (ImGui::Button("Play", ImVec2(30.0f, 30.0f)))
	{
		paused = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause", ImVec2(30.0f, 30.0f)))
	{
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

void Editor::EditorUpdate(Scene* currentScene, float dt)
{
	currentScene->Update(dt);
}

void Console::Print(string message)
{
	output.push_back(message);

	// TODO: maybe add a way to remove old messages after size exceeded max size to reduce memory usage for unneeded messages
}