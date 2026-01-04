#include "lib_fxp.h"
#include <stdio.h>

int main()
{
  printf("Default N_INT: %d\n",  fxp_get_whole_bits());
  printf("Default N_FRAC: %d\n",  fxp_get_frac_bits());

  //  fxp_set_whole_bits(1);
  fxp_set_frac_bits(31);
  printf("==================================================SETTING NEW N_INT and N_FRAC==================================================\n");
  printf("N_INT: %d\n",  fxp_get_whole_bits());
  printf("N_FRAC: %d\n",  fxp_get_frac_bits());

  printf("Max decimal fractional representable by actual N_BITS: %d\n", fxp_get_frac_max_dec() );
  
  int fxp_normal =  fxp_dec(0,5000);

  float value = 0.5f;

  int fxp_from_float = f2fxp(value);

  print_fxp(fxp_normal);
  printf("\n");
  print_fxp(fxp_from_float);

  return 0;

}
