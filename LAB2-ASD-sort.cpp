#include <cstdlib>
#include <ctime>
#include <iostream>

#include "ASD-sort.h"

using namespace std;

/**************************************************/
/*       funzioni ausiliare                      */
/**************************************************/

/*scambia le posizione i e j in v assumendo che siano posizione correte*/
void swap_ind(vector<int>& v, int i, int j)
{ 
  int tmp = v.at(j);
  v.at(j) = v.at(i);
  v.at(i) = tmp;
}

/**************************************************/
/*       funzioni da implementare                 */
/**************************************************/

void quickSortTrivial(vector<int>& v) {
   quickSortTrivialHelper(v, 0, v.size() - 1);
}

void quickSortTrivialHelper(vector<int>& v, int low, int high) {
   if (low < high) {
      int pivotIndex = partition(v, low, high);
      quickSortTrivialHelper(v, low, pivotIndex - 1);
      quickSortTrivialHelper(v, pivotIndex + 1, high);
   }
}

/*quicksort randomizzato*/
void quickSortRandom(vector<int>& v) {
   quickSortRandomHelper(v, 0, v.size() - 1);
}

void quickSortRandomHelper(vector<int>& v, int low, int high) {
   if (low < high) {

      srand(time(0));
      int randomPivotIndex = low + rand() % (high - low + 1);
      swap_ind(v, low, randomPivotIndex);
      int pivotIndex = partition(v, low, high);

      quickSortRandomHelper(v, low, pivotIndex - 1);
      quickSortRandomHelper(v, pivotIndex + 1, high);
   }
}

/*partition per entrambi i quicksort*/

int partition(vector<int>& v, int low, int high) {
   int pivot = v[low];
   int i = low + 1;
   for (int j = low + 1; j <= high; ++j) {
      if (v[j] < pivot) {
         swap_ind(v, i, j);
         ++i;
      }
   }
   swap_ind(v, low, i - 1);
   return i - 1;
}

/**************************************************/
/*      funzioni implementate                     */
/**************************************************/

/* selection sort in place*/
void selectionSort(vector<int>& v){
   unsigned int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   { 
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j){
        if (v.at(current_min_index) > v.at(j)){
            current_min_index = j;
         }
     }
     swap_ind(v, i, current_min_index);
   }
}

/* insertion sort in place*/
void insertionSort(vector<int>& v){
   unsigned int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i){ 
      current=i; 
      prev=i-1;
      while(v.at(current)<v.at(prev)){
         swap_ind(v, current, prev);
         --current;
         if(prev>0){
            --prev;
         }else{
            break;
         }
      }
   }
}

/* bubble sort in place*/
void bubbleSort(vector<int>& v){
   unsigned int size = v.size();
   bool swapped=false;
   do{
      swapped=false;
      for (unsigned int i=1; i<size; ++i){
         if(v.at(i-1)>v.at(i)){ 
            swap_ind(v,i-1,i);
            swapped = true;
         }
      }
   }while(swapped);
}

/*merge sort in place*/
void merge(vector<int>& v, unsigned int beg, unsigned int cent, unsigned int end){
   unsigned int p1=beg;
   unsigned int p2=cent;
   vector<int> mv;
   while(p1<cent && p2<end){
      if(v.at(p1)<=v.at(p2)){
         mv.push_back(v.at(p1));
         ++p1;
      }else{
         mv.push_back(v.at(p2));
         ++p2;
      }
   }
   while(p1<cent){
      mv.push_back(v.at(p1));
      ++p1; 
   }
   while(p2<end){
      mv.push_back(v.at(p2));
      ++p2; 
   }
   for(unsigned int i=0;i<mv.size();++i){
      v.at(beg+i)=mv.at(i);
   }
}

void mergeSort(vector<int>& v){
   unsigned int s=v.size();
   for(unsigned int width=1;width<s;width=2*width){
      for(unsigned int i=0;i<s;i=i+2*width){
         if(i+width<s){
            unsigned int end=(i+2*width<=s)?(i+2*width):s;
            merge(v,i,i+width,end);
         }
      }
   }
}