#ifndef BUFFER_HANDLER_H
#define BUFFER_HANDLER_H

#include "../../deps/glad/glad.h"

#define BUFFER_OBJECT_SIZE 1

typedef struct VBO {
  GLuint ID;
  GLsizeiptr size;
  GLfloat *vertices; 
} VBO;

typedef struct EBO {
  GLuint ID;
  GLsizeiptr size;
  GLuint *indices; 
} EBO;

// handle binding
void bindVBO(VBO *vbo);
void bindEBO(EBO *ebo);

// handle unbinding
void unbindVBO();
void unbindEBO();

// handle deleting
void deleteBuffers(VBO *vbo, EBO *ebo);

#endif