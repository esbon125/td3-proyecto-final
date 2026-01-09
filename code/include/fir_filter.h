//description: Header file for FIR filter
//author: Esteban Bustamante
//date: 2025-11-12

/**
 * @file fir_filter.h
 * @brief Macros y funciones para un software-defined Filtro FIR en punto fijo.
 */

/**
 * @mainpage Filtro FIR en Punto Fijo
 *
 * @section intro Introducción
 * Este proyecto se presenta como parte práctica del trabajo final de la asignatura Técnicas Digitales III. Consiste en un Filtro FIR definido en software, haciendo uso del lenguaje C. Utiliza un buffer de entrada para lograr el sincronismo entre el filtro y las muestras de entrada. Actualmente tanto la salida como la entrada serán escritos a archivos de datos en formato PCM (.pcm), que simplifica su procesamiento garantizando el uso de un estándar para generar los gráficos correspondientes de las señales de entrada y salida. Se ha generado una interfaz gráfica en Python que facilite su uso, pero también puede ser utilizado desde línea de comandos con su respectiva CLI. Junto al binario se entrega también una demo lista para correr tanto en GUI como en CLI(Ver @ref demo "Demostración").
 * 
 *
 * @section features Características
 * - Programa simple en C basado en la librería FXP 
 * - Configurable en Número de bits, truncado/redondeado, saturado/overflow
 *
 * @section demo Demostración
 * 
 * @see https://github.com/rsaavedraf/fxp
 */
// una interfaz USB para una conexión a algún dispositivo muestreador que entregue las muestras de entrada. 

#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Error máximo permitido en aserciones y verificaciones.
 *
 * Este valor define la tolerancia utilizada para comparar resultados
 * numéricos en pruebas, aserciones y chequeos de precisión.
 */
#define DELTA_ERROR 1e-4f

/**
 * @brief Número de bits fraccionales.
 *
 * Indica cuántos bits del total se utilizan para representar
 * la parte fraccionaria en un formato de punto fijo.
 */
#define NB_FRAC     31

/**
 * @brief Número total de bits.
 *
 * Define el ancho total de palabra utilizado en la representación
 * numérica (por ejemplo, 32 bits).
 */
#define NB          32

/**
 * @brief Número de bits enteros.
 *
 * Se calcula como la diferencia entre el número total de bits
 * y el número de bits fraccionales.
 */
#define NB_INT      (NB - NB_FRAC)

/**
 * @brief Número máximo de muestras de entrada procesables en un solo ciclo.
 *
 * Limita la cantidad de muestras que pueden ser procesadas
 * en un único bucle de procesamiento.
 */
#define MAX_INPUT_LEN  256

/**
 * @brief Número máximo de coeficientes (taps) soportados.
 *
 * Define el tamaño máximo del filtro, expresado como el número
 * de coeficientes utilizados.
 */
#define MAX_N_TAPS  256

/**
 * @brief Tamaño máximo del buffer de muestras de entrada.
 *
 * Este tamaño contempla el solapamiento necesario entre bloques
 * de entrada y la cantidad de coeficientes del filtro.
 */
#define MAX_INPUT_BUFFER_SIZE    (MAX_N_TAPS + MAX_INPUT_LEN - 1)

/**
 * @brief Tamaño máximo para cadenas de nombre de archivo.
 *
 * Define la longitud máxima permitida para almacenar rutas
 * o nombres de archivos.
 */
#define MAX_FILENAME_SIZE   256

/**
 * @brief Códigos de estado de retorno.
 *
 * Este enumerado define los posibles estados que pueden
 * devolver las funciones del sistema o biblioteca.
 */
typedef enum status_t {
  /** Error genérico */
  STATUS_ERROR = -1,

  /** Ejecución correcta */
  STATUS_OK = 0,

  /** Puntero nulo u objeto no inicializado */
  STATUS_NULL = 1
} status_t;

/**
 * @brief      Función de filtro FIR, donde se calcula la salida para una cantidad de muestras,
 *             utilizando las muestras de entrada y los coeficientes del filtro.
 *
 * @param[in]      coeffs  puntero al arreglo de coeficientes
 *
 * @param[in]      input   puntero a donde se almacenan las nuevas muestras de entrada
 *
 * @param[out]     output  puntero al arreglo donde se almacenará la salida calculada
 *
 * @param[in]      length  cantidad de muestras a procesar en paralelo
 *
 * @param[in]      filterLength  número de taps (coeficientes) del filtro
 */
void firFixed(int * coeffs, int * input, int * output,int length, int filterLength );


#endif /* FIR_FILTER_H */
