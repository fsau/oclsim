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

#define PINFORM(x, ...) {fprintf(stderr, (x), ##__VA_ARGS__)}
#define PERROR(x) {fprintf(stderr,\
"Error on line %d, file %s (function %s):\n%s",\
__LINE__, __FILE__, __func__, (x))}
#define CHKERROR(flag,str) {if(flag){PERROR(str),exit(1)}}

struct oclsim_con
{
  cl_platform_id platform;
  cl_device_id device;
  cl_context context;
  cl_command_queue queue;
};

struct oclsim_sys
{
  cl_program program;
  cl_kernel *kernels;
  cl_mem *buffers;
  cl_event *events;
};

oclCon
oclsim_init(int plati, int devi)
{
  oclCon newcon = malloc(sizeof(struct oclsim_con));
  cl_int err=0;
  size_t plats_n;

  err = clGetPlatformIDs(0,NULL,&plats_n);
  cl_platform_id platforms[plats_n];
  CHKERROR((plati<0)||(plati>=plats_n), "Selected platform is out of range");

	err = clGetPlatformIDs(plats_n, platforms, NULL);
  CHKERROR(err<0,"Couldn't idenfity platforms");

  newcon->platform = platforms[plati];

  char platname[100];
  err = clGetPlatformInfo(newcon->platform,CL_PLATFORM_NAME,100,platname,NULL);
  CHKERROR(err<0,"Couldn't get platform name");
  PINFORM("Selected platform: %s", platname);

  size_t devs_n;
  err=clGetDeviceIDs(newcon->platform,CL_DEVICE_TYPE_ALL,0,NULL,&devs_n);

  cl_device_id devices[devs_n];
  err=clGetDeviceIDs(newcon->platform,CL_DEVICE_TYPE_ALL,devs_n,devices,NULL);
  CHKERROR(err<0,"Couldn't identify device");
  CHKERROR((plati<0)||(plati>=plats_n),"Selected platform is out of range");

  newcon->device = devices[devi];
  newcon->context = clCreateContext(NULL, 1, &newcon->device, NULL, NULL, &err);
  CHKERROR(err<0,"Couldn't create context");

  newcon->queue = clCreateCommandQueueWithProperties(context, device,
                  (const cl_queue_properties[])
                  {CL_QUEUE_PROPERTIES,CL_QUEUE_PROFILING_ENABLE, 0}, &err);

  return newcon;
}

oclSys
oclsim_new_sys(oclCon con, char *src_file)
{
  oclSys new_sys = malloc(sizeof(struct oclsim_sys));

  // copy file to buffer
  FILE *src_fh = fopen(src_file, "r");
  char *src_buff;
  size_t src_size;
  cl_int err=0;
  CHKERROR(src_fh==NULL, "Couldn't open .cl src file");

  fseek(src_fh, 0, SEEK_END);
  src_size = ftell(program_handle);
  rewind(src_fh);

  src_buff = (char*)malloc(src_size + 1);
  src_buff[src_size] = '\0';
  fread(src_buff, sizeof(char), src_size, src_fh);
  fclose(src_fh);

  new_sys->program = clCreateProgramWithSource(ctx, 1,(const char**)&src_buff,
                                               &src_size, &err);
  CHKERROR(err<0, "Couldn't create program");
  free(src_buff);

  err = clBuildProgram(new_sys->program, 0, NULL, "-I.", NULL, NULL);
  if(err < 0)
  {
    size_t log_size;
    clGetProgramBuildInfo(new_sys->program, new_sys->device,
                         CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    char *log_buff = (char*) malloc(log_size + 1);
    log_buff[log_size] = '\0';
    clGetProgramBuildInfo(new_sys->program, new_sys->device,
                          CL_PROGRAM_BUILD_LOG, log_size + 1, log_buff, NULL);
    printf("%s\n", log_buff);
    free(log_buff);
    exit(1);
  }

  return new_sys;
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
  clReleaseContext(con->context);
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
