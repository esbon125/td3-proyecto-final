//description: defines for FIR filter
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
 * Este proyecto se presenta como parte práctica del trabajo final de la asignatura Técnicas Digitales III. Consiste en un Filtro FIR definido en software que posee una interfaz USB para una conexión a algún dispositivo muestreador que entregue las muestras de entrada. Utiliza un buffer de entrada para lograr el sincronismo entre el filtro y las muestras de entrada. Actualmente tanto la salida como la entrada serán escritos a archivos de datos (.csv), para generar los gráficos correspondientes de las señales de entrada y salida.
 * 
 *
 * @section features Características
 * - Programa simple en C basado en la librería FXP 
 * - Configurable en Número de bits, truncado/redondeado, saturado/overflow
 *
 * @see https://github.com/rsaavedraf/fxp
 */


#ifndef FIR_FILTER_H
#define FIR_FILTER_H

/** @brief Maximum error allowed in asserts and checks. */
#define DELTA_ERROR 1e-4f

/** @brief Number of fractional bits. */
#define NB_FRAC     31

/** @brief Number of bits */
#define NB          32

/** @brief Number of integer bits */
#define NB_INT      NB - NB_FRAC

#endif /* FIR_FILTER_H */

