#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


int
sys_thread_create(void){
    void (*fcn);
    void *stack;
    void *arg;
    argptr(0, &fcn, sizeof (fcn));
    argptr(1, &stack, sizeof (void*));
    argptr(2, &arg, sizeof (void*));
    return thread_create(fcn, stack, arg);
}

int sys_thread_join(void){
    return thread_join();
}

int
sys_thread_exit(void){
    thread_exit();
    return 0;
}

int
sys_lock_init(void){
    struct sleeplock *lock;
    argptr(0, (char**)&lock, sizeof(lock));
    return lock_init(lock);
}

int
sys_lock_acquire(void){
    struct sleeplock *lock;
    argptr(0, (char**)&lock, sizeof(lock));
    return lock_acquire(lock);
}

int
sys_lock_release(void){
    struct sleeplock *lock;
    argptr(0, (char**)&lock, sizeof(lock));
    return lock_release(lock);
}
