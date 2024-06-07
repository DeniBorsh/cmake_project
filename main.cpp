#include "GLFW/glfw3.h"
#include <MyProjectConfig.h>
#include <iostream>
#ifdef USE_ADDER
    #include "adder.h"
#endif

using namespace std;

int main(int argc, char** argv) {
#ifdef USE_ADDER
    cout << "ADDER: " << mearlymath::add(40, 2) << endl;
#else
    cout << 40 + 2 << endl;
#endif
    cout << argv[0] << " Version " 
         << MyProject_VERSION_MAJOR << "." << MyProject_VERSION_MINOR << endl;

    GLFWwindow* window;
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(300, 300, "Gears", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}