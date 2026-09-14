#ifndef RAYLIB_TEST_GRAPHICS_H
#define RAYLIB_TEST_GRAPHICS_H
#include "raylib.h"

class Graphics {
private:
    Camera camera;
    int screenWidth;
    int screenHeight;
    Vector3 deltaVectorFromTarget;

    constexpr static float cursorFadeOutDistance = 1.5;

    void correctTarget(Vector3 ogPos);

public:
    Graphics();

    void init(int screenWidth, int screenHeight, int fps, Vector3 cam_pos, Vector3 cam_target, const char* title);

    Camera* getCamera();

    Vector3 getTarget();
    Vector3 getDeltaVectorFromTarget();
    void updateDeltaVectorFromTarget();
    float getDistanceFromTarget();

    void drawCursor();

    void updateCamera();

    void moveCameraToPos(Vector3 position);
    void moveCameraForward(float distance);
    void moveCameraRight(float distance);
    void moveCameraUp(float distance);
    void zoomCamera(float delta);

    void setTarget(Vector3 target);

    void rotateCameraYawAroundTarget(float yaw);
    void rotateCameraPitchAroundTarget(float pitch);

    static Color getProximityColor(Vector3 a, Vector3 b);
};

#endif //RAYLIB_TEST_GRAPHICS_H
