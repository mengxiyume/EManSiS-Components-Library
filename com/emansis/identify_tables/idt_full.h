/*
 *  0x00000000
 *  ...->保留字段
 *  0x000FFFFF
*/
#include "./idt_retained.h"

/*
 *  0x00100000
 *  ...->异常编号段
 *  0x001FFFFF
*/
#include "./idt_exception.h"