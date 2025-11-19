//+author:Esteban Bustamante<ebustamante896@gmail.com>
//+date: 2025-11-19

#include "fir_filter.h"
#include <stdio.h>
#include <string.h>

void print_help()
{
  printf("Software FIR Filter - UTN Facultad Regional La Rioja\nCopyright (C) 2025  Esteban Bustamante \n\nUsage:\nfir_filter --N_COEFFS=<n_coeffs> --NB_FRAC=<nb_frac>\n\nOptions: \n\n-h:\t\t\t\t\t\tPrints this screen and returns.\n--N_COEFFS=<n_coeffs>\t\t\t\tThe size of the filter determined by <n_coeffs>.\n--NB_FRAC=<nb_frac>\t\t\t\tNumber <nb_frac> of fractional bits of fixed point representation.");
}

int main(int argc, char *argv[])
{
  if(argc < 2)
    {
      printf("No arguments given.\n");
      print_help(); //Printing help output if only given the program name. This is the same as writing fir_filter -h
      return 0;
    }else if (argc == 2 && !strcmp(argv[1],"-h"))
    {
      print_help(); //Printing help if given -h argument.
      return 0;
    }

  return 0;
}
