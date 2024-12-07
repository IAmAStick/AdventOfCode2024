#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct report{
    int level[10];
    struct report *next;
    int rep_level_num;
} report_t;

FILE *file;

report_t *new_report()
{
    report_t *new_rep_node = (report_t *)malloc(sizeof(report_t));
    if(new_rep_node == NULL){
        printf("couldn't malloc new report bruh\n");
        return NULL;
    }
    new_rep_node->rep_level_num = 0;
    return(new_rep_node);
}

report_t *read_file(FILE *file)
{
    report_t *head = (report_t*)malloc(sizeof(report_t));
    report_t *tmp = head;
    char row[30];
    int i = 0;
    while(fgets(row, 30, file)!=NULL){
        tmp->level[i] = atoi(strtok(row, " "));
        while(tmp->level[i]){
            i++;
            tmp->level[i] = atoi(strtok(NULL, " "));
        }
        tmp->rep_level_num = i;
        i = 0;
        tmp->next = new_report();
        tmp = tmp->next;
        tmp->next = NULL;
    }
    return(head);
}

int is_safe(report_t *head)
{
    report_t *comp = head;
    int safe_check = 1;
    int unsafe_cnt = 0;
    if((comp->level[0]==comp->level[1])||(abs(comp->level[0] - comp->level[1])<1)||(abs(comp->level[0] - comp->level[1])>3)){
        safe_check = 0;

    }
    for (int blob = 1; blob < comp->rep_level_num - 1; blob++) {     
        if((comp->level[0] > comp->level[1])){
            if((comp->level[blob] <= comp->level[blob+1])||(abs(comp->level[blob] - comp->level[blob+1])<1)||(abs(comp->level[blob] - comp->level[blob+1])>3)){
                safe_check = 0;
                break;
            }
        }
        if((comp->level[0] < comp->level[1])){
            if((comp->level[blob] >= comp->level[blob+1])||(abs(comp->level[blob] - comp->level[blob+1])<1)||(abs(comp->level[blob] - comp->level[blob+1])>3)){
                safe_check = 0;
                break;
            }
        }
    }
    return(safe_check);
}

int how_many_safe(report_t *head)
{   
    int safe_cnt = 0;
    int blob = 1;
    int safe = 1; 
    report_t *comp = head;
    while(comp->next != NULL){
        safe = is_safe(comp);
        if(safe == 1){
            safe_cnt++;
        }
        comp=comp->next;
        blob = 1;
    }
    return(safe_cnt);
}

int main()
{
    file = fopen("test.txt", "r");
        if (file == NULL) {
            printf("Error: Could not open file %s\n", "list_day1_1.txt");
            return 1;
        }
    int temp = 0;

    report_t *head = read_file(file);
    int cnt_safe = how_many_safe(head);
    printf("safe cnt %d\n", cnt_safe);
}