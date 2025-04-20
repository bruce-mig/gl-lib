/*
 * =====================================================================================
 *
 *       Filename:  main.c
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
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct emp_ {

   char name[30];
   unsigned int salary;
   char designation[30];
   unsigned int emp_id;
   glthread_node_t glnode;
} emp_t;

void print_emp_details(emp_t *emp) {

   printf("Employee name = %s\n", emp->name);
   printf("salary = %u\n", emp->salary);
   printf("designation = %s\n", emp->designation);
   printf("emp_id = %u\n", emp->emp_id);
}

int main(int argc, char **argv) {

   emp_t *emp1 = calloc(1, sizeof(emp_t));
   strncpy(emp1->name, "Tino", strlen("Tino"));
   emp1->salary = 500;
   strncpy(emp1->designation, "HR", strlen("HR"));
   emp1->emp_id = 21;
   glthread_node_init((&emp1->glnode));

   emp_t *emp2 = calloc(1, sizeof(emp_t));
   strncpy(emp2->name, "Bruce", strlen("Bruce"));
   emp2->salary = 1500;
   strncpy(emp2->designation, "SE3", strlen("SE3"));
   emp2->emp_id = 32;
   glthread_node_init((&emp2->glnode));

   emp_t *emp3 = calloc(1, sizeof(emp_t));
   strncpy(emp3->name, "Migeri", strlen("Migeri"));
   emp3->salary = 600;
   strncpy(emp3->designation, "SE4", strlen("SE4"));
   emp3->emp_id = 27;
   glthread_node_init((&emp3->glnode));

   /*Now Create a glthread*/
   glthread_t *emp_list = calloc(1, sizeof(glthread_t));
   init_glthread(emp_list, offsetof(emp_t, glnode));

   /*Now insert the records in glthread*/
   glthread_add(emp_list, &emp1->glnode);
   glthread_add(emp_list, &emp2->glnode);
   glthread_add(emp_list, &emp3->glnode);

   /*Walk over glthread*/
   emp_t *ptr = NULL;
   ITERATE_GL_THREADS_BEGIN(emp_list, emp_t, ptr) { print_emp_details(ptr); }
   ITERATE_GL_THREADS_ENDS;

   /*Let us remove one record at random*/

   glthread_remove(emp_list, &emp2->glnode);
   printf("\nprinting again . . . \n");

   ITERATE_GL_THREADS_BEGIN(emp_list, emp_t, ptr) { print_emp_details(ptr); }
   ITERATE_GL_THREADS_ENDS;

   /*Free all Dynamicall allocations*/
   ITERATE_GL_THREADS_BEGIN(emp_list, emp_t, ptr) {

      glthread_remove(emp_list, &ptr->glnode);
      free(ptr);
   }
   ITERATE_GL_THREADS_ENDS;
   free(emp_list);

   return 0;
}
