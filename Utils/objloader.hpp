#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace glm;
using namespace std;

namespace util {
    bool loadOBJ(const char*, vector<vec3>&, vector<vec2>&, vector<vec3>&);
    bool loadAssImp(const char*, vector<unsigned short>&, vector<vec3>&,vector<vec2>&, vector<vec3>&);
}
#endif