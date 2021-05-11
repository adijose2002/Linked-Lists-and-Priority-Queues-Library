/*list.cpp*/

//
// Author: Adithya Jose, UIC, Spring 2021
// Assignment: Project 5, Part 01
// This library implements and defines a one-way linked-list.
// Task is to implement a set of functions to create and manipulate one-way linked-lists.
//

#include "list.h"


//
// Functions:
//

// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L)
{
    // Setting elements of List structs empty.
    L.Head = NULL;
    L.Count = 0;
}

//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L)
{
    Node* cur = L.Head;
    
    cout << "List: ";
    
    while (cur != NULL) // printing list to console through iteration
    {
        cout << "(" << (cur->Data.ID) << "," << (cur->Data.Priority) << ") ";
        cur = cur->Next;
    }
    
    cout << endl;
}

//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d)
{
    Node* newN = new Node();
    newN->Data = d;
    newN->Next = L.Head;
    
    L.Head = newN;
    L.Count++; // increment counting as each node is inserted
}

//
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d)
{
    Node* cur = L.Head;
    Node* newN = new Node();
    
    if (cur == NULL) // reached back of list
    {
        newN->Data = d;
        newN->Next = L.Head;
        L.Head = newN;
        L.Count++;
    }
    else
    {
        while (cur->Next != NULL) // not back of list keep iterating
        {
            cur = cur->Next;
        }
        
        cur->Next = newN;
        newN->Next = NULL;
        newN->Data = d;
        L.Count++;
        
    }
}

//
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID)
{
    Node* cur = L.Head;
    
    int count = 0; // returning int object to adjust later
       
    while (cur != NULL) // iterating through list to find specific ID
    {
        if ((cur->Data.ID) != ID)
        {
            count = count + 1;
            cur = cur->Next;
        }
        else
        {
             break;
        }
          
    }
       
    if (cur == NULL)
    {
        count = -1; // ID not found
    }
    
    return count; // final int returned
}

//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L)
{
    Node* cur = L.Head;
    Node* next;
    
    while (cur != NULL) // deleting each node through iteration
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
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//
NodeData retrieve_from_list(List L, int pos)
{
    Node* cur = L.Head;
    int count = 0;
    
    while (cur != NULL)
    {
        if (count != pos) // not yet reached pos
        {
            count++;
            cur = cur->Next;
        }
        else
        {
            break; // reached
        }
    }
    
    if (cur == NULL)
    {
        throw invalid_argument("retrieve_from_list: invalid position");
    }
    
    return (cur->Data); // return data at pos
}

//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos)
{
    NodeData temp;
    
    if ((pos >= L.Count) || (pos < 0))
    {
        throw invalid_argument("remove_from_list: invalid position");
    }
    
    Node* cur = L.Head;
    
    if (pos == 0) // at beggining of list 
    {
        temp.ID = cur->Data.ID;
        temp.Priority = cur->Data.Priority;
        L.Head = cur->Next;
        delete cur;
        L.Count--;
        return temp;
    }
    else
    {
        Node* last = NULL;
        int i = -1;
        while (cur != NULL) // iterating through the list
        {
            i++;
            if (i == pos) // reached pos
            {
                break;
            }
            last = cur;
            cur = cur->Next;
        }
        
        temp.ID = cur->Data.ID;
        temp.Priority = cur->Data.Priority;
        last->Next = cur->Next;
        delete cur;
        L.Count--; // lowering count as each node is removed
        return temp;
    }
}