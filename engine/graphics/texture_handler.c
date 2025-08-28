#include "texture_handler.h"

// Assuming you are setting the bind size and texture type
// TODO: EXTRA OVERHEAD FOR HANDLING JPEG/JPG IMAGES DUE TO NUM OF COLOR CHANNELS
// AND FIX ROWALIGNMENT ISSUES THAT ARE COMMON WHEN LOADING JPGS
void getTexture(const char *path_to_image, My_Texture_t *texture) {
  stbi_set_flip_vertically_on_load(1);
  u8 *image_in_bytes =
      stbi_load(path_to_image, &texture->width, &texture->height,
                &texture->num_color_channel, 0);

  glGenTextures(texture->bind_size, &texture->ID);

  glActiveTexture(GL_TEXTURE0);

  glBindTexture(texture->type, texture->ID);

  glTexParameteri(texture->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(texture->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(texture->type, GL_AUTO_GENERATE_MIPMAP, GL_FALSE);

  glTexParameteri(texture->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(texture->type, GL_TEXTURE_WRAP_T, GL_REPEAT);

  if (texture->type == GL_TEXTURE_2D) {
    glTexImage2D(texture->type, 0, GL_RGBA, texture->width, texture->height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image_in_bytes);
  }

  stbi_image_free(image_in_bytes);
  unbindTexture(texture);
}

void setTextureUnit(Envy_Shader *shader, const char *uniform, GLuint unit) {
  GLuint texUnit = envy_GetShaderUniform(shader, uniform);
  envy_UseShader(shader);
  glUniform1i(texUnit, unit);
}

void setActiveTexture(GLenum texture_unit) { glActiveTexture(texture_unit); }

// Bind texture
void bindTexture(My_Texture_t *texture) {
  glBindTexture(texture->type, texture->ID);
}

// Unbind texture by texture->type (i.e GL_TEXTURE_2D)
void unbindTexture(My_Texture_t *texture) { glBindTexture(texture->type, 0); }

// Delete with texture->bind_size and ->ID
void deleteTexture(My_Texture_t *texture) {
  glDeleteTextures(texture->bind_size, &texture->ID);
}
