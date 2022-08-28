
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2014.05

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <glad/glad.h>
    #include "SinPlane.hpp"
    #include <string>

    namespace example
    {

        class View
        {
        private:

            static const std::string   vertex_shader_code;
            static const std::string fragment_shader_code;

            GLint  model_view_matrix_id;
            GLint  projection_matrix_id;
            GLint  time_id;
			GLint  radius_id;

            GLfloat sine_modifier;

            SinPlane plane;

            float position;
            float  angle;
            float time;

        public:

            View(int width, int height);

            void   update ();
            void   render ();
            void   resize (int width, int height);

        private:

            GLuint compile_shaders        ();
            void   show_compilation_error (GLuint  shader_id);
            void   show_linkage_error     (GLuint program_id);

        };

    }

#endif
