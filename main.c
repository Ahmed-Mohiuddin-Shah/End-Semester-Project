#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "maze.h"
#include "variabledefinitions.h"

void SplashScreen();
void InputSelection();
void DrawBackground();
void MainMenu();
void Level1();

int main()
{

	InitWindow(WindowWidth, WindowHeight, "Interactive Maze");
	InitAudioDevice();
	WindowIcon = LoadImage("resources/icon.png");

	ImageFormat(&WindowIcon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(WindowIcon);
	SetTargetFPS((int)FPS);

	// ToggleFullscreen();

	// SplashScreen();

	wallCube = LoadModel("Wall.obj");
	wallTexture = LoadTexture("Wall.png");
	wallCube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wallTexture;

	ball = LoadModel("Ball.obj");
	ballBoundingBox = GetModelBoundingBox(ball);

	while (!WindowShouldClose())
	{ // Replace later with should exit

		gravity = GetFrameTime() * 100 / -9.8;

		// printf("%f\n", GetFrameTime());

		if (IsWindowResized())
		{
			WindowWidth = GetScreenWidth();
			WindowHeight = GetScreenHeight();
		}

		switch (layers)
		{
		case 0:
			InputSelection();
			break;
		case 1:
			MainMenu();
			break;
		case 2:
			Level1();
			break;
		}
	}

	CloseAudioDevice();
	CloseWindow();
	return 0;
}

void SplashScreen()
{
	int frames = 0;
	int animFrames = 0;

	ClearBackground(BLACK);

	Image IntroLogo = LoadImageAnim("resources/IntroLogo.gif", &animFrames);
	Texture2D IntroLogoTexture = LoadTextureFromImage(IntroLogo);

	unsigned int nextFrameDataOffset = 0;
	int currentAnimatedFrame = 0;
	int frameDelay = (int)(FPS / 25);
	int frameCounter = 0;
	float fade = 1.0;

	while (frames < animFrames * frameDelay)
	{

		frameCounter++;
		if (frameCounter >= frameDelay)
		{
			currentAnimatedFrame++;
			if (currentAnimatedFrame >= animFrames)
			{
				currentAnimatedFrame = 0;
			}
			nextFrameDataOffset = IntroLogo.width * IntroLogo.height * 4 * currentAnimatedFrame;
			UpdateTexture(IntroLogoTexture, ((unsigned char *)IntroLogo.data) + nextFrameDataOffset);

			frameCounter = 0;
		}
		BeginDrawing();
		DrawTexture(IntroLogoTexture, GetScreenWidth() / 2 - IntroLogoTexture.width / 2, GetScreenHeight() / 2, WHITE);
		EndDrawing();
		frames++;
	}

	while (fade > 0)
	{
		frameCounter++;
		if (frameCounter >= 3)
		{
			fade -= 0.02;
			frameCounter = 0;
		}
		BeginDrawing();
		DrawRectangle(0, 0, WindowWidth, WindowHeight, Fade(BLACK, fade));
		EndDrawing();
	}
}

void InputSelection()
{

	ClearBackground(BROWN);

	vect.x = 400;
	vect.y = 400;

	static int change = 1;

	if (change)
	{

		ExitButton.x = GetScreenWidth() / 2 - MainMenuButtonWidth / 2;
		ExitButton.y = GetScreenHeight() - MainMenuButtonHeight - 2 * spacing;
		ExitButton.width = MainMenuButtonWidth;
		ExitButton.height = MainMenuButtonHeight;

		InputButton.x = GetScreenWidth() / 2 - MainMenuButtonWidth / 2;
		InputButton.y = GetScreenHeight() - 2 * MainMenuButtonHeight - 3 * spacing;
		InputButton.width = MainMenuButtonWidth - MainMenuButtonWidth / 8 - spacing;
		InputButton.height = MainMenuButtonHeight;

		SettingsButton.x = GetScreenWidth() / 2 + MainMenuButtonWidth / 2 - MainMenuButtonWidth / 8;
		SettingsButton.y = GetScreenHeight() - 2 * MainMenuButtonHeight - 3 * spacing;
		SettingsButton.width = MainMenuButtonWidth / 8;
		SettingsButton.height = MainMenuButtonHeight;

		ScoreBoard.x = GetScreenWidth() / 2 - MainMenuButtonWidth / 2;
		ScoreBoard.y = GetScreenHeight() - 3 * MainMenuButtonHeight - 4 * spacing;
		ScoreBoard.width = MainMenuButtonWidth;
		ScoreBoard.height = MainMenuButtonHeight;

		PlayButton.x = GetScreenWidth() / 2 - MainMenuButtonWidth / 2;
		PlayButton.y = GetScreenHeight() - 4 * MainMenuButtonHeight - 5 * spacing;
		PlayButton.width = MainMenuButtonWidth;
		PlayButton.height = MainMenuButtonHeight;

		HelloHeadline = LoadFontEx("resources/HelloHeadline.ttf", 150, 0, 0);
		GladosMusicSelectionVoice = LoadMusicStream("resources/welcome_page.wav");
		PlayMusicStream(GladosMusicSelectionVoice);
		change = 0;
	}

	if (CheckCollisionPointRec(GetMousePosition(), ExitButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		shouldExit = 1;
	}

	if (CheckCollisionPointRec(GetMousePosition(), ScoreBoard) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		layers = 1;
	}

	if (CheckCollisionPointRec(GetMousePosition(), PlayButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		layers = 2;
		StopMusicStream(GladosMusicSelectionVoice);
	}

	if (!(GetMusicTimePlayed(GladosMusicSelectionVoice) < GetMusicTimeLength(GladosMusicSelectionVoice) - 0.5))
	{
		StopMusicStream(GladosMusicSelectionVoice);
	}
	else
	{
		UpdateMusicStream(GladosMusicSelectionVoice);
	}

	BeginDrawing();

	DrawRectangleRounded(ExitButton, 0.5, 20, BLUE);
	DrawRectangleRounded(InputButton, 0.5, 20, BLUE);
	DrawRectangleRounded(SettingsButton, 0.5, 20, BLUE);
	DrawRectangleRounded(ScoreBoard, 0.5, 20, BLUE);
	DrawRectangleRounded(PlayButton, 0.5, 20, BLUE);

	DrawTextEx(HelloHeadline, "Maze Testing Initiative", vect, 50, 0, WHITE);

	EndDrawing();
}

void DrawBackground()
{
}

void MainMenu()
{
	BeginDrawing();
	DrawBackground();
	EndDrawing();
}

void Level1()
{
	static int change = 1;

	if (change)
	{
		// Define the camera to look into our 3d world
		camera.fovy = 70.0;
		camera.projection = 0;
		camera.position = (Vector3){-0.002371f, 15.0f, 43.558060f};
		camera.target = (Vector3){-0.091722f, 11.853745f, 39.693504f};
		camera.up = (Vector3){0.0f, 10.0f, 0.0f};

		FloorPosition = (Vector3){0.0f, -10.0f, 0.0f};
		FloorSize = (Vector3){80.0f, 1.0f, 80.0f};

		CubePosition = (Vector3){-39.0f, -8.0f, -39.0f};
		CubeSize = (Vector3){2.0f, 2.0f, 2.0f};

		BallPosition = (Vector3){0.0f, 10.0f, 0.0f}; // Set model position     // Unload cubesmap image from RAM, already uploaded to VRAM
		BallSpeedVector = (Vector3){0.0f, 0.0f, 0.0f};

		SetCameraMode(camera, CAMERA_FREE); // Set an orbital camera mode
		SetCameraPanControl(KEY_W);

		CollisionWithFloor = false;

		change = 0;
	}

	FloorBoundingBox = (BoundingBox){(Vector3){FloorPosition.x - FloorSize.x / 2,
											   FloorPosition.y - FloorSize.y / 2,
											   FloorPosition.z - FloorSize.z / 2},
									 (Vector3){FloorPosition.x + FloorSize.x / 2,
											   FloorPosition.y + FloorSize.y / 2,
											   FloorPosition.z + FloorSize.z / 2}};

	BallSpeedVector = (Vector3){0.0f, gravity, 0.0f};

	// camera.position = BallPosition;
	camera.target = BallPosition;

	if (CheckCollisionBoxSphere(FloorBoundingBox, BallPosition, BallRadius))
		CollisionWithFloor = true;

	if (CollisionWithFloor)
	{
		BallSpeedVector.y = 0;
		CollisionWithFloor = false;
	}
	else
	{
		BallPosition.y += BallSpeedVector.y;
	}

	if (isBallCollidedWithWall)
	{
	}

	BallSpeedVector.x += GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) * GetFrameTime() * 10;
	BallSpeedVector.z += GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) * GetFrameTime() * 10;

	BallPosition.x += BallSpeedVector.x;

	BallPosition.z += BallSpeedVector.z;

	collidedWithX = false;
	collidedWithY = false;
	// CheckCollisionBoxSphere();
	UpdateCamera(&camera);
	//----------------------------------------------------------------------------------
	//
	// printf("%f, %f, %f\n%f, %f, %f\n",camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z);
	// Draw
	//----------------------------------------------------------------------------------

	{
		BeginDrawing();

		BeginMode3D(camera);

		ClearBackground(TERMINALBROWN);

		DrawRectangle(0, 0, WindowWidth, WindowHeight, TERMINALBROWN);
		DrawRectangleLines(spacing, spacing, WindowWidth - 2 * spacing, WindowHeight - 2 * spacing, TERMINALOUTLINEYELLOW);
		DrawRectangleLines(spacing + 4, spacing + 4, WindowWidth - 2 * spacing - 4, WindowHeight - 2 * spacing - 4, TERMINALOUTLINEYELLOW);

		DrawCubeV(FloorPosition, FloorSize, BROWN);
		DrawCubeWiresV(FloorPosition, FloorSize, TERMINALOUTLINEYELLOW);

		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				if (level1[i][j])
				{
					DrawModel(wallCube, (Vector3){CubePosition.x + 2 * i, CubePosition.y - 1, (CubePosition.z + 2 * j) - 1}, 2.0f, WHITE);
					if (CheckCollisionBoxSphere((BoundingBox){(Vector3){CubePosition.x + 2 * i - CubeSize.x / 2,
																		CubePosition.y - CubeSize.y / 2,
																		CubePosition.z + 2 * j - CubeSize.z / 2},
															  (Vector3){CubePosition.x + 2 * i + CubeSize.x / 2,
																		CubePosition.y + CubeSize.y / 2,
																		CubePosition.z + 2 * j + CubeSize.z / 2}},
												(Vector3){BallPosition.x, BallPosition.y, BallPosition.z}, BallRadius))
					{
						ballRectangle = (Rectangle){
							BallPosition.x - BallRadius,
							BallPosition.z - BallRadius,
							BallPosition.x + BallRadius,
							BallPosition.z + BallRadius};

						wallRectangle = (Rectangle){CubePosition.x + 2 * i - CubeSize.x / 2, CubePosition.z + 2 * j - CubeSize.z / 2, CubePosition.x + 2 * i + CubeSize.x / 2, CubePosition.z + 2 * j + CubeSize.z / 2};

						collision = GetCollisionRec(ballRectangle, wallRectangle);

						// Use the position and dimensions of the collision rectangle
						// to determine the direction of the collision
						if (collision.x > ballRectangle.x)
						{
							BallPosition.x -= BallSpeedVector.x;
						}
						else if (collision.x + collision.width < ballRectangle.x + ballRectangle.width)
						{
							BallPosition.x -= BallSpeedVector.x;
						}
						else if (collision.y > ballRectangle.y)
						{
							BallPosition.z -= BallSpeedVector.z;
						}
						else if (collision.y + collision.height < ballRectangle.y + ballRectangle.height)
						{
							BallPosition.z -= BallSpeedVector.z;
						}
						else
						{
							// Collision from the front or back
						}
					}
				}
			}
		}
		DrawModel(ball, (Vector3){BallPosition.x, BallPosition.y + 0.5, BallPosition.z}, 1.0, ORANGE);
		DrawModelWires(ball, (Vector3){BallPosition.x, BallPosition.y + 0.5, BallPosition.z}, 1.0, BLACK);
		DrawText(TextFormat("%f", difX), 100, 100, 15, BLACK);
		DrawText(TextFormat("%f", difZ), 120, 120, 15, BLACK);
		EndMode3D();

		DrawRectangleLinesEx((Rectangle){spacing, spacing, WindowWidth - 2 * spacing, WindowHeight - 2 * spacing}, 10, TERMINALOUTLINEYELLOW);
		DrawRectangleLinesEx((Rectangle){0, 0, WindowWidth, WindowHeight}, 20, TERMINALBROWN);
		DrawFPS(1, 1);
		EndDrawing();
	}
}