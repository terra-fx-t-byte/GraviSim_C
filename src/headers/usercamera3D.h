#include <raylib.h>

typedef struct PlayerCamera {
    Camera3D Camera_instance;
    Vector3 velocity;
    float movespeed;
    float mousesensitivity;
    float yaw;
    float pitch;
    bool firstmouse;
    void (*UpdateSelf)(struct PlayerCamera* ctx, float deltatime);
} PlayerCamera;

PlayerCamera Set3DCamera(float mvspeed, float ms_sensitivity, Vector3 initialposition);