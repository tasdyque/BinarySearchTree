//--------------------------------------------------------------------
//
//  Laboratory 2                     database.cpp
//  Version 1.1
//  Date written: 10/8/20
//  Date last modified: 10/19/20
//  Authors: Tasdyque Syed and Alex Hernadi
//  
//  Program function: Implements a BST for a list of accounts provided
//                    by the file accountsdb.dat which contains an accounts
//                    ID, first and last name, and account balance
//  Input Files: accountsdb.dat
//  Output Files: none
//  cpp files: BSTree.cpp
//--------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

/// <summary>
/// stores the maxmimum length for a name
/// </summary>
const int maxLength = 11;

/// <summary>
/// struct that stores personal information
/// </summary>
struct AccountRecord
{
    /// <summary>
    /// account ID variable
    /// </summary>
    int accID;

    /// <summary>
    /// first and last name data variables
    /// </summary>
    char firstName[maxLength],
        lastName[maxLength];

    /// <summary>
    /// stores the balance
    /// </summary>
    double balance;                  // Balance for the account
};

/// <summary>
/// struct that is used for account Indexing
/// </summary>
struct IndexEntry
{
    /// <summary>
    /// account ID, the key for the BSTree
    /// </summary>
    int accID;

    /// <summary>
    /// record number used to search for an account 
    /// </summary>
    long recordNum;

    /// <summary>
    /// Function sets the keyfield
    /// </summary>
    //Inputs: Key to search for
    //Outputs: none
    ///
    /// precondition: recordNum is uninitialized
    /// postcondition: recordNum is set to the value of paramter key

    void setKey(int key)
    {
        recordNum = key;
    }

    /// <summary>
    /// Function returns the current key
    /// </summary>
    ///
    /// precondition: there is a key stored in the struct
    /// postcondition: returns the key field
    int getKey() const
    {
        return recordNum;
    }
};

//--------------------------------------------------------------------


int main ()
{
   /// <summary>
   /// ifstream accFile allows accountsdb.dat to be read
   /// </summary>
   /// <returns></returns>
    ifstream accFile ("accountsdb.dat");  

    /// <summary>
    ///  Account record object  is used to allocate account holder information
    /// </summary>
    /// <returns></returns>
    AccountRecord accRec;       

    /// <summary>
    /// BSTree object allows use of BSTree member functions
    /// </summary>
    /// <returns></returns>
    BSTree<IndexEntry,int> index;         

    /// <summary>
    /// IndexEntry object is used to enter an accountID as a key
    /// </summary>
    /// <returns></returns>
    IndexEntry entry;                     

    /// <summary>
    /// record number variable
    /// </summary>
    /// <returns></returns>
    int recNum = 0;                          

    /// <summary>
    /// counts the number of IDs in the file
    /// </summary>
    /// <returns></returns>
    int dataCount = 0;  
   
    /// <summary>
    /// The if statement checks to see if the accountsdb.dat is open, 
    /// The file will be closed after data is allocated
    /// The while loop enters the account names, balance into the AccountRecord object
    /// The loop also enters the AccountID and record number into the AccountRecord and IndexEntry objects
    /// as well as update the data count. 
    /// </summary>
    /// <returns></returns>
    if (accFile.is_open())
    {
        while (accFile >> entry.accID  && accFile >> entry.recordNum
            && accFile >> accRec.firstName >> accRec.lastName >> accRec.balance)
        {
            recNum = recNum + 1;
            index.insert(entry);
            dataCount++;
        }
        accFile.close();
        
    }
    else
    {
        cout << "unable to open file" << endl;
    }

    /// <summary>
    /// makes both IDs the same for the record and index
    /// </summary>
    /// <returns></returns>
    accRec.accID = entry.accID;

    /// <summary>
    /// outputs the keys in ascending order
    /// </summary>
    /// <returns></returns>
    index.showStructure();

    /// <summary>
    /// clears the status flags for the file
    /// </summary>
    /// <returns></returns>
    accFile.clear();
    
    
    /// <summary>
    /// input value/sentinel value for the main while loop
    /// </summary>
    /// <returns></returns>
    int sentinel = 0;

    /// <summary>
    /// Inner while loop iterator
    /// </summary>
    /// <returns></returns>
    int i = 0; 

    /// <summary>
    /// Second account record
    /// </summary>
    /// <returns></returns>
    AccountRecord accRec2;             

    /// <summary>
    /// second index entry 
    /// </summary>
    /// <returns></returns>
    IndexEntry entry2;         

    /// <summary>
    /// inner while loop condition, checks if ID is found
    /// </summary>
    /// <returns></returns>
    bool found = false;    

    /// <summary>
    /// Outer while loop, managed by sentinel value
    /// </summary>
    /// <returns></returns>
    while (sentinel != -1)
    {
        cout << "Enter an account ID(enter -1 to exit): ";
        cin >> sentinel;

        if (sentinel == -1)
        {
            cout << "program ended" << endl;
            break;
        }
        else if (index.retrieve(sentinel, entry))
        {
         
            /// <summary>
            /// inner while loop used to manage the search
            /// </summary>
            /// <returns></returns>
            while (i < dataCount && found == false)
            {
                accFile.open("accountsdb.dat");

                /// <summary>
                /// for loop allows entire file to be read line by line
                /// </summary>
                /// <returns></returns>
                for (int j = 0; j < dataCount; j++)
                {
                    accFile >> entry2.recordNum;
                    accFile >> entry2.accID;
                    accFile >> accRec2.firstName;
                    accFile >> accRec2.lastName;
                    accFile >> accRec2.balance;

                    accRec2.accID = entry2.accID;

                    if (sentinel == entry2.accID)
                    {
                        cout << "Match Found: " << endl;
                        cout << "Account ID: " << accRec2.accID << endl;
                        cout << "Record Number: " << entry2.getKey() << endl;
                        cout << "First Name: " << accRec2.firstName << endl;
                        cout << "Last Name: " << accRec2.lastName << endl;
                        cout << "Balance: " << accRec2.balance << endl;
                        found = true;
                        sentinel = -1;
                    }
                    
                   
                 
                }
                accFile.close();
                accFile.clear();
  

                i++;
            }
            
        }
        else
        {
            cout << "Invalid sentinel value" << endl;
        }
    }

}
