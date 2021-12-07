#include "test.h"

kernel void
init_k(global struct state_s *output,
       constant struct init_arg_s *arg)
{
  size_t i = get_global_id(0),
         j = get_global_id(1);

}

kernel void
update_k(global struct state_s *output,
         global struct state_s *input,
         local void *lc_skpd,
         constant struct main_arg_s *arg)
{
  size_t i = get_global_id(0),
         j = get_global_id(1);

}

kernel void
measure_k(global struct output_s *output,
          global struct state_s *input,
          local void* lc_skpd,
          constant struct meas_arg_s *arg)
{
  size_t i = get_global_id(0),
         i_l = get_local_id(0),
         i_T = get_local_size(0);

}
