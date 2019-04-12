//
//  OpenGL.h
//  GLhomework1
//
//  Created by Nevin Flanagan on 1/29/16.
//  Copyright © 2016 PlaySmith. All rights reserved.
//

#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <string>
#include <stdexcept>

namespace gl {
    template <class T>
    class Name {
    public:
        operator bool() { return name != 0; }
        Name& operator= (Name && source) { name = source.name; source.name = 0; return *this; }
    protected:
        Name();
        Name(Name && source) { name = source.name; source.name = 0; }
        Name(GLuint existing): name(existing) {}
        ~Name();
        
        GLuint name;
    };

    struct Point3 {
        GLfloat x, y, z;
        
        Point3(GLfloat _x, GLfloat _y, GLfloat _z = 0.0f): x(_x), y(_y), z(_z) {}
        Point3( ): x(0.0f), y(0.0f), z(0.0f) {}
    };

    struct Vector2 {
        GLfloat x, y;
        
        Vector2(GLfloat _x, GLfloat _y): x(_x), y(_y) {}
        Vector2( ): x(0.0f), y(0.0f) {}
    };

    struct Vector3: public Vector2 {
        GLfloat z;
        
        Vector3(GLfloat _x, GLfloat _y, GLfloat _z = 0.0f): Vector2(_x, _y), z(_z) {}
        Vector3( ): Vector2(0.0f, 0.0f), z(0.0f) {}
    };
}

namespace shader {
    extern std::string vFlat;
    extern std::string fFlat;
}

#define TRAPGL(a) { auto e = glGetError(); if (e) throw std::runtime_error(std::string(a) + std::to_string(e)); }
