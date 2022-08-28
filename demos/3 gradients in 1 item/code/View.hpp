
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <string>
    #include <memory>
    #include "Cube.hpp"

    namespace example
    {

        class View
        {
        private:

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

            GLint  model_view_matrix_id;
            GLint  projection_matrix_id;

            Cube   cube;                    // Se creará un cubo sin textura pero con coordenadas de textura

            float  angle;
            float  depth;
            float  speed;

        public:

            View(int width, int height);

            void   update ();
            void   render ();
            void   resize (int  width, int height);

        private:

            GLuint compile_shaders        ();
            void   show_compilation_error (GLuint  shader_id);
            void   show_linkage_error     (GLuint program_id);

        };

    }

#endif
