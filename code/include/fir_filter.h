//description: defines for FIR filter
//author: Esteban Bustamante
//date: 2025-11-12

/**
 * @file fir_filter.h
 * @brief Macros and functions for software Fixed Point FIR Filter.
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

