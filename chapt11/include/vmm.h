#ifndef INCLUDE_VMM_H_
#define INCLUDE_VMM_H_

#include "types.h"
#include "idt.h"
#include “vmm.h"

#define PAGE_OFFSET 	0xc0000000

#define PAGE_PRESENT 	0x1

#define PAGE_WRITE   	0x2

#define PAGE_USER	0X4

#define PAGE_SIZE	4096

#define PGD_INDEX	(((x)>>22)&0x3ff)

#define PTE_INDEX(x)	(((x)>>12)&0x3ff)

#define OFFSET_INDEX(x)	((x) & 0xfff)

typedef uint32_t pgd_t;

typedef uint32_t pte_t;

#define PGD_SIZE	(PAGE_SIZE/sizeof(pte_t))

#define PTE_SIZE	(PAGE_SIZE/sizeof(uint32_t))

#define PTE_COUNT	128

extern pgd_t pgd_kern[PGD_SIZE];

void init_vmm();

void switch_pgd(uint32_t pd);

void map(pgd_t *pgd_now,uint32_t va,uint32_t pa,uint32_t flags);

void unmap(pgd_t *pgd_now,uint32_t va);

uint32_t get_mappint(pgd_t *pgd_now,uint32_t va,uint32_t *pa);

void page_fault(pt_regs *regs);

#endif

