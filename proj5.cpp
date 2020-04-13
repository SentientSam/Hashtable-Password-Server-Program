// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 5                                *
// * Filename: proj5.cpp                                     *
// * Date Created: 4/6/2020                                  *
// * References: Contained files, cplusplus.org              *
// *                                                         *
// * Description: Driver file for the hashtable project      *
// *                                                         *
// *                                                         *
// *                                                         *
// ***********************************************************

#include <crypt.h>
#include <iostream>
#include <string>
#include "passserver.h"

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
using namespace std;
int main()
{
  size_t size;
  cout << "Enter preferred hash table capacity: ";
  cin >> size;
  PassServer ps(size);
  char c;
  char* filename = new char[30];
  do
  {
    Menu();
    cin >> c;
    string name,password;
    string newPassword;
    switch(c)
    {
      case 'l':
        cout << "Enter password file name to load from: ";
        cin >> filename;
        if (!ps.load(filename))
        {
          cout << "Cannot open file " << filename << endl;
        }
        break;
      case 'a':
        cout << "Enter Username: ";
        cin >> name;
        cout << "Enter Password: ";
        cin >> password;
        if (ps.addUser(make_pair(name,password)))
        {
          cout << "User " << name << " added\n";
        }
        else
        {
          cout << "******Error: User already exists. Could not add user.\n ";
        }
        break;
      case 'r':
        cout << "Enter Username: ";
        cin >> name;
        if (ps.removeUser(name))
        {
          cout << "User " << name << " deleted" << endl;
        }
        else
        {
          cout << "*****Error: User not found. Could not delete user" << endl;
        }
        break;
      case 'c':
        cout << "Enter Username: ";
        cin >> name;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter new password: ";
        cin >> newPassword;
        if(!ps.changePassword(make_pair(name,password),newPassword))
        {
          cout << "****Error: Could not change user password" << endl;
        }
        else
        {
          cout << "Password changed for user " << name << endl;
        }
        break;
      case 'f':
        cout << "Enter Username: ";
        cin >> name;
        if (!ps.find(name))
        {
          cout << "User " << name << " not found." << endl;
        }
        else
        {
          cout << "User " << name << " found." << endl;
        }
        break;
      case 'd':
        ps.dump();
        break;
      case 's':
        cout << "Size of hashtable: " << ps.size() << endl;
        break;
      case 'w':
        cout << "Enter password file name to write to: ";
        cin >> filename;
        if (!ps.write_to_file(filename))
          cout << "*****Error: Could not write to file " << filename << endl; 
        break;
      case 'x':
        cout << "Goodbye!\n";
        break;
    }

  }
  while(c != 'x');
  return 0;
}