#include "integerset.h"
#include "test.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::stringstream;
using std::milli;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;

int main(int argc, char* argv[]){
    IntegerSet a;
    int testPassed = 0;
    const float TOTAL_TESTS = 58.0f;
    // Tests for Initial State
    if (Test(a.Size() == 0, "Initial: Size")){
        testPassed++;
    }
    if (Test(a.IsEmpty(), "Initial: Is Empty")){
        testPassed++;
    }
    if (Test(a.ToString() == "{}", "Initial: ToString")){
        testPassed++;
    }
    if (Test(!a.Contains(0), "Initial: Contains")){
        testPassed++;
    }
    if (Test(!a.Remove(0), "Initial: Remove")){
        testPassed++;
    }
    // Add elements
    if (Test(a.AddElement(5), "Add Element - 5")){
        testPassed++;
    }
    if (Test(!a.AddElement(5), "Add Repeated Element - 5")){
        testPassed++;
    }
    if (Test(a.ToString() == "{5}", "ToString Single Element")){
        testPassed++;
    }
    if (Test(a.Size() == 1, "Size after adding one element")){
        testPassed++;
    }
    if (Test(!a.IsEmpty(), "Is Empty false after adding")){
        testPassed++;
    }
    if (Test(a.AddElement(10), "Add another element - 10")){
        testPassed++;
    }
    if (Test(a.AddElement(8), "Add another element - 8")){
        testPassed++;
    }
    if (Test(a.Size() == 3, "Checking Size = 3")){
        testPassed++;
    }
    if (Test(a.ToString() == "{5, 8, 10}", "Checking elements and sorted")){
        testPassed++;
    }
    if (Test(a.Contains(5), "Check Contains(5)")){
        testPassed++;
    }
    if (Test(a.Contains(8), "Check Contains(8)")){
        testPassed++;
    }
    if (Test(a.Contains(10), "Check Contains(10)")){
        testPassed++;
    }
    if (Test(!a.Contains(3), "Check does not Contain(3)")){
        testPassed++;
    }
    if (Test(!a.Contains(6), "Check does not Contain(6)")){
        testPassed++;
    }
    if (Test(!a.Contains(9), "Check does not Contain(9)")){
        testPassed++;
    }
    if (Test(!a.Contains(20), "Check does not Contain(20)")){
        testPassed++;
    }
    if (Test(!a.Remove(1), "Check cannot remove 1")){
        testPassed++;
    }
    if (Test(!a.Remove(6), "Check cannot remove 6")){
        testPassed++;
    }
    if (Test(!a.Remove(9), "Check cannot remove 9")){
        testPassed++;
    }
    if (Test(!a.Remove(12), "Check cannot remove 12")){
        testPassed++;
    }
    if (Test(a.Remove(8), "Check Remove 8")){
        testPassed++;
    }
    if (Test(a.ToString() == "{5, 10}", "Check ToString after Removing")){
        testPassed++;
    }
    a.Clear();
    if (Test(a.Size() == 0, "Check Size == 0 after Clear")){
        testPassed++;
    }
    if (Test(a.ToString() == "{}", "ToString after Clear")){
        testPassed++;
    }
    if (Test(!a.Contains(5), "Contains(5) after Clear")){
        testPassed++;
    }
    if (Test(!a.Contains(10), "Contains(10) after Clear")){
        testPassed++;
    }
    if (Test(!a.Remove(0), "Remove after Clear")){
        testPassed++;
    }

    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
            "B a s i c    O p e r a t i o n s    P a s s e d" << endl <<
            "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    stringstream data("45 44 93 31 68 36 58 87 45 31 72 93 40");
    if (Test(a.Read(data) == 10, "Reading from Stream 10 values")){
        testPassed++;
    }
    if (Test(a.ToString() == "{31, 36, 40, 44, 45, 58, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }
    stringstream outputTest;
    if (Test(a.Write(outputTest)==10,"Writing to Stream")){
        testPassed++;
    }
    if (Test(outputTest.str() == "31 36 40 44 45 58 68 72 87 93 ", "Stream output")){
        testPassed++;
    }
    data.clear();
    data.str("12 58 41");
    if (Test(a.Read(data) == 2, "Reading additional 3, 1 repeated ")){
	    testPassed++;
    }
    if (Test(a.ToString() == "{12, 31, 36, 40, 41, 44, 45, 58, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }
    data.clear();
    data.str("61 x3r");
    if (Test(a.Read(data) == 1, "Invalid value in the stream")){
	    testPassed++;
    }
    if (Test(a.ToString() == "{12, 31, 36, 40, 41, 44, 45, 58, 61, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }
    data.clear();
    data.str("r1re 70");
    if (Test(a.Read(data) == 0, "Initial invalid value in the stream")){
	    testPassed++;
    }
    if (Test(a.ToString() == "{12, 31, 36, 40, 41, 44, 45, 58, 61, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }



    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  I / O     O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    int setX[] = {1, 5, 8}, setY[] = {3, 5, 13}, setZ[] = {4, 8};
    IntegerSet x(setX, sizeof(setX) / sizeof(setX[0]));
    IntegerSet y(setY, sizeof(setY) / sizeof(setY[0]));
    IntegerSet z(setZ, sizeof(setZ) / sizeof(setZ[0]));

    if (Test(x.Size() == sizeof(setX) / sizeof(setX[0]), "Set from Array X Size")){
        testPassed++;
    }
    if (Test(y.Size() == sizeof(setY) / sizeof(setY[0]), "Set from Array Y Size")){
        testPassed++;
    }
    if (Test(z.Size() == sizeof(setZ) / sizeof(setZ[0]), "Set from Array Z Size")){
        testPassed++;
    }

    if (Test(x.ToString() == "{1, 5, 8}", "Set X ToString")){
        testPassed++;
    }
    if (Test(y.ToString() == "{3, 5, 13}", "Set Y ToString")){
        testPassed++;
    }
    if (Test(z.ToString() == "{4, 8}", "Set Z ToString")){
        testPassed++;
    }
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  A r r a y    O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    IntegerSet r;
    r = x.Intersection(y);
    if (Test(r.Size() == 1, "Intersection Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{5}", "Intersection Result")){
        testPassed++;
    }
    r = y.Intersection(z);
    if (Test(r.Size() == 0, "Disjoint Intersection Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{}", "Disjoint Intersection Result")){
        testPassed++;
    }
    r = x.Union(z);
    if (Test(r.Size() == 4, "Union Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 4, 5, 8}", "Union Result")){
        testPassed++;
    }
    r = x.Difference(z);
    if (Test(r.Size() == 2, "Difference Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 5}", "Difference Result")){
        testPassed++;
    }
    r = z.Difference(x);
    if (Test(r.Size() == 1, "Difference Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{4}", "Difference Result")){
        testPassed++;
    }

    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  S e t     O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  S t a r t i n g    T i m e d   T e s t s" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    time_point<steady_clock> start, end;
    srand(time(NULL));
    IntegerSet k, l, m;
    start = steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        k.AddElement(rand() % 10000);
    }
    end = steady_clock::now();
    cout << "Inserting 10,000 random elements: " << duration<double, milli>(end - start).count() << " ms" << endl;
    cout << "Elements inserted: " << k.Size() << endl;

    start = steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        l.AddElement(rand() % 10000);
    }
    end = steady_clock::now();
    cout << "Inserting 10,000 random elements: " << duration<double, milli>(end - start).count() << " ms" << endl;
    cout << "Elements inserted: " << l.Size() << endl;

    start = steady_clock::now();
    m = k.Union(l);
    end = steady_clock::now();
    cout << "Union of two sets:        " << duration<double, milli>(end - start).count() << " ms\t";
    cout << "Size of LHS: " << k.Size() << " Size of RHS: " << l.Size() << " Size of Result: " << m.Size() << endl;

    start = steady_clock::now();
    m = k.Intersection(l);
    end = steady_clock::now();
    cout << "Intersection of two sets: " << duration<double, milli>(end - start).count() << " ms\t";
    cout << "Size of LHS: " << k.Size() << " Size of RHS: " << l.Size() << " Size of Result: " << m.Size() << endl;

    start = steady_clock::now();
    m = k.Difference(l);
    end = steady_clock::now();
    cout << "Difference of two sets:   " << duration<double, milli>(end - start).count() << " ms\t";
    cout << "Size of LHS: " << k.Size() << " Size of RHS: " << l.Size() << " Size of Result: " << m.Size() << endl;


    cout << endl << "Test Passed: " << testPassed << "\t\t"
        << testPassed / TOTAL_TESTS * 100 << "%" << endl << endl;
    cout << endl << "All Unit Tests Passed!!!" << endl << endl;

    cout
            << "    .     '     ,		" << endl
            << "      _________		    " << endl
            << "   _ /_|_____|_\\ _	    " << endl
            << "     '. \\   / .'		" << endl
            << "       '.\\ /.'		    " << endl
            << "         '.'			" << endl << endl << endl;


    return 0;
}
