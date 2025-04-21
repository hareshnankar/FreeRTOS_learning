/**
* Baker Hughes Confidential
* Copyright 2023. Baker Hughes.
*
* NOTICE:  All information contained herein is, and remains the property of Baker Hughes and its suppliers, and
* affiliates if any.  The intellectual and technical concepts contained herein are proprietary to Baker Hughes
* and its suppliers and affiliates and may be covered by U.S. and Foreign Patents, patents in process, and are
* protected by trade secret or copyright law.  Dissemination of this information or reproduction of this material is
* strictly forbidden unless prior written permission is obtained from Baker Hughes.
*
* @file     C11Wrapper.c
* @version  1.00.00
* @author   Simon Smith
* @date     16 June 2023
*
* @brief    Wrapper around compiler-specific C11 functions to cater for compiler differences between IAR and Visual Studio.
*/
//*********************************************************************************************************************

/* Includes ---------------------------------------------------------------------------------------------------------*/
#include "misra.h"

//MISRAC_DISABLE
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
//MISRAC_ENABLE
#include "C11Wrapper.h"

/* Typedefs ---------------------------------------------------------------------------------------------------------*/

/* Defines ----------------------------------------------------------------------------------------------------------*/

/* Macros -----------------------------------------------------------------------------------------------------------*/
#ifdef SIMULATOR
#define TEMP_BUFFER_LENGTH 2641u // FILE_MAX_LINE_LENGTH
#else
#define TEMP_BUFFER_LENGTH 1850u
#endif

/* Variables --------------------------------------------------------------------------------------------------------*/

/* Prototypes -------------------------------------------------------------------------------------------------------*/

/* User code --------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
 * DISABLE MISRA C 2004 CHECK for Rule 16.1 as function needs a variable number of arguments which violates the rule.
 **********************************************************************************************************************/
//_Pragma("diag_suppress=Pm064")
/**
 * @brief   Concatenate formatted strings
 * @param   as per snprintf
 * @retval  true = success, false = failed
 */
bool snprintcatf(char* output, size_t size, const char* format, ...)
{
    char temp[TEMP_BUFFER_LENGTH+1u];
    temp[0] = '\0';
    int len = 0;
    bool ok = false;

    // Check for temp buffer overrun
    if (size <= TEMP_BUFFER_LENGTH)
    {
        va_list args;
        va_start(args, format);
//#ifdef SIMULATOR
        len = vsnprintf_s(temp, sizeof(temp), size, format, args);
//#else
//       // len = vsnprintf_s(temp, size, format, args);
//        len = vsnprintf_s(temp, sizeof(temp), size, format, args);
//#endif
        va_end(args);

        // Check for output buffer overrun
        if ((strnlen_s(output, size) + (size_t)len) <= size)
        {
            (void)strncat_s(output, size, temp, size);
            ok = true;
        }
    }

   // assert(ok);

    return ok;
}
/**********************************************************************************************************************
 * RE-ENABLE MISRA C 2004 CHECK for Rule 16.1 as function needs a variable number of arguments which violates the rule.
 **********************************************************************************************************************/
//_Pragma("diag_default=Pm064")

/**
 * @brief   Safely copies the value ch into each of the first count characters of the object pointed to by dest.
 * @param   as per memset_s
 * @retval  as per memset_s
 * @note    constraint handler called on error
 */
errno_t memset_safe(void *dest, rsize_t destsz, int ch, rsize_t count)
{
//#ifdef SIMULATOR
    (void)destsz; // not used
    return memset(dest, ch, count);
//#else
//    //return memset_s(dest, destsz, ch, count);
//    return memset(dest, ch, count);
//#endif
}

/**
 * @brief   Finds the next token in a null-terminated byte string pointed to by str. The separator characters are identified by null-terminated byte string pointed to by delim.
 * @param   as per strtok_s
 * @retval  as per strtok_s
 * @note    constraint handler called on error
 */
char *strtok_safe(char *str, rsize_t *strmax, const char *delim, char **ptr)
{
//#ifdef SIMULATOR
    (void)strmax; // not used
    return strtok_s(str, delim, ptr);
//#else
//    //return strtok_s(str, strmax, delim, ptr);
//    return strtok_s(str, delim, ptr);
//#endif
}

/**********************************************************************************************************************
 * RE-ENABLE MISRA C 2004 CHECK for Rule 10.1 as we are using OS_ERR enum which violates the rule
 **********************************************************************************************************************/
//_Pragma("diag_default=Pm128")