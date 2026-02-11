#include "raylib.h"
#include "stdbool.h"

typedef struct Solar_body{
    float mass;
    Color color;
    float size;
    Vector3 position;
    Vector3 velocity;
    Model currentModel;
    bool loaded;
    void (*EnloadModelSelf)(struct Solar_body* ctx, Model insidemodel);
    void (*UnloadSelf)(struct Solar_body* ctx);
    void (*DrawSelf)(struct Solar_body* ctx);
} Solar_body;

Solar_body GetSolarBody(float size_inner, float mass_inner, Color color_inner, Vector3 position_inner, Vector3 velocity_inner);
void UpdateSolarBodies(Solar_body** SolarBodies, unsigned int amount);
