#include <stdio.h>

// WINDOWS

#include "../../Libraries/SDL2-devel-2.0.12-mingw/SDL2-devel-2.0/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2/SDL.h"
#include "../../Libraries/glad/glad.h"
#include "headers/buildShaders.hpp"
#include "headers/setupVertexArray.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../Libraries/stb/stb_image.h"

// MACOS

// #include <SDL2/SDL.h>
// #include <OpenGL/gl3.h>

// LINUX

// #include <SDL2/SDL.h>
//#include <GL/gl.h>

GLuint getTextureHandle(char* path);

float currentTime, deltaTime, lastFrame;

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

    // do I need something to turn vsync on on macOS?
    // glfwSwapInterval(1); // To my knowledge, this turns on vsync on macOS

    printf("%s\n", glGetString(GL_VERSION));

    SDL_Event event;
    int running = 1;

	GLuint shaderProgram = glCreateProgram();
    shaderProgram = buildShaders(shaderProgram, "shaders/quad.vs", "shaders/quad.fs");
    setupVAO();

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glUseProgram(shaderProgram);

    GLuint channel_logo = getTextureHandle("assets/logo.png");
    glBindTexture(GL_TEXTURE_2D, channel_logo);

    // for alpha (opacity)
    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    while(running)
    {


        SDL_ShowCursor(SDL_DISABLE);

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        // currentTime = NOW;
        // deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );

        // // need how to get time in sdl
        currentTime = SDL_GetTicks() / 1000.0;
        // printf("currentTime: %f\n", currentTime);
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

		while(SDL_PollEvent(&event))
		{
		    if (event.type == SDL_QUIT)
		    {
			running = 0;
		    }
		}
		glClearColor(1.0f, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
        glUniform1f(glGetUniformLocation(shaderProgram, "transX"), cos(currentTime));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SDL_GL_SwapWindow(window);
    }

    glDeleteProgram(shaderProgram);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}


GLuint getTextureHandle(char* path)
{
    GLuint textureHandle;
    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
    
    // Set our texture parameters
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // Set texture wrapping to GL_REPEAT
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);   // Set texture wrapping to GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load, create texture and generate mipmaps; 
    //
    // Note: image loaders usually think of top left as being (0,0) while in OpenGL I would rather think of bottom left as being (0,0) as OpenGL does that already, so that is why I set the stb library to flip image vertically. There are other workarounds like flipping our texCoords upside down or flipping things in the vs or fs, but that would mean that we are choosing in OpenGL to work with two different coordinate systems, one upside-down from the other. I would rather choose not to do that and simply flip images when loading in. It is a matter of personal choice.
    // 

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *image = stbi_load(path, &width, &height, &nrChannels, 0);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
   
    // free memory 
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0); // unbind so that we can deal with other textures

    return textureHandle;
}
