#ifndef ENVY_SHADER_H
#define ENVY_SHADER_H

#include "../../deps/glad/glad.h"
#include "../../defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Envy_Shader {
  GLuint program;
} Envy_Shader;

// Return true on success, On failure prints errors to stderr and leaves `shader->program == 0`
bool envy_CreateShadersFromFiles(Envy_Shader *shader, const char *vertex_path, const char *fragment_path);

// Build from in-memory sources (handy for embedded shaders)
bool envy_CreateShaderFromSources(Envy_Shader *shader, const char *vertex_src, const char *fragment_src);

// Make this program current
void envy_UseShader(const Envy_Shader *shader);

// Free GL Resources (safe to call multiple times)
void envy_DestroyShader(Envy_Shader *shader);

GLuint envy_GetShaderUniform(const Envy_Shader *shader, const char *name);
#endif