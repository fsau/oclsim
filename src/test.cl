#include "test.h"

kernel void
init_k(global struct state_s *output,
       constant struct init_arg_s *arg)
{
  size_t i = get_global_id(0);

  output->states[i] = arg->x0 + i*arg->dx;
  if(i==0)
  {
    output->counter=1;
  }
}

kernel void
update_k(global struct state_s *output,
         global struct state_s *input,
         local void *lc_skpd,
         constant struct main_arg_s *arg)
{
  size_t i = get_global_id(0);

  state_t in = input->states[i];
  output->states[i] = in+in;

  if(i==0)
  {
    output->counter = input->counter+1;
  }
}

kernel void
measure_k(global struct output_s *output,
          global struct state_s *input,
          local void* lc_skpd,
          constant struct meas_arg_s *arg)
{
  size_t i = get_global_id(0);
  output->out[i] = input->states[i];

  if(i==0)
  {
    output->counter = input->counter;
  }
}
