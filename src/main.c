/*
Copyright (C) 2021 Franco Sauvisky
main.c is part of oclsim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "oclsim.h"
#include "ising_defs.h"

#include <stdio.h>
#include <time.h>
#include <math.h>

void
main(void)
{
  float beta = 1/2;

  oclSys ising = cls_new_sys(2,0);
  cls_load_sys_from_file(ising, "./ising.cl", sizeof(struct state_s));

  struct init_arg_s init_arg;
  struct main_arg_s main_arg;
  struct meas_arg_s meas_arg = {.idiv = 1};
  dims_i init_dims = {.dim=1,.global=GLOBAL_1D_RANGE,.local=LOCAL_1D_RANGE};
  dims_i main_dims = {.dim=2,.global=GLOBAL_2D_RANGE,.local=LOCAL_2D_RANGE};
  dims_i meas_dims = {.dim=1,.global=GLOBAL_1D_RANGE,.local=LOCAL_1D_RANGE};

  uint rseed = (uint)time(NULL);
	srand(rseed);
  cl_uint2 new_seed;
  new_seed.x = rand();
  new_seed.y = rand();
  init_arg.rseed = new_seed;

  for(int i = 0; i < PROB_L; i++)
  {
    main_arg.probs[i] = (cl_ulong)CL_UINT_MAX * PROB_MAX * ((i <= PROB_Z)? 1 : exp(-beta*(i-PROB_Z)));
  }

  cls_set_init_arg(ising, &init_arg, sizeof(init_arg), init_dims);
  cls_set_main_arg(ising, &main_arg, sizeof(main_arg), 1, main_dims);
  cls_set_meas_arg(ising, &meas_arg, sizeof(meas_arg), sizeof(state_t)*LOCAL_1D_LENGTH, sizeof(struct output_s), meas_dims);

  cls_run_init(ising);
  for(int i = 0; i < BUFFLEN; i++)
  {
    cls_run_update(ising);
    cls_run_meas(ising);
  }

  struct output_s *out = malloc(sizeof(struct output_s));
  cls_get_meas(ising, out);
  cls_release_sys(ising);

  for(int i = 0; i < BUFFLEN; i++)
  {
    printf("%f\n", out->mag[i]);
  }
}
