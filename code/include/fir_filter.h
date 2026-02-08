//description: Header file for FIR filter
//author: Esteban Bustamante
//date: 2025-11-12

/**
 * @file fir_filter.h
 * @brief Macros y funciones para un Filtro FIR en software utilizando aritmética
 *        de punto fijo.
 */

/**
 * @mainpage Filtro FIR en Punto Fijo
 *
 * @section intro Introducción
 *
 * Este proyecto se presenta como parte práctica del trabajo final de la asignatura
 * <b>Técnicas Digitales III</b>. Consiste en la implementación de un Filtro FIR
 * (Finite Impulse Response) definido completamente en software, desarrollado en
 * lenguaje C y orientado a sistemas digitales.
 *
 * El filtro opera sobre muestras de entrada representadas en formato de punto fijo,
 * haciendo uso de la librería FXP. Para garantizar el correcto sincronismo entre
 * las muestras de entrada y el proceso de filtrado, se emplea un buffer de entrada
 * que permite el procesamiento por bloques de muestras en paralelo.
 *
 * Tanto la señal de entrada como la señal de salida del filtro se almacenan en
 * archivos de datos en formato PCM (.pcm). Este formato simplifica el procesamiento
 * posterior de los datos y garantiza compatibilidad con herramientas externas
 * para la visualización y el análisis de señales.
 *
 * Con el objetivo de facilitar su uso y análisis, el proyecto incluye una
 * interfaz gráfica desarrollada en Python, que permite generar señales de prueba,
 * ejecutar el filtro y visualizar gráficamente tanto la entrada como la salida.
 * Asimismo, el filtro puede ser ejecutado directamente desde línea de comandos
 * mediante una interfaz CLI.
 *
 * Junto al binario se entrega una demostración lista para ser ejecutada tanto en
 * modo gráfico como en modo línea de comandos
 * (ver @ref demo "Demostración").
 *
 * @section architecture Arquitectura del sistema
 *
 * El sistema se encuentra dividido en los siguientes bloques principales:
 *
 * - <b>Generador de señales</b>: encargado de generar señales de prueba
 *   (por ejemplo, tonos senoidales) y almacenarlas en formato PCM.
 * - <b>Filtro FIR</b>: núcleo del sistema, implementado en C, que realiza el
 *   filtrado en punto fijo utilizando coeficientes configurables.
 * - <b>Interfaz gráfica (GUI)</b>: desarrollada en Python, permite configurar
 *   parámetros, ejecutar el filtro y visualizar resultados.
 * - <b>Interfaz de línea de comandos (CLI)</b>: permite ejecutar el filtro de forma
 *   directa, facilitando su integración en scripts y pruebas automatizadas.
 *
 * @section features Características
 *
 * - Implementación de un filtro FIR en software.
 * - Uso de aritmética de punto fijo mediante la librería FXP.
 * - Configuración del número de bits fraccionales.
 * - Procesamiento de múltiples muestras en paralelo.
 * - Coeficientes de filtro configurables externamente.
 * - Entrada y salida en formato PCM de 32 bits.
 * - Visualización gráfica de:
 *   - señal de entrada
 *   - señal de salida
 *   - coeficientes del filtro
 * - Soporte para ejecución en modo GUI y modo CLI.
 *
 * @section usage Uso del filtro
 *
 * El filtro puede utilizarse de dos maneras:
 *
 * - Mediante una interfaz gráfica (GUI), pensada para demostraciones y análisis
 *   visual.
 * - Mediante una interfaz de línea de comandos (CLI), orientada a pruebas rápidas
 *   o automatización.
 *
 * @section demo Demostración
 * Para la demostración de la funcionalidad el filtro en C, se generó un filtro haciendo uso de [FIIR](https://fiiir.com), que permite generar coeficientes para filtros arbitrarios con frecuencias de muestreo y filtrado determinadas. Para esta demostración se generó un FIR cuya respuesta al impulso coincide con un seno cardinal (sinc), con una frecuencia de muestreo de 48kHz, una frecuencia de cutoff de 800Hz y un ancho de banda de transición de 3840Hz, el cual observando su respuesta en frecuencia, tenemos que genera una atenuación de 35dB a 0.1 frecuencia relativa a la de Nyquist, es decir ((0.1)Fs/2 = 2.4kHz).
 * @image html demo_response_freq.png "Respuesta en frecuencia del filtro demostración"
 *
 * @subsection demo_gui Demostración en modo gráfico (GUI)
 *
 * Para ejecutar la demostración en modo gráfico, será necesario descargar en primer lugar la última [release](https://github.com/esbon125/td3-proyecto-final/releases), y luego utilizar los siguientes comandos para ejecutar el script con la interfaz gráfica:
 *
 * @code{.sh} 
 * cd code/src && make
 * cd ../utils/scripts
 * ./fir_filter_utn -gui
 * @endcode
 *
 * Desde la interfaz gráfica es posible:
 * - Generar señales de entrada con uno o más tonos.
 * - Configurar la frecuencia de muestreo y amplitudes.
 * - Cargar un archivo de coeficientes del filtro.
 * - Ejecutar el filtro FIR.
 * - Visualizar gráficamente la señal de entrada, la salida filtrada
 *   y los coeficientes del filtro.
 *
 * @subsection demo_cli Demostración en modo línea de comandos (CLI)
 *
 * El filtro también puede ejecutarse directamente desde la línea de comandos. Para esto deberán tener los archivos coeficientes.pcm e input.pcm que se incluyen con el programa, incluídos en el link de las releases. Es necesario ubicar estos archivos dentro de la carpeta td3-proyecto-final-1.6.0 que se extrae del zip descargado. Luego ejecutando estos comandos podríamos correr el programa.
 *
 * @code{.sh}
 * cp coeficientes.pcm input.pcm code/utils/scripts/
 * cd code/src && make
 * cd ../utils/scripts
 * ./fir_filter_utn -fc=coeficientes.pcm -NB-FRAC=31 --samples=80 input.pcm
 * @endcode
 *
 * donde:
 * - <b>coeficientes.pcm</b> es el archivo que contiene los coeficientes del filtro
 *   (en formato float, uno por línea).
 * - <b>NB-FRAC</b> indica el número de bits fraccionales utilizados.
 * - <b>samples</b> define la cantidad de muestras procesadas en paralelo.
 * - <b>input.pcm</b> es el archivo PCM de entrada.
 *
 * El archivo de salida se genera automáticamente en formato PCM y puede ser
 * posteriormente visualizado o procesado con herramientas externas.
 *
 * @section todo Posibles mejoras
 * Si bien por el alcance de este proyecto puede considerarse terminado, estas son algunas mejoras interesantes que pueden interesarle al desarrollador: 
 * - Hacer una interfaz común a distintos periféricos para permitir distintas entradas.
 * - Optimizar el filtro haciendo uso de threads en paralelo, lo que implicaría un mecanismo de sincronización.
 * - Hacer uso de la librería libusb para permitir el procesamiento de datos en tiempo real, además haciendo uso de la interfaz anteriormente mencionada.
 * @section references Referencias
 *
 * - Librería FXP:
 *   @see https://github.com/rsaavedraf/fxp
 *
 * - Conceptos de filtros FIR:
 *   @see https://en.wikipedia.org/wiki/Finite_impulse_response
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
