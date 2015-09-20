#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_structures.h"
#include "lru_cache.h"

page *head = NULL;
page *tail = NULL;
int current_size = 0;

page* create_from_db_entry(db_entry *entry)
{
  page *p = NULL;
  
  if(entry != NULL){
    p = (page *) malloc(sizeof(page));
    strcpy(p->key, entry->key);
    strcpy(p->value, entry->value);
  }

  return p;
}

/* free all the pages that were allocated during runtime */
void free_cache(){
  page *next, *current;

  next = head;

  while(next != NULL) {
    current = next;
    next = current->next;
    free(current);
  }
}

int swap_in_page(page *p, unsigned int capacity)
{
  if(p == NULL){
    return 0;
  }

  p->prev = NULL;

  if(head == NULL && tail == NULL){
    head = tail = p;
  }
  else{
    if(capacity == current_size){
      evict_page(capacity);
    }

    p->next = head;

    // check whether the queue is empty or not, condition arises after evicting a page from queue of length 1
    if(head != NULL)
      head->prev = p;
    else
      tail = p; // queue is empty, the new page will be the first item in the queue

    head = p;
  }

  current_size++;
  
  return 1;
}

int evict_page(unsigned int capacity)
{
  page *oldest;
  
  if(current_size < 1){
    return 0;
  }

  oldest = tail;
  
  if(tail->prev == NULL){
    head = tail = NULL;
  }
  else{
    tail = tail->prev;
    tail->next = NULL;
  }

  free(oldest);

  current_size--;

  return 1;
}

int access_page(page *p, unsigned int capacity)
{
  page *next, *prev;
    
  if(p == NULL ||current_size == 0){
    return 0;
  }

  // do nothing if the accessed page is at front

  if(p == head){
    return 1;
  }
  
  prev = p->prev;
  next = p->next;

  if(prev != NULL)
    prev->next = next;

  if(next != NULL)
    next->prev = prev;

  current_size--;

  return swap_in_page(p, capacity);
}

/* test code */

void display()
{
  page *current;

  current = head;

  while(current != NULL){
    printf("%s ", current->value);
    current = current->next;
  }

  printf("\n");
}

int main()
{
  page *p1 = (page *) malloc(sizeof(page));
  page *p2 = (page *) malloc(sizeof(page));
  page *p3 = (page *) malloc(sizeof(page));
  page *p4 = (page *) malloc(sizeof(page));

  strcpy(p1->value, "a");
  strcpy(p2->value, "b");
  strcpy(p3->value, "c");
  strcpy(p4->value, "d");

  swap_in_page(p1, 3);
  display();
  swap_in_page(p2, 3);
  display();
  swap_in_page(p3, 3);
  display();
  swap_in_page(p4, 3);
  display();
  access_page(p2, 3);
  display();
  access_page(p4, 3);
  display();
  access_page(p2, 3);
  display();
  access_page(p3, 3);
  display();
  access_page(p3, 3);
  display();
  
  free_cache();
  
  return 0;
}
