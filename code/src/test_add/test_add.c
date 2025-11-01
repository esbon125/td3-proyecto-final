//+author:Esteban Bustamante<ebustamante896@gmail.com>
//+date: 2025-11-01

#include "lib_fxp.h"
#include <stdio.h>
#include "assert.h"

void set_frac_dec_max();
void set_frac_n_bits();

int main()
{
  printf("==================================================STARTING TEST_ADD test==================================================\n");
  
  int n1, n2, result;
  set_frac_dec_max();
  set_frac_n_bits();  

  n1 = fxp_dec(0,5*1000); //0.5 Always adjust numbers to frac_max_dec
  n2 = fxp_dec(0,25*100); //0.25
  
  printf("SHOWING ADDENDS\n");
  print_fxp(n1);
  printf("\n");
  print_fxp(n2);
  printf("\n\n");

  printf("SHOWING RESULT\n");

  result = fxp_add(n1, n2);
  print_fxp(result);
  printf("\n");  

  assert(result & (0b110 << 28));
  printf("==================================================END TEST: TEST_ADD -> SUCCESS==================================================\n");
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
  fxp_set_frac_bits(31);

  return;
}
