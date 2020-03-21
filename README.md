# LAB 7 - Integer Set implemented with Linked List


## Goal

The goal of this lab is for you to practice:
- Multiple files compilation
- Command line compilation
- Apply pointers and dynamic memory by implementing a single linked list
- Use Unit Tests to check the correct implementation of your program

 
## Description
For this lab you will implement a class to represent a set of integers: `IntegerSet`. This class will store the elements of the set using a single linked list.

The operations of the `IntegerSet` are:

Operation | Description
--------- | -----------
Default Constructor | Creates an empty set
Constructor initializing with an array | Creates a set using the data given by an array taken as parameter. The array is not guaranteed to be sorted.
Copy Constructor | Creates a deep copy of the object
Assignment Operator | Helps with the assignment of `IntegerSet` objects
Destructor | Takes care of releasing the allocated memory
`ToString` | returns a string representation of the set (i.e. `{0, 3, 5}`)
`Read` | Reads the numbers of a set from an input stream
`Write` | Writes the elements of the set to an output stream
`Size` | Returns the number of elements in the set
`IsEmpty` | Returns whether the set is empty or not
`Equals` | Returns true when two sets are identical
`AddElement` | To add an element to the set
`Clear` | Removes all elements of the set
`Contains` | Checks if a number is contained in the set
`Remove` | Removes an element from the set
`Union` | Calculates the union of two sets
`Intersection` | Calculates the intersection of two sets
`Difference` | Calculates the difference of two sets

### Linked List Implementation Details

For this lab you will use a single linked list. For this purpose you will need a `struct` to represent a _Node_ of the list. This `struct` is private to the class `IntegerSet` since no other client needs to know about the specific implementation of the set.
The `struct` declaration is:
```cpp
struct Node{
    int number;
    Node* next;
};
```
Each node will contain a number to represent a single element in the set, and a pointer to the next node.

The `IntegerSet` class has one data member:
```cpp
    Node* _head;
```

The `_head` represents the first element in the list. By default, in the beginning this member is set to `nullptr`. 

The following image shows the internal representation of a set with elements 2, 5 and 9.
![SetExample](images/set-example.png)

The following images will show the progression of adding elements to the set. Please note that the set is always sorted!

When the set is just declared:
![Step1](images/set-step1.png)

After adding 3.
![Step1](images/set-step2.png)

After adding 8.
![Step1](images/set-step3.png)

After adding 4.
![Step1](images/set-step4.png)

After adding 2.
![Step1](images/set-step5.png)

Although is not shown in the pictures, the set never has repeated elements.

### More detailed description of methods

- **Default Constructor**, initializes `_head` to `nullptr`.Simple method: one liner!.
- **Constructor initializing with an array**, takes in an array and its size as parameter. Then it attempts to add each of the elements of the array to the set. The elements are not guaranteed to be sorted and there might be duplicates.
- **Copy Constructor**, creates a deep copy, traverses the original set adding each of its element to the new set. The code for this method is provided to you. Do not modify this code.
- **Assignment Operator**, very much like the Copy Constructor, but at the end it returns `*this`. The code for this method is provided to you. Do not modify this code.
- **Destructor**, this method will take care of _cleaning up_ when an `IntegerSet` object needs to be de-allocated. The method will traverse the list releasing the allocated memory for each of the nodes. Be careful not to lose the reference of the next node before deleting the current one.
- **`ToString`** returns a string representation of the `IntegerSet`. The string representation is just the numbers on the set separated by commas and between curly braces: `{4, 6, 8, 11, 12, 21}`. Notice there is a space after the comma.
- **`Read`** reads the the elements of a set from an input stream (it can be an `istringstream` or an `ifstream`, as a matter of fact any `istream`). There are no guarantees that the numbers are going to be sorted or that there will be no duplicates. Make sure to validate the input, the input stream could have characters! The method returns the number of elements that were actually added to the set. For instance if the input stream has the following data: `44 22 11 33 44` then when calling the `Read` method on that input stream, the resulting set would be `{11, 22, 33, 55}` and the `Read` method would return `4`. Additionally, if the input stream has the following data `{32 alpha}` then your `Read` method should return `1` as it was able to read `32` into the set but then failed when it found a string.
- **`Write`** writes the elements of the set the the given output stream (it can be an `ostringstream` or an `ofstream`, as a matter of fact any `ostream`). The method just sends the elements separated by spaces to the output stream, no further formatting is required.
- **`Size`** returns the elements of the set. 
- **`IsEmpty`** returns `true` if the set is empty, that is if it has zero elements, it returns `false` otherwise.
- **`Equals`** returns `true` if the set sent as parameter is identical to the object that called the method. Remember that your elements must be always sorted so comparing the two sets should be done with linear time, O(n). If the sets do not have the same elements then the method returns `false`.
- **`AddElement`** adds an element to the set. Issues to remember:
  - The set needs to be always sorted, so every time you add an element the first thing you need to do is find what is the appropriate place to insert the new element.
  - The set does not store repeated values, so if the value is already on the set, do not add it and return `false`.
  - Once you have successfully added the element to the set, you can increase the `_size` and return `true`.
  When adding an element to the list, remember to consider the different cases: the element should go before `_head`, the element goes after the `_head`, the element goes last, the list is empty.
- **`Clear`** removes all elements of the list, sets `_head` to `nullptr` and `_size` to `0`.
- **`Contains`** takes in a number as parameter, the method returns `true` if the number is on the set, `false` otherwise.
- **`Remove`** removes an element from the set. The method removes the node containing the number from the list, remember to release the memory used by the removed node. The method returns `true` if it successfully removes the element, `false` if it does not, for example, if the element was not on the set.
- **`Union`** creates a new set containing the union of the elements of the set sent as parameter and the object calling the method. When the newly created set has the union of `this` and the parameter the method returns it. For example:
```cpp
    int a[] = {1, 5, 9}, b[] = {2, 5};
    IntegerSet A(a, 3), B(b, 2); // Using the constructor that takes in an array
    IntegerSet C; // Calls the default constructor
    C = A.Union(B); // Calls the Union method and assigns the result to C (note that the operator overload is provided)
    cout << C.ToString() << endl; // outputs: {1, 2, 5, 9}
```
- ***`Intersection`** creates a new set containing the intersection of the elements of the set sent as parameter and the object calling the method. When the newly created set has the intersection of `this` and the parameter the method returns it. For example:
```cpp
    int a[] = {1, 5, 9}, b[] = {2, 5};
    IntegerSet A(a, 3), B(b, 2); // Using the constructor that takes in an array
    IntegerSet C; // Calls the default constructor
    C = A.Intersection(B); // Calls the Intersection method and assigns the result to C (note that the operator overload is provided)
    cout << C.ToString() << endl; // outputs: {5}
```
- **`Difference`** creates a new set containing the difference of the elements of the set sent as parameter and the object calling the method. When the newly created set has the difference of `this` and the parameter the method returns it. For example:
```cpp
    int a[] = {1, 5, 9}, b[] = {2, 5};
    IntegerSet A(a, 3), B(b, 2); // Using the constructor that takes in an array
    IntegerSet C; // Calls the default constructor
    C = A.Difference(B); // Calls the Difference method and assigns the result to C (note that the operator overload is provided)
    cout << C.ToString() << endl; // outputs: {1, 9}
```



## Sample Run (main)

To compile the program you will need to open your command line and move to the directory where your source code resides. You will find there the following files: `integerset.h`, `integerset.cpp`, `main.cpp`, `unit-test.cpp`, `test.h`, `test.cpp` and `makefile`. These are the files you are going to need to compile your program. The following pictures shows the contents of the project directory. 

![contents](images/files-on-dir.png)

To compile run the following command: `make`. The picture shows what is going to happen. The `make` utility is a program that executes the `makefile`. In the `makefile` we have written instructions on how and what to compile to create the executable file. Note in the picture that now a file `set` appears. This is the newly created executable. Your code should compile without errors and without warnings.

![making](images/making-and-set.png)

To run the program just type: `./set` and that will execute your program. The following text shows an instance of the program running. You are expected to write your own main program that has the exact same output as the one shown here.
```

root@fa746f285819:/tmp/tmp.ILoveSPU/# ./set
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
1
Set A:
Input numbers to be included in the set, -1 to stop
3 5 9 10 2 4 3 -1
3 successfully added
5 successfully added
9 successfully added
10 successfully added
2 successfully added
4 successfully added
3 already in the set
A = {2, 3, 4, 5, 9, 10}
Set B:
Input numbers to be included in the set, -1 to stop
11 3 2 -1
11 successfully added
3 successfully added
2 successfully added
B = {2, 3, 11}
A U B = C = {2, 3, 4, 5, 9, 10, 11}
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
2
Set A:
Input numbers to be included in the set, -1 to stop
10 8 5 3 -1
10 successfully added
8 successfully added
5 successfully added
3 successfully added
A = {3, 5, 8, 10}
Set B:
Input numbers to be included in the set, -1 to stop
8 11 1 -1
8 successfully added
11 successfully added
1 successfully added
B = {1, 8, 11}
A n B = C = {8}
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
3
Set A:
Input numbers to be included in the set, -1 to stop
12 3 4 1 4 8 11 1 -1
12 successfully added
3 successfully added
4 successfully added
1 successfully added
4 already in the set
8 successfully added
11 successfully added
1 already in the set
A = {1, 3, 4, 8, 11, 12}
Set B:
Input numbers to be included in the set, -1 to stop
12 99 3 17 11 -1
12 successfully added
99 successfully added
3 successfully added
17 successfully added
11 successfully added
B = {3, 11, 12, 17, 99}
A - B = C = {1, 4, 8}
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
4
Goodbye


```

### Error validation

Your program should be robust and not crash on wrong input. See the following sample run:
```
root@fa746f285819:/tmp/tmp.CodingIsFun/# ./set
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
9
Incorrect menu option!
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
alpha
Incorrect input!
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
a
Incorrect input!
1. Set Union
2. Set Intersection
3. Set Difference
4. Exit
4
Goodbye
```


## Sample Run (unit test)

We are providing you with an additional file that has a `main` function. The source code is on the file `unit-test.cpp`. To run this you will need to compile it first. To compile you will need to run the command: `make test`. This command will create a new executable called `test`. To test your program you need only to run test: `./test`. The following figure shows the compilation process.

![test](images/making-test.png)

When you run your test program the output should be:

```

root@fa746f285819:/tmp/tmp.JesusLovesYou/# ./test
Initial: Size                            Passed   1 tests passed
Initial: Is Empty                        Passed   2 tests passed
Initial: ToString                        Passed   3 tests passed
Initial: Contains                        Passed   4 tests passed
Initial: Remove                          Passed   5 tests passed
Add Element - 5                          Passed   6 tests passed
Add Repeated Element - 5                 Passed   7 tests passed
ToString Single Element                  Passed   8 tests passed
Size after adding one element            Passed   9 tests passed
Is Empty false after adding              Passed  10 tests passed
Add another element - 10                 Passed  11 tests passed
Add another element - 8                  Passed  12 tests passed
Checking Size = 3                        Passed  13 tests passed
Checking elements and sorted             Passed  14 tests passed
Check Contains(5)                        Passed  15 tests passed
Check Contains(8)                        Passed  16 tests passed
Check Contains(10)                       Passed  17 tests passed
Check does not Contain(3)                Passed  18 tests passed
Check does not Contain(6)                Passed  19 tests passed
Check does not Contain(9)                Passed  20 tests passed
Check does not Contain(20)               Passed  21 tests passed
Check cannot remove 1                    Passed  22 tests passed
Check cannot remove 6                    Passed  23 tests passed
Check cannot remove 9                    Passed  24 tests passed
Check cannot remove 12                   Passed  25 tests passed
Check Remove 8                           Passed  26 tests passed
Check ToString after Removing            Passed  27 tests passed
Check Size == 0 after Clear              Passed  28 tests passed
ToString after Clear                     Passed  29 tests passed
Contains(5) after Clear                  Passed  30 tests passed
Contains(10) after Clear                 Passed  31 tests passed
Remove after Clear                       Passed  32 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
B a s i c    O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Reading from Stream 10 values            Passed  33 tests passed
ToString after Reading from Stream       Passed  34 tests passed
Writing to Stream                        Passed  35 tests passed
Stream output                            Passed  36 tests passed
Reading additional 3, 1 repeated         Passed  37 tests passed
ToString after Reading from Stream       Passed  38 tests passed
Invalid value in the stream              Passed  39 tests passed
ToString after Reading from Stream       Passed  40 tests passed
Initial invalid value in the stream      Passed  41 tests passed
ToString after Reading from Stream       Passed  42 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  I / O     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Set from Array X Size                    Passed  43 tests passed
Set from Array Y Size                    Passed  44 tests passed
Set from Array Z Size                    Passed  45 tests passed
Set X ToString                           Passed  46 tests passed
Set Y ToString                           Passed  47 tests passed
Set Z ToString                           Passed  48 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  A r r a y    O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Intersection Size                        Passed  49 tests passed
Intersection Result                      Passed  50 tests passed
Disjoint Intersection Size               Passed  51 tests passed
Disjoint Intersection Result             Passed  52 tests passed
Union Size                               Passed  53 tests passed
Union Result                             Passed  54 tests passed
Difference Size                          Passed  55 tests passed
Difference Result                        Passed  56 tests passed
Difference Size                          Passed  57 tests passed
Difference Result                        Passed  58 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  S e t     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

- - - - - - - - - - - - - - - - - - - - - - - -
  S t a r t i n g    T i m e d   T e s t s
- - - - - - - - - - - - - - - - - - - - - - - -

Inserting 10,000 random elements: 157.372 ms
Elements inserted: 6378
Inserting 10,000 random elements: 154.405 ms
Elements inserted: 6355
Union of two sets:        412.764 ms	Size of LHS: 6378 Size of RHS: 6355 Size of Result: 8705
Intersection of two sets: 91.8759 ms	Size of LHS: 6378 Size of RHS: 6355 Size of Result: 4028
Difference of two sets:   205.131 ms	Size of LHS: 6378 Size of RHS: 6355 Size of Result: 2350


Test Passed: 58		100%


All Unit Tests Passed!!!

    .     '     ,
      _________
   _ /_|_____|_\ _
     '. \   / .'
       '.\ /.'
         '.'


```

Once you have passed all the unit tests your code is ready to be submitted.

## Description of Lab Files

- `integerset.h` contains the `IntegerSet` class declaration. This file should not be modified.
- `integerset.cpp` contains the `IntegerSet` class methods definition. This is where you will do most of your work.
- `main.cpp` contains the program that holds the menu shown in the previous section.
- `unit-test.cpp` contains the unit tests for the `IntegerSet` class. This file should not be modified.
- `test.cpp` and `test.h` contain helper functions for the unit tests. These files should not be modified.
- `makefile` contains the instructions on how to compile your code to produce the `set` program and the `test` program


## Style

Your program needs to be orderly and readable.  If you are working a development team and don’t write clean looking code, you will be unpopular among your colleagues and may not work on that team very long.  Because of this your program will be graded on style as well as correctness.  Please refer to the style guidelines discussed in class and in reading assignments concerning

  *	Indention of code
  *	Consistent use of {}, preferably Stroustrup style
  *	Meaningful names of identifiers
  *	Naming conventions for identifiers (camelCase for variables, CamelCase for function names. First word of a function name typically should be a verb. Data members with the _ prefix)
  *	No use of global variables. Global variables sometimes are appropriate, but not in the assignments we will be giving this quarter.
  *	Making sure `struct` and object parameters are passed by reference (and declared const if appropriate)
  
## Documentation
    
At the start of your file you should have a header comment that gives the title of the assignment, the purpose, and your name.  Here is an example (from Lab 1) of what that could look like:

```cpp
/*
    Title:      Lab 7 – integerset.cpp
    Purpose:    implement the IntegerSet class methods
    Author:     John Wayne
    Date:       January 6, 2020
*/
```
Each subordinate function should also start with a header that describes what it does, it’s parameters, what it returns, and how errors are handled.  Here is an example (again from Lab 1):

```cpp
// Produce a string of evaluation steps for simplifying an expression
// For example:
//      if “2+3*4-5”  is passed to this function, the string “2+3*4-5 = 2+12-5\n        = 14-5\n        = 9”
//      would be returned
// Parameters:
//      expression - an arithmetic expression
// Returns:
//      a string consisting of the evaluation steps needed to simplify the expression
// Possible Error Conditions: 
//      If evaluating the expression causes division by zero, this function crash.
//      If evaluating the expression causes an oveflow, the results may not be reliable.
```

You should include additional comments in your code to describe what you are doing.   If it is hard to understand what a variable is for, add a comment after it.   It possible, though, to put in too many comments, so be judicious and make sure you have time left to do well in your other classes when it comes to commenting.

## Submitting your code
Your solution should be contained within files that were provided.  You MUST NOT modify `unit-test.cpp`, `test.h`, `test.cpp`, `integerset.cpp`, `makefile` or `CMakeFiles.txt`.

Make sure you test your code thoroughly.  We will try your code with our own test files, and we will programmatically test your database ADT with our own test program.  

Your code needs to be submitted through GitHub.  You will need to push your last version of your program before the lab deadline. As a good programming practice remember to commit frequently and to push every time you have a functioning version of your code.

## Grading
Correctness is essential.  Make sure your solution builds as described above and correctly handles the test cases displayed in the screen shot.  We will test on other input values as well. Your code must compile and should not have runtime errors (crash).

Even if your solution operates correctly, points will be taken off for:
- Not following the design described above
- Not adhering to style guidelines described above
- Using techniques not presented in class
- Programming error not caught by other testing
- Not following good programming practices

## Academic Integrity
This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid and you are encouraged to talk among yourselves about programming in general and current assignments in particular.  Keep in mind, however, that each individual student must do the work in order to learn.  Hence, the following guidelines are established:
- Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
- Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
- If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
- **If there is any evidence that a program or other written assignment was copied from another student, neither student will receive any credit for it. This rule will be enforced.**
- Protect yourself: Handle throw-away program listings carefully, keep your repository private.

Refer to the ECS Department Policy on Academic Integrity that is included in the class syllabus.

## Grading Rubric Summary
The following aspects are going to be consider during grading. Make sure you comply with all of them.
- The program compiles (there will be no partial credit for programs that do not compile)
- Provides the correct output for the test cases
- Catches errors gracefully, the program does not crash on incorrect input
- The program outputs the information in the specified format
- The assignment follows all the instructions
- In general the program does not crash 

Refer to the Rubrics PPT on Canvas to refresh how Lab Assignments are graded.
