#include "Inspector.h"

void Inspector::EditorUI()
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
			if (ImGui::RadioButton("UI", &index, 4)) {
				_pSelectedGameObject->SetType(ObjectType::UI);
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
						if (ImGui::Button(("Up##component" + std::to_string(i)).c_str()))
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
					if (ImGui::Button(("Down##component" + std::to_string(i)).c_str()))
					{
						_pSelectedGameObject->SwapComponents(i, i + 1);
					}
				}
			}

			ImGui::Separator();
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
						_pSelectedGameObject->LoadTexture(new Texture2D((char*)texPath.c_str()));
					}
				}

				if (ImGui::Button("Particle System"))
				{
					_pSelectedGameObject->AddComponent<ParticleSystem>(new ParticleSystem(100, glm::vec4(1.0f), new Texture2D((char*)texPath.c_str()), _pSelectedGameObject->GetTransform()));
				}

				if (ImGui::Button("Camera"))
				{
					float aspectRatio = Window::GetAspectRatio();
					float zoomLevel = 1.0f;
					float left = -aspectRatio * zoomLevel;
					float right = aspectRatio * zoomLevel;
					float bottom = -zoomLevel;
					float top = zoomLevel;
					_pSelectedGameObject->AddComponent<Camera>(new Camera(left, right, bottom, top, _pSelectedGameObject->GetName(), _pSelectedGameObject));

				}
			}
		}
	}

	ImGui::End();
}
