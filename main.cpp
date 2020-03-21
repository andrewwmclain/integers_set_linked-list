#include "integerset.h"

#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

int Menu();

int main(int argc, char* argv[]) {
    //prompt user for menu choice until user chooses -1
    while(Menu() != -1){
        continue;
    }
    cout << "goodbye\n";
    return 0;
}

//Presents menu options and prompts user for choice of operation and
//array elements. Calls functions accordingly.
//Parameters:
//  None.
//Returns:
//  Nothing
//Possible errors:
//  Invalid or incorrect user response

int Menu(){
    string userNumsA;
    string userNumA;
    string userNumsB;
    string userNumB;
    string userResponse;
    IntegerSet A;
    IntegerSet B;

    cout << "1. Set Union\n";
    cout << "2. Set Intersection\n";
    cout << "3. Set Difference\n";
    cout << "4. Exit\n";

    cin >> userResponse;

    while(static_cast<int>(userResponse[0]) - 48 < 1 || static_cast<int>(userResponse[0]) - 48 > 4 ||
          !isdigit(userResponse[0]) || userResponse.size() > 1){
        if(!isdigit(userResponse[0]) || userResponse.size() > 1){
            cout << "Incorrect input!\n";
            cout << "1. Set Union\n";
            cout << "2. Set Intersection\n";
            cout << "3. Set Difference\n";
            cout << "4. Exit\n";
            cin >> userResponse;
        }
        else{
            cout << "Incorrect menu option!\n";
            cout << "1. Set Union\n";
            cout << "2. Set Intersection\n";
            cout << "3. Set Difference\n";
            cout << "4. Exit\n";
            cin >> userResponse;
        }
    }
    if(static_cast<int>(userResponse[0]) - 48 == 4 ){
        return -1;
    }

    cout << "Set A:\n";
    cout << "Input numbers to be included in the set, -1 to stop\n";

    while(userNumA != "-1"){
        cin >> userNumA;
        userNumsA.append(userNumA + " ");
    }

    stringstream ss;
    ss << userNumsA;
    A.Read(ss);
    ss.clear();
    userNumsA.clear();
    cout << "A = " << A.ToString() << endl;

    cout << "Set B:\n";
    cout << "Input numbers to be included in the set, -1 to stop\n";

    while(userNumB != "-1"){
        cin >> userNumB;
        userNumsB.append(userNumB + " ");
    }

    ss << userNumsB;
    B.Read(ss);
    ss.clear();
    userNumsB.clear();
    cout << "B = " << B.ToString() << endl;

    if(static_cast<int>(userResponse[0]) - 48 == 1 ){
        cout << "A U B = C = " << A.Union(B).ToString() << endl;
        return 1;
    }
    else if(static_cast<int>(userResponse[0]) - 48 == 2 ){
        cout << "A n B = C = " << A.Intersection(B).ToString() << endl;
        return 2;
    }
    else if(static_cast<int>(userResponse[0]) - 48 == 3 ){
        cout << "A - B = C = " << A.Difference(B).ToString() << endl;
        return 3;
    }
        return -1;
}
