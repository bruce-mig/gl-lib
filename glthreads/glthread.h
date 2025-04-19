#ifndef __GLTHREADS__
#define __GLTHREADS__

#include <stdint.h> // Add this include for uintptr_t

typedef struct glthread_node_ {

   struct glthread_node_ *left;
   struct glthread_node_ *right;
} glthread_node_t;

typedef struct glthread_ {

   glthread_node_t *head;
   unsigned int offset;
} glthread_t;

void glthread_add(glthread_t *lst, glthread_node_t *glnode);

void glthread_remove(glthread_t *lst, glthread_node_t *glnode);

/*Iterative macro to Iterate Over GLTHhreads*/
#define ITERATE_GL_THREADS_BEGIN(lstptr, struct_type, ptr)                     \
   {                                                                           \
      glthread_node_t *_glnode = NULL, *_next = NULL;                          \
      for (_glnode = lstptr->head; _glnode; _glnode = _next) {                 \
         _next = _glnode->right;                                               \
         ptr = (struct_type *)((char *)_glnode - lstptr->offset);

#define ITERATE_GL_THREADS_ENDS                                                \
   }                                                                           \
   }

#define glthread_node_init(glnode)                                             \
   glnode->left = NULL;                                                        \
   glnode->right = NULL;

void init_glthread(glthread_t *glthread, unsigned int offset);

/* Macro to compute the offset of a given field in a given C structure. */
#define offsetof(struct_name, field_name)                                      \
   ((uintptr_t)&((struct_name *)0)->field_name)

#endif /* __GLTHREADS__ */
