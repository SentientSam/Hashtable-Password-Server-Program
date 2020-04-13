
// max_prime is used by the helpful functions provided
// to you.static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. static const unsigned int default_capacity = 11;

// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 5                                *
// * Filename: hashtable.h                                   *
// * Date Created: 4/6/2020                                  *
// * References: Dr. Gaitros Assignment 5 video              *
// *                                                         *
// * Description: header file for hashtable class            *
// *                                                         *
// *                                                         *
// *                                                         *
// ***********************************************************

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<list>
#include<vector>
#include<iterator>
#include<iostream>
#include<utility>
#include<algorithm>
#include<fstream>

using namespace std;
namespace cop4530
{
  static const uint max_prime = 1301081;
  static const uint default_capacity = 11;
  template <typename K, typename V>
  class HashTable
  {		
    public:		
      HashTable(size_t size = 101);				
      // HashTable(size_t size = 101);
      // HashTable(const HashTable &);							
      ~HashTable();			
      bool contains(const K & k) const;
      bool match(const pair<K,V> & kv) const;
      bool insert(const pair<K,V> & kv);	
      bool insert(const pair<K,V> && kv);
      bool remove(const K & k);
      void clear();
      size_t size() const;	
      bool load(const char *filename);
      bool write_to_file(const char *filename) const;			
      void dump() const;
      // const HashTable & operator=(const HashTable &);					
    private:
      size_t myhash(const K & k) const;
      size_t cSize = 0;
      vector<list<pair<K,V>>> hTable;
      void makeEmpty();
      void rehash();
      unsigned long prime_below(unsigned long n);
      void setPrimes(std::vector<unsigned long>& vprimes);
  };

  #include "hashtable.hpp"
}
#endif