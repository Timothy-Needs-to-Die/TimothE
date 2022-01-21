#include "Editor.h"
#include "ImGuiManager.h"
#include "Texture2D.h"
#include "BoxColliderComponent.h"

#include "misc/cpp/imgui_stdlib.h"
#include "misc/cpp/imgui_stdlib.cpp"
#include "dirent.h"
#include "Input.h"
#include "CircleCollider.h"
#include "Application.h"
#include "imgui.h"

DIR* _mDirectory;
struct dirent* _mDirent;
vector<string> _mDirectoryList;

vector<string> Console::output = vector<string>();

Editor::Editor(Application* pApp, Window* pWindow)
	: _pWindow(pWindow), _pApplication(pApp)
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

	//Creates the screen shader for the framebuffer
	_pScreenShader = new Shader("fbVert.vs", "fbFrag.fs");

	//Creates the editor framebuffer
	_pEditorFramebuffer = new Framebuffer(_pScreenShader);

	_pEditorCamera = new Camera(pWindow->GetGLFWWindow(), 1280, 720, 45.0f);

	pImGuiSample = new Texture2D(NULL);
	pImGuiSample->Load("lenna3.jpg");

	//pContentTextureImage->Load("Icons/ImageContent.png", "Linear");
	//pContentTextureScene->Load("Icons/SceneContent.png", "Linear");
	//pContentTextureConfig->Load("Icons/ConfigContent.png", "Linear");
	//pContentTextureScript->Load("Icons/ScriptContent.png", "Linear");
	//pContentTextureSound->Load("Icons/SoundContent.png", "Linear");
	//pContentTextureFile->Load("Icons/FileContent.png", "Linear");
	//pContentTextureFolder->Load("Icons/FolderContent.png", "Linear");
}

Editor::~Editor()
{
	delete _pEditorFramebuffer;
	delete _pScreenShader;
}

void Editor::EditorLoop(Scene* currentScene, float dt, bool& editorMode, bool& paused)
{
	_pEditorCamera->Update(dt);

	EditorImGui(currentScene);
	ImGUISwitchRender(editorMode, paused);

	EditorUpdate(currentScene, dt);
}

void Editor::EditorImGui(Scene* currentScene)
{
	ImGui::ShowDemoWindow();

	static bool changeObject = false;



	//ImGui::DockSpaceOverViewport(0, ImGuiDockNodeFlags_PassthruCentralNode);

	{
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::MenuItem("File")) {
				if (ImGui::BeginChild("FileMenu")) {
					if (ImGui::MenuItem("New Scene"))
					{
						std::cout << "New Scene" << std::endl;
					}
					if (ImGui::MenuItem("Load Scene")) {
						std::cout << "Load Scene" << std::endl;
					}
				}
				ImGui::EndChild();
			}
			if (ImGui::MenuItem("Edit")) {

			}
			if (ImGui::MenuItem("View")) {

			}
		}
		ImGui::EndMainMenuBar();
	}

	{
		ImGui::Begin("Notes", 0, ImGuiWindowFlags_NoMove);

		string notes;
		ImGui::InputTextMultiline("Notes", &notes, ImVec2(300.0f, 600.0f), 0, 0);

		ImGui::End();
	}

	//Tile Editor
	{
		ImGui::Begin("Tile Editor", 0, ImGuiWindowFlags_NoMove);

		//Left Panel
		ImGui::BeginChild("Tiles", ImVec2(200, 0), true);

		for (int i = 0; i < 16; ++i) {

			for (int j = 0; j < 3; ++j) {
				if (ImGui::ImageButton((void*)pImGuiSample->GetID(), ImVec2(50, 50))) {

				}


				ImGui::SameLine();
			}
			ImGui::NewLine();
		}

		ImGui::EndChild();

		ImGui::End();
	}


	//Inspector
	{


		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);

		if (_pSelectedGameObject != nullptr)
		{
			// text box to change name
			{
				static string text = _pSelectedGameObject->GetName();
				if (changeObject)
				{
					text = _pSelectedGameObject->GetName();
				}
				if (ImGui::InputText(" ", &text, ImGuiInputTextFlags_CharsNoBlank))
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

			// for each component in the game object
			for (int i = 0; i < _pSelectedGameObject->GetComponents().size(); i++)
			{
				Component* c = _pSelectedGameObject->GetComponents()[i];
				// draw the UI for the current component
				c->DrawEditorUI();

				// check the current component is not transform
				if (c->GetType() != Component::Transform_Type)
				{
					// add a delete button
					if (ImGui::Button(("Delete component##" + to_string(c->GetType())).c_str()))
					{
						_pSelectedGameObject->RemoveComponent(c);
					}
					// check if i is not the first
					if (i > 0)
					{
						if (_pSelectedGameObject->GetComponents()[i - 1]->GetType() != Component::Transform_Type)
						{
							ImGui::SameLine();
							// add button to move the component up 
							if (ImGui::Button("Up"))
							{
								_pSelectedGameObject->SwapComponents(i, i - 1);
							}
						}
					}
					// check if i is not the last
					if (i < _pSelectedGameObject->GetComponents().size() - 1)
					{
						ImGui::SameLine();
						// add button to move the component down
						if (ImGui::Button("Down"))
						{
							_pSelectedGameObject->SwapComponents(i, i + 1);
						}
					}
				}
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
							_pSelectedGameObject->AddComponent(new Transform(_pSelectedGameObject));
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
						BoxColliderComponent* pTest = _pSelectedGameObject->GetComponent<BoxColliderComponent>();
						if (pTest == nullptr)
						{
							_pSelectedGameObject->AddComponent(new BoxColliderComponent(_pSelectedGameObject));
						}
					}
					if (ImGui::Button("Circle Collider"))
					{
						CircleCollider* pTest = _pSelectedGameObject->GetComponent<CircleCollider>();
						if (pTest == nullptr)
						{
							_pSelectedGameObject->AddComponent(new CircleCollider(_pSelectedGameObject));
						}
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
					ImGui::InputText("Texture path", &texPath);
					if (ImGui::Button("Texture"))
					{
						Texture2D* tex = _pSelectedGameObject->GetComponent<Texture2D>();
						if (tex == nullptr)
						{
							_pSelectedGameObject->LoadTexture(new Texture2D((char*)texPath.c_str()));
						}
					}
				}
			}
		}

		ImGui::End();
	}

	//Hierarchy
	{
		ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_NoMove);

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
				currentScene->AddGameObject(obj);
				Console::Print("Object added: " + name);
				name = "New GameObject";
			}
		}

		changeObject = false;

		// index of the selected object
		static int index = 0;
		// get vector of objects from the current scene
		vector<GameObject*> objects = currentScene->GetGameObjects();
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
					currentScene->RemoveGameObject(objects[i]);
					_pSelectedGameObject = nullptr;
					// update objects and take 1 from i (because the object at the current index was removed)
					objects = currentScene->GetGameObjects();
					i--;

					if (i <= index)
					{
						if (index > 0)
							index--;
					}
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
		ImGui::Begin("Console", 0, ImGuiWindowFlags_NoMove);

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
		ImGui::Begin("Content Browser", 0, ImGuiWindowFlags_NoMove);

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::CollapsingHeader("New Script"))
			{
				static string name = "New Script";
				if (ImGui::InputText(" ", &name, ImGuiInputTextFlags_CharsNoBlank)) {}
				if (ImGui::MenuItem("Add"))
				{
					std::ofstream cppStream(_mCurrentDir + "/" + name + ".cpp");
					cppStream.close();
					std::ofstream hStream(_mCurrentDir + "/" + name + ".h");
					hStream.close();
					SearchFileDirectory();
				}

			}

			ImGui::EndPopup();
		}

		//adds back button which removes last directory and updates options
		if (ImGui::Button("Back"))
		{
			_mCurrentDir = _mCurrentDir.substr(0, _mCurrentDir.find_last_of("\\/"));
			SearchFileDirectory();
		}

		//for each item in directory create new button
		for (int i = 2; i < _mDirectoryList.size(); i++) {
			//add image for each directory

			//ImGui::Image((void*)pContentTextureScript->GetID(), ImVec2(100,100));

			//adds button with directory name which when pressed adds its name to directory string and updates buttons
			if (ImGui::Button(_mDirectoryList[i].c_str()))
			{
				_mCurrentDir += "/" + _mDirectoryList[i];
				SearchFileDirectory();
			}
			ImGui::Dummy(ImVec2(0, 80.0f));
		}
		ImGui::End();
	}

}

void Editor::EditorStartRender()
{
	_pEditorFramebuffer->BindFramebuffer();
	glEnable(GL_DEPTH_TEST);
	_pEditorFramebuffer->BindShader();
}

void Editor::ImGUISwitchRender(bool& editorMode, bool& paused)
{
	ImGui::Begin("Application Mode", 0, ImGuiWindowFlags_NoMove);

	if (ImGui::Button("Play", ImVec2(90.0f, 30.0f)))
	{
		//paused = false;
		_pApplication->GameStart();
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause", ImVec2(90.0f, 30.0f)))
	{
		paused = true;
	}
	ImGui::SameLine();
	ImGui::Text(("Paused: " + to_string(paused)).c_str());
	ImGui::End();
}

void Editor::EditorRender()
{
	ImGui::Begin("Scene Window", 0 ,ImGuiWindowFlags_NoMove);
	_windowPos = ImGui::GetCursorScreenPos();
	ImGui::GetWindowDrawList()->AddImage(
		(void*)_pEditorFramebuffer->GetTexture(),
		_windowPos,
		ImVec2(_windowPos.x + 640, _windowPos.y + 360),
		ImVec2(0, 1.0), ImVec2(1.0, 0));

	_windowSize = ImGui::GetWindowSize();
	ImGui::End();

	ConvertGameToEditorSpace();
}

void Editor::EditorEndRender()
{
	_pWindow->SwapBuffers();
}

void Editor::ConvertGameToEditorSpace()
{
	glm::vec2 mousePos = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
	glm::vec2 editorPos = glm::vec2(0.0f);

	editorPos.x = mousePos.x - _windowPos.x;
	editorPos.y = mousePos.y + _windowPos.y - _windowSize.y;

	if (editorPos.x < 0) editorPos.x = 0.0f;
	else if (editorPos.x > _windowSize.x) editorPos.x = _windowSize.x;

	if (editorPos.y < 0) editorPos.y = 0.0f;
	else if (editorPos.y > _windowSize.y) editorPos.y = _windowSize.y;

	_mousePosInEditorSpace = editorPos;
}


void Editor::EditorUpdate(Scene* currentScene, float dt)
{
	currentScene->EditorUpdate();
	ConvertGameToEditorSpace();
}

void Editor::CreateFileInContentBrowser()
{
}

//creates list of directorys for the content browser
void Editor::SearchFileDirectory()
{
	//clears old directory list
	_mDirectoryList.clear();
	std::cout << _mCurrentDir << std::endl;
	//opens directory with current directory string and adds them to a list, closes directory finishing update
	_mDirectory = opendir(_mCurrentDir.c_str());
	if (_mDirectory)
	{
		while ((_mDirent = readdir(_mDirectory)) != NULL)
		{
			_mDirectoryList.push_back(_mDirent->d_name);

			std::cout << "Content Browser loaded: " << _mDirent->d_name << std::endl;
		}
		closedir(_mDirectory);
	}
}
