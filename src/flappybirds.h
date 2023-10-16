#ifndef FLAPPYBIRDS_H_
#define FLAPPYBIRDS_H_

#include <stdbool.h>

#include "math.h"
#include "shader.h"

#include "bird.h"
#include "pipes.h"

typedef enum {
  IDLE,
  RUNNING,
  SCORE,
} State;


typedef struct {
  Mat4 projection;
  Bird bird;
  Pipes pipes;
  State state;
} FB;

void FB_init(FB *fb, int width, int height);

void FB_destroy(FB *fb);

void FB_update(FB *fb, bool pressedKeys[], double dt);

void FB_draw(const FB *fb);

#endif // FLAPPYBIRDS_H_
