#include "../include/graphics.hpp"

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
    camera.up         = { .x = 0.0f, .y = 1.0f, .z = 0.0f };
    camera.fovy       = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    updateDeltaVectorFromTarget();

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(fps);

    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

Camera* Graphics::getCamera() {
    return &camera;
}

Vector3 Graphics::getTarget() {
    return camera.target;
}

Vector3 Graphics::getDeltaVectorFromTarget() {
    return deltaVectorFromTarget;
}

void Graphics::updateDeltaVectorFromTarget() {
    deltaVectorFromTarget = Vector3Subtract(camera.position, camera.target);
}

float Graphics::getDistanceFromTarget() {
    return Vector3Distance(camera.position, camera.target);
}

void Graphics::drawCursor() {
    float distance = getDistanceFromTarget();
    unsigned char alpha = 255;
    if (distance < cursorFadeOutDistance)
        alpha = static_cast<unsigned char>((distance / cursorFadeOutDistance) * 255);

    auto color = Color(255, 255, 255, alpha);
    DrawSphere(camera.target, 0.05f, color);
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
void Graphics::zoomCamera(float delta) {
    if (getDistanceFromTarget() > 0.1 || delta < 0) {
        camera.position = Vector3MoveTowards(camera.position, camera.target, delta);
        updateDeltaVectorFromTarget();
    }
}

void Graphics::setTarget(Vector3 target) {
    camera.target = target;
}


void Graphics::rotateCameraYawAroundTarget(float yaw) {
    CameraYaw(&camera, yaw, true);
    updateDeltaVectorFromTarget();
}
void Graphics::rotateCameraPitchAroundTarget(float pitch) {
    CameraPitch(&camera, pitch, false, true, false);
    updateDeltaVectorFromTarget();
}


Color Graphics::getProximityColor(Vector3 a, Vector3 b) {
    float distance = Vector3Distance(a, b);

    if (distance < 1.2f)
        return ColorLerp(Color(255, 0 ,0, 255), YELLOW, distance / 0.8f);
    else if (distance < 2.0f)
        return ColorLerp(YELLOW, GREEN, (distance - 0.8f) / 0.8f);
    else if (distance < 3.8f)
        return ColorLerp(GREEN, BLUE, (distance - 1.6f) / 0.8f);
    else
        return BLUE;
}