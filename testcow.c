#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int main(int argc, char* argv[]) {
  printf(1, "# of free pages before allocation: %d\n", getNumFreePages());

  char* bigBlockOfMem = malloc(PGSIZE);

  printf(1, "# of free pages after allocation: %d\n", getNumFreePages());
  
  for (int i = 0; i < PGSIZE; i++) {
    bigBlockOfMem[i] = ' ';
  }

  printf(1, "# of free pages after setting: %d\n", getNumFreePages());

  int id = fork();

  if (id < 0) {
    printf(1, "%d failed in fork!\n", getpid());
    exit();
    return -1;
  }

  char* anotherBigBlock = 0;
  if (id > 0) { // parent
    printf(1, "PARENT: # of free pages after fork: %d\n", getNumFreePages());
    anotherBigBlock = malloc(PGSIZE);
    for (int i = 0; i < PGSIZE; i++) {
      anotherBigBlock[i] = PGSIZE - i;
    }
    printf(1, "PARENT: # of free pages after construction: %d\n", getNumFreePages());
    memmove((void*)(bigBlockOfMem), (void*)anotherBigBlock, PGSIZE / 2);
    printf(1, "PARENT: # of free pages after copy: %d\n", getNumFreePages());
    wait();
  } else { // child
    printf(1, "CHILD: # of free pages after fork: %d\n", getNumFreePages());
    anotherBigBlock = malloc(PGSIZE);
    for (int i = 0; i < PGSIZE; i++) {
      anotherBigBlock[i] = i*2;
    }
    printf(1, "CHILD: # of free pages after construction: %d\n", getNumFreePages());
    memmove((void*)(bigBlockOfMem+(PGSIZE/2)), (void*)anotherBigBlock, PGSIZE / 2);
    printf(1, "CHILD: # of free pages after copy: %d\n", getNumFreePages());
    exit();
    return 0;
  }

  // parent process only from this point
  printf(1, "# of free pages after fork: %d\n", getNumFreePages());
  printf(1, "first 10 values of block: [ ");
  for (int i = 0; i < 10; i++) printf(1, "%d, ", bigBlockOfMem[i]);
  printf(1, " ]\n");
  printf(1, "last 10 values of block: [ ");
  for (int i = 1; i <= 10; i++) printf(1, "%d, ", bigBlockOfMem[PGSIZE - i]);
  printf(1, " ]\n");
  exit();
}