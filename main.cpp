#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SceneManager.hpp"
#include "CameraView.hpp"

using namespace std;
using namespace ghostfly;

SceneManager *scene;
CameraView camera;

/**
 * Compilação linux: g++ -Wall main.cpp CameraView.cpp SceneManager.cpp Utils/utils.cpp Utils/objloader.cpp Utils/shader.cpp Utils/texture.cpp -o fly -lGLEW -lGL -lGLU -lglut -lglfw -lSOIL
 *                   ./fly Files/input.txt
 * É preciso glm.
 **/

/**
 * Ainda é preciso fazer:
 *  - Carregar texturas nas paredes e piso
 *  - Carregar objetos obj
 *  - Verificar se os objetos não irão se sobrepor na mesma sala
 *  - Ajustar controle de câmera
 *  - Ajustar iluminação e shading
 *  - Fazer relatório
*/
class Window {
    public:
        Window() {
            this->interval = 1000 / 60;
            this->window_handle = -1;
        }
        int window_handle, interval;
        glm::ivec2 size;
        float window_aspect;
} window;


void Reshape(int w, int h) {
    if (h > 0) {
		window.size = glm::ivec2(w, h);
		window.window_aspect = float(w) / float(h);
	}
	camera.SetViewport(0, 0, window.size.x, window.size.y);
}

void RenderScene(void) {
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, window.size.x, window.size.y);
    // for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 model, view, projection;
    camera.Update();
    camera.SetMatrices(projection, view , model);
    
    glm::mat4 mvp = projection * view * model;
    glLoadMatrixf(glm::value_ptr(mvp));
    glEnable(GL_DEPTH);

    scene->RenderScene();
    glutSwapBuffers();
}

/// Translate de camera according to the keys pressed on keyboard 
/// UP key translates the camera on +y axis.
/// DOWN key translates the camera on -y axis.
/// LEFT key translates the camera on -x axis.
/// RIGHT key translates the camera on +x axis.
/// \param key represents the key pressed
/// \param x represents the x coordinate
/// \param y represents the y coordinate
void ProcessKeyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            camera.Translate(UP);
            break;
        case GLUT_KEY_DOWN:
            camera.Translate(DOWN);
            break;
        case GLUT_KEY_RIGHT:
            camera.Translate(RIGHT);
            break;
        case GLUT_KEY_LEFT:
            camera.Translate(LEFT);
            break;
        case GLUT_KEY_F1:
            camera.SetPosition(glm::vec3(5, 3.5, 15));
            camera.SetLookAt(glm::vec3(30, 2.5, 15));
            break;
        case 27:
            exit(0);
            break;
    }
}

/// Moves the camera using the mouse scroll.
/// Scrolling forward gives the effect of zoom in. The opposite for scrolling backward.
void MouseKeys(int button, int state, int x, int y) {
    if (button == 3)
        camera.MouseMove(FORWARD);
    if (button == 4)
        camera.MouseMove(BACK);
}


void MousePosition(int x, int y) {
    camera.SetPosition(x, y);
}

void Timer(int value) {
	if (window.window_handle != -1) {
		glutTimerFunc(window.interval, Timer, value);
		glutPostRedisplay();
	}
}

void MotionFunc(int x, int y){
    camera.Move2D(x, y);
}

void Initialize() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    scene->initLight();
    //glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_ARB_explicit_attrib_location);
    //glEnable(GL_ARB_explicit_uniform_location);
    scene->processTextures();
    // couldn't load custom objs
    scene->processModels();
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    
    camera.SetPosition(glm::vec3(5, 3.5, 15));
    camera.SetLookAt(glm::vec3(30, 2.5, 15));
    camera.SetClipping(.1, 1000);
    camera.SetFOV(45);
}

int main(int argc, char **argv) {
    scene = new SceneManager();
    scene->processEnvironment(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 100);
    window.window_handle = glutCreateWindow("Ghost fly");

    glutIgnoreKeyRepeat(false);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(ProcessKeyboard);
    //glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(MouseKeys);
    glutMotionFunc(MotionFunc);
    glutPassiveMotionFunc(MousePosition);
    glutTimerFunc(window.interval, Timer, 0);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "GLEW failed to initialize" <<endl;
        return 1;
    }
    
    Initialize();
    
    glutMainLoop();

    return EXIT_SUCCESS;
}