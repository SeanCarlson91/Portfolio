//
//  World.hpp
//  GLProject1
//
//  Created by Nevin Flanagan on 1/17/16.
// Edited by Sean Carlson
//  Copyright © 2016 PlaySmith. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
using namespace std;

#include "OpenGL.hpp"
#include "Buffer.hpp"
#include "Vertex.hpp"

#include "glm/glm.hpp"

using glm::vec3; using glm::vec4; using glm::mat4;

namespace gl {
    class Object {
    public:
        Object(string const& filename, GLuint program);
        
        void Render ( ) const;
        
        void Rotate(float angle, vec3 axis);
        void Translate(vec3 distance);

		void RotateLocal(float angle, vec3 axis);
		void TranslateLocal(vec3 distance);
        
        vec4 color;
    protected:
        gl::Vertex::Array data;
        vector<GLushort> faces;
        GLuint program;
        mat4 transform;
    };
}
