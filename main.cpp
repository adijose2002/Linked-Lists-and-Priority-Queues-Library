//
// Author: Adithya Jose, UIC, Spring 2021
// Assignment: Project 05 Testing
//

#include <iostream>
#include <string> 
#include <fstream>
#include "list.h"
#include "pqueue.h"

int main()
{    
    List L;
    pq_init(L);
    

    pq_enqueue(L, 10, 19);
    
    pq_print(L);
    
    
    pq_enqueue(L, 84, 25);
    pq_enqueue(L, 79, 25);
    pq_enqueue(L, 21, 50);
    
    pq_print(L);
    
    
    
    pq_enqueue(L, 84, 50);
    pq_print(L);
    
    cout << "Front of the list: " << pq_front(L) << endl;
    
    pq_dequeue(L);
    
    pq_print(L);
    
    List xl = pq_duplicate(L);
    pq_print(xl);
    
    pq_nudge(L, 21);
    pq_print(L);
    pq_nudge(L, 84);
    pq_print(L);
          
    
    pq_clear(L);
    
    pq_print(L);
    
}
    