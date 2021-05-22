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

typedef struct oclsim_con* oclCon;
typedef struct oclsim_sys* oclSys;

void oclsim_print_devices(void);

oclCon oclsim_new_con(int plat_i, int dev_i);
oclSys oclsim_new_sys_from_file(oclCon con, char* src_filename, size_t states_s);
oclSys oclsim_new_sys_from_str(oclCon con, char* src_str, size_t states_s);

void oclsim_set_init(oclSys sys, const char* fname, void* arg, size_t arg_s, cl_uint* dims);
void oclsim_set_main(oclSys sys, const char* fname, void* arg, size_t arg_s, size_t local_s, cl_uint* dims);
void oclsim_set_meas(oclSys sys, const char* fname, void* arg, size_t arg_s, size_t local_s, size_t meas_s, cl_uint* dims);

void oclsim_run_init(oclSys sys);
void oclsim_run_main(oclSys sys);
void oclsim_run_meas(oclSys sys);

void oclsim_get_meas(oclSys sys, void *meas);

void oclsim_destroy_con(oclCon con);
void oclsim_destroy_sys(oclSys sys);

#endif
