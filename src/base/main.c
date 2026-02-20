//#include <stdio.h>
#include <raylib.h>
#include "../headers/usercamera3D.h"
#include "../headers/SolarBodies.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int main() {
    InitWindow(screenWidth, screenHeight, "Simulation");
    SetTargetFPS(100);

    PlayerCamera P_CAM = Set3DCamera(25.0f, 0.1f, (Vector3){0.0f, 100.0f, 0.0f});

    // Array of bodies (contiguous in memory)
    Solar_body simulation[2] = {
        GetSolarBody(10.0f, 1.0e7f, ORANGE, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}),
        GetSolarBody(4.0f, 1.0e3f, BLUE, (Vector3){150.0f, 50.0f, 0.0f}, (Vector3){0.0f, .0f, -75.0f})
    };

    unsigned int simsize = 2;

    // Load 3D models for each body
    for (unsigned int i = 0; i < simsize; ++i) {
        simulation[i].EnloadModelSelf(&simulation[i], LoadModelFromMesh(GenMeshSphere(simulation[i].size, 16, 16)));
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Call the improved function directly with the array
        UpdateSolarBodies(simulation, simsize, dt);
        P_CAM.UpdateSelf(&P_CAM, dt);
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(P_CAM.Camera_instance);

		for (unsigned int i = 0; i < simsize; ++i) {
			simulation[i].DrawSelf(&simulation[i]);
    	}

        DrawGrid(10, 15.0f);


        EndMode3D();

        DrawFPS(50, 50);

        EndDrawing();
    }

    // Unload models
    for (unsigned int i = 0; i < simsize; ++i) {
        simulation[i].UnloadSelf(&simulation[i]);
    }

    CloseWindow();
    return 0;
}