#define GLM_ENABLE_EXPERIMENTAL

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#define ROOM_WIDTH 30
#define ROOM_LENGTH 30
#define ROOM_HEIGHT 5

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>
#include <vector>
#include <random>
#include <math.h>
#include "Utils/utils.hpp"
#include "Utils/objloader.hpp"
#include "Utils/shader.hpp"
#include "Utils/texture.hpp"

using namespace util;
using namespace std;

namespace ghostfly {
    class SceneManager {
        public:
            SceneManager();
            ~SceneManager();
            std::vector<objs> fileObjects;
            model objModel;

            std::vector<GLuint> fTex;
            std::vector<GLuint> wTex;
            
            void RenderScene(void);
            void initLight();

            void setNumberOfRooms(int);
            int getNumberOfRooms();

            void processEnvironment(std::string);
            void processTextures();
            void processModels();

           // objLoader *obj;

        private:
            int numOfRooms;

            void drawGround();
            void drawWalls();
            void displayObjects();
    };
}

#endif // SCENEMANAGER_H