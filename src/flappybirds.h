#ifndef FLAPPYBIRDS_H_
#define FLAPPYBIRDS_H_

#include <stdbool.h>

#include "math.h"
#include "shader.h"

#include "bird.h"
#include "pipes.h"

#define N_PIPES 3

typedef enum {
  IDLE,
  RUNNING,
  DEAD,
} State;

typedef struct {
  Mat4 projection;
  Bird bird;
  Pipes pipes[N_PIPES];
  State state;
  // TODO: pb_score
} FB;

void FB_init(FB *fb, int width, int height);

void FB_destroy(FB *fb);

void FB_update(FB *fb, bool pressedKeys[], double dt);

void FB_draw(const FB *fb);

#endif // FLAPPYBIRDS_H_
