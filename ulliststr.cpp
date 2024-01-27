#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val)
{
  //check if the list is empty, if so allocate new node
  if(empty()){//scenario 4 from video, allocate a new node
    Item* newItem = new Item();
    head_ = newItem;
    tail_ = newItem;
    newItem->val[0] = val;//it is easier to put value in 0 index and push back
    newItem->last++;
  }
  else if((tail_->last) == ARRSIZE){//scenario 2 it no more space in item, then allocate new node
    Item* newItem = new Item();//allocate a new node in case no more space
    
    tail_->next = newItem;
    newItem->prev = tail_;
    tail_ = newItem;
    newItem->val[0] = val;//insert data into new allocated node

    newItem->last++;
  }else{//check if tail is not full
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  size_++;
  
/*
else if(head_ == nullptr){
  Item* n = new Item();
  head_ = n;
  tail_ = n;
  size_++;
}else{
  Item* n =new Item();
  n->val = val;
  n->next = nullptr;
  n->prev = nullptr;

  Item* temp = n;
  tail_->next = temp;
  temp->prev = tail_;
  tail_->next = temp;
  tail_ = temp;
  size_++;
}*/
  
  
}

void ULListStr::pop_back()
{
  /*
  if(empty()){
    return;
  }*/
  if(tail_ == nullptr){//check empty list
    return;
  }
  else if(size_ == 1){//when list has 1 element, just pop 1 element
    delete tail_;
    tail_ = nullptr;
    head_ = nullptr;
  }
  else if(tail_->last == 1){//check if the list has 1 element
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = nullptr;
  }else{//else node has more than 1 elements 
    tail_->last--;
  }
  size_--;
}

void ULListStr::push_front(const std::string& val)
{
  //check if the list is empty, if so allocate new node
  if(empty()){//scenario 4 from video, allocate a new node
    Item* newItem = new Item();
    head_ = newItem;
    tail_ = newItem;
    newItem->val[0] = val;//it is easier to put value in 0 index and push front
    newItem->last++;
    size_++; 
  }//if head is full
  else if(head_->first == 0){//scenario 2 it no more space in item, then allocate new node
    Item* newItem = new Item(); 
    //std::cout << "push front allocate head full" << std::endl;
    newItem->next = head_;
    head_->prev = newItem; 
    head_ = newItem; 
    //allocate node and put data at the end of arr of new node
    newItem->val[ARRSIZE - 1] = val; //end of the arr ARRSIZE -1
    newItem->last = ARRSIZE; 
    newItem->first = ARRSIZE-1; 
    size_++; 
  }
  else{//check if head is not full
    head_->val[head_->first - 1] = val; 
    head_->first--; 
    size_++; 
  }
  /*
  else if(head_->last !=ARRSIZE){
    head_->val[head_->first-1] = val; 
    head_->first--; 
  }*/
}
//same way as pop back but pop from front
void ULListStr::pop_front()
{
  if(head_ == nullptr){//check if 
    return;
  }
  else if(size_ == 1){//condition if list has 1 element in arr
    Item* newItem = head_; 
    delete newItem; 
    head_ = nullptr;
    tail_ = nullptr;
    size_--; 
  }
  else if(head_->first == ARRSIZE - 1){
    head_ = head_->next; 
    delete head_->prev; 
    head_->prev = nullptr; 
    size_--; 
  }
  else{//more than 1 element in arr
    head_->first++; 
    size_--; 
  }

}

//assume the list is not empty.
//if someone calls front() or back() on an empty list, they can
//have no expectation for what will be returned.
//(or even cause the program to crash)
std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1]; //end of the list last-1
}
std::string const & ULListStr::front() const
{
  return head_->val[head_->first]; 
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  //cannot fix valgrind.......
  
  if(loc >= size_ || loc < 0){
    return nullptr;//no node, empty list
  }else{
    Item* newItem = head_;//allocate node
    int loc_current = 0;
    while(newItem != nullptr){//loop til the end of the node
      for(int i = newItem->first; i < newItem->last; i++){
        if(loc_current == loc){//loop til find the location
          return &(newItem->val[i]);//dereference of pointer to get val
        }
        loc_current++;//increment loc_current to keep track of loop
      }
      newItem = newItem->next;
    }
    return NULL;//nothing
  }
  
}