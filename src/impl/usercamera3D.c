#include "usercamera3D.h"
#include "raymath.h"

void ProcessMouseMovements(PlayerCamera* ctx);
void ProcessKeyboardInner(PlayerCamera* ctx);
void UpdateCameraVectors(PlayerCamera* ctx);
void InnerCameraUpdate(PlayerCamera* ctx, float deltatime);

PlayerCamera Set3DCamera(float mvspeed, float ms_sensitivity, Vector3 initialposition) {
    PlayerCamera newcamera;
    newcamera.movespeed = mvspeed;
    newcamera.mousesensitivity = ms_sensitivity;
    newcamera.Camera_instance.fovy = 70.0f;
    newcamera.Camera_instance.up = (Vector3){0.0f, 1.0f, 0.0f};
    newcamera.Camera_instance.position = initialposition;
    newcamera.Camera_instance.projection = CAMERA_PERSPECTIVE;
    newcamera.Camera_instance.target = (Vector3){0.0f, 0.0f, 0.0f};
    newcamera.velocity = (Vector3){0.0f, 0.0f, 0.0f};
    newcamera.yaw = -90.0f;
    newcamera.pitch = 0.0f;
    newcamera.UpdateSelf = InnerCameraUpdate;
    return newcamera;
}

void ProcessMouseMovements(PlayerCamera* ctx){
    Vector2 MouseDelta = GetMouseDelta();
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_LEFT_ALT)) {
        HideCursor();
        DisableCursor();
        ctx->yaw += MouseDelta.x * ctx->mousesensitivity;
        ctx->pitch -= MouseDelta.y * ctx->mousesensitivity;

        if (ctx->pitch > 89.0f) ctx->pitch = 89.0f;
        if (ctx->pitch < -89.0f) ctx->pitch = -89.0f;
    } else {
        ShowCursor();
        EnableCursor();
    }
}

void ProcessKeyboardInner(PlayerCamera* ctx) {
    ctx->velocity = (Vector3){0.0f, 0.0f, 0.0f};
    if (IsKeyDown(KEY_W)) {
        Vector3 forward = Vector3Normalize(Vector3Subtract(ctx->Camera_instance.target, ctx->Camera_instance.position));
        ctx->velocity = Vector3Add(ctx->velocity, forward);
    }
    if (IsKeyDown(KEY_S)) {
        Vector3 forward = Vector3Normalize(Vector3Subtract(ctx->Camera_instance.target, ctx->Camera_instance.position));
        ctx->velocity = Vector3Subtract(ctx->velocity, forward);
    }
    if (IsKeyDown(KEY_D)) {
        Vector3 forward = Vector3Normalize(Vector3Subtract(ctx->Camera_instance.target, ctx->Camera_instance.position));
        Vector3 right = Vector3CrossProduct(forward, ctx->Camera_instance.up);
        ctx->velocity = Vector3Add(ctx->velocity, right);
    }
    if (IsKeyDown(KEY_A)) {
        Vector3 forward = Vector3Normalize(Vector3Subtract(ctx->Camera_instance.target, ctx->Camera_instance.position));
        Vector3 right = Vector3CrossProduct(forward, ctx->Camera_instance.up);
        ctx->velocity = Vector3Subtract(ctx->velocity, right);
    }
    if (IsKeyDown(KEY_SPACE)) {
        ctx->velocity.y += 1.0f;
    } else if (IsKeyDown(KEY_C)) {
        ctx->velocity.y -= 1.0f;
    }
    if (Vector3Length(ctx->velocity) > 0) {
        ctx->velocity = Vector3Normalize(ctx->velocity);
        ctx->velocity = Vector3Scale(ctx->velocity, ctx->movespeed);
    }
}

void UpdateCameraVectors(PlayerCamera* ctx) {
    Vector3 front;
    front.x = cos(DEG2RAD * ctx->yaw) * cos(DEG2RAD * ctx->pitch);
    front.y = sin(DEG2RAD * ctx->pitch);
    front.z = sin(DEG2RAD * ctx->yaw) * cos(DEG2RAD * ctx->pitch);
    front = Vector3Normalize(front);
    ctx->Camera_instance.target = Vector3Add(ctx->Camera_instance.position, front);
}

void InnerCameraUpdate(PlayerCamera* ctx, float deltatime) {
    ProcessMouseMovements(ctx);
    ProcessKeyboardInner(ctx);
    ctx->Camera_instance.position = Vector3Add(ctx->Camera_instance.position, Vector3Scale(ctx->velocity, deltatime));
    UpdateCameraVectors(ctx);
}