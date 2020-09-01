#include "sched.h"
static void put_prev_task_mypri(struct rq *rq, struct task_struct *p);
static int select_task_rq_mypri(struct task_struct *p, int cpu, int sd_flag, int flags);
static void set_curr_task_mypri(struct rq *rq);
static void task_tick_mypri(struct rq *rq,struct task_struct *p, int oldprio);
static void switched_to_mypri(struct rq *rq, struct task_struct *p);
void init_mypri_rq(struct mypri_rq *mypri_rq);
static void update_curr_mypri(struct rq *rq);
static void enqueue_task_mypri(struct rq *rq, struct task_struct *p, int flags);
static void dequeue_task_mypri(struct rq *rq, struct task_struct *p, int flags);
static void check_preempt_curr_mypri(struct rq *rq, struct task_struct *p,int flags);
struct task_struct *pick_next_task_mypri(struct rq *rq, struct task_struct *prev);
static void prio_changed_mypri(struct rq *rq, struct task_struct *p, int oldprio);

#define MYRR_TIME_SLICE 3
const struct sched_class mypri_sched_class={
	.next=&fair_sched_class,
	.enqueue_task=enqueue_task_mypri,
	.dequeue_task=dequeue_task_mypri,
	.check_preempt_curr=check_preempt_curr_mypri,
	.pick_next_task=pick_next_task_mypri,
	.put_prev_task=put_prev_task_mypri,
#ifdef CONFIG_SMP
	.select_task_rq=select_task_rq_mypri,
#endif
	.set_curr_task=set_curr_task_mypri,
	.task_tick=task_tick_mypri,
	.prio_changed=prio_changed_mypri,
	.switched_to=switched_to_mypri,
	.update_curr=update_curr_mypri,
};

void init_task_mypri(struct task_struct *p)
{
	p->sched_class = &mypri_sched_class;
}

void init_mypri_rq (struct mypri_rq *mypri_rq)
{
	printk(KERN_INFO "***[MYPRI] mypri class is online \n");
	mypri_rq->nr_running=0;
	INIT_LIST_HEAD(&mypri_rq->queue);
}

static void update_curr_mypri(struct rq *rq){	
	/*struct mypri_rq *mypri_rq = &rq->mypri;
	struct list_head *pos = NULL;
	struct task_struct *pos_p = NULL;
	struct sched_mypri_entity *pos_se = NULL;
	struct task_struct *p = rq->curr;
	struct list_head *tmp = &rq->curr->mypri.run_list;
	int i=0;
	
	if (p->mypri.pri_num > 10)
	{
		p->mypri.pri_num = p->mypri.pri_num - 10;
		printk(KERN_INFO "***[MYPRI] update_curr_mypri: pid=%d, pri_num=%d\n", p->pid, p->mypri.pri_num);
	}

	if(mypri_rq->nr_running > 1)
	{
		for(pos = mypri_rq->queue.next; pos!= &mypri_rq->queue; pos=pos->next)
		{	
			pos_se = container_of(pos, struct sched_mypri_entity, run_list);
			pos_p = container_of(pos_se, struct task_struct, mypri);
		
			if(p->mypri.pri_num >= pos_se->pri_num)
			{
				list_del_init(tmp);
				printk(KERN_INFO "[MYPRI] update_curr_mypri_reschedule: success cpu=%d, nr_running=%d, pid=%d\n", cpu_of(rq), mypri_rq->nr_running, p->pid);
				__list_add(tmp, pos->prev, pos);
				resched_curr(rq);
			}
		}
	}*/
}

static void enqueue_task_mypri(struct rq *rq, struct task_struct *p, int flags) 
{
	struct mypri_rq *mypri_rq = &rq->mypri;
	struct list_head *pos = NULL;
	struct sched_mypri_entity *pos_se = NULL;
	
	int enqueue_flag = 0;
	
	if(!rq->mypri.nr_running)
	{
		printk(KERN_INFO "***[MYPRI] enqueue first: success cpu=%d, nr_running=%d, pid=%d\n", cpu_of(rq), rq->mypri.nr_running, p->pid);
		list_add_tail(&p->mypri.run_list, &rq->mypri.queue);
	}
	else
	{
		for(pos=mypri_rq->queue.next; pos!= &mypri_rq->queue; pos=pos->next)
		{
			pos_se = container_of(pos, struct sched_mypri_entity, run_list);
			
			if(p->mypri.pri_num > pos_se->pri_num)
			{
				printk(KERN_INFO "***[MYPRI] enqueue head: success cpu=%d, nr_running=%d, pid=%d, next pri_num=%d\n", cpu_of(rq), mypri_rq->nr_running, p->pid, pos_se->pri_num);
				__list_add(&p->mypri.run_list, pos->prev, pos);
				enqueue_flag = 1;
				break;
			}
		}
		if(!enqueue_flag)
		{
			printk("***[MYPRI] enqueue tail: success cpu=%d, nr_running=%d, pid=%d, next pri_num=%d\n", cpu_of(rq), mypri_rq->nr_running, p->pid, pos_se->pri_num);
			list_add_tail(&p->mypri.run_list, &mypri_rq->queue);
		}
	}
	rq->mypri.nr_running++;
}
	
static void dequeue_task_mypri(struct rq *rq, struct task_struct *p, int flags) 
{
	if(!list_empty(&rq->mypri.queue))
	{
		list_del_init(&p->mypri.run_list);	
		rq->mypri.nr_running--;
		printk(KERN_INFO"***[MYPRI] dequeue: success cpu=%d, nr_running=%d, pid=%d\n",cpu_of(rq), rq->mypri.nr_running, p->pid);
	}
	else{
	}
}
void check_preempt_curr_mypri(struct rq *rq, struct task_struct *p, int flags) {
	printk("***[MYRR] check_preempt_curr_myrr\n");
}

struct task_struct *pick_next_task_mypri(struct rq *rq, struct task_struct *prev)
{
	struct sched_mypri_entity *next_se = NULL;
	struct task_struct *next_p = NULL;
	struct mypri_rq *mypri_rq = &rq->mypri;
	struct list_head *pos = NULL;
	struct task_struct *pos_p = NULL;
	struct sched_mypri_entity *pos_se = NULL;
	int i=0;

	if(rq->mypri.nr_running==0 ){
		return NULL;
	}
	
	if(prev->sched_class != &mypri_sched_class)
	{
		put_prev_task(rq, prev);
	}

	pos = &mypri_rq->queue;
	
	for(i=0;i<mypri_rq->nr_running; i++)
	{
		pos = pos->next;
		pos_se = container_of(pos, struct sched_mypri_entity, run_list);
		pos_p = container_of(pos_se, struct task_struct, mypri);
		printk(KERN_INFO "\t\t***[MYPRI] show_queue: p->pid=%d, p->pri_num=%d\n", pos_p->pid, pos_se->pri_num);
	}

	next_se = container_of(mypri_rq->queue.next, struct sched_mypri_entity, run_list);
	next_p = container_of(next_se, struct task_struct, mypri);
	printk(KERN_INFO "\t***[MYPRI] pick_next_task: cpu=%d, prev->pid=%d, next_p->pid=%d, nr_running=%d, next_se->pri_num=%d\n", cpu_of(rq), prev->pid, next_p->pid, mypri_rq->nr_running, next_se->pri_num);

	return next_p;
}

void put_prev_task_mypri(struct rq *rq, struct task_struct *p) {
	printk(KERN_INFO "\t***[MYPRI] put_prev_task: do_nothing, p->pid=%d\n",p->pid);
}
int select_task_rq_mypri(struct task_struct *p, int cpu, int sd_flag, int flags)
{
	return task_cpu(p);
}

void set_curr_task_mypri(struct rq *rq){
}
void task_tick_mypri(struct rq *rq, struct task_struct *p, int queued) {
	update_curr_mypri(rq);
}
void prio_changed_mypri(struct rq *rq, struct task_struct *p, int oldprio) { }
/*This routine is called when a task migrates between classes*/
void switched_to_mypri(struct rq *rq, struct task_struct *p)
{
	resched_curr(rq);
}
