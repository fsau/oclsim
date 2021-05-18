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

#ifdef __OPENCL_VERSION__
typedef char state_t;
typedef char4 state_v;
typedef float float_t;
typedef int int_t;
#else
typedef cl_char state_t;
typedef cl_char4 state_v;
typedef cl_float float_t;
typedef cl_int int_t;
#endif

#define SIZEX 64
#define SIZEY 64
#define VECLEN (SIZEX*SIZEY)
#define BUFFLEN 1024

struct ising_measure
{
  float_t a;
};

struct ising_data
{
  state_t data[BUFFLEN*VECLEN];
  struct ising_measure measure[BUFFLEN];
  int_t rseed[VECLEN];
  int_t counter;
};

struct ising_arg
{
  float_t beta;
  int_t rseed;
};

#endif
