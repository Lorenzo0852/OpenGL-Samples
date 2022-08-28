
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "View.hpp"
#include <iostream>
#include <cassert>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace example
{

    using namespace std;

    const string View::vertex_shader_code =

        "#version 330\n"
        ""
        "uniform mat4 model_view_matrix;"
        "uniform mat4 projection_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec2 vertex_texture_uv;"
        ""
        "out vec2 texture_uv;"
        ""
        "void main()"
        "{"
        "   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   texture_uv  = vertex_texture_uv;"
        "}";

    const string View::fragment_shader_code =

        "#version 330\n"
        ""
        "in  vec2 texture_uv;"
        "out vec4 fragment_color;"   
        ""                            
        "void main()" 
        "{"
		"    fragment_color = texture_uv.t < 0.5 ? mix(vec4(1,0,0,1), vec4(0,1,0,1), texture_uv.t / 0.5) : mix(vec4(0,1,0,1), vec4(0,0,1,1), (texture_uv.t) - 0.5); "
        "}";

    View::View(int width, int height)
    :
        angle( 0.0f),
        depth(-5.0f),
        speed(-0.1f)
    {
        // Se compilan y se activan los shaders:

        GLuint program_id = compile_shaders ();

        glUseProgram (program_id);

        model_view_matrix_id = glGetUniformLocation (program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation (program_id, "projection_matrix");

        // Se establece la configuración básica:

        glEnable     (GL_CULL_FACE);
        glClearColor (0.f, 0.f, 0.f, 1.f);

        resize (width, height);
    }

    void View::update ()
    {
        angle += 0.01f;
        depth += speed;

        if (depth < -22.f || depth > -3.f)
        {
            speed = -speed;
        }
    }

    void View::render ()
    {
        glClear (GL_COLOR_BUFFER_BIT);

        // Se rota el cubo y se empuja hacia el fondo:

        glm::mat4 model_view_matrix(1);

        model_view_matrix = glm::translate (model_view_matrix, glm::vec3(0.f, 0.f, depth));
        model_view_matrix = glm::rotate    (model_view_matrix, angle, glm::vec3(1.f, 2.f, 1.f));

        glUniformMatrix4fv (model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

        // Se renderiza el cubo:

        cube.render ();
    }

    void View::resize (int width, int height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 0.1f, 50.f);

        glUniformMatrix4fv (projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glViewport (0, 0, width, height);
    }

    GLuint View::compile_shaders ()
    {
        GLint succeeded = GL_FALSE;

        // Se crean objetos para los shaders:

        GLuint   vertex_shader_id = glCreateShader (GL_VERTEX_SHADER  );
        GLuint fragment_shader_id = glCreateShader (GL_FRAGMENT_SHADER);

        // Se carga el código de los shaders:

        const char *   vertex_shaders_code[] = {   vertex_shader_code.c_str () };
        const char * fragment_shaders_code[] = { fragment_shader_code.c_str () };
        const GLint    vertex_shaders_size[] = { GLint(  vertex_shader_code.size ()) };
        const GLint  fragment_shaders_size[] = { GLint(fragment_shader_code.size ()) };

        glShaderSource  (  vertex_shader_id, 1,   vertex_shaders_code,   vertex_shaders_size);
        glShaderSource  (fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        // Se compilan los shaders:

        glCompileShader (  vertex_shader_id);
        glCompileShader (fragment_shader_id);

        // Se comprueba que si la compilación ha tenido éxito:

        glGetShaderiv   (  vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (  vertex_shader_id);

        glGetShaderiv   (fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (fragment_shader_id);

        // Se crea un objeto para un programa:

        GLuint program_id = glCreateProgram ();

        // Se cargan los shaders compilados en el programa:

        glAttachShader  (program_id,   vertex_shader_id);
        glAttachShader  (program_id, fragment_shader_id);

        // Se linkan los shaders:

        glLinkProgram   (program_id);

        // Se comprueba si el linkage ha tenido éxito:

        glGetProgramiv  (program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) show_linkage_error (program_id);

        // Se liberan los shaders compilados una vez se han linkado:

        glDeleteShader (  vertex_shader_id);
        glDeleteShader (fragment_shader_id);

        return (program_id);
    }

    void View::show_compilation_error (GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            //OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

    void View::show_linkage_error (GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        #ifdef _MSC_VER
            //OutputDebugStringA (info_log.c_str ());
        #endif

        assert(false);
    }

}
