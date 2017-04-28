/***********************************************************************
 * Program:
 *    Lab C_lab, ECEN 324 Learning C Lab
 *    Brother Jones, ECEN 324
 * Author:
 *    Wellesley Shumway
 * Summary:
 *    Demonstrates various ways to print things in different formats,
 *    and in addition demonstrates how to do simple tasks in C like
 *    constants, loops, points, memory allocation/deletion.
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415926

int main() {

  const char LETTER = 'A';
  printf("24\n");
  printf("%.5f\n", PI);
  printf("%c\n", LETTER);

  float payRate = 10.5;
  float hours = 40.0;

  printf("Users pay rate: $%.1f\n", payRate);
  printf(" Hours worked: %.0f\n", hours);
  printf("    Gross Pay: $%.0f\n", (hours * payRate) );

  int number;

  perror("Enter number: ");
  scanf("%d", &number);
  printf("Twice %d is %d\n", number, (2 * number));

  int anInt = 99;
  float aFloat = 43.2;

  printf("\n");
  printf("Integer: %d ###\n", anInt);
  printf("Integer: %10d ###\n", anInt);
  printf("Integer: %-10d ###\n\n", anInt);

  printf("  Float: %.1f ###\n", aFloat);
  printf("  Float: %-10.1f ###\n", aFloat);
  printf("  Float: %10.2f ###\n", aFloat);
  printf("  Float: %.3f ###\n", aFloat);
  printf("  Float: %10.3f ###\n", aFloat);
  printf("  Float: %-10.4f ###\n\n", aFloat);

  printf("\tOct   Dec   Hex   Char\n");
  printf("\t----------------------\n");

  int i;
  for (i = 'a'; i <= 'z'; i++) {
    printf("\t%-5o %-5d %x %4c\n", i, i, i, i);
  }

  printf("\n");
  int *p1;
  int *p2;

  p1 = (int *)malloc(sizeof(int));
  *p1 =42;
  p2 = p1;
  printf("*p1 == %d\n", *p1);
  printf("*p2 == %d\n", *p2);

  *p2 = 53;
  printf("*p1 == %d\n", *p1);
  printf("*p2 == %d\n", *p2);

  p1 = (int *)malloc(sizeof(int));
  *p1 = 88;
  printf("*p1 == %d\n", *p1);
  printf("*p2 == %d\n", *p2);

  printf("Hope you got the point of this example!\n");

  free(p1);
  free(p2);

  return 0;
}
