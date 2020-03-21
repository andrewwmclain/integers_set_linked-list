/*
 * Title:   Lab 7 - IntegerSet.h
 *
 * Purpose: Declares the class IntegerSet it will implement a Set of Integers
 *          using a Linked List as the underlying data structure
 *
 * Class:   CSC 2430 Winter 2020
 * Author:  Carlos Arias
 */


#ifndef INTEGER_SET_H
#define INTEGER_SET_H

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

class IntegerSet{
private:
    // struct to represent each node
    // contains the number and the
    // pointer to the next element on
    // the linked list
    struct Node{
        int number;
        Node* next;
    };
    // Head of the list
    Node* _head;
    // Number of elements on the Set
    size_t _size;

public:
    // Default constructor
    IntegerSet();
    // Constructor to create the set with the elements of the array
    // There are no guarantees that the array is sorted or that it
    // does not have duplicates
    IntegerSet(const int data[], size_t size);
    // Copy constructor indispensable because of Union et al operations
    IntegerSet(const IntegerSet&);
    // Copy Assignment operator
    const IntegerSet& operator=(const IntegerSet&);
    // Destructor, takes care of deallocating the linked list
    ~IntegerSet();

    // Adds an element to the set
    bool AddElement(int element);
    // Clears the set to become empty set
    void Clear();
    // Checks if the number is in the set
    bool Contains(int number)const;
    // Returns true if the set is empty
    bool IsEmpty()const;
    // Returns how many elements on the set
    size_t Size()const;
    // Removes an element from the set
    bool Remove(int);
    // Returns true if this has the exact same elements as rhs
    bool Equals(const IntegerSet& rhs)const;

    // Returns a new set containing the union of this and rhs
    IntegerSet Union(const IntegerSet& rhs)const;
    // Returns a new set containing the intersection of this and rhs
    IntegerSet Intersection(const IntegerSet& rhs)const;
    // Returns a new set containing the difference of this and rhs
    IntegerSet Difference(const IntegerSet& rhs)const;


    // Returns a string representation of the set
    string ToString()const;
    // Reads the elements from input and adds them to the set
    size_t Read(istream& input);
    // Sends the elements of the set to the output
    size_t Write(ostream& output)const;

};

#endif
