#include "vertex_array_handler.h"

void linkAttrib(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
  // Ensure VBO is binded first
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  // Unbind VBO here
}

void genVAO(VAO *vao) {
  glGenVertexArrays(1, &vao->ID);
}

void bindVAO(VAO *vao) {
  glBindVertexArray(vao->ID);
}

void unbindVAO() {
  glBindVertexArray(0);
}

void deleteVAO(VAO *vao) {
  glDeleteVertexArrays(1, &vao->ID);
}