#include "flappybirds.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

#include "bird.h"

void FB_init(FB *fb, int width, int height) {
  //orthographic(&fb->projection, -10.f, 10.f, -10.0f * (float)width/(float)height, 10.0f * (float)width/(float)height, -1.0, 1.0);
  orthographic(&fb->projection, 0, width/100, 0, height/100, -1, 1);
  fb->state = IDLE;

  bird_init(&fb->bird, &fb->projection, 3, 3);
}

void FB_destroy(FB *fb) {
  printf("Flappy birds destroyed\n");
  bird_destroy(&fb->bird);
}

void FB_update(FB *fb, bool pressedKeys[], double dt) {
  bird_update(&fb->bird, pressedKeys, dt);
}

void FB_draw(const FB *fb) {
  bird_draw(&fb->bird);
}
