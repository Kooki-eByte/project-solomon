#include "envy_shader.h"

// Reads files based on the path given and output length to help realloc to return string
static char *read_glsl_file(const char *path, size_t *output_len) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "ERROR: Failed to open file -> [%s]\n", path);
    exit(1);
  }

  char *shader_string = NULL;

  b32 c;
  size_t ind = 0;

  while ((c = fgetc(file)) != EOF) {
    // Resize string size if necessary
    if (ind >= *output_len) {
      *output_len += 1000; // increase size
      shader_string = realloc(shader_string, *output_len);
      if (shader_string == NULL) {
        fprintf(stderr, "ERROR: Memory Allocation failed at file [%s] - function [%s] => output len is %zu\n", __FILE__, "getFileContents", *output_len);
        exit(2);
      }
    }

    shader_string[ind++] = c; // Store character
  }

  shader_string[ind] = '\0'; // Null-terminate the string
  fclose(file);
  return shader_string;
}

// Handle creating and compiling machine code for the shaders
static GLuint compileShader(GLenum type, const char *shader_src, const char *label) {
  u32 s = glCreateShader(type);
  if (!s) {
    fprintf(stderr, "Shader: glCreateSahder failed [%s]\n", label);
    return 0;
  }

  glShaderSource(s, 1, &shader_src, NULL);
  glCompileShader(s);

  return s;
}

// Linking shaders to programs and calling the linkProgram from openGL
static bool linkProgram(GLuint prog, const char *label) {
  glLinkProgram(prog);
  GLint ok_status = 0;
  glGetProgramiv(prog, GL_LINK_STATUS, &ok_status);
  if (!ok_status) {
    fprintf(stderr, "shader: link failed [%s]\n", label);
    return false;
  }
  return true;
}

bool envy_CreateShadersFromFiles(Envy_Shader *shader, const char *vertex_path, const char *fragment_path) {
  // initial string length for vertex and fragment shaders
  size_t vert_len = 0, frag_len = 0;

  char *vertex_src = read_glsl_file(vertex_path, &vert_len);
  if (!vertex_src) return false;
  char *frag_src = read_glsl_file(fragment_path, &frag_len);
  if (!frag_src) {
    free(vertex_src);
    return false;
  }

  bool ok_status = envy_CreateShaderFromSources(shader, vertex_src, frag_src);

  free(vertex_src);
  free(frag_src);
  return ok_status;
}

bool envy_CreateShaderFromSources(Envy_Shader *shader, const char *vertex_src, const char *fragment_src) {
  if (!shader) return false;
  // Set  program to default
  shader->program = 0;

  b32 vert_shader = compileShader(GL_VERTEX_SHADER, vertex_src, "vertex");
  if (!vert_shader) {
    fprintf(stderr, "Error: Vertex shaders fail to compile\n"); 
    return false;
  }

  b32 frag_shader = compileShader(GL_FRAGMENT_SHADER, fragment_src, "fragment");
  if (!frag_shader) {
    glDeleteShader(vert_shader);
    fprintf(stderr, "Error: Frag shaders fail to compile\n");
    return false;
  }

  b32 prog = glCreateProgram();
  if (!prog) {
    fprintf(stderr, "Shader: glCreateProgram failed\n");
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    return false;
  }

  glAttachShader(prog, vert_shader);
  glAttachShader(prog, frag_shader);

  bool ok_status = linkProgram(prog, "program");

  glDetachShader(prog, vert_shader);
  glDetachShader(prog, frag_shader);
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  if (!ok_status) {
    glDeleteProgram(prog);
    return false;
  }

  shader->program = prog;
  return true;
}

void envy_UseShader(const Envy_Shader *shader) {
  if (shader && shader->program) {
    glUseProgram(shader->program);
  }
}

void envy_DestroyShader(Envy_Shader *shader) {
  if (shader && shader->program) {
    glDeleteProgram(shader->program);
    shader->program = 0;
  }
}

GLuint envy_GetShaderUniform(const Envy_Shader *shader, const char *name) {
  if (!shader || !shader->program || !name) return -1;

  return glGetUniformLocation(shader->program, name);
}