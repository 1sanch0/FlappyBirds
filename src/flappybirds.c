#include "flappybirds.h"

#include <stdio.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>

#include "bird.h"

static bool testCollisions(const FB *fb);

void FB_init(FB *fb, int width, int height) {
  float hwidth = (float)width / 190.0f;
  float hheight = (float)height / 190.0f;

  orthographic(&fb->projection, -hwidth, hwidth, -hheight, hheight, -1, 1);
  fb->state = IDLE;

  bird_init(&fb->bird, &fb->projection, 0);
  pipes_init(&fb->pipes, &fb->projection, 0, -3, 2);
}

void FB_destroy(FB *fb) {
  bird_destroy(&fb->bird);
  pipes_destroy(&fb->pipes);
}

void FB_update(FB *fb, bool pressedKeys[], double dt) {
  bird_update(&fb->bird, pressedKeys, dt);
  pipes_update(&fb->pipes, pressedKeys, dt);
}

void FB_draw(const FB *fb) {
  bird_draw(&fb->bird);
  pipes_draw(&fb->pipes);
}

bool testCollisions(const FB *fb) {
  return false;
}
