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

#define PINFORM(x, ...) fprintf(stderr, (x), ##__VA_ARGS__)
#define PERROR(x) fprintf(stderr,\
"Error on line %d, file %s (function %s):\n%s",\
__LINE__, __FILE__, __func__, (x))
#define CHKERROR(flag,str) (if((flag)<0){PERROR(str),exit(1)})

typedef struct _oclsim_context* oclCon;
typedef struct _oclsim_system* oclSys;

int oclsim_init(int dev, oclCon *con);
int oclsim_new_sys(oclCon con, char *src_file, oclSys *sys);
int oclsim_enqueue(oclSys sys);
int oclsim_get_data(oclSys sys, void *dataptr);
int oclsim_destroy_con(olcCon con);
int oclsim_destroy_sys(olcSys sys);
int oclsim_print_devices(void);

#endif
