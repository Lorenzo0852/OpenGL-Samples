
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include "Cone.hpp"

namespace example
{

    const GLfloat Cone::coordinates[] =
    {
         0.f, 0.f,    1.f,            // 0
       0.65f, 0.f,  0.65f,            // 1
         1.f, 0.f,    0.f,            // 2
       0.65f, 0.f, -0.65f,            // 3
         0.f, 0.f,   -1.f,            // 4
      -0.65f, 0.f, -0.65f,            // 5
        -1.f, 0.f,    0.f,            // 6
      -0.65f, 0.f,  0.65f,            // 7

         0.f, 2.f,    0.f,            // 8
    };

    const GLfloat Cone::colors[] =
    {
        0, 0, 1,            // 0    Representa un cubo RGB
        1, 0, 1,            // 1
        0, 1, 1,            // 2
        0, 0, 0,            // 3
        1, 0, 0,            // 4
        1, 1, 0,            // 5
        0, 1, 0,            // 6
        0, 0, 1,            // 7

        1, 1, 1,            // 8 

    };

    const GLubyte Cone::indices[] =
    {
        1,   0,   2,  // Circle Base
        2,   0,   3,           
        3,   0,   4,           
        4,   0,   5,           
        5,   0,   6,           
        6,   0,   7,
        

        8,   0,  1,   // Edge
        8,   1,  2,   
        8,   2,  3,   
        8,   3,  4,   
        8,   4,  5,   
        8,   5,  6,
        8,   6,  7,
        8,   7,  0,
        
    };

    Cone::Cone()
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

    Cone::~Cone()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }

    void Cone::render ()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray (vao_id);
        glDrawElements    (GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);
        glBindVertexArray (0);
    }

}
