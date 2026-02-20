#include "../headers/SolarBodies.h"
#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include <raylib.h>

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
    
    nsb.EnloadModelSelf = EnloadSelfInner;
    nsb.UnloadSelf = UnloadSelfInner;
    nsb.DrawSelf = DrawSelfInner;

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


void UpdateSolarBodies(Solar_body* Solarbodies, unsigned int amount, float deltatime) {
    if (amount == 0) return;

    // Allocate temporary acceleration arrays
    Vector3* accelerations = (Vector3*)malloc(amount * sizeof(Vector3));
    Vector3* new_accelerations = (Vector3*)malloc(amount * sizeof(Vector3));

    // --- First acceleration calculation (at current positions) ---
    for (unsigned int i = 0; i < amount; i++) {
        Solar_body* body_i = &Solarbodies[i];          // pointer to current body
        Vector3 acc_i = {0.0f, 0.0f, 0.0f};

        for (unsigned int j = 0; j < amount; j++) {
            if (i == j) continue;

            Solar_body* body_j = &Solarbodies[j];      // pointer to other body

            float dx = body_j->position.x - body_i->position.x;
            float dy = body_j->position.y - body_i->position.y;
            float dz = body_j->position.z - body_i->position.z;

            float dist_sqr = dx*dx + dy*dy + dz*dz + SOFTENING;
            float dist = sqrtf(dist_sqr);
            float inv_dist_cube = 1.0f / (dist * dist_sqr);   // = 1/r^3

            float factor = GRAVITYCONST * body_j->mass * inv_dist_cube;
            acc_i.x += factor * dx;
            acc_i.y += factor * dy;
            acc_i.z += factor * dz;
        }
        accelerations[i] = acc_i;
    }

    // --- First half‑step velocity update and full position update ---
    for (unsigned int i = 0; i < amount; i++) {
        Solar_body* body = &Solarbodies[i];
        Vector3 acc = accelerations[i];

        // v_half = v + 0.5 * a * dt
        body->velocity.x += 0.5f * acc.x * deltatime;
        body->velocity.y += 0.5f * acc.y * deltatime;
        body->velocity.z += 0.5f * acc.z * deltatime;

        // r_new = r + v_half * dt   (this gives r + v*dt + 0.5*a*dt^2)
        body->position.x += body->velocity.x * deltatime;
        body->position.y += body->velocity.y * deltatime;
        body->position.z += body->velocity.z * deltatime;
    }

    // --- Second acceleration calculation (at new positions) ---
    for (unsigned int i = 0; i < amount; i++) {
        Solar_body* body_i = &Solarbodies[i];
        Vector3 new_acc_i = {0.0f, 0.0f, 0.0f};

        for (unsigned int j = 0; j < amount; j++) {
            if (i == j) continue;

            Solar_body* body_j = &Solarbodies[j];

            float dx = body_j->position.x - body_i->position.x;
            float dy = body_j->position.y - body_i->position.y;
            float dz = body_j->position.z - body_i->position.z;

            float dist_sqr = dx*dx + dy*dy + dz*dz + SOFTENING;
            float dist = sqrtf(dist_sqr);
            float inv_dist_cube = 1.0f / (dist_sqr * dist);   // = 1/r^3

            float factor = GRAVITYCONST * body_j->mass * inv_dist_cube;
            new_acc_i.x += factor * dx;
            new_acc_i.y += factor * dy;
            new_acc_i.z += factor * dz;
        }
        new_accelerations[i] = new_acc_i;
    }

    // --- Second half‑step velocity update (using new accelerations) ---
    for (unsigned int i = 0; i < amount; i++) {
        Solar_body* body = &Solarbodies[i];
        Vector3 new_acc = new_accelerations[i];

        // v = v_half + 0.5 * a_new * dt
        body->velocity.x += 0.5f * new_acc.x * deltatime;
        body->velocity.y += 0.5f * new_acc.y * deltatime;
        body->velocity.z += 0.5f * new_acc.z * deltatime;
    }

    free(accelerations);
    free(new_accelerations);
}