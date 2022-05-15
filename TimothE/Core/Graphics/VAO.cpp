#include "../../pch.h"
#include "VAO.h"
#include "Base.h"
#include "OpenGLError.h"


std::shared_ptr<VAO> VAO::Create()
{
    return CreateRef<VAO>();
}

VAO::VAO()
{
    GLCall(glCreateVertexArrays(1, &_rendererID));
}

VAO::~VAO()
{
    GLCall(glDeleteVertexArrays(1, &_rendererID));
}

void VAO::Bind() const
{
    GLCall(glBindVertexArray(_rendererID));
}

void VAO::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VAO::AddVertexBuffer(const std::shared_ptr<VBO>& vertexBuffer)
{
    GLCall(glBindVertexArray(_rendererID));
    vertexBuffer->Bind();

    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout) {
        switch (element.type) {
        case ShaderDataTypes::Float:
        case ShaderDataTypes::Float2:
        case ShaderDataTypes::Float3:
        case ShaderDataTypes::Float4:
            {
            GLCall(glEnableVertexAttribArray(_vertexBufferIndex));
            GLCall(glVertexAttribPointer(_vertexBufferIndex,
                element.GetComponentCount(),
                GL_FLOAT,
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.offset));
            _vertexBufferIndex++;
            break;
            }
        case ShaderDataTypes::Int:
        case ShaderDataTypes::Int2:
        case ShaderDataTypes::Int3:
        case ShaderDataTypes::Int4:
        {
            GLCall(glEnableVertexAttribArray(_vertexBufferIndex));
            GLCall(glVertexAttribIPointer(_vertexBufferIndex,
                element.GetComponentCount(),
                GL_INT,
                layout.GetStride(),
                (const void*)element.offset));
            _vertexBufferIndex++;
            break;
        }
        case ShaderDataTypes::Bool:
        {
            GLCall(glEnableVertexAttribArray(_vertexBufferIndex));
            GLCall(glVertexAttribIPointer(_vertexBufferIndex,
                element.GetComponentCount(),
                GL_BOOL,
                layout.GetStride(),
                (const void*)element.offset));
            _vertexBufferIndex++;
            break;
        }
        case ShaderDataTypes::Mat3:
        case ShaderDataTypes::Mat4:
        {
            unsigned int count = element.GetComponentCount();
            for (unsigned int i = 0; i < count; i++) {
                GLCall(glEnableVertexAttribArray(_vertexBufferIndex));
                GLCall(glVertexAttribPointer(_vertexBufferIndex,
                    count,
                    element.normalized ? GL_TRUE : GL_FALSE,
                    GL_FLOAT,
                    layout.GetStride(),
                    (const void*)(element.offset + sizeof(float) * count * i)));
                GLCall(glVertexAttribDivisor(_vertexBufferIndex, 1));
                _vertexBufferIndex++;
                break;
            }
        }
        default:
            std::cout << "[Error: VAO::AddVertexBuffer]: Shader Data Type not defined" << std::endl;
        }

    }
    _vertexBuffers.push_back(vertexBuffer);
}

void VAO::SetIndexBuffer(const std::shared_ptr<IBO>& indexBuffer)
{
    GLCall(glBindVertexArray(_rendererID));

    indexBuffer->Bind();
    _indexBuffer = indexBuffer;

}