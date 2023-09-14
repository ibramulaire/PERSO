#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include "shader.hpp"
#include <string.h>



void Resize_Window(GLFWwindow* window, int largeur, int hauteur);
void Input(GLFWwindow *window);
int Initialisation();

int largeur=800;
int hauteur=600;
const char* titre="tuto1";
GLFWwindow* window;


GLuint MyShader ;

using namespace std;
unsigned int VBO, VAO, EBO;

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  


void Genere_gpu_data()
{
  
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

      // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    

}




int main(int argc, char const *argv[])
{
  if( !Initialisation())
  {
    cout<<"creation de fenetre echoué"<<endl;
    return -1;
  }

  MyShader=LoadShaders("VS.vert","FS.frag");
  

  Genere_gpu_data();

  glUseProgram(MyShader);
  


  while (!glfwWindowShouldClose(window))
  {
    Input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(MyShader, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(MyShader);

    glfwTerminate();

    return 0;
}


void Resize_Window(GLFWwindow* window, int largeur, int hauteur)
{
     glViewport(0, 0, largeur, hauteur);
}

void Input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int Initialisation()//initialise une fenetrecontex et glew
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif

  window = glfwCreateWindow(largeur, hauteur, titre, NULL, NULL);
  if (window == NULL)
  {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return 0;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, Resize_Window); 


  	if (glewInit() != GLEW_OK) 
    {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 0;
	}

//info version GLSL
std::cout << "***** Info GPU *****" << std::endl;
    std::cout << "Fabricant : " << glGetString (GL_VENDOR) << std::endl;
    std::cout << "Carte graphique: " << glGetString (GL_RENDERER) << std::endl;
    std::cout << "Version : " << glGetString (GL_VERSION) << std::endl;
    std::cout << "Version GLSL : " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;


  return 1;
}