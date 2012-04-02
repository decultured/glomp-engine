/*
 * 	main.cpp
 *
 * 	glomp engine starts here!
 *
 */

#include <GL/glfw.h>

int main() {
	bool running = true;
	// Initialize GLFW
	if( !glfwInit() )
	{
		return -1;
	}
	// Open an OpenGL window
	if( !glfwOpenWindow( 800,600, 0,0,0,0,0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		return -1;
	}
	// Main loop
	while( running )
	{
		// OpenGL rendering goes here...
		glClear( GL_COLOR_BUFFER_BIT );
		// Swap front and back rendering buffers
		glfwSwapBuffers();
		// Check if ESC key was pressed or window was closed
		running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
	}

	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	return 0;
}
