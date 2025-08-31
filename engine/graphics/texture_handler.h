#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H

#include "../../deps/stb/stb_image.h"
#include "../../deps/glad/glad.h"
#include "../../defines.h"
#include "envy/envy_shader.h"


// Naming is for playground purposes only !
typedef struct My_Texture_t {
  GLuint ID;
  GLsizei bind_size;
  GLenum type;
  b32 width;
  b32 height;
  b32 num_color_channel;
} My_Texture_t;

void getTexture(const char *path_to_image, My_Texture_t *texture);

void setTextureUnit(Envy_Shader *shader, const char *uniform, GLuint unit);

void setActiveTexture(GLenum texture_unit);

// Bind texture
void bindTexture(My_Texture_t *texture);

// Unbind texture by texture->type (i.e GL_TEXTURE_2D)
void unbindTexture(My_Texture_t *texture);

// Delete with texture->bind_size and ->ID
void deleteTexture(My_Texture_t *texture);

#endif