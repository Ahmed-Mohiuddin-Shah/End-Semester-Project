bool CollisionWithFloor = false, CollisionWithBoundary = false, isBallCollidedWithWall = false;

Camera camera;

Model model;

Mesh ModelMesh;

Vector3 BallPosition, FloorPosition, FloorSize, CubePosition, CubeSize;
float BallRadius = 0.4f;
Vector3 BallSpeedVector;

BoundingBox FloorBoundingBox, CubeBoundingBox;

Rectangle ExitButton, InputButton, SettingsButton, ScoreBoard, PlayButton;

Font HelloHeadline;

Music GladosMusicSelectionVoice;

Vector2 vect;

Texture2D BackgroundImageTexture;

Image BackgroundImage;
Image WindowIcon;

Color TERMINALBROWN = { 99, 59, 7, 255 };
Color TERMINALOUTLINEYELLOW = { 119, 91, 19, 255 };


int WindowWidth = 1920;
int WindowHeight = 1080;


float MainMenuButtonWidth = 400;
float MainMenuButtonHeight = 50;
float spacing = 20;
float FPS = 120.0;

float gravity;

int shouldExit = 0;
int layers = 2;

int delayFrame = 0;
int delay = 3;
