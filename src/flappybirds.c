#include "flappybirds.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>

#include "bird.h"

#include "sprite.h"

#include "settings.h"

#define RANDRANGEF(min, max) (float)rand()/((float)RAND_MAX/(float)(max - min)) + (float)min

static float time = 0;
static Sprite background;
static Sprite message;
static Sprite gameover;
// TODO: score (gonna need its own ting)

static bool testCollisions(const FB *fb);
static void reset(FB *fb);
static bool tap(bool pressedKeys[]);

void FB_init(FB *fb) {
  Mat4 tmp1, tmp2;

  orthographic(&fb->projection, LEFT, RIGHT, BOTTOM, TOP, NEAR, FAR);

  bird_init(&fb->bird, &fb->projection, 0);
  for (int i = 0; i < N_PIPES; i++)
    pipes_init(&fb->pipes[i], &fb->projection, RIGHT + 0.5f + (1.0f + PIPES_HGAP)*i, 0);

  time = 0;

  sprite_init(&background, &fb->projection, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/background-day.png", BG_Z, false);
  scale(&background.model, BG_SCALEX, BG_SCALEY);
  useShader(background.shader);
  setMatrix4f(background.shader, "model", &background.model);

  sprite_init(&message, &fb->projection, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/message.png", MSG_Z, false);
  translation(&tmp1, MSG_X, MSG_Y);
  scale(&tmp2, MSG_SCALEX, MSG_SCALEY);
  matmul(&tmp1, &tmp2, &message.model);
  useShader(message.shader);
  setMatrix4f(message.shader, "model", &message.model);

  sprite_init(&gameover, &fb->projection, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/gameover.png", GO_Z, false);
  translation(&tmp1, GO_X, GO_Y);
  scale(&tmp2, GO_SCALEX, GO_SCALEY);
  matmul(&tmp1, &tmp2, &gameover.model);
  useShader(gameover.shader);
  setMatrix4f(gameover.shader, "model", &gameover.model);

  reset(fb);
}

void FB_destroy(FB *fb) {
  bird_destroy(&fb->bird);
  for (int i = 0; i < N_PIPES; i++)
    pipes_destroy(&fb->pipes[i]);

  sprite_destroy(&background);
  sprite_destroy(&message);
  sprite_destroy(&gameover);
}

void FB_update(FB *fb, bool pressedKeys[], double dt) {
  time += dt;

  if (testCollisions(fb))
    fb->state = DEAD;

  if (fb->state == IDLE) {
    fb->bird.y = 0.23f * sin(3 * time);
    fb->bird.acc = 0;
    if (tap(pressedKeys)) {
      fb->state = RUNNING;
      fb->bird.acc = -JUMP_ACC * dt;
    }
  }

  if (fb->state != DEAD)
    bird_update(&fb->bird, dt);

  if (fb->state == RUNNING) {
    // Bird jump
    if (tap(pressedKeys))
      fb->bird.acc = -JUMP_ACC * dt;

    for (int i = 0; i < N_PIPES; i++)
      pipes_update(&fb->pipes[i], dt);
  }

  if (fb->state == DEAD) {
    if (tap(pressedKeys)) {
      reset(fb);
      fb->state = IDLE;
    }
  }

}

void FB_draw(const FB *fb) {
  sprite_draw(&background);

  if (fb->state != IDLE)
    for (int i = 0; i < N_PIPES; i++)
      pipes_draw(&fb->pipes[i]);

  bird_draw(&fb->bird);

  if (fb->state == IDLE)
    sprite_draw(&message);

  if (fb->state == DEAD)
    sprite_draw(&gameover);
}

bool testCollisions(const FB *fb) {
  float bird_ar = 24.0f / 34.0f;
  float pipe_ar = 320.0f / 52.0f;

  float birdTop = fb->bird.y + bird_ar * 0.5f;
  float birdBottom = fb->bird.y - bird_ar * 0.5f;

  if (birdTop >= TOP) return true;
  if (birdBottom <= BOTTOM) return true;

  for (int i = 0; i < N_PIPES; i++) {
    float topPipeBottom = fb->pipes[i].top.y - pipe_ar * 0.5f;
    float bottomPipeTop = fb->pipes[i].bottom.y + pipe_ar * 0.5f;

    if (fb->pipes[i].top.x >= -1.0f && fb->pipes[i].top.x <= 1.0f)
      if (birdTop >= topPipeBottom || birdBottom <= bottomPipeTop)
        return true;
  }

  return false;
}

void reset(FB *fb) {
  fb->state = IDLE;
  fb->bird.y = 0;

  for (int i = 0; i < N_PIPES; i++) {
    float rn = RANDRANGEF(PIPE_MIN_Y, PIPE_MAX_Y);
    pipes_setX(&fb->pipes[i], RIGHT + 0.5f + (1.0f + PIPES_HGAP)*i);
    pipes_setY(&fb->pipes[i], rn);
  }

}

bool tap(bool pressedKeys[]) {
  static int oneTap = true;

  if (pressedKeys[GLFW_KEY_SPACE] && oneTap) {
    oneTap = false;
    return true;
  }

  if (!pressedKeys[GLFW_KEY_SPACE]) oneTap = true;

  return false;
}
