

// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 5                                *
// * Filename: passserver.cpp                                *
// * Date Created: 4/6/2020                                  *
// * References: Dr. David Gaitros, cplusplusference.com,    *
// * GNU C Library crypt()                                   *
// * Description: Definition file for the password server    *
// * class PassServer                                        *
// *                                                         *
// *                                                         *
// ***********************************************************
#include <string>
#include <crypt.h>
#include "hashtable.h"

// ******************************************************************************************************************
// * Name: PassServer(size_t size)                                                                                                                               
// * Description: Constructor                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
PassServer::PassServer(size_t size):HashTable<string,string>(size)
{

}

// ******************************************************************************************************************
// * Name: ~PassServer()                                                                                                                          
// * Description: Destructor                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
PassServer::~PassServer()
{

}

// ******************************************************************************************************************
// * Name: load(const char* filename)                                                                                                                               
// * Description: Loads a password file. Each line contains a pair of username and excrypted password.                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::load(const char* filename)
{
  return HashTable<string,string>::load(filename);
}


// ******************************************************************************************************************
// * Name: addUser(std::pair<string,string> & kv)                                                                                                                               
// * Description: adds a new username and password. It should be encrypted before insertion.                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::addUser(pair<string,string> & kv)
{
  string v = encrypt(kv.second);
  return HashTable<string,string>::insert(make_pair(kv.first,v));
}


// ******************************************************************************************************************
// * Name: addUser(pair<string,string> && kv)                                                                                                                          
// * Description: move version of the previous function, converting to r-value.                                                                                             
// * Reference: COP3330/4530, cppreference.com  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::addUser(pair<string,string> && kv)
{
  string v = encrypt(std::move(kv.second));
  return HashTable<string,string>::insert(std::make_pair(std::move(kv.first),v));
}


// ******************************************************************************************************************
// * Name: removeUser(const string & k)                                                                                                                            
// * Description: Deletes existing user with username k                                                                                            
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::removeUser(const string & k)
{
  return HashTable<string,string>::remove(k);
}


// ******************************************************************************************************************
// * Name: changePassword(const pair<string,string> & p, const string & newpassword)                                                                                                                             
// * Description: when prompted for a new password (having provided credentials) 
// * it will delete old user and crate a new user with the new pass                                                                                              
// * Reference: Dr. Gaitros for the advie to delete and create new.  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::changePassword(const pair<string,string> & p, const string & newpassword)
{
  string pass = encrypt(p.second);
  string user = p.first;
  auto currentCredentials = make_pair(user,pass);
  if (!HashTable<string,string>::match(currentCredentials))
  {
    return false;
  }
  if (p.second == newpassword)
  {
    return false;
  }
  removeUser(user);
  return addUser(make_pair(user,newpassword));
}


// ******************************************************************************************************************
// * Name: find(const string & user) const                                                                                                                              
// * Description: chek if a user exists if that user is in the hash table.                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::find(const string & user) const
{
  return HashTable<string,string>::contains(user);
}

// ******************************************************************************************************************
// * Name: dump() const                                                                                                                          
// * Description: shows the ontents of the hash table                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
void PassServer::dump() const
{
  HashTable<string,string>::dump();
}


// ******************************************************************************************************************
// * Name: size() const                                                                                                                               
// * Description: size of the hashtable (number of username/password combos)                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
size_t PassServer::size() const
{
  return HashTable<string,string>::size();
}


// ******************************************************************************************************************
// * Name: write_to_file(const char* filename) const                                                                                                                               
// * Description: Saves the username/password combo into a file.                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool PassServer::write_to_file(const char* filename) const
{
  return HashTable<string,string>::write_to_file(filename);
}

//////////////////////
// Private Function //
//////////////////////


// ******************************************************************************************************************
// * Name: encrypt(const string & str)                                                                                                                               
// * Description: GNU C Library crypt                                                                                             
// * Reference: GNU C Library
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
string PassServer::encrypt(const string & str)
{
  char salt[]="$1$########";
  string currentCredentials = crypt(str.c_str(),salt);
  return currentCredentials.substr(12,22); 
}
