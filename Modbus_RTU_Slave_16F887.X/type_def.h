/*
 * Заголовочный файл с типами и структурами переменных
 */


#ifndef TYPE_DEF_H
#define	TYPE_DEF_H

/* Specify an extension for GCC based compilers */
#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

#if !defined(__PACKED)
    #define __PACKED
#endif

#ifndef _BOOL
typedef enum _BOOL { FALSE = 0, TRUE } BOOL;    /* Undefined size */
#define _BOOL _BOOL
#endif

typedef void                    VOID;

typedef char                    CHAR;
typedef unsigned char           UCHAR;

typedef unsigned char           BYTE;                           /* 8-bit unsigned  */
typedef unsigned int            WORD;                           /* 16-bit unsigned */
typedef signed int              INT;                            /*16-bit signed*/
typedef unsigned long           DWORD;                          /* 32-bit unsigned */
typedef float                   SINGLE;                         /*32- bit float*/

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */

__EXTENSION
typedef signed char             CHAR;                           /* 8-bit signed    */
typedef signed short int        SHORT;                          /* 16-bit signed   */
typedef signed long             SLONG;                           /* 32-bit signed   */

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */

__EXTENSION
typedef union
{
    BYTE Val;
    struct __PACKED
    {
        __EXTENSION BYTE b0:1;
        __EXTENSION BYTE b1:1;
        __EXTENSION BYTE b2:1;
        __EXTENSION BYTE b3:1;
        __EXTENSION BYTE b4:1;
        __EXTENSION BYTE b5:1;
        __EXTENSION BYTE b6:1;
        __EXTENSION BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2] __PACKED;
    struct __PACKED
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct __PACKED
    {
        __EXTENSION BYTE b0:1;
        __EXTENSION BYTE b1:1;
        __EXTENSION BYTE b2:1;
        __EXTENSION BYTE b3:1;
        __EXTENSION BYTE b4:1;
        __EXTENSION BYTE b5:1;
        __EXTENSION BYTE b6:1;
        __EXTENSION BYTE b7:1;
        __EXTENSION BYTE b8:1;
        __EXTENSION BYTE b9:1;
        __EXTENSION BYTE b10:1;
        __EXTENSION BYTE b11:1;
        __EXTENSION BYTE b12:1;
        __EXTENSION BYTE b13:1;
        __EXTENSION BYTE b14:1;
        __EXTENSION BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

#undef __EXTENSION

#endif	/* TYPE_DEF_H */

