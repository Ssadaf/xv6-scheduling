struct ticketlock {
	int serving;
	int next_ticket;
	struct spinlock lk;
};
