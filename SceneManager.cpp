#define GLM_ENABLE_EXPERIMENTAL

#include "SceneManager.hpp"
#include "CameraView.hpp"

using namespace glm;

namespace ghostfly {

    SceneManager::SceneManager() {
        setNumberOfRooms(0);
        fTex = {};
        wTex = {};
       // obj = new objLoader();
    }

    void SceneManager::initLight() {
        GLfloat luz_pontual_pos[] = {5, 5, 5, 1};

        GLfloat light0_pos[] = {3, 15, 5, 1};
        GLfloat light0_diffuse[] = {1, 1, 1, 1};
        glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

        GLfloat light1_diffuse[] = { 1, 1, 1, 1.0 };
        GLfloat light1_specular[] = { 1, 1, 1, 1.0 };
        GLfloat light1_ambient[] = { 1.0, 1.0, 1.0, 1 };

        glLightfv(GL_LIGHT1, GL_POSITION, luz_pontual_pos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); 

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }

    void SceneManager::RenderScene(void) {
        drawGround();
        drawWalls();
        displayObjects();
    }
    
    void SceneManager::drawGround() {
        int numRooms = getNumberOfRooms();
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        for(auto i = 0; i < numRooms; i++) {
            glBindTexture(GL_TEXTURE_2D, fTex[fileObjects[i].floorTex]);
            glBegin(GL_QUAD_STRIP);
                glTexCoord2f(0, 0);
                glVertex3f(i * ROOM_LENGTH, 0, ROOM_WIDTH);
                // P2
                glTexCoord2f(0, 6);
                glVertex3f(ROOM_LENGTH + i * ROOM_LENGTH, 0, ROOM_WIDTH);
                // P3
                glTexCoord2f(6, 0);
                glVertex3f(i * ROOM_LENGTH, 0, 0);
                // P4
                glTexCoord2f(6, 6);
                glVertex3f(ROOM_LENGTH + i * ROOM_LENGTH, 0, 0);
            glEnd();
        }
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    }

    void SceneManager::drawWalls() {
        int numRooms = getNumberOfRooms();
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        for(auto i = 0; i < numRooms; i++) {
            glBindTexture(GL_TEXTURE_2D, wTex[fileObjects[i].wallTex]);       
            glBegin(GL_QUAD_STRIP);
                // 1st edge
                glTexCoord2f(0.0, 0.0);
                glVertex3f(i * ROOM_LENGTH, 0, 0);
                glTexCoord2f(0, 1);
                glVertex3f(i * ROOM_LENGTH, ROOM_HEIGHT, 0);
                // 2nd edge
                glTexCoord2f(6.0, 0.0); 
                glVertex3f(i * ROOM_LENGTH, 0, ROOM_WIDTH);
                glTexCoord2f(6.0, 1);
                glVertex3f(i * ROOM_LENGTH, ROOM_HEIGHT, ROOM_WIDTH);
                // 3rd edge
                glTexCoord2f(0.0, 0.0);
                glVertex3f(ROOM_LENGTH + i * ROOM_LENGTH, 0, ROOM_WIDTH);
                glTexCoord2f(0.0, 1);
                glVertex3f(ROOM_LENGTH + i * ROOM_LENGTH, ROOM_HEIGHT, ROOM_WIDTH);
                // 4th edge
                glTexCoord2f(6.0, 0.0);
                glVertex3f(ROOM_LENGTH + i * ROOM_LENGTH, 0, 0);
                glTexCoord2f(6.0, 1);
                glVertex3f(ROOM_LENGTH + i * ROOM_LENGTH, ROOM_HEIGHT, 0);
                // 5th and final edge to complete a room
                glTexCoord2f(0.0, 0.0);
                glVertex3f(i * ROOM_LENGTH, 0, 0);
                glTexCoord2f(0.0, 1);
                glVertex3f(i * ROOM_LENGTH, ROOM_HEIGHT, 0);
            glEnd();
        }
        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
    } 

    void SceneManager::displayObjects() {            
        //glEnable(GL_LIGHTING_BIT);
        int rooms = getNumberOfRooms();
        
        for (auto j = 0; j < rooms; j++) {
            //printf("room %d\n", j);        
            int numObjOne = fileObjects[j].numObjOne;
            for (auto i = 0; i < numObjOne; i++) {
                /*
                glPushAttrib(GL_LIGHTING_BIT); 
                // Carregamento do objeto. Shading não funciona
                glPushMatrix();
                glUseProgram(objModel.prgID);        
                
                //glUniformMatrix4fv(objModel.matID, 1, GL_FALSE, &)
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, objModel.texture);
                glUniform1i(objModel.texID, 0);
                glEnableVertexAttribArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, objModel.vertbuffer);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

                // 2nd attribute buffer : UVs
                glEnableVertexAttribArray(1);
                glBindBuffer(GL_ARRAY_BUFFER, objModel.uvbuffer);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glTranslatef(fileObjects[j].coordObj1[i].posX, 
                            fileObjects[j].coordObj1[i].posY, 
                            fileObjects[j].coordObj1[i].posZ);
                // Draw the triangle !
                glDrawArrays(GL_TRIANGLES, 0, objModel.vert.size());
                glDisableVertexAttribArray(0);
                glDisableVertexAttribArray(1);
                glPopMatrix();
                glPopAttrib();
                */
                glPushMatrix();
                GLfloat mat_specular[] = { 0.243, 0.3, 0.116, 1 };
                GLfloat mat_diffuse[] = { .5, .48, .8, 1.0 };
                GLfloat mat_shininess[] = { 80.0 };

                //glPushAttrib(GL_LIGHTING_BIT);
                glTranslatef(fileObjects[j].coordObj1[i].posX, 
                             fileObjects[j].coordObj1[i].posY, 
                             fileObjects[j].coordObj1[i].posZ);
                glLightfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glLightfv(GL_FRONT, GL_SHININESS, mat_shininess);
                glLightfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glEnable(GL_LIGHTING);
                glutSolidTorus(.2, .3, 30, 30);
                glClearColor(1, 1, 1, 1);
                glPopMatrix();
                //glPopAttrib();*/
            }               
             
            int numObjTwo = fileObjects[j].numObjTwo;
            for (auto i = 0; i < numObjTwo; i++) {                
                glPushMatrix();
                GLfloat mat_specular[] = { 0.214, 0.262, 0.556, 1};
                GLfloat mat_diffuse[] = { 0.214, 0.262, 0.556, 1};
                GLfloat mat_shininess[] = { 50.0 };
                glLightfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glLightfv(GL_FRONT, GL_SHININESS, mat_shininess);
                glLightfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                
                glPushAttrib(GL_LIGHTING_BIT);
               // glColor3f(0.243, 0.262, 0.556);
                glTranslatef(fileObjects[j].coordObj2[i].posX, 
                             fileObjects[j].coordObj2[i].posY, 
                             fileObjects[j].coordObj2[i].posZ);
                
                glEnable(GL_LIGHTING); 
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, fTex[7]);
                glutSolidTeapot(.65);
                glDisable(GL_LIGHTING);
                glDisable(GL_TEXTURE_2D);
                glPopAttrib();
                glPopMatrix();
            }         
        }
        glDisable(GL_LIGHTING_BIT);
    }
    
    void SceneManager::setNumberOfRooms(int num) {
        numOfRooms = num;
    }
    
    int SceneManager::getNumberOfRooms() {
        return numOfRooms;
    }

    void SceneManager::processEnvironment(string fileName) {
        auto linesContent = fileReader(fileName);
        
        // get the first line of file
        int rooms = stoi(linesContent[0][0]);
        setNumberOfRooms(rooms);

        fileObjects.resize(rooms);
        /// helpers to find a position in the room
        objCoord coord;
        vector<objCoord> auxCoord;
    
        /** This is how the content is placed on linesContent
         *   |0  1  2 3  4 5 6
         * --|-----------------
         * 0 |3
           1 |s1 o1 3 2 o2 6 3
           2 |s2 o1 3 0 o2 6 1
           3 |s3 o1 8 1 o2 2 2
        */
        for (int i = 1; i <=  rooms; i++) {
            // random number of objects generated by gaussian distribution
            int numObj1 = randomNumByGaussianDist(stoi(linesContent[i][2]), stoi(linesContent[i][3]));
            int numObj2 = randomNumByGaussianDist(stoi(linesContent[i][5]), stoi(linesContent[i][6]));
            printf("Room %d\n", i);

            // i-1 because loop starts at 1
            fileObjects[i-1].room = linesContent[i][i-i];
            fileObjects[i-1].numObjOne = numObj1;
            fileObjects[i-1].numObjTwo = numObj2;
            fileObjects[i-1].floorTex = (int)randomPos(-2, 8);
            //printf("Floor: %d\n", fileObjects[i-1].floorTex);
            fileObjects[i-1].wallTex = (int)randomPos(-2, 8);
           // printf("Wall: %d\n", fileObjects[i-1].wallTex);


            // coordinates of obj1
            printf("obj1\n");
            for (auto j = 0; j < numObj1; j++) {
                int x, z;
                do {
                   x = randomPos((i-1) * ROOM_LENGTH, ROOM_LENGTH + (i-1) * ROOM_LENGTH);
                   z = randomPos(0, ROOM_WIDTH);
                } while (!validPos(x, z, auxCoord));
                
                coord.posX = x;
                coord.posY = .5;
                coord.posZ = z;
                printf("%d %d\n", x, z);
                auxCoord.push_back(coord);
            }
            fileObjects[i-1].coordObj1 = auxCoord;
            auxCoord.clear();

            // coordinates of obj2
            printf("obj2\n");
            for (auto j = 0; j < numObj2; j++) {
                int x, z;
                do {
                    x = randomPos((i-1) * ROOM_LENGTH, ROOM_LENGTH + (i-1) * ROOM_LENGTH);
                    z = randomPos(0, ROOM_WIDTH);
                } while (!validPos(x, z, auxCoord));
                
                coord.posX = x;
                coord.posY = 0.5;
                coord.posZ = z;
                printf("%d %d\n", x, z);
                auxCoord.push_back(coord);
            }
            fileObjects[i-1].coordObj2 = auxCoord;
            auxCoord.clear();
        }
    }
   
    void SceneManager::processTextures() {
        loadTexture(fTex, "Floor");
        loadTexture(wTex, "Wall");
    }

    void SceneManager::processModels() {
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);    
        glGenVertexArrays(1, &objModel.vertArrayID);
        glBindVertexArray(objModel.vertArrayID);

        objModel.prgID = LoadShaders("Utils/vertexshader.vs", "Utils/fragmentshader.fs");
        objModel.matID = glGetUniformLocation(objModel.prgID, "MVP");
        objModel.texture = loadDDS("Models/uvmap.DDS");
        //objModel.texture = loadBMP_custom("Models/horizontal.bmp");
        objModel.texID = glGetUniformLocation(objModel.prgID, "texSampler");

        bool obj = loadOBJ("Models/cube.obj", objModel.vert, objModel.uvs, objModel.normals);
        if (obj) printf("Model loaded!\n");

        glGenBuffers(1, &objModel.vertbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, objModel.vertbuffer);
        glBufferData(GL_ARRAY_BUFFER, objModel.vert.size() * sizeof(vec3), &objModel.vert[0], GL_STATIC_DRAW);

        glGenBuffers(1, &objModel.uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, objModel.uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, objModel.uvs.size() * sizeof(vec2), &objModel.uvs[0], GL_STATIC_DRAW);
    }
}