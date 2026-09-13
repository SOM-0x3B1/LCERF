#include "../include/graphics.h++"

#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

Graphics::Graphics() : camera() {
    screenWidth = 0;
    screenHeight = 0;
}

void Graphics::init(int sw, int sh, int fps, const Vector3 cam_pos, const Vector3 cam_target, const char* title) {
    screenWidth = sw;
    screenHeight = sh;

    camera.position   = cam_pos;
    camera.target     = cam_target;
    camera.up         = { 0.0f, 1.0f, 0.0f };
    camera.fovy       = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(fps);

    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

Camera* Graphics::getCamera() {
    return &camera;
}

void Graphics::updateCamera() {
    UpdateCamera(&camera, CAMERA_CUSTOM);
}

void Graphics::moveCameraToPos(Vector3 position) {
    camera.position = position;
    setTarget(camera.position);
    updateCamera();
}


void Graphics::correctTarget(Vector3 ogPos) {
    const Vector3 diffPos = Vector3Subtract(ogPos, camera.position);
    camera.target = Vector3Add(camera.target, diffPos);
}

void Graphics::moveCameraForward(float distance) {
    const Vector3 ogPos = camera.position;
    CameraMoveForward(&camera, distance, true);
}
void Graphics::moveCameraRight(float distance) {
    const Vector3 ogPos = camera.position;
    CameraMoveRight(&camera, distance, true);
}
void Graphics::moveCameraUp(float distance) {
    const Vector3 ogPos = camera.position;
    CameraMoveUp(&camera, distance);
}

void Graphics::setTarget(Vector3 target) {
    camera.target = target;
}


void Graphics::rotateCameraYawAroundTarget(float yaw) {
    CameraYaw(&camera, yaw, true);
}
void Graphics::rotateCameraPitchAroundTarget(float pitch) {
    CameraPitch(&camera, pitch, false, true, false);
}


Color Graphics::getProximityColor(Vector3 a, Vector3 b) {
    float distance = Vector3Distance(a, b);

    if (distance < 0.8f)
        return  ColorLerp(Color(255, 0 ,0, 255), YELLOW, distance / 0.8f);
    else if (distance < 1.6f)
        return ColorLerp(YELLOW, GREEN, (distance - 0.8f) / 0.8f);
    else if (distance < 2.4f)
        return ColorLerp(GREEN, BLUE, (distance - 1.6f) / 0.8f);
    else
        return BLUE;
}