#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "ticketlock.h"

void initticketlock(struct ticketlock *lk)
{
	initlock(&lk->lk, "ticket lock");
	lk->serving = 0;
	lk->next_ticket = 0;
}

void acquireticketlock(struct ticketlock *lk)
{
	int myticket = fetch_and_add(&(lk->next_ticket), 1);
	while (lk->serving != myticket) sleep(lk, &lk->lk);
}

void releaseticketlock(struct ticketlock *lk)
{
	lk->serving++;
	wakeup(lk);
}
