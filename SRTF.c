/**
Doubly Linked List Shortest Remaining Time Scheduling
FILE	SRTF.c
DATA	2017-06-05
AUTHOR	이영현(Lee Young Hyun)
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct priority_queue *queue_pointer;
struct priority_queue{
        int pid;
        int priority;
        int computing_time;
        int turn_around_time;
        int counting_time;
        queue_pointer left_link, right_link;
};

typedef struct queue_head *head_pointer;
struct queue_head{
        queue_pointer left_link;
        queue_pointer right_link;
};

head_pointer queue;

int inter_time;

void initialize_queue();
int insert_queue(int pid, int priority, int computing_time);
void scheduling_queue();

int main(void){

        FILE *fp;
        int type, process_id, priority, computing_time;

        fp = fopen("input_file.txt", "r");
        if (fp == NULL) printf(" File open failed. \n");

        initialize_queue();
		inter_time = 0;

		printf("----------------------------------------------------------------\n");
		printf("Process_id\tpriority\tcomputing_time\tturn_around_time\n");
        while (!feof(fp))
        {
                fscanf(fp, "%d %d %d %d", &type, &process_id, &priority, &computing_time);
                if (type == 0)
                {
                        insert_queue(process_id, priority, computing_time);
                }
                else if (type == 1)
                {
                        scheduling_queue();
                }
                else if (type == -1)
                {
                        while (queue->right_link != NULL)
                        {
                                scheduling_queue();
                        }
                }
        }

        fclose(fp);
        return 0;
}

void initialize_queue(void){

        queue = (head_pointer)malloc(sizeof(head_pointer));
        queue->left_link = NULL;
        queue->right_link = NULL;
}

int insert_queue(int pid, int priority, int computing_time){

        queue_pointer process;
        queue_pointer new_process = (queue_pointer)malloc(sizeof(queue_pointer));
        new_process->left_link = (queue_pointer)malloc(sizeof(queue_pointer));
        new_process->right_link = (queue_pointer)malloc(sizeof(queue_pointer));
		new_process->left_link = NULL;
        new_process->right_link = NULL;
		new_process->pid = pid;
        new_process->priority = priority;
        new_process->computing_time = computing_time;
        new_process->turn_around_time = inter_time;
		new_process->counting_time = computing_time;

        if (queue->right_link == NULL){
                queue->right_link = new_process;
                new_process->left_link = queue->right_link;
                new_process->right_link = NULL;
        }
        else
        {
                process = queue->right_link;
                if (process->counting_time > computing_time)
                {
                        new_process->left_link = queue->right_link;
                        new_process->right_link = process;
                        queue->right_link = new_process;
                        process->left_link = new_process;
                }
                else
                {
                        while (process->counting_time <= computing_time)
                        {

                                if (process->right_link == NULL)
                                {
                                        process->right_link = new_process;
                                        new_process->left_link = process;
                                        new_process->right_link = NULL;
                                        break;
                                }
                                process = process->right_link;
                        }

                        new_process->left_link = process->left_link;
                        new_process->right_link = process;
                        process->left_link->right_link = new_process;
                        process->left_link = new_process;

                }
        }
        return 0;
}

void scheduling_queue(void){
        queue_pointer process = (queue_pointer)malloc(sizeof(queue_pointer));
        int counting = 20;
        int dummy = 0;

        process = queue->right_link;

        dummy = process->counting_time;

        while (counting != 0){
                dummy = process->counting_time;
                while (dummy != 0 && counting != 0){
                        dummy--;
                        inter_time++;
                        counting--;
                        process->counting_time = dummy;
                }
                if (dummy == 0){
                        process->turn_around_time = inter_time - process->turn_around_time;
                        printf("%d \t \t %d \t \t %d \t \t %d\n", process->pid, process->priority, process->computing_time, process->turn_around_time);
                        if (queue->right_link->right_link == NULL)
                        {
                                queue->right_link = NULL;
                                process->left_link = NULL;
                                process->right_link = NULL;
                        }
                        else
                        {
                                queue->right_link = process->right_link;
                                process->right_link->left_link = queue->right_link;
                                process->left_link = NULL;
                                process->right_link = NULL;
                        }
                        break;
                }
        }

        if (dummy!=0)
                process->counting_time = dummy;
}
