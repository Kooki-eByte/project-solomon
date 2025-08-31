#include "buffer_handler.h"


void bindVBO(VBO *vbo) {
  glGenBuffers(BUFFER_OBJECT_SIZE, &vbo->ID);
  glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
  glBufferData(GL_ARRAY_BUFFER, vbo->size, vbo->vertices, GL_STATIC_DRAW);
}

void bindEBO(EBO *ebo) {
  glGenBuffers(BUFFER_OBJECT_SIZE, &ebo->ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo->size, ebo->indices, GL_STATIC_DRAW);
}

void unbindVBO() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void unbindEBO(EBO *ebo) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void deleteBuffers(VBO *vbo, EBO *ebo) {
  glDeleteBuffers(BUFFER_OBJECT_SIZE, &vbo->ID);
  glDeleteBuffers(BUFFER_OBJECT_SIZE, &ebo->ID);
}