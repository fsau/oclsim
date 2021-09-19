/*
Copyright (C) 2021 Franco Sauvisky
ising_defs.h is part of oclsim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef ISING_DEFS_HEADER
#define ISING_DEFS_HEADER

// Definitions & constants:
#define SIZEX 64
#define SIZEY 64
#define NEIGH_N 4
#define BUFFLEN 1024
#define VECLEN (SIZEX*SIZEY)

// Macros:
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)>(y)?(y):(x))
#define IND(x,y) ( (x)*SIZEX + (y) ) // 2D xy -> 1D vector
#define RIND(x,y) ( ((x)%SIZEX)*SIZEX + ((y)%SIZEY) ) // rectangular
#define TIND(x,y) ( ((x)*SIZEX + (y))%VECLEN ) // torus
#define GETI(c,x,y) ( (y) = ((c)-((x)=(c)/SIZEX)) ); // 1D vector -> 2D xy

// Structs:
struct output_s
{
  state_t state[VECLEN*BUFFLEN];
  out_t mag[BUFFLEN];
  out_t en[BUFFLEN];
};

struct state_s
{
  state_t state[VECLEN];
  rand_st randi[VECLEN];
  int_t counter;
};

struct init_arg_s
{
  rand_st rseed;
};

struct main_arg_s
{
  float_t beta;
};

struct meas_arg_s
{
  // empty
};

// Typedefs:
#ifdef __OPENCL_VERSION__
typedef float state_t;
typedef float out_t;
typedef int int_t;
typedef float float_t;
typedef long rand_st;
#else
typedef cl_float state_t;
typedef cl_float out_t;
typedef cl_int int_t;
typedef cl_float float_t;
typedef cl_long rand_st;
#endif

typedef struct state_s* state_p;
typedef struct output_s* output_p;
typedef struct init_arg_s* init_arg_p;
typedef struct main_arg_s* main_arg_p;
typedef struct meas_arg_s* meas_arg_p;

#endif
