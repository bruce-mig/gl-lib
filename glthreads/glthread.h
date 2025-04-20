/*
 * =====================================================================================
 *
 *       Filename:  glthread.h
 *
 *    Description:  This file defines the Data structure and APIs for Glue
 *    thread
 *
 *        Version:  1.0
 *        Created:  Sunday 16 February 2025 17:48:36  CAT
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:  BRUCE MIGERI, Software Developer (BM), bmigeri@gmail.com
 *
 *        This file is part of the bruce-mig distribution
 *       (https://github.com/bruce-mig). Copyright (c) 2025 Bruce Migeri. This
 *       program is free software: you can redistribute it and/or modify it
 *       under the terms of the GNU General Public License as published by the
 *       Free Software Foundation, version 3.
 *
 *        This program is distributed in the hope that it will be useful, but
 *        WITHOUT ANY WARRANTY; without even the implied warranty of
 *        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *        General Public License for more details.
 *
 *        You should have received a copy of the GNU General Public License
 *        along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * =====================================================================================
 */

#ifndef __GLTHREADS__
#define __GLTHREADS__

#include <stdint.h>

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
