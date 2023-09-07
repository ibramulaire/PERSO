#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int largeur=800;
int hauteur=600;
const char* titre="tuto1";
GLFWwindow* window;

using namespace std;


void Resize_Window(GLFWwindow* window, int largeur, int hauteur)
{
     glViewport(0, 0, largeur, hauteur);
}

void Input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int Init_Window()//initialise une fenetre et le cointext opengl
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
  return 1;
}



int main(int argc, char const *argv[])
{
  if( !Init_Window())
  {
    cout<<"creation de fenetre echoué"<<endl;
    return -1;
  }

  while (!glfwWindowShouldClose(window))
  {
    Input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

    glfwTerminate();

    return 0;
}