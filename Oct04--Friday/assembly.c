/*Instruction set

set of opernations 


architecture: what you need to know to program assembly -- instructiopn set, registers

-Microarchitecture: implementation (IA32 on non-intel chips)

GAS:
  assembler used by GCC
  differences with NASM
  AT&T syntax

  be careful when reading the intel manuals -- operand orders!

gcc -S displays the assembly

tools:
compiler -- GCC
assembler -- as aka gas
linker -- ld
debugger -- gdb
disassembler -- objdump
profiler -- gprof


8086
Register

8 general purposes
  

byte -- 1 byte
word -- 2 bytes
doubleword -- 4 bytes
quadword -- 8 bytes
double quadword -- 16bytes

*/

int sum()
{
  int x = 30;
  int y = 57;
  int z = 39;

  return x+y+z;
  
}
