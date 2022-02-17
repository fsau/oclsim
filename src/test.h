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

#define VECLEN 512

#define GLOBAL_1D_LENGTH (VECLEN*VECLEN)
#define GLOBAL_1D_RANGE {VECLEN*VECLEN,0,0}
#define GLOBAL_2D_RANGE {VECLEN,VECLEN,0}

#define LOCAL_2D_WIDTH 16
#define LOCAL_1D_LENGTH (LOCAL_2D_WIDTH*LOCAL_2D_WIDTH)
#define LOCAL_1D_RANGE {LOCAL_1D_LENGTH,0,0}
#define LOCAL_2D_RANGE {LOCAL_2D_WIDTH,LOCAL_2D_WIDTH,0}

#define ISING_DIMS_1D ((dims_i){.dim=1,.global=GLOBAL_1D_RANGE,.local=LOCAL_1D_RANGE})
#define ISING_DIMS_2D ((dims_i){.dim=2,.global=GLOBAL_2D_RANGE,.local=LOCAL_2D_RANGE})

// Macros:
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)>(y)?(y):(x))
#define IND(x,y) ( (x)*VECLEN + (y) ) // 2D xy -> 1D vector
#define RIND(x,y) ( ((x)%VECLEN)*VECLEN + ((y)%VECLEN) ) // rectangular
#define TIND(x,y) ( ((x)*VECLEN + (y))%VECLEN ) // torus
#define GETI(c,x,y) ( *(y) = ((c)-(*(x)=(c)/VECLEN)) ); // 1D vector -> 2D xy

// Typedefs:
#ifdef __OPENCL_VERSION__
typedef double2 state_t;
typedef int int_t;
typedef uint uint_t;
typedef float float_t;
#else
typedef cl_double2 state_t;
typedef cl_int int_t;
typedef cl_uint uint_t;
typedef cl_float float_t;
typedef cl_uint2 rand_st;
#endif

typedef struct state_s* state_p;
typedef struct output_s* output_p;
typedef struct init_arg_s* init_arg_p;
typedef struct main_arg_s* main_arg_p;
typedef struct meas_arg_s* meas_arg_p;

// Structs:
struct output_s
{
  float_t abs[VECLEN*VECLEN];
  int_t lastc[VECLEN*VECLEN];
};

struct state_s
{
  state_t states[VECLEN*VECLEN];
  state_t z0[VECLEN*VECLEN];
  int_t lastc[VECLEN*VECLEN];
};

struct init_arg_s
{
  state_t z0, dz;
};

struct main_arg_s
{
  int_t und; // can't be empty (yet)
};

struct meas_arg_s
{
  int_t und;
};

#endif
