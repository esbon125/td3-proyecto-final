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
  //  printf("Min float representable by actual N_BITS: %f\n", fxp_get_min_f() );
  int fxp_number_bin = fxp_bin(0,5);
  int fxp_number_dec = fxp_dec(0,1320);

  int fxp_number_bin_neg = fxp_bin(0,-5);
  int fxp_number_dec_neg = fxp_dec(0,-5);
  printf("\nNumber created with binary function: %b using printf", fxp_number_bin);
  printf("\nNumber created with decimal function: %b using printf", fxp_number_dec);

  printf("==================================================PRINTING NUMBERS WITH FXP_AUX==================================================\n");
  printf("\n");
  print_fxp_as_bin(fxp_number_bin);
  printf("\n\n");
  print_fxp_as_bin(fxp_number_dec);
  printf("\n\n");  
  print_fxp_as_bin(fxp_number_bin_neg);
  printf("\n\n");
  print_fxp_as_bin(fxp_number_dec_neg);
  printf("\n");
  print_fxp(fxp_number_bin);
  printf("\n\n");
  print_fxp(fxp_number_dec);
  printf("\n\n");  
  

  return 0;
}
