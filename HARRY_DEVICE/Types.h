#ifndef __TYPES_H
#define __TYPES_H
#include <stdint.h>

//time structure
typedef struct
{
    uint32_t hours;
    uint32_t minutes;
    uint32_t seconds;
    uint32_t milliseconds;      // add millisecond based on data log
    uint32_t day;
    uint32_t month;
    uint32_t year;

} sTime_t;



typedef enum // In sec 
{
    FIVE_SEC_I    = 5,
    TEN_SEC_I     = 10,
    THIRTY_SEC_I  = 30,
    ONE_MIN_I     = 60,
    FIVE_MIN_I   = 300,
    FIFTEEN_MIN_I = 900,
    ONE_HOUR_I    = 3600,
    ONE_DAY_I     = 86400
} logInterval_t;

typedef enum // In sec 
{
    ONE_MIN_D = 60,
    FIFTEEN_MIN_D = 900,
    ONE_HOUR_D = 3600,
    SIX_HOUR_D = 21600,
    ONE_DAY_D = 86400,
    ONE_MOUNTH_D = 2592000,
    SIX_MOUNTHS_D = 15552000,
    ONE_YEAR_D = 31536000,
    CIRCULER_D = 0
} logDuration_t;

typedef enum
{
    DEFAULT = 0,
    SCIENTFIC = 1
}Dec_point_formate;

#endif
