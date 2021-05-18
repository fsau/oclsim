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

oclCon oclsim_init(int dev);
oclSys oclsim_new_sys(oclCon con, char *src_file);
int oclsim_set_arg(oclSys sys, void *argptr, size_t size);
int oclsim_enqueue(oclSys sys);
int oclsim_get_data(oclSys sys, void *dataptr, size_t size);
void oclsim_destroy_con(olcCon con);
void oclsim_destroy_sys(olcSys sys);
int oclsim_print_devices(void);

#endif
