/*
 * =====================================================================================
 *
 *       Filename:  glthread.c
 *
 *    Description:  Implementation of glthread Library
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

#include "glthread.h"
#include <stdio.h>
#include <stdlib.h>

/*Private function to add a new_node right after curr_node*/
static void _glthread_add_next(glthread_node_t *curr_node,
                               glthread_node_t *new_node) {

   if (!curr_node->right) {
      curr_node->right = new_node;
      new_node->left = curr_node;
      return;
   }

   glthread_node_t *temp = curr_node->right;
   curr_node->right = new_node;
   new_node->left = curr_node;
   new_node->right = temp;
   temp->left = new_node;
}

/*Fn to insert a new GLnode into a glthread at the first position
 * in a glthread i.e. new node becomes a head
 * */
void glthread_add(glthread_t *lst, glthread_node_t *glnode) {

   glnode->left = NULL;
   glnode->right = NULL;
   if (!lst->head) {
      lst->head = glnode;
      return;
   }
   glthread_node_t *head = lst->head;
   _glthread_add_next(glnode, head);
   lst->head = glnode;
}

static void _remove_glthread(glthread_node_t *glnode) {

   if (!glnode->left) {
      if (glnode->right) {
         glnode->right->left = NULL;
         glnode->right = 0;
         return;
      }
      return;
   }
   if (!glnode->right) {
      glnode->left->right = NULL;
      glnode->left = NULL;
      return;
   }

   glnode->left->right = glnode->right;
   glnode->right->left = glnode->left;
   glnode->left = 0;
   glnode->right = 0;
}

/*API to remove a glnode from glthread*/
void glthread_remove(glthread_t *lst, glthread_node_t *glnode) {

   glthread_node_t *head = lst->head;
   /*If the node being removed is the head node itself, then update the
    * head*/
   if (head == glnode) {
      lst->head = head->right;
   }
   _remove_glthread(glnode);
}

void init_glthread(glthread_t *glthread, unsigned int offset) {

   glthread->head = NULL;
   glthread->offset = offset;
}
