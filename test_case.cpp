#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
 
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		return -1;

	std::cout << glGetString(GL_VERSION) << std::endl;

    GLuint vao = 0;
    glCreateVertexArrays( 1, &vao );
    glBindVertexArray( vao );	

	{
		float position[] =
		{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.0f,  0.5f
		};

		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

		std::string vertexShader = 
			"#version 330 core\n"
			"layout (location = 0) in vec4 position;\n"
			"void main()\n"
			"{\n"
			"gl_Position = position;\n"
			"}";
		std::string fragmentShader =
			"#version 330 core\n"
			"layout (location = 0) out vec4 color;\n"
			"void main()\n"
			"{\n"
			"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
			"}";

		const char* src_v = vertexShader.c_str();
		const char* src_f = fragmentShader.c_str();

		unsigned int program;
		program = glCreateProgram();

		unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &src_v, NULL);
		glCompileShader(vs);
 
		int success;
	    char infoLog[512];
	    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	    if (!success)
	    {
	        glGetShaderInfoLog(vs, 512, NULL, infoLog);
	        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &src_f, NULL);
		glCompileShader(fs);

		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	    if (!success)
	    {
	        glGetShaderInfoLog(fs, 512, NULL, infoLog);
	        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
 
		glGetProgramiv(program, GL_LINK_STATUS, &success);
	    if (!success)  
		{
	        glGetProgramInfoLog(program, 512, NULL, infoLog);
	        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glUseProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */

			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
