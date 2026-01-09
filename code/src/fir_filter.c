//+author:Esteban Bustamante<ebustamante896@gmail.com>
//+date: 2025-11-19

#include "fir_filter.h"
#include "lib_fxp.h"

/**
 * @file fir_filter.c
 * @brief Filtro Definido en Software
 */

int32_t input_buffer[MAX_INPUT_BUFFER_SIZE];// array to hold input samples
int fxp_coeffs[MAX_N_TAPS];
int samples = 80;
int nb_frac = 31;
int filter_length = 0;

void print_help()
{
    printf("Software FIR Filter - UTN Facultad Regional La Rioja\nCopyright (C) 2025  Esteban Bustamante \n\nUsage:\nfir_filter_utn [--NB_FRAC=<nb_frac>] [--samples=<samples_in_parallel>] -fc=<coefficient_filename>\n\nOptions: \n\n-h:\t\t\t\t\t\tPrints this screen and returns.\n--NB_FRAC=<nb_frac>\t\t\t\tNumber <nb_frac> of fractional bits of fixed point representation. Default value is 30\n--samples=<samples_in_parallel>\t\t\tThe number of samples processed in parallel per loop. Default value is 80\n-fc=<coefficient_filename>\t\t\tThe filter coefficient filename. The format should be float coefficients separated by newlines. See further information in the documentation.");
}

// FIR init
void firFixedInit( void )
{
    memset( input_buffer, 0, sizeof(input_buffer));
}

// FIR filter function
void firFixed( int *coeffs, int *input, int *output,
	       int length, int filterLength )
{
    int acc;     // accumulator for MACs
    int *coeffp; // pointer to coefficients
    int *inputp; // pointer to input samples
    int n;
    int k;
 
    // put the new samples at the high end of the buffer
    memcpy( &input_buffer[filterLength - 1], input,
            length * sizeof(int) );
 
    // apply the filter to each input sample
    for ( n = 0; n < length; n++ ) {
        // calculate output n
	coeffp = coeffs;
        inputp = &input_buffer[filterLength - 1 + n];
        // load rounding constant FIXME
	//        acc = 1 << 14;
        // perform the multiply-accumulate
        for ( k = 0; k < filterLength; k++ ) {
            acc = fxp_add(acc, fxp_mul(*coeffp++, *inputp--));
        }
        /* // saturate the result FIXME*/
        /* if ( acc > 0x3fffffff ) { */
        /*     acc = 0x3fffffff; */
        /* } else if ( acc < -0x40000000 ) { */
        /*     acc = -0x40000000; */
        /* } */
        // convert from Q30 to Q15 - which also applied rounding
	//        output[n] = (int16_t)(acc >> 15);
        output[n] = acc;
	acc = 0;
    }
 
    // shift input samples back in time for next time
    memmove( &input_buffer[0], &input_buffer[length],
	     (filterLength - 1) * sizeof(int) );
 
}

uint8_t coefficients_init(FILE *coeff_file, int * fxp_coeffs)
{
    status_t status = STATUS_OK;
    float coeff_f = 0.f;

    memset( fxp_coeffs, 0, sizeof(int) * MAX_N_TAPS); //initializing the coefficients in 0

    if (coeff_file == NULL) {
	printf("Error opening file\\n");
	status = STATUS_NULL;
	return status;
    }

    while (fscanf(coeff_file, "%f", &coeff_f) == 1) {
	fxp_coeffs[filter_length] = f2fxp(coeff_f);//converting float to fxp
	filter_length++;
    }

    return status;
}

int main(int argc, char *argv[])
{
    status_t status = STATUS_OK;

    //----------ARGUMENT PARSER--------------//
    char coeff_file_s[MAX_FILENAME_SIZE];  
    char input_file_s[MAX_FILENAME_SIZE];

    char * tmp_fc      = NULL;
    char * tmp_samples = NULL;
    char * tmp_nb_frac = NULL;

    memset(coeff_file_s, 0, sizeof(coeff_file_s));//Initializing the filename
    memset(input_file_s, 0, sizeof(input_file_s));//Initializing the filename  

    if(argc < 2)
	{
	    printf("No arguments given.\n");
	    print_help(); //Printing help output if only given the program name. This is the same as writing fir_filter -h
	    return 0;
	}else if (argc == 2 && !strcmp(argv[1],"-h"))
	{
	    print_help(); //Printing help if given -h argument.
	    return 0;
	} else //checking for significative flags
	{
	    for (int i = 0; i < argc; i++)
		{
		    if(tmp_fc == NULL)
			tmp_fc      = strstr(argv[i], "-fc="); //Checking for file of coefficients

		    if(tmp_samples == NULL)
			tmp_samples = strstr(argv[i], "--samples="); //Checking for file of coefficients

		    if(tmp_nb_frac == NULL)
			tmp_nb_frac = strstr(argv[i], "--NB_FRAC="); //Checking for file of coefficients

		    if(i == argc-1)
			memmove(input_file_s, argv[i], strlen(argv[i]));
		    
		}

	    if(tmp_fc == NULL )
		{
		    perror("Filter coefficients file not given.\n");
		    return STATUS_ERROR;
		} else
		{
		    memmove(coeff_file_s, tmp_fc+4, strlen(tmp_fc)-4);
		}

	    if(tmp_samples != NULL )
		samples = atoi(tmp_samples+10);
    
	    if(tmp_nb_frac != NULL )
		nb_frac = atoi(tmp_nb_frac+10);

	}


    FILE * coeff_file = fopen(coeff_file_s,"r"); //Open file in main and pass it as reference to coefficients_init
    status = coefficients_init(coeff_file, fxp_coeffs);

    printf("\nConfig for Filter\n\nNumber of samples: %d, Fractional bits: %d ", samples, nb_frac);
    fclose(coeff_file);

    //--------------------------------------------//

    //---------------FILTER APPLYING----- --------//

    int size;
    int input[samples];
    int output[samples];
    FILE   *in_fid;
    FILE   *out_fid;
 
    // open the input waveform file
    //    in_fid = fopen( "input.pcm", "rb" );
    in_fid = fopen( input_file_s, "rb" );
    if ( in_fid == NULL )
	{
	    printf("\ncouldn't open input file\n");
	    return STATUS_ERROR;
	}
 
    // open the output waveform file
    out_fid = fopen( "out/outputFixed.pcm", "wb" );
    if ( out_fid == 0 ) {
        printf("\ncouldn't open output file\n");
        exit(EXIT_FAILURE);
    }
 
    // initialize the filter
    firFixedInit();
 
    // process all of the samples
    do {
        // read samples from file
        size = fread( input, sizeof(int), samples, in_fid );
        // perform the filtering
        firFixed( fxp_coeffs, input, output, size, filter_length);
        // Write samples to file
        fwrite( output, sizeof(int), size, out_fid );
    } while ( size != 0 );
 
    fclose( in_fid );
    fclose( out_fid );

    //--------------------------------------------//

    if(status == STATUS_ERROR)
	{
	    perror("GENERIC ERROR\n");
	    return -1;
	} else if(status == STATUS_NULL)
	{
	    perror("NULL ERROR\n");
	    return -1;
	}
    
    return 0;
}
