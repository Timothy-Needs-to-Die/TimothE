#include "pch.h"
#include "ImageUIObject.h"

ImageUIObject::ImageUIObject(Sprite* sprite, std::string name, glm::vec2 designPos, glm::vec2 designSize) 
	: UIObject(name, designPos, designSize), _pSprite(sprite)
{
	//std::shared_ptr<VBO> pVBO = VBO::Create(6 * sizeof(QuadVertex));


	_pVao = VAO::Create();
}

ImageUIObject::~ImageUIObject()
{

}

void ImageUIObject::Draw()
{
	_pVao->Bind();
	_pShader->BindShader();

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ImageUIObject::Update()
{

}
