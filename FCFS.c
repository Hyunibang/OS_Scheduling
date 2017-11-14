/**
Doubly Linked List FCFS Scheduling
FILE	FCFS.c
DATA	2017-06-05
AUTHOR	이영현(Lee Young Hyun)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct process *process_pointer;
struct process {
	
	int pid;
	int priority;
	int computing_time;
	int turn_around_time;
	int process_in_time;

	process_pointer left_link;
	process_pointer right_link;
};

typedef struct process_head *head_pointer;
struct process_head {
	
	process_pointer left_link;
	process_pointer right_link;
};

head_pointer head_queue;

void initialize_queue(void);
int insert_queue(int, int, int);
int scheduling_queue(int);


int in_time, out_time;



int main(void){

	FILE *fp;
	int type, Process_id, Priority, computing_time, turn_around_time;
	fp = fopen("input_file.txt", "r");
	if(fp == NULL){
		printf(" File open failed. \n");
	}

	initialize_queue();

	in_time = 0;
	out_time = 0;
	turn_around_time = 20;

	printf("----------------------------------------------------------------\n");
	printf("Process_id\tpriority\tcomputing_time\tturn_around_time\n");
	
	while(!feof(fp)){
		fscanf(fp, "%d %d %d %d", &type, &Process_id, &Priority, &computing_time);

		if(type == 0){

			insert_queue(Process_id, Priority, computing_time);

		}else if(type == 1){

			in_time += turn_around_time;
			scheduling_queue(turn_around_time);

		}else if(type == -1){

			while(head_queue->left_link != head_queue->right_link){

			scheduling_queue(turn_around_time);

			}
		}
	}

	fclose(fp);
	return 0;
}



void initialize_queue(void){

	head_queue = (head_pointer)malloc(sizeof(head_pointer));
	head_queue->left_link = NULL;
	head_queue->right_link = NULL;
}


int insert_queue(int Process_id, int priority, int computing_Time){

	process_pointer process = (process_pointer)malloc(sizeof(process_pointer));
	process_pointer maked_process = (process_pointer)malloc(sizeof(process_pointer));
	process->left_link = (process_pointer)malloc(sizeof(process_pointer));
	process->right_link = (process_pointer)malloc(sizeof(process_pointer));	
	process->left_link = NULL;
	process->right_link = NULL;
	process->pid = Process_id;
	process->priority = priority;
	process->computing_time = computing_Time;
	process->turn_around_time = 0;
	process->process_in_time = in_time;

	if(head_queue->left_link == NULL){

		head_queue->left_link = process;
		head_queue->right_link = process;
		process->left_link = head_queue->left_link;
		process->right_link = head_queue->right_link;
	}
	else{

		maked_process = head_queue->left_link;

		while( maked_process != head_queue->right_link){

			maked_process = maked_process->right_link;
		}
		process->left_link = maked_process;
		process->right_link = head_queue->right_link;
		maked_process->right_link = process;
		head_queue->right_link = process;
	}
		

	return process->pid;

}


int scheduling_queue(int turn_around_time){

	process_pointer process = (process_pointer)malloc(sizeof(process_pointer));
	process->left_link = (process_pointer)malloc(sizeof(process_pointer));
	process->right_link = (process_pointer)malloc(sizeof(process_pointer));
	process = head_queue->left_link;

	if (process == NULL){

		printf("No");
	}
	else{

		if (process->computing_time >= turn_around_time){

			process->computing_time -= turn_around_time;
			process->turn_around_time += turn_around_time;

		}
		else if (process->computing_time < turn_around_time){

			turn_around_time -= process->computing_time;
			process->turn_around_time += process->computing_time;	
			process->computing_time = 0;					

		}

		if (process->computing_time == 0){

			out_time += process->turn_around_time;
			printf("%d \t \t %d \t \t %d \t \t %d\n", process->pid, process->priority, process->turn_around_time, (out_time - process->process_in_time));
			if (head_queue->left_link == head_queue->right_link)
				return process->turn_around_time;
			else{	

				head_queue->left_link = process->right_link;
				process->left_link->right_link = head_queue->left_link;	

			}
		}
	}

	if (head_queue->left_link == head_queue->right_link){

		scheduling_queue(turn_around_time);
	}

	return process->turn_around_time;
}
