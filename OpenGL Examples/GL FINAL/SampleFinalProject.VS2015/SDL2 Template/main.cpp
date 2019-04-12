//
//  GL1.cpp
//  GLProject1
//
//  Created by Nevin Flanagan on 1/9/16.
// Edited by Sean Carlson
//  Copyright © 2016 PlaySmith. All rights reserved.
//

#include <iostream>
#include <list>

#include "SDL.hpp"

#include "mesh.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using glm::vec3; using glm::mat4;

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_keycode.h>

using namespace std;

SDL_Window* displayWindow;
bool running = true;

list<gl::Object*> objects;

GLuint plain;

class Transform {
public:
	glm::vec3 position;
	glm::quat rotation;
};

Transform world_camera;

void setup_camera(GLuint program) {
	glUseProgram(program);
	mat4 camera = glm::lookAt(vec3{ 0.0f, 2.0f, 6.0f }, vec3{ 0.0f, 0.0f, 0.0f }, vec3{ 0.0f, 1.0f, 0.0f });
	world_camera.position = vec3{ 0.0f, 2.0f, -6.0f };
	world_camera.rotation = glm::angleAxis(glm::radians(180.0f), vec3(1.0f, 0.0f, 0.0f));
	glm::angleAxis(atan2(world_camera.position.y, world_camera.position.z), vec3(1.0f, 0.0f, 0.0f)) * world_camera.rotation;
	camera = glm::translate(glm::mat4_cast(world_camera.rotation), world_camera.position);
	glUniformMatrix4fv(glGetUniformLocation(program, "camera"), 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(glm::perspective(1.0f, 4.0f/3.0f, 1.0f, 20.0f)));
	glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));
}

void buildWorld(list<gl::Object*>& w) {
	w.push_back(new gl::Object("sphere.obj", plain));
	w.back()->Translate(vec3(0.0f, 0.0f, 0.0f));
	w.back()->color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	w.push_back(new gl::Object("sphere.obj", plain));//this is the electron
	w.back()->Translate(vec3(-5.0f, 0.0f, 0.0f));//this is the electron
	w.back()->color = vec4(1.0f, 1.0f, 1.0f, 1.0f);//this is the electron
	w.push_back(new gl::Object("sphere.obj", plain));
	w.back()->Translate(vec3(1.0f, 0.0f, 0.0f));
	w.back()->color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

void applyTime(float seconds, float lifetime) {
	//Do not erase
	auto electron = *++objects.rbegin();
	electron->Rotate(seconds, vec3{ 0.0f, 0.3f, 0.0f });//This is making it rotate on its axis, not around 0,0,0.
	electron->Translate(vec3(0.2f, 0.0f, 0.0f));
	//Do not erase
	

	GLuint camera_index = glGetUniformLocation(plain, "camera");
	mat4 camera;
	glm::ivec2 mouse, size; //Integer Vector
	SDL_GetMouseState(&mouse.x, &mouse.y); //Pointers to mouse
	SDL_GetWindowSize(displayWindow, &size.x, &size.y); //Pointers to window size

	float mouse_x = static_cast<float>(mouse.x) / size.x; // 0 - 1
	mouse_x = mouse_x * 2.0f - 1.0f;
	world_camera.rotation = glm::angleAxis(mouse_x * seconds, vec3(0.0f, 1.0f, 0.0f)) * world_camera.rotation; //Negate mouse_y * seconds for opposite movement

//Keyboard controls for the camera
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	if (keys[SDL_GetScancodeFromName("A")] || keys[SDL_GetScancodeFromKey(SDLK_LEFT)])
	{
		world_camera.position += vec3{ vec4(seconds, 0.0f, 0.0f, 1.0f) * glm::mat4_cast(world_camera.rotation) };
	}
	if (keys[SDL_GetScancodeFromName("D")] || keys[SDL_GetScancodeFromKey(SDLK_RIGHT)])
	{
		world_camera.position += vec3{ vec4(-seconds, 0.0f, 0.0f, 1.0f) * glm::mat4_cast(world_camera.rotation) };
	}
	if (keys[SDL_GetScancodeFromName("W")])
	{
		world_camera.position += vec3{ vec4(seconds, 0.0f, 0.5f, 0.0f) * glm::mat4_cast(world_camera.rotation) };
	}
	if (keys[SDL_GetScancodeFromName("S")])
	{
		world_camera.position -= vec3{ vec4(-seconds, 0.0f, 0.5f, 0.0f) * glm::mat4_cast(world_camera.rotation) };
	}
	camera = glm::translate(glm::mat4_cast(world_camera.rotation), world_camera.position);
	glUniformMatrix4fv(camera_index, 1, GL_FALSE, glm::value_ptr(camera));

	
}

void init_display(unsigned int width, unsigned int height) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    displayWindow = SDL_CreateWindow("", 20, 20, width, height, SDL_WINDOW_OPENGL);
    if (!displayWindow) throw sdl::Exception( "Failed to create window" );
    if (!SDL_GL_CreateContext(displayWindow)) throw sdl::Exception("Failed to create context");
    
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError();
#endif
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    
    /* Setup our viewport. */
    glViewport( 0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height) );
}

void init_rendering() {
    GLuint v = glCreateShader(GL_VERTEX_SHADER), f = glCreateShader(GL_FRAGMENT_SHADER);
    GLint length = static_cast<GLint>(shader::vFlat.length());
    char const* text = shader::vFlat.c_str();
    glShaderSource(v, 1, &text, &length);
    glCompileShader(v);
	GLint status = GL_FALSE;
	glGetShaderiv(v, GL_COMPILE_STATUS, &status);
    length = static_cast<GLint>(shader::fFlat.length());
    text = shader::fFlat.c_str();
    glShaderSource(f, 1, &text, &length);
    glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &status);
    
    plain = glCreateProgram();
    glAttachShader(plain, v);
    glAttachShader(plain, f);
    glBindAttribLocation(plain, gl::Vertex::Array::position, "position");
    glBindAttribLocation(plain, gl::Vertex::Array::normal, "normal");
    glBindAttribLocation(plain, gl::Vertex::Array::uv, "uv");
    glLinkProgram(plain);
	glGetProgramiv(plain, GL_LINK_STATUS, &status);
    glDetachShader(plain, v);
    glDetachShader(plain, f);

	setup_camera(plain);
    
    buildWorld(objects);
}

void render( ) {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    for (gl::Object* object: objects) {
        object->Render();
    }
    
    SDL_GL_SwapWindow(displayWindow);
}

void processKey(SDL_Keysym const& keysym) {
    switch( keysym.sym ) {
        case SDLK_ESCAPE:
            running = false;
            break;
        default:
            break;
    }
}

void events() {
    /* Our SDL event placeholder. */
    SDL_Event event;
    
    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {
        
        switch( event.type ) {
            case SDL_KEYDOWN:
                /* Handle key presses. */
                processKey( event.key.keysym );
                break;
            case SDL_QUIT:
                /* Handle quit requests (like Ctrl-c). */
                running = false;
                break;
        }
    }
}

int run() {
    Uint32 lastCall = 0;
    while (running) {
        events();
        Uint32 time = SDL_GetTicks();
        applyTime(static_cast<float>(time - lastCall) / 1000.0f, static_cast<float>(time) / 1000.0f);
        lastCall = time;
        render();
    }
    return 0;
}

int main(int argc, char* argv[]) {
    static_cast<void>(argc), static_cast<void>(argv);
    
    try {
        sdl::Library SDL2(SDL_INIT_VIDEO);
        init_display(1920, 1080);
        init_rendering();
        return run();
    } catch (std::exception& e) {
        cerr << e.what() <<endl;
        return 1;
    }
}
