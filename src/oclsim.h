/*
Copyright (C) 2021 Franco Sauvisky
oclsim.h is part of oclsim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef OCLSIM_HEADER_BLOCK
#define OCLSIM_HEADER_BLOCK

// kernel void init_k(void* output, void* arg)
#define INIT_K_NAME "init"
// kernel void update_k(void* output, void* input, void* local, void* arg)
#define MAIN_K_NAME "update"
// kernel void measure_k(void* output, void* input, void* local, void* arg)
#define MEASURE_K_NAME "measure"

typedef struct oclsim_sys* oclSys;

typedef struct _dims_i
{
  size_t dim; // run dimensions
  size_t global[3]; // global range
  size_t local[3]; // local range
} dims_i;

// void ocls_print_devices(void);
oclSys cls_new_sys(int plat_i, int dev_i);

void cls_load_src_file(oclSys sys, char* src_filename, size_t states_s);
void cls_load_src_str(oclSys sys, char* src_str, size_t states_s);

void cls_set_init_arg(oclSys sys, void* arg, size_t arg_s, dims_i dims);
void cls_set_main_arg(oclSys sys, void* arg, size_t arg_s, size_t local_s, dims_i dims);
void cls_set_meas_arg(oclSys sys, void* arg, size_t arg_s, size_t local_s, size_t meas_s, dims_i dims);

void cls_run_init(oclSys sys);
void cls_run_main(oclSys sys);
void cls_run_meas(oclSys sys);

void oclsim_get_meas(oclSys sys, void *out, size_t meas_s);

void oclsim_destroy_sys(oclSys sys);

#endif
