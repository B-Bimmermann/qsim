#include <stdio.h>
#include <stdint.h>
#include <sys/sysinfo.h>

#define DEBUG_ENABLE 1
#include "debug_print.h"

__attribute__((always_inline))
static inline void do_cpuid(uint32_t val) {
#if defined(__aarch64__)
  asm volatile("msr pmcr_el0, %0" :: "r" (val));
#else
  asm("cpuid;\n":: "a"(val) : "%ebx", "%ecx", "%edx");
#endif
}

static inline void set_n_cpus(void) {
#if defined(__aarch64__)
  DB_PRINT("HERE IS A CODE");
#else
  asm volatile("cpuid;\n":: "a"(0xc5b1fffc), "b"(get_nprocs()):"ecx","edx");
#endif
}

int main(int argc, char** argv) {
  DB_PRINT("START APLICATION");
  if      (argc == 1) {
        DB_PRINT("write: 0xaaaaaaaa");
	do_cpuid(0xaaaaaaaa);
	do_cpuid(0x12344321);
        DB_PRINT("HAVE SAVED HERE !!!!");
	while (1)
	{
		do_cpuid(0x12344321);
        	DB_PRINT("have write: 0x12344321");
	}
  }
  else if (argc == 2) {
        DB_PRINT("write: 0xfa11dead");
	do_cpuid(0xfa11dead);
  }
  DB_PRINT("call set_n_cpus()");
  // set number of processors in qsim
  set_n_cpus();
  DB_PRINT("have called set_n_cpus()");

  DB_PRINT("END APLICATION");
  return 0;
}
