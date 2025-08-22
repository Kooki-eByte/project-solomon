# Project Solomon

## Project Structure

- Goal is to create a clean, modular, and scalable project structure.
- Makefile-only build system.
- Capable of pulling engine code and making game separately to ensure separation of concern and
  reusability with other ideas.

Project_Solomon/
├── Makefile
├── README.md
├── LICENSE
├── bin/ # Output binaries
├── build/ # Temporary build files
├── deps/ # External dependencies (GLFW, GLAD, etc.)
│ ├── glad/
│ └── glfw/
├── engine/ # Core engine code (reusable, abstract)
│ ├── core/ # Init, memory, time, logging, etc.
│ ├── graphics/ # OpenGL rendering abstraction
│ ├── input/ # Input handling (GLFW-specific)
│ ├── math/ # Math types (vec3, mat4, etc.)
│ ├── physics/ # Optional physics systems
│ ├── ecs/ # Entity-Component-System
│ ├── scene/ # Scene graph, object loading
│ └── engine.h
├── game/ # Game-specific logic
│ ├── gameplay/ # Player movement, camera control, etc.
│ ├── assets/ # Models, textures, shaders
│ ├── levels/ # Map/level data
│ ├── main.c # Game entry point
│ └── game.h
└── include/ # Shared/public headers
