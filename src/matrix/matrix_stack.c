#include "matrix_stack.h"

#include <stdlib.h>

typedef struct mat_node_t {
  MAT* mat;
  struct mat_node_t* prev;
} mat_node_t;

mat_node_t *head;
mat_node_t *guard;

void initMatrixStack() {
  head = (mat_node_t*)malloc(sizeof(mat_node_t));
  guard = (mat_node_t*)malloc(sizeof(mat_node_t));
  guard->prev = NULL;
  head->prev = guard;
  head->mat = m_get_ident(4); 
  guard->mat = m_get_ident(4);
}

MAT* topMatrix() {
  return head->mat;
}

MAT* popMatrix() {
  if(head == guard) {
    return guard->mat;
  }
  mat_node_t* last_head = head;
  head = head->prev;
  MAT* mat = last_head->mat;
  free(last_head);
  return mat;
}

void pushMatrix(MAT* matrix) {
  mat_node_t* newHead = (mat_node_t*)malloc(sizeof(mat_node_t));
  newHead->mat = matrix;
  newHead->prev = head;
  head = newHead;
}
