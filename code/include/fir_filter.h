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
 * modo gráfico como en modo línea de comandos.
 * (ver @ref demo "Demostración").
 *
 * @section architecture Arquitectura del sistema
 *
 * El sistema completo se compone de múltiples bloques que interactúan entre sí,
 * permitiendo tanto el procesamiento de señales como su análisis y visualización.
 *
 * @image html figures/system.png  "Arquitectura general del sistema" width=70%
 *
 * Los principales componentes son:
 *
 * - <b>Generador de señales</b>:
 *   Permite generar señales de prueba como impulso, multitono, chirp y ruido.
 *   Estas señales son almacenadas en formato PCM de 32 bits.
 *
 * - <b>Conversión de formatos</b>:
 *   Se realiza la conversión entre archivos WAV y PCM32, permitiendo trabajar
 *   tanto con señales reales como con señales generadas artificialmente.
 *
 * - <b>Filtro FIR (núcleo en C)</b>:
 *   Implementado en lenguaje C utilizando aritmética de punto fijo Q1.31.
 *   Realiza el procesamiento de las muestras mediante convolución discreta.
 *
 * - <b>Interfaz Python</b>:
 *   Encargada de:
 *   - Ejecutar el binario del filtro
 *   - Gestionar archivos de entrada/salida
 *   - Visualizar señales en tiempo y frecuencia
 *
 * - <b>Visualización</b>:
 *   Permite analizar:
 *   - Señales en dominio temporal
 *   - Espectro en frecuencia mediante FFT
 *   - Coeficientes del filtro
 *
 * Esta arquitectura modular permite desacoplar el procesamiento numérico
 * (implementado en C) de la interacción con el usuario y análisis (Python),
 * facilitando la portabilidad, reutilización y extensibilidad del sistema.
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
 * - Análisis espectral mediante FFT de señales y respuesta al impulso.
 *
 * @section audio Manejo de audio
 *
 * El sistema implementa soporte para archivos de audio en formato WAV,
 * permitiendo su integración directa con el flujo de procesamiento del filtro FIR.
 *
 * Internamente, el filtro opera exclusivamente sobre datos en formato PCM
 * de 32 bits (Q1.31), por lo que se incorporan mecanismos de conversión
 * entre ambos formatos.
 *
 * @subsection wav_to_pcm Conversión WAV a PCM32
 *
 * Los archivos WAV de entrada son leídos y convertidos a formato PCM32 mediante:
 *
 * - Normalización de la señal al rango [-1, 1]
 * - Conversión a punto fijo Q1.31
 * - Reducción a un solo canal en caso de audio estéreo
 *
 * Este proceso permite utilizar señales reales como entrada del filtro,
 * manteniendo consistencia con la representación interna del sistema.
 *
 * @subsection pcm_to_wav Conversión PCM32 a WAV
 *
 * Luego del procesamiento, la señal filtrada puede convertirse nuevamente
 * a formato WAV, permitiendo:
 *
 * - Reproducción directa del resultado
 * - Análisis en herramientas externas (Audacity, MATLAB, etc.)
 *
 * La conversión incluye:
 *
 * - Escalado de Q1.31 a formato flotante
 * - Conversión a entero de 16 bits (formato estándar WAV)
 * - Escritura del archivo con la frecuencia de muestreo correspondiente
 *
 * @subsection audio_playback Reproducción de audio
 *
 * El sistema permite la reproducción de señales de entrada y salida mediante
 * herramientas del sistema operativo (por ejemplo, <i>aplay</i> en Linux).
 *
 * Esta funcionalidad facilita la validación perceptual del filtro,
 * permitiendo evaluar su efecto directamente sobre señales de audio reales.
 *
 * En conjunto, estas capacidades convierten al sistema en una herramienta
 * completa de procesamiento de audio, integrando:
 *
 * - Adquisición de señal
 * - Procesamiento digital
 * - Visualización
 * - Evaluación auditiva
 *
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
 * @section dependencies Instalación de dependencias
 *
 * Para ejecutar correctamente el entorno de simulación, visualización y GUI,
 * es necesario instalar las dependencias de Python requeridas.
 *
 * Se provee un script que automatiza este proceso.
 *
 * @subsection install_dependencies Instalación automática
 *
 * Ejecutar:
 *
 * @code{.sh}
 * chmod +x install_dependencies.sh
 * ./install_dependencies.sh
 * @endcode
 *
 * Este script instala:
 * - numpy
 * - matplotlib
 * - tkinterdnd2
 *
 * Además, en sistemas Linux, se recomienda contar con:
 *
 * @code{.sh}
 * # Instalación manual (alternativa al script)
 *
 * # Ubuntu / Debian
 * sudo apt install python3-tk alsa-utils
 *
 * # Arch Linux
 * sudo pacman -S tk alsa-utils
 *
 * # Fedora
 * sudo dnf install python3-tkinter alsa-utils
 *
 * @endcode
 *
 * donde:
 * - <b>python3-tk</b> permite el uso de la interfaz gráfica (Tkinter)
 * - <b>alsa-utils</b> permite la reproducción de audio mediante <i>aplay</i>
 *
 * @section demo Demostración
 *
 * Para la validación del filtro FIR implementado, se diseñó un filtro pasabanda
 * utilizando la herramienta externa [FIIR](https://fiiir.com), que permite generar
 * coeficientes a partir de especificaciones en frecuencia.
 *
 * El filtro generado presenta una respuesta al impulso equivalente a una función
 * seno cardinal (sinc), con una frecuencia de muestreo de 48 kHz, una frecuencia
 * de corte f1=1000 Hz y f2=5000Hz con un ancho de transición para ambos cortes de 700Hz.
 *
 * A partir de la respuesta al impulso obtenida, se calculó su Transformada Rápida
 * de Fourier (FFT), lo que permite analizar su comportamiento en frecuencia.
 *
 * @image html figures/fft_impulse_response.png "FFT de la respuesta al impulso del filtro" width=70%
 *
 * En dicha figura se observa la respuesta en frecuencia del sistema, verificando
 * la atenuación en banda de rechazo y el comportamiento esperado del filtro FIR.
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
