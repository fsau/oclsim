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
  float beta = 1.5;

  oclSys ising = cls_new_sys(1,0);
  cls_load_sys_from_file(ising, "./ising.cl", sizeof(struct state_s));

  struct init_arg_s init_arg;
  struct main_arg_s main_arg;
  struct meas_arg_s meas_arg = {.idiv = 1};

  uint rseed = (uint)time(NULL);
	srand(rseed);
  cl_uint new_seed = rand();
  init_arg.rseed = new_seed;

  for(int i = 0; i < PROB_L; i++)
  {
    main_arg.probs[i] = (cl_ulong)CL_UINT_MAX * PROB_MAX * ((i <= PROB_Z)? 1 : exp(-beta*(i-PROB_Z)));
  }

  cls_set_init_arg(ising, &init_arg, sizeof(init_arg), ISING_DIMS_2D);
  cls_set_main_arg(ising, &main_arg, sizeof(main_arg), 1, ISING_DIMS_2D);
  cls_set_meas_arg(ising, &meas_arg, sizeof(meas_arg), sizeof(state_t)*LOCAL_1D_LENGTH, sizeof(struct output_s), ISING_DIMS_1D);

  cls_run_init(ising);
  for(int i = 0; i < BUFFLEN; i++)
  {
    cls_run_update(ising);
    cls_run_meas(ising);
  }

  struct output_s *out = malloc(sizeof(struct output_s));
  cls_get_meas(ising, out);
  cls_release_sys(ising);

	// Print states/data
	printf("\e[1;1H\e[2J"); // clear screen
  for (int k = 0; k < BUFFLEN; k+=1)
  {
    printf("\033[0;0H"); // Move cursor to (0,0)

    // Print states
    printf("┌");
    for(int i = 0; i < 2*SIZEX/OVERSAMPLE+2; i++) printf("─");
    printf("┐\n");

    for (int i = 0; i < SIZEY; i+=OVERSAMPLE)
    {
      printf("│ ");
      for (int j = 0; j < SIZEX; j+=OVERSAMPLE)
      {
        int sum = 0;
        for(int iov = 0; iov < OVERSAMPLE; iov++)
        {
          for(int jov = 0; jov < OVERSAMPLE; jov++)
          {
            sum+=out->states[k][(i+iov)*SIZEX + (j+jov)];
          }
        }
        printf("\033[48;5;%3dm  \e[0m",242 + 8*sum/(OVERSAMPLE*OVERSAMPLE));
      }
      printf("\e[0m │\n");
    }

    printf("└");
    for(int i = 0; i < 2*SIZEX/OVERSAMPLE+2; i++) printf("─");
    printf("┘\n");
  }
}
