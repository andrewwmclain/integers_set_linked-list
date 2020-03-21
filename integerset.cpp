#include "integerset.h"
#include <sstream>
#include <iostream>

using namespace std;

/**
 * Default Constructor
 * Initializes _head to nullptr and _size to zero
 */
IntegerSet::IntegerSet(){
    _head = nullptr;
    _size = 0;
}
/**
 * Special Constructor: Set values on an array
 * Adds the values from the array parameter into the set. There are no
 * guarantees that the array is sorted.
 * @param data the array of integers to be added to the set
 * @param size the number of elements on the array
 */
IntegerSet::IntegerSet(const int data[], size_t size){
    _head = nullptr;
    _size = 0;
    for(size_t i = 0; i < size; i++){
        AddElement(data[i]);
    }
}

/**
 * Copy Constructor
 * Creates a deep copy of the set given as parameter.
 * @param otherSet the original set to be copied
 */
IntegerSet::IntegerSet(const IntegerSet& otherSet){
    _head = nullptr;
    _size = 0;
    for (Node* tmp = otherSet._head; tmp != nullptr; tmp = tmp->next)
        AddElement(tmp->number);
    }
/**
 * Destructor
 * Deallocates the memory of the whole list. It traverses the list
 * deallocating each of the nodes of the list.
 */
IntegerSet::~IntegerSet(){
    Clear();
}

/**
 * Copy Assignment Operator (Assignment operator overload)
 * It takes care of assignments of set, it creates a deep copy of the set on the
 * right hand side (rhs) of the operator.
 * @param rhs the original set to be copied to this
 */
const IntegerSet &IntegerSet::operator=(const IntegerSet& rhs) {
    if (&rhs == this)
        return *this;
    Clear();
    for (Node* tmp = rhs._head; tmp != nullptr; tmp = tmp->next) {
        AddElement(tmp->number);
    }
    return *this;
}
/**
 * Add Element
 * It adds an element to the set. There should not be repeated elements on the set.
 * The set should always be sorted. Remember to consider all the possible cases when
 * adding to the list:
 * - The List is empty
 * - The List is not empty and you want to insert before the _head
 * @param element the number you want to insert to the set
 * @returns true when the element was added to the set, false if the element was not added
 *          (the element was already on the set)
 */

bool IntegerSet::AddElement(int element){
    //if head is empty
    if(_size == 0){
        Node* neo = new Node();
        neo->number = element;
        _head = neo;
        _size++;
        return true;
    }
    //if head number is greater than element
    if(_head->number > element){
        Node* neo = new Node();
        neo->number = element;
        neo->next = _head;
        _head = neo;
        _size++;
        return true;
    }
    //if head number is equal to element, element can't be added
    if(_head->number == element){
        return false;
    }
    //if head is less than element, find which index to insert at
    else{
        Node* tmp = _head;
        //stops traversing on second to last
        while(tmp->next != nullptr){
            if(tmp->next->number == element){
                return false;
            }
            if(tmp->next->number > element){
                Node* neo = new Node();
                neo->number = element;
                neo->next = tmp->next;
                tmp->next = neo;
                _size++;
                return true;
            }
            tmp = tmp->next;
        }

        //if element is greater than the last node, add element at the end of the list
        Node* neo = new Node();
        neo->number = element;
        neo->next = nullptr;
        tmp->next = neo;
        _size++;
        return true;
    }
}

/**
 * Clear
 * Clears the whole set. It removes all elements of the set and makes the set become an
 * empty set.
 */

void IntegerSet::Clear(){
    //create temp node
    Node* tmp = _head;
    Node* tmpNext = nullptr;
    //deallocate memory for each element from heap
    for (size_t i = 0; i < _size; ++i) {
        tmpNext = tmp->next;
        delete tmp;
        tmp = tmpNext;
    }
    _size = 0;
}

/**
 * Contains
 * Verifies if the number is contained in the set. Do you think doing a Binary Search would make
 * the process faster?
 * @param number the number that is being checked if it is contained on the set
 * @returns true if the number is contained, false otherwise
 */

bool IntegerSet::Contains(int number) const{
    //if list is empty, return false
    if(_size == 0){
        return false;
    }
    Node* tmp = _head;
    //check for element in list
    for(size_t i = 0; i < _size; i++){
        if(tmp->number == number){
            return true;
        }
        tmp = tmp->next;
    }
    //if end is reached w/o finding element, return false
    return false;
}

/**
 * IsEmpty
 * Verifies if the set is emtpy.
 * @returns true if the set is empty, false otherwise
 */
bool IntegerSet::IsEmpty() const{
    if(_size == 0){
        return true;
    }
    return false;
}

/**
 * Size
 * Returns the number of elements on the set
 * @returns number of elements on the set
 */

size_t IntegerSet::Size() const{
    return _size;
}

/**
 * Remove
 * Removes a given element from the set, if that element is on the set.
 * @param number the number to be removed
 * @returns true if the number was contained and successfully removed, false otherwise
 */

bool IntegerSet::Remove(int num){
    size_t i;
    //if list is empty, return false
    if(_size == 0){
        return false;
    }
    //if num is at head
    if(_head->number == num){
        Node* tmp = _head;
        _head = _head->next;
        delete tmp;
        _size--;
        return true;
    }
    //if num is not at head
    Node* nxt = _head;
    for(i = 0; i < _size; i++){
        nxt = nxt->next;
        if(nxt == nullptr){
            return false;
        }
        //if num is found in list, remove it and deallocate memory
        if(nxt->number == num){
            Node* prev = _head;
            for(size_t j = 0; j < i; j++){
                prev = prev->next;
            }
            nxt = nxt->next;
            delete prev->next;
            prev->next = nxt;
            _size--;
            return true;
        }
    }
    //if num is not found in list, return false
    return false;
}

/**
 * Equals
 * Compares each of the elements on the set to see if the two sets are completely equal.
 * @param rhs the set to be compared to this
 * @returns true if this and rhs are exactly the same, false otherwise
 */

bool IntegerSet::Equals(const IntegerSet& rhs) const{
    //create two temp nodes for lhs and rhs
    Node* tmp1 = _head;
    Node* tmp2 = rhs._head;
    //check each element in lhs against corresponding index in rhs
    for(size_t i = 0; i < _size; i++){
        //if rhs is too short, return false
        if(tmp2 == nullptr){
            return false;
        }
        //if one element doesn't match, return false
        if(tmp2->number != tmp1->number){
            return false;
        }
        //iterate to next element
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    //if both lists go all the way through, return true
    return true;
}

/**
 * Union
 * It creates and returns a new set containing the union of the two sets. Given the following
 * sets:
 * A = {1, 4, 5} and B = {1, 6, 7, 9}
 * C = A.Union(B)
 * C would become {1, 4, 5, 6, 7, 9}
 * Notice that the result is also sorted and that there are no repeated elements. The time
 * complexity of this operation should be O(n).
 * @param rhs the set to be union'ed with this
 * @returns the result of the union of this and rhs
 */
IntegerSet IntegerSet::Union(const IntegerSet& rhs) const{
    IntegerSet C;
    Node*tmp1 = _head;
    Node* tmp2 = rhs._head;
    for(size_t i = 0; i < _size; i++){
        C.AddElement(tmp1->number);
        tmp1 = tmp1->next;
    }
    for(size_t i = 0; i < rhs._size; i++){
        C.AddElement(tmp2->number);
        tmp2 = tmp2->next;
    }
    return C;
}

/**
 * Intersection
 * It creates and returns a new set containing the intersection of the two sets. Given the following
 * sets:
 * A = {1, 4, 9} and B = {1, 6, 7, 9}
 * C = A.Intersection(B)
 * C would become {1, 9}
 * Notice that the result is also sorted and that there are no repeated elements. The time
 * complexity of this operation should be O(n).
 * @param rhs the set to be intersection'ed with this
 * @returns the result of the intersection of this and rhs
 */
IntegerSet IntegerSet::Intersection(const IntegerSet& rhs) const{
    IntegerSet C;
    Node* tmp1 = _head;
    Node* tmp2;
    for(size_t i = 0; i < _size; i++){
        tmp2 = rhs._head;
        for(size_t j = 0; j < rhs._size; j++){
            if(tmp1->number == tmp2->number){
                C.AddElement(tmp1->number);
            }
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
    }
    return C;
}

/**
 * Difference
 * It creates and returns a new set containing the difference of the two sets. Given the following
 * sets:
 * A = {1, 4, 9} and B = {1, 6, 7, 9}
 * C = A.Difference(B)
 * C would become {4}
 * Notice that the result is also sorted and that there are no repeated elements. The time
 * complexity of this operation should be O(n).
 * @param rhs the set to be difference'ed with this
 * @returns the result of the difference of this and rhs
 */

IntegerSet IntegerSet::Difference(const IntegerSet& rhs) const{
    IntegerSet C;
    Node* tmp1 = _head;
    Node* tmp2;
    size_t j;

    for(size_t i = 0; i < _size; i++){
        tmp2 = rhs._head;
        for(j = 0; j < rhs._size; j++){
            if(tmp1->number == tmp2->number){
                break;
            }
            tmp2 = tmp2->next;
        }
        if(j == rhs._size){
            C.AddElement(tmp1->number);
        }
        tmp1 = tmp1->next;
    }
    return C;
}

/**
 * ToString
 * Creates a string representation of the set using the following form:
 * {element, element, element}
 * Notice that elements are separated by comma and a single space. There is no space or comma
 * before the closing curly braces.
 * @returns a string representing the set.
 */

string IntegerSet::ToString() const{
    Node* tmp = _head;
    if(_size == 0){
        return "{}";
    }
    string str = "{";
    for(size_t i = 0; i < _size - 1; i++){
        str.append(to_string(tmp->number));
        str.append(", ");
        tmp = tmp->next;
    }
    str.append(to_string(tmp->number));
    str.append("}");
    return str;
}

/**
 * Read
 * Reads a set from an input stream.
 * @param input an input stream that could be cin, an istringstream or an ifstream
 * @returns the number of elements added to the set
 */

size_t IntegerSet::Read(istream& input){
    size_t numElements = 0;
    int num;
    while(input >> num){
        if(num == -1){
            break;
        }
        if(!AddElement(num)){
            cout << num << " already in the set\n";
        }
        else{
            numElements++;
            cout << num << " successfully added\n";
        }
    }
    return numElements;
}

/**
 * Write
 * Writes the elements of the set into an output stream
 * @param output the output stream that could be cout, an ostringstream or an ofstream
 * @returns the number of elements sent to the output stream
 */

size_t IntegerSet::Write(ostream& output) const{
    Node* tmp = _head;
    for(size_t i = 0; i < _size; i++){
        output << tmp->number << " ";
        tmp = tmp->next;
    }
    return _size;
}