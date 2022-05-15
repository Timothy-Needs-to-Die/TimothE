#include "pch.h"
#include "Editor.h"
#include "ImGuiManager.h"
#include "Texture2D.h"
#include "BoxColliderComponent.h"

#include "misc/cpp/imgui_stdlib.h"
#include "misc/cpp/imgui_stdlib.cpp"
#include "dirent.h"
#include "Input.h"
#include "Application.h"
#include "imgui.h"
//#include "Imgui/imgui_demo.cpp"

DIR* _mDirectory;
struct dirent* _mDirent;
std::vector<std::string> _mDirectoryList;

std::vector<std::string> Console::output = std::vector<std::string>();

Editor::Editor(Application* pApp)
	: _pApplication(pApp)
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
	_pEditorFramebuffer = new Framebuffer(_pScreenShader);


	float aspectRatio = Window::GetAspectRatio();
	float zoomLevel = 1.0f;

	float left = -aspectRatio * zoomLevel;
	float right = aspectRatio * zoomLevel;
	float bottom = -zoomLevel;
	float top = zoomLevel;


	pImGuiSample = new Texture2D(NULL);
	pImGuiSample->Load("lenna3.jpg");
}

Editor::~Editor()
{
	delete _pEditorFramebuffer;
	delete _pScreenShader;
}

void Editor::EditorLoop(Scene* currentScene, bool& editorMode, bool& paused)
{


	EditorImGui(currentScene);
	ImGUISwitchRender(editorMode, paused);

	EditorUpdate(currentScene);
}

void Editor::EditorImGui(Scene* currentScene)
{
	//ImGui::End();
	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(true ? viewport->WorkPos : viewport->Pos);
	ImGui::SetNextWindowSize(true ? viewport->WorkSize : viewport->Size);

	ImGui::ShowDemoWindow();

	static bool changeObject = false;

	static bool fileDropdownOpen = false;

	//{
	//	if (ImGui::BeginMainMenuBar()) {
	//		if (ImGui::BeginMenu("File")) {
	//			if (ImGui::MenuItem("Save Scene"))
	//			{
	//				std::cout << "Saving Scene" << std::endl;
	//				SceneManager::GetCurrentScene()->Save();
	//			}
	//			else if (ImGui::MenuItem("Save Scene As")) {
	//
	//				fileDropdownOpen = true;
	//
	//			}
	//			if (ImGui::MenuItem("Load Scene")) {
	//				std::cout << "Load Scene" << std::endl;
	//			}
	//			ImGui::EndMenu();
	//		}
	//		ImGui::EndMainMenuBar();
	//	}
	//}

	//if (fileDropdownOpen) {
	//	if (!ImGui::IsPopupOpen("Save Scene As")) ImGui::OpenPopup("Save Scene As");
	//	if (ImGui::BeginPopupModal("Save Scene As", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
	//
	//		
	//		ImGui::Text("Not yet functional");
	//
	//		//ImGui::Text("New Name: ");
	//		//char inputBuf[256];
	//		//ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
	//		//if (ImGui::InputText("##", inputBuf, IM_ARRAYSIZE(inputBuf), input_text_flags)) {
	//		//	char* s = inputBuf;
	//		//
	//		//	char* str_end = s + strlen(s); 
	//		//	while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0;
	//		//	//Strtrim(s);
	//		//	if (s[0])
	//		//		//ExecCommand(s);
	//		//	strcpy(s, "");
	//		//	//reclaim_focus = true;
	//		//}
	//
	//		ImGui::SameLine();
	//		if (ImGui::Button("Save As")) {
	//			//std::cout << std::string(inputBuf) << std::endl;
	//			
	//			fileDropdownOpen = false;
	//			ImGui::CloseCurrentPopup();
	//		}
	//		if (ImGui::Button("Close")) {
	//
	//			fileDropdownOpen = false;
	//			ImGui::CloseCurrentPopup();
	//		}
	//
	//		ImGui::EndPopup();
	//	}
	//}
	//
	//{
	//	ImGui::Begin("Notes", 0, ImGuiWindowFlags_NoMove);
	//
	//	std::string notes;
	//	ImGui::InputTextMultiline("Notes", &notes, ImVec2(300.0f, 600.0f), 0, 0);
	//
	//	ImGui::End();
	//}

	//Tile Editor
	{
		TileMapEditor::Update(currentScene->GetTileMap());
	}


	//Inspector
	{
		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);

		//if (_pSelectedGameObject != nullptr)
		//{
		//	// text box to change name
		//	{
		//		static std::string text = _pSelectedGameObject->GetName();
		//		if (changeObject)
		//		{
		//			text = _pSelectedGameObject->GetName();
		//		}
		//		if (ImGui::InputText(" ", &text, ImGuiInputTextFlags_CharsNoBlank))
		//		{
		//			_pSelectedGameObject->SetName(text);
		//		}
		//	}
		//
		//	// select object type
		//	if (ImGui::CollapsingHeader("Object Type"))
		//	{
		//		int index = (int)_pSelectedGameObject->GetType();
		//		if (ImGui::RadioButton("Player", &index, 0))
		//		{
		//			_pSelectedGameObject->SetType(ObjectType::Player);
		//		}
		//		if (ImGui::RadioButton("Enemy", &index, 1))
		//		{
		//			_pSelectedGameObject->SetType(ObjectType::Enemy);
		//		}
		//		if (ImGui::RadioButton("NPC", &index, 2))
		//		{
		//			_pSelectedGameObject->SetType(ObjectType::NPC);
		//		}
		//		if (ImGui::RadioButton("PickUp", &index, 3))
		//		{
		//			_pSelectedGameObject->SetType(ObjectType::PickUp);
		//		}
		//		if (ImGui::RadioButton("UI", &index, 4)) {
		//			_pSelectedGameObject->SetType(ObjectType::UI);
		//		}
		//	}
		//
		//	Component* componentToDelete = nullptr;
		//
		//	// for each component in the game object
		//	for (int i = 0; i < _pSelectedGameObject->GetComponents().size(); i++)
		//	{
		//		Component* c = _pSelectedGameObject->GetComponents()[i];
		//		// draw the UI for the current component
		//		c->DrawEditorUI();
		//
		//		// check the current component is not transform
		//		if (c->GetType() != Component::Transform_Type)
		//		{
		//			// add a delete button
		//			if (ImGui::Button(("Delete component##" + std::to_string(c->GetType())).c_str()))
		//			{
		//				componentToDelete = c;
		//				break;
		//				//_pSelectedGameObject->RemoveComponent(c);
		//
		//			}
		//			// check if i is not the first
		//			if (i > 0)
		//			{
		//				if (_pSelectedGameObject->GetComponents()[i - 1]->GetType() != Component::Transform_Type)
		//				{
		//					ImGui::SameLine();
		//					// add button to move the component up
		//					if (ImGui::Button(("Up##component" + std::to_string(i)).c_str()))
		//					{
		//						_pSelectedGameObject->SwapComponents(i, i - 1);
		//					}
		//				}
		//			}
		//			// check if i is not the last
		//			if (i < _pSelectedGameObject->GetComponents().size() - 1)
		//			{
		//				ImGui::SameLine();
		//				// add button to move the component down
		//				if (ImGui::Button(("Down##component" + std::to_string(i)).c_str()))
		//				{
		//					_pSelectedGameObject->SwapComponents(i, i + 1);
		//				}
		//			}
		//		}
		//
		//		ImGui::Separator();
		//	}
		//
		//	if (componentToDelete != nullptr) {
		//		_pSelectedGameObject->RemoveComponent(componentToDelete);
		//		componentToDelete = nullptr;
		//	}
		//
		//	// add component
		//	if (ImGui::CollapsingHeader("AddComponent"))
		//	{
		//		if (ImGui::CollapsingHeader("Transform"))
		//		{
		//			if (ImGui::Button("Transform"))
		//			{
		//				if (_pSelectedGameObject->GetTransform() == nullptr)
		//				{
		//					_pSelectedGameObject->AddComponent(new Transform(_pSelectedGameObject));
		//				}
		//			}
		//		}
		//		if (ImGui::CollapsingHeader("Sound System"))
		//		{
		//			if (ImGui::Button("Sound"))
		//			{
		//
		//			}
		//		}
		//		if (ImGui::CollapsingHeader("Colliders"))
		//		{
		//			if (ImGui::Button("Box Collider"))
		//			{
		//				BoxColliderComponent* pTest = _pSelectedGameObject->GetComponent<BoxColliderComponent>();
		//				if (pTest == nullptr)
		//				{
		//					_pSelectedGameObject->AddComponent(new BoxColliderComponent(_pSelectedGameObject));
		//				}
		//			}
		//
		//		}
		//		if (ImGui::CollapsingHeader("AI"))
		//		{
		//			if (ImGui::Button("Pathfinding"))
		//			{
		//
		//			}
		//			if (ImGui::Button("GOAP"))
		//			{
		//
		//			}
		//		}
		//		if (ImGui::CollapsingHeader("Graphics"))
		//		{
		//			// texture component
		//			static std::string texPath = "lenna3.jpg";
		//			ImGui::InputText("Texture path", &texPath);
		//			if (ImGui::BeginDragDropTarget())
		//			{
		//				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_IMAGE"))
		//				{
		//					const char* path = (const char*)payload->Data;
		//					texPath = (string)path;
		//				}
		//
		//				ImGui::EndDragDropTarget();
		//			}
		//
		//
		//			if (ImGui::Button("Texture"))
		//			{
		//				Texture2D* tex = _pSelectedGameObject->GetComponent<Texture2D>();
		//				if (tex == nullptr)
		//				{
		//					_pSelectedGameObject->LoadTexture(new Texture2D((char*)texPath.c_str()));
		//				}
		//			}
		//
		//			if (ImGui::Button("Particle System"))
		//			{
		//				_pSelectedGameObject->AddComponent<ParticleSystem>(new ParticleSystem(100, glm::vec4(1.0f), new Texture2D((char*)texPath.c_str()), _pSelectedGameObject->GetTransform()));
		//			}
		//
		//			if (ImGui::Button("Camera"))
		//			{
		//				float aspectRatio = Window::GetAspectRatio();
		//				float zoomLevel = 1.0f;
		//				float left = -aspectRatio * zoomLevel;
		//				float right = aspectRatio * zoomLevel;
		//				float bottom = -zoomLevel;
		//				float top = zoomLevel;
		//				_pSelectedGameObject->AddComponent<Camera>(new Camera(left, right, bottom, top, _pSelectedGameObject->GetName(), _pSelectedGameObject));
		//
		//			}
		//		}
		//	}
		//}

		ImGui::End();
	}

	//Hierarchy
	{
		ImGui::Begin("Hierarchy", 0, ImGuiWindowFlags_NoMove);

		//if (ImGui::CollapsingHeader("Add GameObject"))
		//{
		//	static std::string name = "New GameObject";
		//
		//	ImGui::InputText("##NewGameObjectName", &name, ImGuiInputTextFlags_CharsNoBlank);
		//	static ObjectType tag = ObjectType::Player;
		//	if (ImGui::CollapsingHeader("Object type"))
		//	{
		//		static int tagIndex = 0;
		//		if (ImGui::RadioButton("Player", &tagIndex, 0))
		//		{
		//			tag = ObjectType::Player;
		//		}
		//		if (ImGui::RadioButton("Enemy", &tagIndex, 1))
		//		{
		//			tag = ObjectType::Enemy;
		//		}
		//		if (ImGui::RadioButton("NPC", &tagIndex, 2))
		//		{
		//			tag = ObjectType::NPC;
		//		}
		//		if (ImGui::RadioButton("PickUp", &tagIndex, 3))
		//		{
		//			tag = ObjectType::PickUp;
		//		}
		//	}
		//	if (ImGui::Button("Add Object"))
		//	{
		//		GameObject* obj = new GameObject(name, tag);
		//		currentScene->AddGameObject(obj);
		//		Console::Print("Object added: " + name);
		//		name = "New GameObject";
		//	}
		//}
		//
		//changeObject = false;
		//
		//// index of the selected object
		//static int index = 0;
		//// get vector of objects from the current scene
		//std::vector<GameObject*> objects = currentScene->GetGameObjects();
		//if (!objects.empty())
		//{
		//	for (int i = 0; i < objects.size(); i++)
		//	{
		//		// create a radio button for each of the objects
		//		// '##' is to add a unique ID for ImGui when labels are the same
		//		ImGui::RadioButton((objects[i]->GetName() + "##" + objects[i]->GetUID()).c_str(), &index, i); ImGui::SameLine();
		//		if (ImGui::Button(("Delete object##" + objects[i]->GetUID()).c_str()))
		//		{
		//			Console::Print("Deleted " + objects[i]->GetName());
		//			// add button next to object button that removes game object
		//			currentScene->RemoveGameObject(objects[i]);
		//			_pSelectedGameObject = nullptr;
		//			// update objects and take 1 from i (because the object at the current index was removed)
		//			objects = currentScene->GetGameObjects();
		//			i--;
		//
		//			if (i <= index)
		//			{
		//				if (index > 0)
		//					index--;
		//			}
		//		}
		//	}
		//	// set selected object to the object that the user has selected. does nothing currently.
		//	if (!objects.empty())
		//	{
		//		if (_pSelectedGameObject != objects[index])
		//		{
		//			_pSelectedGameObject = objects[index];
		//			changeObject = true;
		//		}
		//	}
		//	else
		//		_pSelectedGameObject = nullptr;
		//}
		ImGui::End();
	}

	//Console
	{
		ImGui::Begin("Console", 0, ImGuiWindowFlags_NoMove);

		//// get output from console class
		//std::vector<std::string> consoleOut = Console::GetConsoleOutput();
		//// convert vector to string array
		//std::string* out = &consoleOut[0];
		//if (out != nullptr)
		//{
		//	// output as wrapped text
		//	ImGui::TextWrapped(out->c_str());
		//
		//	// scroll to the bottom of the console window
		//	ImGui::SetScrollY(ImGui::GetScrollMaxY());
		//}

		ImGui::End();
	}

	//Content Browser
	{
		ImGui::Begin("Content Browser", 0, ImGuiWindowFlags_NoMove);

		//if (ImGui::BeginPopupContextWindow())
		//{
		//	static std::string name = " ";
		//	if (ImGui::CollapsingHeader("New Script"))
		//	{
		//		if (ImGui::InputText(" ", &name, ImGuiInputTextFlags_CharsNoBlank)) {}
		//		if (ImGui::MenuItem("Add"))
		//		{
		//			std::ofstream cppStream(_mCurrentDir + "/" + name + ".cpp");
		//			cppStream.close();
		//			std::ofstream hStream(_mCurrentDir + "/" + name + ".h");
		//			hStream.close();
		//			SearchFileDirectory();
		//		}
		//	}
		//	// makes new script with.scene files
		//	if (ImGui::CollapsingHeader("New Scene"))
		//	{
		//		if (ImGui::InputText(" ", &name, ImGuiInputTextFlags_CharsNoBlank)) {}
		//		if (ImGui::MenuItem("Add"))
		//		{
		//			SceneManager::CreateScene(name);
		//			CreateFileInContentBrowser(name, ".scene");
		//			SearchFileDirectory();
		//		}
		//
		//	}
		//
		//	ImGui::EndPopup();
		//}
		//
		////adds back button which removes last directory and updates options
		//if (ImGui::Button("Back"))
		//{
		//	_mCurrentDir = _mCurrentDir.substr(0, _mCurrentDir.find_last_of("\\/"));
		//	SearchFileDirectory();
		//}
		////displays directory next to button
		//ImGui::SameLine();
		//ImGui::Text(_mCurrentDir.c_str());
		//
		////sets up a column to display the files in a grid
		//ImGui::Columns(4, NULL);
		//ImGui::Separator();
		//int j = 0;
		////for each item in directory create new button
		//for (int i = 2; i < _mDirectoryList.size(); i++) {
		//
		//	//checks filetype and give it an icon
		//	CheckFileType(_mDirectoryList[i], j);
		//	j++;
		//	//adds padding to files
		//	ImGui::Dummy(ImVec2(0, 20.0f));
		//
		//	//goes to next column
		//	if (i > 0 || i % 4 == 2)
		//	{
		//		ImGui::NextColumn();
		//	}
		//	ImGui::Dummy(ImVec2(0, 80.0f));
		//}
		ImGui::End();
	}

}

void Editor::EditorStartRender()
{
	_pEditorFramebuffer->BindFramebuffer();
	GLCall(glEnable(GL_DEPTH_TEST));
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
	ImGui::Begin("Scene Window", 0, ImGuiWindowFlags_NoMove);

	if (ImGui::IsWindowFocused())
	{
		CameraManager::GetCamera("Editor")->OnUpdate();
	}


	ImVec2 wp = ImGui::GetCursorScreenPos();
	_windowPos = { wp.x,wp.y };
	ImGui::GetWindowDrawList()->AddImage(
		(void*)_pEditorFramebuffer->GetTexture(),
		wp,
		ImVec2(_windowPos.x + Window::GetWidth() / 2.0f, _windowPos.y + Window::GetHeight() / 2.0f),
		ImVec2(0, 1.0), ImVec2(1.0, 0));

	ImVec2 ws = ImGui::GetWindowSize();
	_windowSize = { ws.x, ws.y };
	if (_windowSize.y > Window::GetHeight() / 2.0f) _windowSize.y = Window::GetHeight() / 2.0f;

	ImGui::End();

	ConvertGameToEditorSpace();
}

void Editor::EditorEndRender()
{
	Window::SwapBuffers();
}

void Editor::ConvertGameToEditorSpace()
{
	glm::vec2 mousePos = glm::vec2(Input::GetMouseX(), Input::GetMouseY());
	glm::vec2 editorPos = glm::vec2(0.0f);

	//editorPos.x = mousePos.x - _windowPos.x;
	//editorPos.y = mousePos.y + _windowPos.y - _windowSize.y;

	//if (editorPos.x < 0) editorPos.x = 0.0f;
	//else if (editorPos.x > _windowSize.x) editorPos.x = _windowSize.x;

	//if (editorPos.y < 0) editorPos.y = 0.0f;
	//else if (editorPos.y > _windowSize.y) editorPos.y = _windowSize.y;

	//_mousePosInEditorSpace = editorPos;

	//std::cout << "Window Pos: " << _windowPos.x << " " << _windowPos.y << std::endl;
	editorPos = { _windowPos.x, _windowPos.y };

	ImVec2 edMousePos = ImGui::GetMousePos();

	glm::vec2 cPos = { edMousePos.x - editorPos.x, edMousePos.y - editorPos.y };


	cPos /= _windowSize;
	glm::vec2 clampExtents = CameraManager::GetCamera("Editor")->Size();

	cPos *= clampExtents * 2.0f;
	cPos -= clampExtents;

	//Invert Y axis
	cPos.y *= -1.0f;


	if (cPos.x < -clampExtents.x) cPos.x = -clampExtents.x;
	else if (cPos.x > clampExtents.x) cPos.x = clampExtents.x;

	if (cPos.y < -clampExtents.y) cPos.y = -clampExtents.y;
	else if (cPos.y > clampExtents.y) cPos.y = clampExtents.y;

	_mousePosInEditorSpace = cPos;
	Input::SetEditorMousePos(cPos.x, cPos.y);
}


void Editor::EditorUpdate(Scene* currentScene)
{
	currentScene->EditorUpdate();
}

void Editor::CreateFileInContentBrowser(std::string name, std::string type)
{
	std::ofstream fileStream(_mCurrentDir + "/" + name + type);
	fileStream.close();
}

//checks file type and displays file in content browser
void Editor::CheckFileType(std::string fileDirectory, int i)
{
	string fulldir = _mCurrentDir + "/" + fileDirectory;

	//if file is a script
	if (fileDirectory.find(".cpp") != std::string::npos || fileDirectory.find(".h") != std::string::npos)
	{
		ImGui::PushID(i);
		if (ImGui::ImageButton((void*)pContentTextureScript->GetID(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1)))
		{

		}

		if (ImGui::BeginDragDropSource())
		{

			ImGui::SetDragDropPayload("CONTENT_SCRIPT", fulldir.c_str(), fulldir.size(), ImGuiCond_Once);
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();

	}
	//if file is an image
	else if (fileDirectory.find(".png") != std::string::npos || fileDirectory.find(".jpg") != std::string::npos)
	{
		//ImGui::Image((void*)pContentTextureImage->GetID(), ImVec2(100, 100));
		ImGui::PushID(i);
		if (ImGui::ImageButton((void*)pContentTextureImage->GetID(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1)))
		{

		}

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("DRAGCONTENT_IMAGE", fulldir.c_str(), fulldir.size(), ImGuiCond_Once);
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();
	}
	//if file is a scene
	else if (fileDirectory.find(".scene") != std::string::npos)
	{
		//ImGui::Image((void*)pContentTextureScene->GetID(), ImVec2(100, 100));
		ImGui::PushID(i);
		if (ImGui::ImageButton((void*)pContentTextureScene->GetID(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1)))
		{
			std::stringstream ss(fileDirectory);
			std::string sub;
			getline(ss, sub, '.');

			SceneManager::SetCurrentScene(sub);
		}
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("DRAGCONTENT_SCENE", fulldir.c_str(), fulldir.size(), ImGuiCond_Once);
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();
	}
	//file is a config file
	else if (fileDirectory.find(".ini") != std::string::npos)
	{
		ImGui::Image((void*)pContentTextureConfig->GetID(), ImVec2(100, 100));
	}
	//file is a sound
	else if (fileDirectory.find(".mp3") != std::string::npos || fileDirectory.find(".wav") != std::string::npos)
	{
		//ImGui::Image((void*)pContentTextureSound->GetID(), ImVec2(100, 100));
		ImGui::PushID(i);
		if (ImGui::ImageButton((void*)pContentTextureSound->GetID(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1)))
		{

		}

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("DRAGCONTENT_SOUND", fulldir.c_str(), fulldir.size(), ImGuiCond_Once);
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();
	}
	//file is a folder
	else if (fileDirectory.find(".") == std::string::npos)
	{
		ImGui::PushID(i);
		//ImGui::Image((void*)pContentTextureFolder->GetID(), ImVec2(100, 100));
		//adds button with directory name which when pressed adds its name to directory string and updates buttons
		//if (ImGui::Button(fileDirectory.c_str()))
		if (ImGui::ImageButton((void*)pContentTextureFolder->GetID(), ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1)))
		{
			_mCurrentDir += "/" + fileDirectory;
			SearchFileDirectory();
		}
		ImGui::PopID();
	}
	//other file types
	else
	{
		ImGui::Image((void*)pContentTextureFile->GetID(), ImVec2(100, 100));
	}
	ImGui::Text(fileDirectory.c_str());


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

	GetDirectoriesOfType("png", ".");
}

//give type like jpg or mp3 and it will return all directories for this and for the current directorory it should be the folder you want to search
vector<string> Editor::GetDirectoriesOfType(string type, string currentDir)
{
	vector<string> list;
	DIR* dir = opendir(currentDir.c_str());
	if (dir)
	{
		while ((_mDirent = readdir(dir)) != NULL)
		{

			string temp = _mDirent->d_name;
			if (temp.find(type) != std::string::npos)
			{
				list.push_back(temp);
				std::cout << "Found: " << _mDirent->d_name << std::endl;
			}
			else if (temp.find(".") == std::string::npos)
			{
				vector<string> tempList = GetDirectoriesOfType(type, _mDirent->d_name);
				for (int i = 0; i < tempList.size(); i++)
				{
					list.push_back(tempList[i]);
				}
			}
		}
		closedir(dir);
	}
	return list;
}
