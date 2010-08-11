#include <stdio.h>
#include <assert.h>

#include "types.h"
#include "color.h"
#include "cpu_ops.h"

int main () {
  REG8 target = 0x81;
  UINT32 zero = 0, negative = 0, half = 0, carry = 0;

  printf ("Test types START\n");

  assert (sizeof (INT8) == 1);
  assert (sizeof (INT16) == 2);
  assert (sizeof (INT32) == 4);
  assert (sizeof (UINT8) == 1);
  assert (sizeof (UINT16) == 2);
  assert (sizeof (UINT32) == 4);
  assert (sizeof (ADDR8) == 1);
  assert (sizeof (ADDR16) == 2);
  assert (sizeof (ADDR32) == 4);
  assert (sizeof (REG8) == 1);
  assert (sizeof (REG16) == 2);
  assert (sizeof (REG32) == 4);
  assert (sizeof (BYTE) == 1);
  assert (sizeof (WORD) == 2);
  assert (sizeof (DWORD) == 4);
  assert (TRUE != 0);
  assert (FALSE == 0);

  printf ("Test types END\n");

  printf ("Test Color START\n");

  Color *color = color_new (0x11, 0x22, 0x33);

  assert (color_get_red (color) == 0x11);
  assert (color_get_green (color) == 0x22);
  assert (color_get_blue (color) == 0x33);

  color_free (color);

  printf ("Test Color END\n");

  printf ("target : %2x | carry : %2x\n", target, carry);
  cpu_ops_8b_rrc (&target, &zero, &negative, &half, &carry);
  printf ("target : %2x | carry : %2x\n", target, carry);

  // 8bit loading test
  cpu_ops_8b_ld(&target, 0x0);
  assert(target == 0);
  cpu_ops_8b_ld(&target, 0xFF);
  assert(target == 0xFF);
  cpu_ops_8b_ld(&target, (BYTE)0x1FF);
  assert(target == 0xFF);
  cpu_ops_8b_ld(&target, 0x1F);
  assert(target == 0x1F);
  
  // 8bit addition test
  cpu_ops_8b_ld(&target, 0x0);
  cpu_ops_8b_add(&target, 0x0E, &zero, &negative, &half, &carry);
  printf("cpu_ops_8b_add > target: %2x, zero: %2x | negative: %2x | half: %2x | carry: %2x\n", target, zero, negative, half, carry);
  assert(zero == 0x0);
  assert(negative == 0x0);
  assert(half == 0x0);
  assert(carry == 0x0);
  
  cpu_ops_8b_add(&target, 0x02, &zero, &negative, &half, &carry);
  printf("cpu_ops_8b_add > target: %2x, zero: %2x | negative: %2x | half: %2x | carry: %2x\n", target, zero, negative, half, carry);
  assert(zero == 0x0);
  assert(negative == 0x0);
  assert(half == 0x1);
  assert(carry == 0x0);
  
  cpu_ops_8b_ld(&target, 0x10);
  cpu_ops_8b_add(&target, 0xFF, &zero, &negative, &half, &carry);
  printf("cpu_ops_8b_add > target: %2x, zero: %2x | negative: %2x | half: %2x | carry: %2x\n", target, zero, negative, half, carry);
  assert(zero == 0x0);
  assert(negative == 0x0);
  assert(half == 0x0);
  assert(carry == 0x1);
  
  cpu_ops_8b_ld(&target, 0x0E);
  cpu_ops_8b_add(&target, 0xF2, &zero, &negative, &half, &carry);
  printf("cpu_ops_8b_add > target: %2x, zero: %2x | negative: %2x | half: %2x | carry: %2x\n", target, zero, negative, half, carry);
  assert(zero == 0x1);
  assert(negative == 0x0);
  assert(half == 0x1);
  assert(carry == 0x1);
    
  return 0;
}