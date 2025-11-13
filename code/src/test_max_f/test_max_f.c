//+author:Esteban Bustamante<ebustamante896@gmail.com>
//+date: 2025-11-01

#include "lib_fxp.h"
#include <stdio.h>
#include "assert.h"


#define N_BITS 32


void set_frac_dec_max();
void set_frac_n_bits();

int main()
{
  printf("==================================================STARTING TEST_MAX_F test==================================================\n");

  set_frac_dec_max();
  printf("Max float with %d fractional bits: %f",N_BITS - fxp_get_whole_bits(),fxp_get_max_f());
  set_frac_n_bits();  				 
  printf("\n\n");
  printf("Max float with %d fractional bits: %f",N_BITS - fxp_get_whole_bits(),fxp_get_max_f());
  printf("\n\n");
  printf("==================================================END TEST_MAX_F test==================================================\n");
  return 0;
}


void set_frac_dec_max()
{
  printf("DECIMAL RESOLUTION %d\n", fxp_get_frac_max_dec());

  fxp_set_auto_frac_max_dec();
  //  fxp_set_frac_max_dec(9999);
  printf("DECIMAL RESOLUTION AFTER SETTING %d\n", fxp_get_frac_max_dec());

  return;
}   


void set_frac_n_bits()
{
  fxp_set_frac_bits(6);
  return;
}
