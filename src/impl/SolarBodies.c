#include "SolarBodies.h"
#include "stdio.h"
#include "string.h"

void EnloadSelfInner(Solar_body* ctx, Model insidemodel);
void UnloadSelfInner(Solar_body* ctx);
void DrawSelfInner(Solar_body* ctx);

Solar_body GetSolarBody(float size_inner, float mass_inner, Color color_inner, Vector3 position_inner, Vector3 velocity_inner) {
    Solar_body nsb;
    nsb.size = size_inner;
    nsb.mass = mass_inner;
    nsb.color = color_inner;
    nsb.position = position_inner;
    nsb.velocity = velocity_inner;
    nsb.loaded = false;

    //dont forget about your functions included in!

    memset(&nsb.currentModel, 0, sizeof(Model));
    return nsb;
}

void EnloadSelfInner(Solar_body* ctx, Model insidemodel) {
    if (ctx->loaded == false) {
        ctx->loaded = true;
        ctx->currentModel = insidemodel;
    } else {
        printf("Already loaded the model!!! Reassigning...");
        UnloadModel(ctx->currentModel);
        ctx->currentModel = insidemodel;
    }
}

void UnloadSelfInner(Solar_body* ctx) {
    if (ctx->loaded == true) {
        UnloadModel(ctx->currentModel);
        ctx->loaded = false;
    } else {
        printf("Already unloaded, skipping...");
    }
}

void DrawSelfInner(Solar_body* ctx) {
    DrawModel(ctx->currentModel, ctx->position, 1.0f, ctx->color);
}


void UpdateSolarBodies(Solar_body** Solarbodies, unsigned int amount) {
    // todo
}