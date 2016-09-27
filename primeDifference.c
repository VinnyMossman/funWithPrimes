/* Some fun with prime numbers
   Author:     Vincent T. Mossman
   Compile by: gcc -o prime prime.c
   Run by:     ./prime
*/

#include "primality.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char * argv[]) {

  if (argc != 2) {
    printf("Usage: %s <followed by [NAT to count to]>\n", argv[0]);
    exit(-1);
  }
  int COUNT_TO, lineCount = 0, i, max = 0;
  sscanf(argv[1], "%d", &COUNT_TO);
  int track[4] = {1, 0, 0, 1}; //Previous Prime Position, Total Distance, Total Primes, Line Start Prime
  clock_t begin = clock();
  printf("\n");
  printf("Difference between primes:\n");
  for (i = 1; i <= COUNT_TO; i++) {
    if (isPrime(i)){
      if (lineCount > 19) {
	printf("    Primes between %d and %d\n", track[3], i);
	lineCount = 0;
      }
      printf("%*d ", 3, i - track[0]); lineCount++;
      if (lineCount == 1) {
	track[3] = i;
      }
      track[1] = track[1] + (i - track[0]);
      if (i - track[0] > max) {
	max = i - track[0];
      }
      track[0] = i;
      track[2]++;
    }
  }
  printf("    Primes between %d and %d\n", track[3], i);
  clock_t end = clock();
  double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
  printf("\nCPU execution time: %0.3lfs\n", time_spent);
  printf("Average difference between primes: %0.3lf\n", (double) track[1] / (double) track[2]);
  printf("Max difference between primes: %d\n\n", max);

}