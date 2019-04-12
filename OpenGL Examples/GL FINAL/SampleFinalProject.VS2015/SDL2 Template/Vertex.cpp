//
//  Vertex.cpp
//  GLhomework1
//
//  Created by Nevin Flanagan on 1/31/16.
//  Copyright © 2016 PlaySmith. All rights reserved.
//

#include "Vertex.hpp"

namespace {
    template<typename block>
    class Attribute {
    public:
        Attribute(GLint i, GLint size, GLuint offset): index(i) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(block), reinterpret_cast<void*>(offset));
        }
        ~Attribute() {
            glDisableVertexAttribArray(index);
        }
    private:
        GLint index;
    };
}

namespace gl {
    template<>
    Name<Vertex::Array>::Name() {
        glGenVertexArrays(1, &name);
    }
    
    template<>
    Name<Vertex::Array>::~Name() {
        if (name) glDeleteVertexArrays(1, &name);
    }
    
    Vertex::Array::Array():
        Name()
    {}
    
    Vertex::Array& Vertex::Array::Bind(Buffer& storage) {
        Activate();
		storage.Activate(GL_ARRAY_BUFFER);
        Attribute<Vertex> pos(position, 3, 0);
        Attribute<Vertex> norm(normal, 3, sizeof(gl::Point3));
        Attribute<Vertex> surf(uv, 2, sizeof(gl::Point3) + sizeof(gl::Vector3));
        Deactivate();
        return *this;
    }
    
    void Vertex::Array::Activate() const {
        glBindVertexArray(name);
    }
    
    void Vertex::Array::Deactivate() {
        glBindVertexArray(0);
    }
}
