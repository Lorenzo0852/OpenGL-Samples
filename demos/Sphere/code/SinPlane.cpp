
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#include "SinPlane.hpp"

using glm::vec3;
using glm::vec2;

namespace example
{
    SinPlane::SinPlane()
    {
		//2pi makes a full 360 degree circunference
		const float circunference = 3.1415926535 * 2;

		const size_t long_steps = 30;
		const size_t lat_steps = 30;
		const float radius = 1;


		const float long_increments = circunference / long_steps;
		const float lat_increments = circunference / lat_steps;

        size_t reserve = long_steps * lat_steps;

        vertex_coordinates.reserve(reserve);

		//longitude = width variation
		//lat		= height variation

        for (GLfloat current_latitude = 0; current_latitude < circunference; current_latitude += lat_increments)
        {
            for (GLfloat current_longitude = 0; current_longitude < circunference; current_longitude += long_increments)
            {
				vertex_coordinates.push_back(current_latitude);
				vertex_coordinates.push_back(current_longitude);
            }

        }


        // Se generan índices para los VBOs del cubo:

        glGenBuffers (VBO_COUNT, vbo_ids);
        glGenVertexArrays (1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:

        glBindVertexArray (vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:

        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, vertex_coordinates.size() * sizeof(GLfloat), vertex_coordinates.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray (0);
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        //// Se suben a un VBO los datos de color y se vinculan al VAO:
        //glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        //glBufferData (GL_ARRAY_BUFFER, vertex_colors.size() * sizeof(GLfloat), vertex_colors.data(), GL_STATIC_DRAW);


        //glEnableVertexAttribArray (1);
        //glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un EBO los datos de índices:

        glBindVertexArray (0);
    }

    SinPlane::~SinPlane()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }

    void SinPlane::render ()
    {
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:

        glBindVertexArray (vao_id);
        //glDrawElements    (GL_TRIANGLES, vertex_indices.size(), GL_UNSIGNED_BYTE, 0);
        // 
        //DrawArrays solo necesita: MODO(GL_TRIANGLES), PRIMERO(0), ÚLTIMO O COUNT DEL ARRAY (que es lo mismo): number_of_cols * etc etc
        // Básicamente es: dibújame desde el índice del array 0 al índice del array x (longitud).
        glDrawArrays(GL_POINTS, 0, long_steps * lat_steps);

        //Se deja libre el binding al VAO, que contiene el array con los vertices.
        glBindVertexArray (0);
    }

}
