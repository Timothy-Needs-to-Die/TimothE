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
std::vector<std::string> _mDirectoryList;

std::vector<std::string> Console::output = std::vector<std::string>();

Editor::Editor(Application* pApp, Window* pWindow)
	: _pWindow(pWindow), _pApplication(pApp)
{
	//icon textures
	pContentTextureScript->Load("Icons/ScriptContent.png");
	pContentTextureImage->Load("Icons/ImageContent.png");
	pContentTextureScene->Load("Icons/SceneContent.png");
	pContentTextureConfig->Load("Icons/ConfigContent.png");
	pContentTextureSound->Load("Icons/SoundContent.png");
	pContentTextureFile->Load("Icons/FileContent.png");
	pContentTextureFolder->Load("Icons/FolderContent.png");



	//Creates the screen shader for the framebuffer
	_pScreenShader = new Shader("fbVert.vs", "fbFrag.fs");

	//Creates the editor framebuffer
	_pEditorFramebuffer = new Framebuffer(_pWindow, _pScreenShader);


	float aspectRatio = pWindow->GetWidth() / pWindow->GetHeight();
	float zoomLevel = 1.0f;

	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;

	_pEditorCamera = new Camera(left, right, bottom, top);

	pImGuiSample = new Texture2D(NULL);
	pImGuiSample->Load("lenna3.jpg");

	pTileMapEditor = new TileMapEditor();
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

		std::string notes;
		ImGui::InputTextMultiline("Notes", &notes, ImVec2(300.0f, 600.0f), 0, 0);

		ImGui::End();
	}

	//Tile Editor
	{
		pTileMapEditor->EnableEditor();
		pTileMapEditor->DisplayEditorGUI();
	}


	//Inspector
	{


		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);

		if (_pSelectedGameObject != nullptr)
		{
			// text box to change name
			{
				static std::string text = _pSelectedGameObject->GetName();
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

			Component* componentToDelete = nullptr;

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
					if (ImGui::Button(("Delete component##" + std::to_string(c->GetType())).c_str()))
					{
						componentToDelete = c;
						break;
						//_pSelectedGameObject->RemoveComponent(c);

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

			if (componentToDelete != nullptr) {
				_pSelectedGameObject->RemoveComponent(componentToDelete);
				componentToDelete = nullptr;
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
					// texture component
					static std::string texPath = "lenna3.jpg";
					ImGui::InputText("Texture path", &texPath);
					if (ImGui::Button("Texture"))
					{
						Texture2D* tex = _pSelectedGameObject->GetComponent<Texture2D>();
						if (tex == nullptr)
						{
							//_pSelectedGameObject->LoadTexture(new Texture2D((char*)texPath.c_str()));
						}
					}

					if (ImGui::Button("Particle System"))
					{
						_pSelectedGameObject->AddComponent<ParticleSystem>(new ParticleSystem(100, glm::vec4(1.0f), new Texture2D((char*)texPath.c_str()), _pSelectedGameObject->GetTransform()));
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
			static std::string name = "New GameObject";

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
		std::vector<GameObject*> objects = currentScene->GetGameObjects();
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

		// get output from console class
		std::vector<std::string> consoleOut = Console::GetConsoleOutput();
		// convert vector to string array
		std::string* out = &consoleOut[0];
		if (out != nullptr)
		{
			// output as wrapped text
			ImGui::TextWrapped(out->c_str());

			// scroll to the bottom of the console window
			ImGui::SetScrollY(ImGui::GetScrollMaxY());
		}

		ImGui::End();
	}

	//Content Browser
	{
		ImGui::Begin("Content Browser", 0, ImGuiWindowFlags_NoMove);

		if (ImGui::BeginPopupContextWindow())
		{
			static std::string name = " ";
			if (ImGui::CollapsingHeader("New Script"))
			{
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
			// makes new script with.scene files
			if (ImGui::CollapsingHeader("New Scene"))
			{
				if (ImGui::InputText(" ", &name, ImGuiInputTextFlags_CharsNoBlank)) {}
				if (ImGui::MenuItem("Add"))
				{
					CreateFileInContentBrowser(name, ".scene");
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
		//displays directory next to button
		ImGui::SameLine();
		ImGui::Text(_mCurrentDir.c_str());

		//sets up a column to display the files in a grid
		ImGui::Columns(4, NULL);
		ImGui::Separator();
		//for each item in directory create new button
		for (int i = 2; i < _mDirectoryList.size(); i++) {

			//checks filetype and give it an icon
			CheckFileType(_mDirectoryList[i]);

			//adds padding to files
			ImGui::Dummy(ImVec2(0, 20.0f));

			//goes to next column
			if (i > 0 || i % 4 == 2)
			{
				ImGui::NextColumn();
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
	ImGui::Text(("Paused: " + std::to_string(paused)).c_str());
	ImGui::End();
}

void Editor::EditorRender()
{
	ImGui::Begin("Scene Window", 0 ,ImGuiWindowFlags_NoMove);
	_windowPos = ImGui::GetCursorScreenPos();
	ImGui::GetWindowDrawList()->AddImage(
		(void*)_pEditorFramebuffer->GetTexture(),
		_windowPos,
		ImVec2(_windowPos.x + _pWindow->GetWidth() / 2.0f, _windowPos.y + _pWindow->GetHeight() / 2.0f),
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
	currentScene->EditorUpdate(dt);
	ConvertGameToEditorSpace();
}

void Editor::CreateFileInContentBrowser(std::string name, std::string type)
{
	std::ofstream fileStream(_mCurrentDir + "/" + name + type);
	fileStream.close();
}

//checks file type and displays file in content browser
void Editor::CheckFileType(std::string fileDirectory)
{
	//if file is a script
	if (fileDirectory.find(".cpp") != std::string::npos || fileDirectory.find(".h") != std::string::npos)
	{
		ImGui::Image((void*)pContentTextureScript->GetID(), ImVec2(100, 100));
		ImGui::Text(fileDirectory.c_str());
	}
	//if file is an image
	else if (fileDirectory.find(".png") != std::string::npos || fileDirectory.find(".jpg") != std::string::npos)
	{
		ImGui::Image((void*)pContentTextureImage->GetID(), ImVec2(100, 100));
		ImGui::Text(fileDirectory.c_str());
	}
	//if file is a scene
	else if (fileDirectory.find(".scene") != std::string::npos)
	{
		ImGui::Image((void*)pContentTextureScene->GetID(), ImVec2(100, 100));
		ImGui::Text(fileDirectory.c_str());
	}
	//file is a config file
	else if (fileDirectory.find(".ini") != std::string::npos)
	{
		ImGui::Image((void*)pContentTextureConfig->GetID(), ImVec2(100, 100));
		ImGui::Text(fileDirectory.c_str());
	}
	//file is a sound
	else if (fileDirectory.find(".mp3") != std::string::npos || fileDirectory.find(".wav") != std::string::npos)
	{
		ImGui::Image((void*)pContentTextureSound->GetID(), ImVec2(100, 100));
		ImGui::Text(fileDirectory.c_str());
	}
	//file is a folder
	else if (fileDirectory.find(".") == std::string::npos)
	{
		ImGui::Image((void*)pContentTextureFolder->GetID(), ImVec2(100, 100));
		//adds button with directory name which when pressed adds its name to directory string and updates buttons
		if (ImGui::Button(fileDirectory.c_str()))
		{
			_mCurrentDir += "/" + fileDirectory;
			SearchFileDirectory();
		}
	}
	//other file types
	else
	{
		ImGui::Image((void*)pContentTextureFile->GetID(), ImVec2(100, 100));
		ImGui::Text(fileDirectory.c_str());
	}
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
