#ifndef SOLOMON_INPUT_H
#define SOLOMON_INPUT_H
#include <stdbool.h>

#include "../../defines.h"
#include "../../deps/glad/glad.h"

// NOTE:(Cristian) Typically will be handling window, input devices, sounds,
// etc... will only be input for now since openGL is being used for the game
// engine.
#include "../engine.h"

#ifdef ENGINE_DEBUG
#include "../debug/cimgui_backend.h"
#endif // ENGINE_DEBUG

extern void process_input(SolomonGameCallbacks *cb, GameEngineConfigs *ec);

#endif // SOLOMON_INPUT_H
