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
    Solar_body simulation[] = {
        GetSolarBody(4.0f, 1.0e4f, GREEN, (Vector3){50.0f, -50.0f, 50.0f}, (Vector3){-10.5f, 0.0f, 10.0f}),
        GetSolarBody(4.0f, 1.0e6f, ORANGE, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}),
        GetSolarBody(4.0f, 1.0e5f, GRAY, (Vector3){-100.0f, 0.0f, -100.0f}, (Vector3){15.5f, 0.0f, -2.0f}),
    };

    unsigned int simsize = (sizeof(simulation) / sizeof(simulation[0]));

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