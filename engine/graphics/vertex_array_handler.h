#ifndef VERTEX_ARRAY_HANDLER_H
#define VERTEX_ARRAY_HANDLER_H

#include "../../deps/glad/glad.h"
#include "../../defines.h"
// needed to access VBO
#include "buffer_handler.h"

typedef struct VAO {
  GLuint ID;
} VAO;

// Handle generating a VAO object
void genVAO(VAO *vao);

// param: layout - This is the location we set in the vertex GLSL 
void linkAttrib(GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);

void bindVAO(VAO *vao);

void unbindVAO();

void deleteVAO(VAO *vao);

#endif