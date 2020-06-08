//#include <GL/glut.h>
//#include <math.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "CameraView.hpp"

using namespace std;

/**
 * Rotação funciona fazendo movimentos no mouse com qualquer botão.
 * As setas (up, left, down, right) transladam a câmera no espaço seguindo seu próprio eixo.
 * O scroll do mouse funciona como zoom in e zoom out.
*/

namespace ghostfly {
    CameraView::CameraView() {
        camUp = glm::vec3(0, 1, 0);
        fieldOfView = 45.0f;
        camPositionDelta = glm::vec3(0,0,0);
        cameraScale = 0.05f;
        maxPitch = 5;
        maxHeading = 5;
    }

    void CameraView::Reset() {
        camUp = glm::vec3(0, 1, 0);
    }

    void CameraView::Update() {
        camDirection = glm::normalize(camLookAt - camPosition);
        glViewport(viewportX, viewportY, width, height);

        projection = glm::perspective(fieldOfView, aspectRatio, nearClip, farClip);
        glm::vec3 axis = glm::cross(camDirection, camUp);
        glm::quat pitchQuaternion = glm::angleAxis(cameraPitch, axis);
        glm::quat headingQuaternion = glm::angleAxis(cameraHeading, camUp);
        glm::quat temp = glm::cross(pitchQuaternion, headingQuaternion);
        temp = glm::normalize(temp);
        camDirection = glm::rotate(temp, camDirection);
        camPosition += camPositionDelta;
        camLookAt = camPosition + camDirection * 1.0f;
        cameraHeading *= .3;
        cameraPitch *= .3;
        camPositionDelta *= .8f;

        view = glm::lookAt(camPosition, camLookAt, camUp);
        model = glm::mat4(1.0f);
        MVP = projection * view * model;
    }

    void CameraView::SetPosition(glm::vec3 position) { camPosition = position; }
    
    void CameraView::SetLookAt(glm::vec3 position) { camLookAt = position; }
    
    void CameraView::SetFOV(double fov) { fieldOfView = fov; }
    
    void CameraView::SetViewport(int x, int y, int w, int h) {
        viewportX = x;
        viewportY = y;
        width = w;
        height = h;
        aspectRatio = double(w) / double(h);
    }

    void CameraView::Translate(CameraDirection camdir) {
        switch (camdir) {
            case DOWN:
                camPositionDelta -= camUp * cameraScale;
                break;
            case UP:
                camPositionDelta += camUp * cameraScale;
                break;
            case RIGHT:
                camPositionDelta += glm::cross(camDirection, camUp) * cameraScale;
                break;
            case LEFT:
                camPositionDelta -= glm::cross(camDirection, camUp) * cameraScale;
                break;
            default:
                break;
        }
    }

    void CameraView::ChangePitch(float degrees) {
        if (degrees < -maxPitch) degrees = -maxPitch;
        else if (degrees > maxPitch) degrees = maxPitch;

        cameraPitch += degrees;

        if (cameraPitch > 360.0f) cameraPitch -= 360.0f;
        else if (cameraPitch < -360.0f) cameraPitch += 360.0f;
    }

    void CameraView::ChangeHeading(float degrees) {
        if (degrees < -maxHeading) degrees = -maxHeading;
        else if (degrees > maxHeading) degrees = maxHeading;

        if ((cameraPitch > 90 && cameraPitch < 270) || (cameraPitch < -90 && cameraPitch > -270))
            cameraHeading -= degrees;
        else 
            cameraHeading += degrees;
        
        if (cameraHeading > 360.0f)
            cameraHeading -= 360.0f;
        else if (cameraHeading < -360.0f)
            cameraHeading += 360.0f;
    }
    
    void CameraView::Move2D(int x, int y) {
        glm::vec3 mouseDelta = mousePosition - glm::vec3(x, y, 0);
            ChangeHeading(.005f * mouseDelta.x);
            ChangePitch(.005f * mouseDelta.y);
        mousePosition = glm::vec3(x, y, 0);
    }
    
    void CameraView::MouseMove(CameraDirection m) {
        switch (m) {
            case FORWARD:
                camPositionDelta += camDirection * cameraScale;
                break;        
            case BACK:
                camPositionDelta -= camDirection * cameraScale;
                break;
            default:
                break;
        }
    }

    void CameraView::SetPosition(int x, int y) {
        camPositionDelta += camUp * .0002f;
        camPositionDelta -= camUp * .0002f;
        //moveCamera = true;
        mousePosition = glm::vec3(x, y, 0);

    }

    void CameraView::SetClipping(double near, double far) {
        nearClip = near;
        farClip = far;
    }

    void CameraView::SetViewport(int &x, int &y, int &w, int &h) {
        x = viewportX;
        y = viewportY;
        width = w;
        height = h;
    }

    void CameraView::SetMatrices(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M) {
        P = projection;
        V = view;
        M = model;
    }

}  // ghostfly