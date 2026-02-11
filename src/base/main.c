#include <stdio.h>
#include <raylib.h>
#include "usercamera3D.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int main(){
	InitWindow(screenWidth, screenHeight, "Simulation");
	SetTargetFPS(100);
	PlayerCamera P_CAM = Set3DCamera(5.0f, 0.1f, (Vector3){5.0f, 5.0f, 5.0f});
	Model cube = LoadModelFromMesh(GenMeshCube(2.0f, 2.0f, 2.0f));
	Vector3 cubepos = {0.0f, 1.0f, 0.0f};
	while(!WindowShouldClose()) {
		float dt = GetFrameTime();
		P_CAM.UpdateSelf(&P_CAM, dt);
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode3D(P_CAM.Camera_instance);
		DrawGrid(100, 1.0f);
		DrawModel(cube, cubepos, 1.0f, GREEN);
		DrawLine3D((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){5.0f, 0.0f, 0.0f}, RED);
		DrawLine3D((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 5.0f, 0.0f}, GREEN);
		DrawLine3D((Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 0.0f, 5.0f}, BLUE);
		EndMode3D();
		EndDrawing();
	}
	UnloadModel(cube);
	CloseWindow();
	return 0;
}