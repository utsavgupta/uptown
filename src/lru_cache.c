#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_structures.h"
#include "lru_cache.h"

// NOTE: Need to add a function for evicting in-memory pages while deleting key value pairs from data store

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

  // update tail pointer if item being accessed is the last element
  
  if(p == tail){
    tail = p->prev;
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

char* lookup_cache(char* key, unsigned int capacity)
{
  page *current;
  
  if(capacity < 1 || head == NULL){
    return NULL;
  }

  current = head;

  while(current != NULL){
    if(strcmp(current->key, key) == 0){
      access_page(current, capacity);
      return current->value;
    }

    current = current->next;
  }

  return NULL;
}

void write_to_cache(db_entry *entry, unsigned int capacity)
{
  page *current;
  
  current = head;

  while(current != NULL){
    if(strcmp(current->key, entry->key) == 0){
      strcpy(current->value, entry->value);
      access_page(current, capacity);
      return;
    }

    current = current->next;
  }

  current = create_from_db_entry(entry);
  swap_in_page(current, capacity);
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

// for testing

void print_cache()
{
  page *current;

  current = head;

  printf("[");

  while(current){
    printf("%s, ", current->key);
    current = current->next;
  }

  printf("]\n");
}
