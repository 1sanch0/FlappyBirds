#include "flappybirds.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

void FB_init(FB *fb, int width, int height) {
  orthographic(&fb->projection, 0, width, height, 0, -1.0, 1.0);
  fb->state = IDLE;
}

void FB_update(FB *fb, bool pressedKeys[], double dt) {
  fb->bird.x = dt;
  if (pressedKeys[GLFW_KEY_SPACE] == GLFW_PRESS) {
    fb->bird.x *= 100;
  }
}

void FB_draw(const FB *fb) {
  printf("x: %f\n", fb->bird.x);
}
