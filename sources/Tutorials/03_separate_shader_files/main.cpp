#include <stdio.h>

// WINDOWS

#include "../../Libraries/SDL2-devel-2.0.12-mingw/SDL2-devel-2.0/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../Libraries/glad/glad.h"
#include "headers/buildShaders.hpp"
#include "headers/setupVertexArray.hpp"

// MACOS

// #include <SDL2/SDL.h>
// #include <OpenGL/gl3.h>

// LINUX

// #include <SDL2/SDL.h>
//#include <GL/gl.h>

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
		"SDL + OpenGL Tutorial",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		SDL_WINDOW_OPENGL
	);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext mainContext = SDL_GL_CreateContext(window);

    #ifndef __APPLE__
        // If Windows or Linux: load all OpenGL function pointers with GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            printf("Failed to initialize GLAD");
            return -1;
        }
    #endif

    printf("%s\n", glGetString(GL_VERSION));

    SDL_Event event;
    int running = 1;

	GLuint shaderProgram = glCreateProgram();
    shaderProgram = buildShaders(shaderProgram, "shaders/quad.vs", "shaders/quad.fs");
    setupVAO();

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glUseProgram(shaderProgram);

    while(running)
    {
		while(SDL_PollEvent(&event))
		{
		    if (event.type == SDL_QUIT)
		    {
			running = 0;
		    }
		}
		glClearColor(1.0f, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(shaderProgram);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
