#include "ising_defs.h"

kernel void
init(global state_p output,
     constant init_arg_p arg)
{

}

kernel void
update(global state_p output,
       global state_p input,
       local void* lc_skpd,
       constant main_arg_p arg)
{

}

kernel void
measure(global output_p output,
        global state_p input,
        local void* lc_skpd;
        constant meas_arg_p arg)
{

}
