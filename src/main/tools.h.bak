#pragma once

#include "math.h"
#include "project_config.h"

#define RAD2DEG	57.2957795130823208767
#define DEG2RAD	0.01745329251994329576

#define ON 1
#define OFF 0

#define UP_BUTTON 1
#define DOWN_BUTTON 2
#define ENTER_BUTTON 3

#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4

int lead_to_degree_borders(int _num);
int lead_to_borders(int max, int min, int _num);
bool is_in_the_angle_borders(int max, int min, int _num);
bool is_in_the_borders(int max, int min, int num);
int constrain(int max, int min, int _num);
float constrainf(float max, float min, float _num);

struct point
{
  int x;
  int y;
  int angle;
  uint8_t significanse;
  uint16_t distance;
};

struct line
{
  double a;
  double c;
};

struct polar_vector
{
  int angle;
  int length;
};

enum trajectory_type
{
  short_trajectory,
  long_trajectory
};

