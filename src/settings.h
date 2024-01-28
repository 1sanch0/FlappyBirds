#ifndef SETTINGS_H_
#define SETTINGS_H_

// Window
#define WIDTH 500
#define HEIGHT 900
#define TITLE "Flappy Birds in C and OpenGL!"
#define RESIZABLE GLFW_FALSE // Do not set to true

// Projection (ortho)
#define LEFT   -(float)WIDTH / 190.0f
#define RIGHT   (float)WIDTH / 190.0f
#define BOTTOM -(float)HEIGHT / 190.0f
#define TOP     (float)HEIGHT / 190.0f
#define NEAR   -1.0
#define FAR     1.0

// Pipes
#define N_PIPES 3

#define PIPE_SPEED 1.4f
#define PIPE_MAX_Y -0.5f
#define PIPE_MIN_Y -5.0f
#define PIPES_VGAP 2.0f   // Top to bottom pipe gap
#define PIPES_HGAP 3.6f   // Horizontal gap between couple of pipes

// Bird
#define JUMP_ACC 5.0f
#define GRAVITY 0.3f


// Background
#define BG_Z -0.2f
#define BG_SCALEX 5.3f
#define BG_SCALEY 5.3f

// Idle message
#define MSG_Z 0.9f
#define MSG_X 0.0f
#define MSG_Y 0.5f
#define MSG_SCALEX 3.0f
#define MSG_SCALEY 3.0f

// Gameover
#define GO_Z 0.9f
#define GO_X 0.0f
#define GO_Y 0.8f
#define GO_SCALEX 3.0f
#define GO_SCALEY 3.0f

#endif // SETTINGS_H_
