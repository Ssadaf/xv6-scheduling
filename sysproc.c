#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "ticketlock.h"

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

int ticket_lock_shared = 0;
struct ticketlock ticket_lock;

int
sys_ticketlockinit(void)
{
  ticket_lock_shared = 0;
  initticketlock(&ticket_lock);
  return 1;
}

int
sys_ticketlocktest(void)
{
  acquireticketlock(&ticket_lock);
  ticket_lock_shared ++;
  releaseticketlock(&ticket_lock);
  return ticket_lock_shared;
}

int readers_writers_shared = 0;
struct ticketlock readers_writers_lock;

int sys_rwinit(void)
{
  readers_writers_shared = 0;
  initticketlock(&readers_writers_lock);
  return 1;
}

int sys_rwtest(void)
{
  int pattern;
  if (argint(0, &pattern) < 0)
    return -1;
  return readers_writers_shared;
}

int sys_changepriority(void)
{
  int priority;
  if (argint(0, &priority) < 0)
    return -1;
  changepriority(priority, myproc()->pid);
  return priority;
}