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
    return;
  }

  if (id > 0) { // parent
    printf(1, "PARENT: # of free pages after fork: %d\n", getNumFreePages());
    
  } else { // child
    printf(1, "CHILD: # of free pages after fork: %d\n", getNumFreePages());
  }

  exit();
}