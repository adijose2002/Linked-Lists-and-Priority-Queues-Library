/*pqueue.cpp*/

//
// Author: Adithya Jose, UIC, Spring 2021
// Assignment: Project 5, Part 02
// I implemented the functions defined in a provided “pqueue.h” header file. These
// functions implement our notion of a priority queue data structure. 
//

#include "pqueue.h"

//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L)
{
    // Setting elements of List structs empty.
    L.Head = NULL;
    L.Count = 0;
}

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L)
{
    Node* cur = L.Head;
    
    cout << "List: ";
    
    while (cur != NULL)
    {
        cout << "(" << (cur->Data.ID) << "," << (cur->Data.Priority) << ") ";
        cur = cur->Next;
    }
    
    cout << endl;
}

//
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L)
{
    Node* cur = L.Head;
    
    while (cur != NULL)
    {
        break; // continuously iterating through the list without action.
    }
    
    if (cur == NULL)
    {
        throw invalid_argument("pq_front: queue empty");
    }
    
    return (cur->Data.ID);  //returning ID at the front of the list.
}

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L)
{
    if (L.Head == NULL)
    {
        throw invalid_argument("pq_dequeue: queue empty");
    }
    
    remove_from_list(L,0); // make use of list.cpp function to remove first node.
}

//
// pq_enqueue
//
// Inserts the given (ID,priority) pair into the queue based on
// the priority, ordered low to high. If elements already exist with
// the same priority, this new element comes after those elements.
// Example: suppose the queue currently contains the following 
// (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to enqueue (79,25) yields the following result:
//
//   (10,19) (84,25) (79,25) (21,50)
//
// If the ID is already in the queue, then the pair is repositioned 
// based on the new priority. For example, suppose the queue is as
// shown above, and we enqueue (84,50). The result is now
//
//   (10,19) (79,25) (21,50) (84,50)
//
void pq_enqueue(List& L, int ID, int priority)
{
    int index = search_list(L,ID);
    
    if (index == -1) // inserting node with unique ID
    {
        Node* temp = new Node();
        NodeData tempData;
        int count = 0;
        tempData.Priority = priority;
        tempData.ID = ID;
        temp->Data = tempData;
        temp->Next = NULL;

        Node* cur = L.Head;
        Node* prev = NULL;

        if (L.Head == NULL) // indicates list is empty therefore will be first node
        {
            L.Head = temp;
            L.Count++;
            return;
        }
        
        while (cur != NULL) // iterates through list to insert node in sorted order 
        {
            if (cur->Data.Priority <= priority)
            {
                prev = cur;
                cur = cur->Next;
                count++;
            }
            else
            {
                break;
            }
        }
        
        if (count == 0)
        {
            temp->Next = cur;
            L.Head = temp;
        }
        else
        {
            temp->Next = cur;
            prev->Next = temp;
        }
        
        L.Count++;
    }
    else // replacing node with same ID
    {
        remove_from_list(L, index);
        pq_enqueue(L, ID, priority);
    }
}

//
// pq_nudge
// 
// Nudges the element with the given ID forward one element in the
// queue. The element takes on the same priority as the element
// that now follows it.  Example: suppose the queue currently contains
// the following (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to "nudge" 21 forward produces this result:
//
//   (10,19) (21,25) (84,25)
//
// If the ID is already at the front of the queue, nothing happens.
// If the ID is not in the queue, throws "invalid_argument" exception, i.e.
// throw invalid_argument("pq_nudge: ID not found");
//
void pq_nudge(List& L, int ID)
{
    Node* cur = L.Head;
    Node* prev = NULL;
    int index = search_list(L,ID);
    
    if (index == -1) // ID not found
    {
         throw invalid_argument("pq_nudge: ID not found");
    }
    else if (index == 0)
    {
        return;
    }
    while (index > 1) // sort
    {
        index--;
        prev = cur;
        cur = cur->Next;
    }
    
    Node* newNode = cur->Next;
    cur->Next = newNode->Next;
    newNode->Next = cur;
    
    if (prev != NULL) // replacing previous nodes by priority
    {
        prev->Next = newNode;
    }
    else
    {
        L.Head = newNode;
    }
    newNode->Data.Priority = cur->Data.Priority;
   
}

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L)
{
    Node* cur = L.Head;
    Node* next;
    
    while (cur != NULL) // deleteing each node through iteration
    {
        next = cur->Next;
        delete(cur);
        cur = next;
    }
   
    // freeing memory 
    L.Head = NULL;
    L.Count = 0;
}

//
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L)
{
    List newList;
    pq_init(newList);
    Node* cur = L.Head;
    
    while (cur != NULL)
    {
        push_back_list(newList, cur->Data); // call to push_back_list function to copy data to new list
        cur = cur->Next;
    }
    
    return newList;
}