#include "lib_fxp.h"
#include <stdio.h>

int main()
{
  printf("Default N_INT: %d\n",  fxp_get_whole_bits());
  printf("Default N_FRAC: %d\n",  fxp_get_frac_bits());

  //fxp_set_whole_bits(1);
  fxp_set_frac_bits(8);
  printf(" N_INT: %d\n",  fxp_get_whole_bits());
  printf(" N_FRAC: %d",  fxp_get_frac_bits());

  int fxp_number = fxp_bin(5,3);
  printf("\nNumber created: %b", fxp_number);
  return 0;
}
