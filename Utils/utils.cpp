#include "utils.hpp"

namespace util {
    //Distribuição objetos
    int randomNumByGaussianDist(int mean, int standard_deviation) {
        random_device rand;
        mt19937 gen(rand());
        normal_distribution<> gaussian(mean, standard_deviation);
        
        // using ceil values get equal to mean very often
        // return ceil(gaussian(generator));
        int randomNum;
        do {
            randomNum = round(gaussian(gen));
        } while (randomNum > mean + standard_deviation || randomNum < mean - standard_deviation);
        return randomNum;
    }

    int randomPos(int x1, int x2) {
        static std::vector<int> values;
        //float num = -1;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(x1 + 2, x2 - 2);
/*
        do {
            num = dist(gen);
        } while(contains(values, num));*/
        return dist(gen);
    }

    bool contains(vector<int> vec, int n) {
        for (auto p : vec)
            if (p == n) return true;
        return false;
    }

    bool validPos(int pX, int pZ, vector<objCoord> roomPos) {
        int size = roomPos.size();
        //printf("size array %d\n", size);
        for (auto i = 0; i < size; i++) {
            if (abs(pX - roomPos[i].posX) < 1 || abs(pZ - roomPos[i].posZ) < 1)
                return false;
        }
        return true;
    }

    string texturePath(string type, GLuint num) {
        stringstream stream;
        stream << "Textures/" << type << "/" << num << ".jpg";
        return stream.str();
    }

    void loadTexture(vector<GLuint> &tex, string type) {
        for (auto i = 0; i < 8; i++ ) {
            string texW = texturePath(type, i);
            tex.push_back(loadTexture(texW));  
        }
    }

    GLuint loadTexture(string path) {
        GLuint tex = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
        //cout << path << " binded" << endl;
        return tex;
    }

    vector<vector<string>> fileReader(string fileName) {
        ifstream file(fileName);
        // file will be loaded to memory like an array 
        // where the lines = rows and columns = elements in a line separeted by space
        vector<vector<string>> linesContent;
        
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                // space is the default delimeter so there is no need to specify
                stringstream ss(line);
                vector<string> row;
                string entry;
                
                while (ss >> entry) row.push_back(entry);                
                linesContent.push_back(row);
            }
            file.close();
        } else {
            cerr << "File could not be open." << endl;
            exit(EXIT_FAILURE);
        }
        return linesContent;
    }
}