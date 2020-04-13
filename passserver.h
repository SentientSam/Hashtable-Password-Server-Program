// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 5                                *
// * Filename: passserver.h                                  *
// * Date Created: 4/6/2020                                  *
// * References: COP4530 Assignment5.pdf                     *
// *                                                         *
// * Description: Header file for passserver class           *
// *                                                         *
// *                                                         *
// *                                                         *
// ***********************************************************
#include <string>
#include <crypt.h>
#include "hashtable.h"
using namespace cop4530;
using namespace std;

class PassServer: public HashTable<string,string>
{
  public:
    PassServer(size_t size = 101);
    ~PassServer();
    bool load(const char* filename);
    bool addUser(pair<string,string> & kv);
    bool addUser(pair<string,string> && kv);
    bool removeUser(const string & k);
    bool changePassword(const pair<string,string> & p, const string & newpassword);
    bool find(const string & user)const;
    void dump()const;
    size_t size()const;
    bool write_to_file(const char* filename)const;

  private:
    string encrypt(const string & str);
};
#include "passserver.cpp"

