#include "flappybirds.h"

#include <stdio.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>

#include "bird.h"

#include "sprite.h"

static float time = 0;
static Sprite background = {};
static Sprite message = {};
static Sprite gameover = {};
// TODO: score (gonna need its own ting)

static bool testCollisions(const FB *fb);

void FB_init(FB *fb, int width, int height) {
  Mat4 tmp1, tmp2;

  float hwidth = (float)width / 190.0f;
  float hheight = (float)height / 190.0f;

  orthographic(&fb->projection, -hwidth, hwidth, -hheight, hheight, -1, 1);
  fb->state = IDLE;

  bird_init(&fb->bird, &fb->projection, 0);
  for (int i = 0; i < N_PIPES; i++)
    pipes_init(&fb->pipes[i], &fb->projection, i + i * 0.5f, -3, 2);

  time = 0;

  sprite_init(&background, &fb->projection, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/background-day.png", -0.2, false);
  scale(&background.model, 5.3, 5.3);
  useShader(background.shader);
  setMatrix4f(background.shader, "model", &background.model);

  sprite_init(&message, &fb->projection, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/message.png", 0.9, false);
  translation(&tmp1, 0, 0.5f);
  scale(&tmp2, 3, 3);
  matmul(&tmp1, &tmp2, &message.model);
  useShader(message.shader);
  setMatrix4f(message.shader, "model", &message.model);

  sprite_init(&gameover, &fb->projection, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/gameover.png", 0.9, false);
  translation(&tmp1, 0, 0.8f);
  scale(&tmp2, 3, 3);
  matmul(&tmp1, &tmp2, &gameover.model);
  useShader(gameover.shader);
  setMatrix4f(gameover.shader, "model", &gameover.model);
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

  bool collision = testCollisions(fb);
  printf("[%d] collision: %d\n", fb->state, collision);

  // ONLY WHILE DEVELOPING (TODO)
  if (pressedKeys[GLFW_KEY_I])
    fb->state = IDLE;
  if (pressedKeys[GLFW_KEY_R])
    fb->state = RUNNING;
  if (pressedKeys[GLFW_KEY_M])
    fb->state = DEAD;
  // END ONLY WHILE DEV (TODO)

  if (fb->state == IDLE) {
    fb->bird.y = 0.23f * sin(3 * time);
  }

  bird_update(&fb->bird, pressedKeys, dt);

  for (int i = 0; i < N_PIPES; i++)
    pipes_update(&fb->pipes[i], pressedKeys, dt);
}

void FB_draw(const FB *fb) {
  sprite_draw(&background);

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

  for (int i = 0; i < N_PIPES; i++) {
    float topPipeBottom = fb->pipes[i].top.y - pipe_ar * 0.5f;
    float bottomPipeTop = fb->pipes[i].bottom.y + pipe_ar * 0.5f;

    if (fb->pipes[i].top.x >= -1.0f && fb->pipes[i].top.x <= 1.0f)
      if (birdTop >= topPipeBottom || birdBottom <= bottomPipeTop)
        return true;
  }

  return false;
}
