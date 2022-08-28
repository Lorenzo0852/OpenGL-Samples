
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include "Pyramid.hpp"

namespace example
{

    const GLfloat Pyramid::coordinates[] =
    {
        -1.f, -1.f, 1.f,            // 0
         1.f, -1.f, 1.f,            // 1
         1.f,  1.f, 1.f,            // 2
        -1.f,  1.f, 1.f,            // 3

         0.f,  0.f, 0.f,            // 4
      
    };

    const GLfloat Pyramid::colors[] =
    {
        0, 0, 1,            // 0    Representa un cubo RGB
        1, 0, 1,            // 1
        1, 1, 0,            // 2
        0, 1, 1,            // 3
        1, 1, 1,            // 4
    };

    const GLubyte Pyramid::indices[] =
    {
        0, 1, 2,            // Base
        0, 2, 3,
        
        4, 0, 3,            // Edge
        4, 2, 1,
        4, 3, 2,            
        4, 1, 0,
    };

    Pyramid::Pyramid()
    {
        // Se generan índices para los VBOs del cubo:

        glGenBuffers (VBO_COUNT, vbo_ids);
        glGenVertexArrays (1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray (vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);

        glEnableVertexAttribArray (0);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un VBO los datos de color y se vinculan al VAO:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        glEnableVertexAttribArray (1);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un EBO los datos de índices:

        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_EBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindVertexArray (0);
    }

    Pyramid::~Pyramid()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }

    void Pyramid::render ()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray (vao_id);
        glDrawElements    (GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray (0);
    }

}
