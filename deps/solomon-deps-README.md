# Dependencies for Project Solomon

## Dependency list

- glad/KHR
  - GLAD is an open source library that manages retieving OpenGL function from the driver and
    onto pointer functions to be used by developers in a more accessible API format.
  - To get the header files to plug into here (since I refuse to use CMake sorry, not sorry) here is the link.
    - http://glad.dav1d.de/

- SDL3
  - Simple DirectMedia Layer is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL/Direct3D/Metal/Vulkan. It is used by video playback software, emulators, and popular games including Valve's award winning catalog and many Humble Bundle games.
  - Link: https://github.com/libsdl-org/SDL/releases

- stb
  - Mainly using stb_image to handle reading images such as PNGs to be used for textures in the pipeline.
  - From link below, just download header file. There is no need to grab the entire stb lib for now.
    - Link: https://github.com/nothings/stb/blob/master/stb_image.h

- cglm
  - A C wrapper for glm library used for common graphics maths such a Vectors and Matrices for example.
  - Best bet is to clone the repo **linked below** and just move cglm file living inside the include directory
    into the deps directory here.
    - Link: https://github.com/recp/cglmhttps://github.com/recp/cglm
