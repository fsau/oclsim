/*
Copyright (C) 2021 Franco Sauvisky
oclsim.c is part of oclsim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

typedef struct _oclsim_context
{
  cl_platform_id platform;
  cl_device_id device;
  cl_context context;
} oclCon_s;

typedef struct _oclsim_system
{
  cl_program *program;
  cl_command_queue *queue;
  cl_kernel *kernels;
  cl_mem *buffers;
  cl_event *events;
} oclSys_s;

oclCon
oclsim_init(int plati, int devi)
{
  oclCon newcon = malloc(sizeof(oclCon_s));
  cl_int err=0;

  size_t plats_n;
  err = clGetPlatformIDs(0,NULL,&plats_n);
  cl_platform_id platforms[plats_n];
  CHKERROR(err,"Couldn't get platforms number");
  CHKERROR(-((plati<0)||(plati>=plats_n)), "Selected platform is out of range");

	err = clGetPlatformIDs(plats_n, platforms, NULL);
  CHKERROR(err,"Couldn't idenfity platforms");

  newcon->platform = platforms[plati];

  char platname[100];
  err = clGetPlatformInfo(newcon->platform,CL_PLATFORM_NAME,100,platname,NULL);
  CHKERROR(err,"Couldn't get platform name");
  PINFORM("Selected platform: %s", platname);

  size_t devs_n;
  err=clGetDeviceIDs(newcon->platform,CL_DEVICE_TYPE_ALL,0,NULL,&devs_n);
  cl_device_id devices[devs_n];
  err=clGetDeviceIDs(newcon->platform,CL_DEVICE_TYPE_ALL,devs_n,devices,NULL);
  CHKERROR(err,"Couldn't access devices");

  newcon->device = devices[devi];

  // // GPU
  // err = clGetDeviceIDs(newcon->platform, CL_DEVICE_TYPE_GPU, 1,
  //                      &newcon->device, NULL);
  // if(err == CL_DEVICE_NOT_FOUND)
  // {
  //   // CPU
  //   PINFORM(stderr,"USING CPU!\n");
  //   err = clGetDeviceIDs(newcon->platform, CL_DEVICE_TYPE_CPU, 1,
  //                        &newcon->device, NULL);
  // }
  // CHKERROR(err,"Couldn't access devices");

  newcon->context = clCreateContext(NULL, 1, &newcon->device, NULL, NULL, &err);
  CHKERROR(err,"Couldn't create context");

  return newcon;
}

int
oclsim_new_sys(oclCon con, char *src_file, oclSys *sys)
{
    oclSys_s new_sys = malloc(sizeof(oclSys_s));
}

int
oclsim_enqueue(oclSys sys)
{

}

int
oclsim_get_data(oclSys sys, void *dataptr)
{

}

int
oclsim_destroy_con(olcCon con)
{
  free(con);
}

int
oclsim_destroy_sys(olcSys sys)
{
  free(sys);
}

int
oclsim_print_devices(void)
{

}
