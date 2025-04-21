/**
* Baker Hughes Confidential
* Copyright 2023.  Baker Hughes.
*
* NOTICE:  All information contained herein is, and remains the property of Baker Hughes and its suppliers, and
* affiliates if any.  The intellectual and technical concepts contained herein are proprietary to Baker Hughes
* and its suppliers and affiliates and may be covered by U.S. and Foreign Patents, patents in process, and are
* protected by trade secret or copyright law.  Dissemination of this information or reproduction of this material is
* strictly forbidden unless prior written permission is obtained from Baker Hughes.
*
* @file     C11Wrapper.h
* @version  1.00.00
* @author   Simon Smith
* @date     16 June 2023
*
* @brief    Wrapper around compiler-specific C11 functions to cater for compiler differences between IAR and Visual Studio.
*/

#ifndef __C11WRAPPER_H
#define __C11WRAPPER_H

#ifdef __cplusplus
extern "C"
{
/* External C language linkage */
#endif

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "misra.h"

//MISRAC_DISABLE
#include <stdbool.h>
#include <string.h>
//MISRAC_ENABLE

/* Defines ----------------------------------------------------------------------------------------------------------*/

/* Macros -----------------------------------------------------------------------------------------------------------*/

/* Prototypes -------------------------------------------------------------------------------------------------------*/
/**********************************************************************************************************************
 * DISABLE MISRA C 2004 CHECK for Rule 16.1 as function needs a variable number of arguments which violates the rule.
 **********************************************************************************************************************/
//_Pragma("diag_suppress=Pm064")
bool snprintcatf(char* output, size_t size, const char* format, ...);
/**********************************************************************************************************************
 * RE-ENABLE MISRA C 2004 CHECK for Rule 16.1 as function needs a variable number of arguments which violates the rule.
 **********************************************************************************************************************/
//_Pragma("diag_default=Pm064")

errno_t memset_safe(void *dest, rsize_t destsz, int ch, rsize_t count);
char *strtok_safe(char *str, rsize_t *strmax, const char *delim, char **ptr);

#ifdef __cplusplus
}                                                               /* End of external C language linkage */
#endif

#endif //__C11WRAPPER_H
