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
  bool collision = testCollisions(fb);
  printf("%d\n", collision);

  bird_update(&fb->bird, pressedKeys, dt);
  pipes_update(&fb->pipes, pressedKeys, dt);
}

void FB_draw(const FB *fb) {
  pipes_draw(&fb->pipes);
  bird_draw(&fb->bird);
}

bool testCollisions(const FB *fb) {
  float pipe_ar = 320.0f / 52.0f;

  //for (int i = 0; i < fb->n_pipes; i++) {
  if (fb->pipes.top.x >= -1.0f && fb->pipes.top.x <= 1.0f) { // Bird's and pipe's widths are 1
    if (fb->bird.y + 1.0f / 2.0f >= fb->pipes.top.y - pipe_ar / 2.0f ||
        fb->bird.y - 1.0f / 2.0f <= fb->pipes.bottom.y + pipe_ar / 2.0f) {
      printf("true\n");
      return true;
    }
    //printf("x: %f, y: %f\n", fb->pipes.top.x, fb->pipes.top.y);
  }

  //}
  //       do pixel perfect collision
  //         if coll return 1

  return false;
}
