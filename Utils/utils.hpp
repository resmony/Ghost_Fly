#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <random>
#include <GL/glut.h>
#include "SOIL/SOIL.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace util {    
    typedef struct ObjectCoordinates {
        GLint posX;
        GLint posZ;
        float posY;
    } objCoord;

    typedef struct Room {
        std::string room;
        int numObjOne;
        int numObjTwo;
        int wallTex;
        int floorTex;
        vector<objCoord> coordObj1;
        vector<objCoord> coordObj2;
    } objs;

    typedef struct Model {
        vector<vec3> vert, normals;
        vector<vec2> uvs;
        GLuint texture, texID, vertbuffer, uvbuffer, prgID, matID, vertArrayID;
    } model;

    int randomNumByGaussianDist(int, int);
    int randomPos(int, int);

    bool validPos(int, int, vector<objCoord>);
    bool contains(vector<int>, int);

    //textures
    void loadTexture(vector<GLuint>&, string);
    GLuint loadTexture(string);
    GLuint getTextureIndex();
    string texturePath(string, GLuint);
    
    vector<vector<string>> fileReader(string path);
    
} // util

#endif