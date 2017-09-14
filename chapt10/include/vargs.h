#ifndef INCLUDE_VARGS_H_
#define INCLUDE_VARGS_H_

typedef __builtin_va_list va_list;

#define va_start(sp,last)   (__builtin_va_start(sp,last))
#define va_arg(ap,type)     (__builtin_va_arg(ap,type))
#define va_end(ap)          

/*#define va_list            char*
 *#define va_start(p,first)  (p=(va_list)&first+sizeof(first))
 *#define va_arg(p,next)     (*(next*)((p += sizeof(next))-sizeof(next)))
 *#define va_end(p)          (p = (va_list)NULL)
 * */

#endif
