#include "Sizeable.h"

namespace fhl
{

Sizeable::Sizeable(glm::vec2 _size)
   : m_vao(new Vao()),
     m_size(_size)
{
   updatePosArray();

   Buffer* posBuffer = new Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
   m_vao->addBuffer("posBuffer", posBuffer);

   m_vao->bind();

   posBuffer->bind();
   posBuffer->setData(sizeof(m_posArray), m_posArray);

   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   m_vao->unbind();
}

void Sizeable::setSize(glm::vec2 _size)
{
   m_size = _size;

   updatePosArray();
   uploadPosArray();
}

void Sizeable::updatePosArray()
{
   m_posArray[0] = { 0.f, 0.f };
   m_posArray[1] = { m_size.x, 0.f };
   m_posArray[2] = m_size;
   m_posArray[3] = { 0.f, m_size.y };
}

void Sizeable::uploadPosArray()
{
   Buffer* posBuffer = m_vao->getBuffer("posBuffer");
   posBuffer->bind();
   posBuffer->updateData(0, sizeof(m_posArray), m_posArray);
   posBuffer->unbind();
}

} // ns