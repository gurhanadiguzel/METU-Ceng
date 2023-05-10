#include <stdio.h>
#include <stdlib.h>
#include "lab3.h"

Node* create_list(int* data, int data_len)
{
  int i = 0;
  Node* head = NULL;
  Node* prev_node = NULL;
  Node* new_node = NULL;
  for(i=0; i < data_len; i++)
  {
    new_node = (Node*)malloc(1 * sizeof(Node));
    new_node->data = data[i];
    new_node->next = NULL;
    if (i == 0)
    {
      head = new_node;
    }
    else
    {
      prev_node->next = new_node;
    }
    prev_node = new_node;
  }
  return head;
}

void print_list(Node* head)
{
  while(head != NULL)
  {
    printf("%d", head->data);
    if(head->next != NULL)
    {
      printf(" -> ");
    }
    else
    {
      printf("\n");
    }
    head = head->next;
  }
}

void print_student_array(Student** array, int student_and_teacher_count)
{
  int i = 0;
  for (i=0; i<student_and_teacher_count; i++)
  {
    printf("studentID: %d (best_teacherID: %d)", array[i]->studentID, array[i]->best_teacher->teacherID);
    if (i < student_and_teacher_count-1)
    {
      printf(" -> ");
    }
    else
    {
      printf("\n");
    }
  }
}

void create_student_array_with_teachers_test_1()
{
  int student_id_list[8] = {14, 12, 15, 43, 32, 27, 55, 21};
  int teacher_id_list[8] = {21, 12, 18, 55, 68, 24, 85, 72};
  int student_and_teacher_count = 8;
  Student** returned_array = create_student_array_with_teachers(student_id_list, teacher_id_list, student_and_teacher_count);
  print_student_array(returned_array, student_and_teacher_count);
  /* Expected Output: studentID: 14 (best_teacherID: 21) -> studentID: 12 (best_teacherID: 12) -> studentID: 15 (best_teacherID: 18) -> studentID: 43 (best_teacherID: 55) -> studentID: 32 (best_teacherID: 68) -> studentID: 27 (best_teacherID: 24) -> studentID: 55 (best_teacherID: 85) -> studentID: 21 (best_teacherID: 72) */
}

void create_student_array_with_teachers_test_2()
{
  int student_id_list[11] = {47, 105, 68, 23, 88, 92, 165, 221, 16, 154, 76};
  int teacher_id_list[11] = {198, 222, 59, 67, 91, 28, 25, 203, 305, 69, 11};
  int student_and_teacher_count = 11;
  Student** returned_array = create_student_array_with_teachers(student_id_list, teacher_id_list, student_and_teacher_count);
  print_student_array(returned_array, student_and_teacher_count);
  /* Expected Output: studentID: 47 (best_teacherID: 198) -> studentID: 105 (best_teacherID: 222) -> studentID: 68 (best_teacherID: 59) -> studentID: 23 (best_teacherID: 67) -> studentID: 88 (best_teacherID: 91) -> studentID: 92 (best_teacherID: 28) -> studentID: 165 (best_teacherID: 25) -> studentID: 221 (best_teacherID: 203) -> studentID: 16 (best_teacherID: 305) -> studentID: 154 (best_teacherID: 69) -> studentID: 76 (best_teacherID: 11) */
}

void create_student_array_with_teachers_test_3()
{
  int student_id_list[4] = {75, 66, 666, 45};
  int teacher_id_list[4] = {75, 66, 666, 45};
  int student_and_teacher_count = 4;
  Student** returned_array = create_student_array_with_teachers(student_id_list, teacher_id_list, student_and_teacher_count);
  print_student_array(returned_array, student_and_teacher_count);
  /* Expected Output: studentID: 75 (best_teacherID: 75) -> studentID: 66 (best_teacherID: 66) -> studentID: 666 (best_teacherID: 666) -> studentID: 45 (best_teacherID: 45) */
}

void insert_tail_test_1()
{
  int data[6] = {55, 86, 24, 9, 6, 101};
  Node* head = create_list(data, 6);
  Node* returned_head = insert_tail(head, 200);
  print_list(returned_head);
  /* Expected Output: 55 -> 86 -> 24 -> 9 -> 6 -> 101 -> 200 */
}

void insert_tail_test_2()
{
  Node* returned_head = insert_tail(NULL, 25);
  print_list(returned_head);
  /* Expected Output: 25 */
}

void remove_kth_node_reversely_test_1()
{
  int data[7] = {57, 85, 3, 25, 55, 108, 19};
  Node* head = create_list(data, 7);
  Node* returned_head = remove_kth_node_reversely(head, 2);
  print_list(returned_head);
  /* Expected Output: 57 -> 85 -> 3 -> 25 -> 108 -> 19 */
}

void remove_kth_node_reversely_test_2()
{
  int data[9] = {58, 65, 222, 546, 486, 321, 200, 42, 89};
  Node* head = create_list(data, 9);
  Node* returned_head = remove_kth_node_reversely(head, 0);
  print_list(returned_head);
  /* Expected Output: 58 -> 65 -> 222 -> 546 -> 486 -> 321 -> 200 -> 42 */
}

void remove_kth_node_reversely_test_3()
{
  int data[6] = {78, 560, 35, 45, 98, 230};
  Node* head = create_list(data, 6);
  Node* returned_head = remove_kth_node_reversely(head, 5);
  print_list(returned_head);
  /* Expected Output: 560 -> 35 -> 45 -> 98 -> 230 */
}

void find_occurrences_of_second_list_test_1()
{
  int data_1[13] = {233, 455, 677, 455, 677, 10, 455, 677, 5, 455, 677, 8, 15};
  Node* head = create_list(data_1, 13);
  int data_2[2] = {455, 677};
  Node* second_head = create_list(data_2, 2);
  printf("%d\n", find_occurrences_of_second_list(head, second_head));
  /* Expected Output: 4 */
}

void find_occurrences_of_second_list_test_2()
{
  int data_1[13] = {43, 58, 43, 58, 43, 58, 43, 58, 43, 58, 43, 3, 22};
  Node* head = create_list(data_1, 13);
  int data_2[3] = {43, 58, 43};
  Node* second_head = create_list(data_2, 3);
  printf("%d\n", find_occurrences_of_second_list(head, second_head));
  /* Expected Output: 5 */
}

void find_occurrences_of_second_list_test_3()
{
  int data_1[9] = {11, 666, 666, 666, 666, 666, 666, 666, 666};
  Node* head = create_list(data_1, 9);
  int data_2[3] = {666, 666, 666};
  Node* second_head = create_list(data_2, 3);
  printf("%d\n", find_occurrences_of_second_list(head, second_head));
  /* Expected Output: 6 */
}

void find_occurrences_of_second_list_test_4()
{
  int data_1[13] = {789, 66, 66, 66, 45, 66, 66, 200, 66, 75, 66, 66, 66};
  Node* head = create_list(data_1, 13);
  int data_2[1] = {66};
  Node* second_head = create_list(data_2, 1);
  printf("%d\n", find_occurrences_of_second_list(head, second_head));
  /* Expected Output: 9 */
}

void find_occurrences_of_second_list_test_5()
{
  int data_1[18] = {105, 390, 45, 401, 105, 105, 390, 45, 401, 105, 390, 45, 401, 401, 105, 390, 45, 401};
  Node* head = create_list(data_1, 18);
  int data_2[4] = {105, 390, 45, 401};
  Node* second_head = create_list(data_2, 4);
  printf("%d\n", find_occurrences_of_second_list(head, second_head));
  /* Expected Output: 4 */
}

void cut_and_paste_test_1()
{
  int data[8] = {12, 45, 98, 25, 108, 80, 4, 255};
  Node* head = create_list(data, 8);
  Node* returned_head = cut_and_paste(head, 5, 4);
  print_list(returned_head);
  /* Expected Output: 12 -> 45 -> 98 -> 25 -> 80 -> 108 -> 4 -> 255 */
}

void cut_and_paste_test_2()
{
  int data[7] = {68, 115, 540, 28, 354, 4, 95};
  Node* head = create_list(data, 7);
  Node* returned_head = cut_and_paste(head, 4, 0);
  print_list(returned_head);
  /* Expected Output: 354 -> 68 -> 115 -> 540 -> 28 -> 4 -> 95 */
}

void cut_and_paste_test_3()
{
  int data[9] = {58, 45, 1,  9, 152, 654, 257, 310, 611};
  Node* head = create_list(data, 9);
  Node* returned_head = cut_and_paste(head, 8, 2);
  print_list(returned_head);
  /* Expected Output: 58 -> 45 -> 611 -> 1 -> 9 -> 152 -> 654 -> 257 -> 310 */
}

void cut_and_paste_test_4()
{
  int data[11] = {196, 12, 18, 657, 325, 20, 128, 987, 2, 56, 23};
  Node* head = create_list(data, 11);
  Node* returned_head = cut_and_paste(head, 10, 0);
  print_list(returned_head);
  /* Expected Output: 23 -> 196 -> 12 -> 18 -> 657 -> 325 -> 20 -> 128 -> 987 -> 2 -> 56 */
}

void sum_symmetric_pairs_test_1()
{
  int data[12] = {54, 85, 660, 204, 650, 305, 880, 450, 48, 105, 160, 500};
  Node* head = create_list(data, 12);
  Node* returned_head = sum_symmetric_pairs(head);
  print_list(returned_head);
  /* Expected Output: 554 -> 245 -> 765 -> 252 -> 1100 -> 1185 */
}

void sum_symmetric_pairs_test_2()
{
  int data[14] = {55, 68, 205, 102, 98, 600, 584, 32, 258, 85, 355, 211, 456, 123};
  Node* head = create_list(data, 14);
  Node* returned_head = sum_symmetric_pairs(head);
  print_list(returned_head);
  /* Expected Output: 178 -> 524 -> 416 -> 457 -> 183 -> 858 -> 616 */
}

void sum_symmetric_pairs_test_3()
{
  int data[16] = {5, 302, 101, 10, 8, 65, 98, 78, 852, 67, 52, 33, 520, 48, 88, 222};
  Node* head = create_list(data, 16);
  Node* returned_head = sum_symmetric_pairs(head);
  print_list(returned_head);
  /* Expected Output: 227 -> 390 -> 149 -> 530 -> 41 -> 117 -> 165 -> 930 */
}

void sum_symmetric_pairs_test_4()
{
  int data[20] = {8, 16, 2, 255, 3, 65, 84, 12, 98, 54, 147, 369, 987, 311, 159, 357, 456, 73, 214, 34};
  Node* head = create_list(data, 20);
  Node* returned_head = sum_symmetric_pairs(head);
  print_list(returned_head);
  /* Expected Output: 42 -> 230 -> 75 -> 711 -> 360 -> 224 -> 395 -> 999 -> 467 -> 201 */
}

int main()
{
  /* Run test case function here*/
  /*
  create_student_array_with_teachers_test_1();
  create_student_array_with_teachers_test_2();
  create_student_array_with_teachers_test_3();
  insert_tail_test_1();
  insert_tail_test_2();
  remove_kth_node_reversely_test_1();
  remove_kth_node_reversely_test_2();
  remove_kth_node_reversely_test_3();
  find_occurrences_of_second_list_test_1();
  find_occurrences_of_second_list_test_2();
  find_occurrences_of_second_list_test_3();
  find_occurrences_of_second_list_test_4();
  find_occurrences_of_second_list_test_5();
  cut_and_paste_test_1();
  cut_and_paste_test_2();
  cut_and_paste_test_3();
  cut_and_paste_test_4();
  sum_symmetric_pairs_test_1();
  sum_symmetric_pairs_test_2();
  sum_symmetric_pairs_test_3();
  sum_symmetric_pairs_test_4();
  */
  return 0;
}