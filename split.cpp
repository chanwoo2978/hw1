/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  //base case
  if(!in){
    evens = nullptr;
    odds = nullptr;
    return;
  }
  else if((in->value) % 2 == 0){//check if val is even, then move to pointer of even
    evens = in;
    split(in->next, odds->next, evens);
  }
  else{//for odd
    odds = in;
    split(in->next, odds, evens->next);
  }

  /*
  //base case end of list
  if(in == nullptr){
    return;
  }
  //check even numbers
  if(in->value %2 == 0){
    if(evens == nullptr){//if even list is empty
      evens = in;
    }else{
      Node* evenTail = evens;
      while(evenTail->next != nullptr){
        evenTail = evenTail->next;
      }
      evenTail->next = in;
    }
  }else{
    //check odd numbers
    if(odds == nullptr){
      odds = in;
    }else{
      Node* oddTail = odds;
      while(oddTail->next != nullptr){
        oddTail = oddTail->next;
      }
      oddTail->next = in;
    }
  }

  Node* nextNode = in->next;
  in->next = nullptr;
  split(nextNode, odds, evens);
  */
 
}

/* If you needed a helper function, write it here */
