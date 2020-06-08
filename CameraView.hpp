#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H
#define GLM_ENABLE_EXPERIEMENTAL

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ghostfly {
    enum CameraDirection { UP, DOWN, LEFT, RIGHT, FORWARD, BACK };

    class CameraView {
        public:
            CameraView();

            void Update();
            void Translate(CameraDirection d);
            void Reset();
            void ChangePitch(float degrees);
            void ChangeHeading(float degrees);
            void Move2D(int x, int y);
            void MouseMove(CameraDirection m);
            //void MouseMove();

            void SetPosition(glm::vec3 position);
            void SetLookAt(glm::vec3 position);
            void SetFOV(double fov); // field of view
            void SetViewport(int x, int y, int width, int height);
            void SetClipping(double near, double far);
            void SetDistance(double dist);
            void SetPosition(int x, int y);
            void SetViewport(int &x, int &y, int &width, int &height);
            void SetMatrices(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);

            int viewportX;
            int viewportY;
            int width;// window width
            int height; // window height

            double aspectRatio;
            double fieldOfView;
            double nearClip;
            double farClip;

            float cameraScale;
            float cameraHeading;
            float cameraPitch;
            float maxPitch;
            float maxHeading;

            bool moveForward;
            bool moveBackward;

            glm::vec3 camPosition;
            glm::vec3 camPositionDelta;
            glm::vec3 camLookAt;
            glm::vec3 camDirection;
            glm::vec3 camUp;
            glm::vec3 mousePosition;

            glm::mat4 projection;
            glm::mat4 view;
            glm::mat4 model;
            glm::mat4 MVP;

    };
}

#endif // CAMERAVIEW_H