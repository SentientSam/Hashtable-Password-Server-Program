
// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 5                                *
// * Filename: hashtable.hpp                                 *
// * Date Created: 4/6/2020                                  *
// * References: COP3330/4530, geeksforgeeks.org,            *
// * ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers),    *
// * Dr. David Gaitros                                       *
// * Description: Defenition file for the hashtable class    *
// *                                                         *
// *                                                         *
// *                                                         *
// ***********************************************************

using namespace std;
using namespace cop4530;
#include <algorithm> // for use of find, move

// ******************************************************************************************************************
// * Name: HashTable(size_t size)                                                                                                                               
// * Description: Constructor                                                                                             
// * Reference: cppreference.com  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
HashTable<K,V>::HashTable(size_t size)
{
  hTable.resize(prime_below(size));
  cSize = 0;
}

// ******************************************************************************************************************
// * Name: ~HashTable()                                                                                                                               
// * Description: HashTable Class Destructor, just calls clear.                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
HashTable<K,V>::~HashTable()
{
  clear();
}

// ******************************************************************************************************************
// * Name: contains(const K & k) const                                                                                                                               
// * Description: itterates through the list and if the i pointing is equal to k, return true                                                                                             
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers), geeksforgeeks.org   
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::contains(const K & k) const
{
  // auto & containsList = hTable[myhash(k)];
  // return find(begin(containsList), end(containsList), k) != end(containsList);
  auto & containsList = hTable[myhash(k)];
  for (auto i = containsList.begin(); i != containsList.end(); ++i)
  {
    if (i -> first == k) 
    {
      return true;
    }
  }
  return false;

}


// ******************************************************************************************************************
// * Name: match(const pair<K,V> & kv) const                                                                                                                               
// * Description: check to see if the key-value pair is in the hash table                                                                                              
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::match(const pair<K,V> & kv) const
{
  auto matchList = hTable[myhash(kv.first)];
  if (matchList.size() == 0)
  {
    return false;
  }
  for (auto i = matchList.begin(); i != matchList.end(); ++i)
  {
    if (i -> first == kv.first)
    {
      return i -> second == kv.second;
    }
  }
  return false;
}

// ******************************************************************************************************************
// * Name: insert(std::pair<K,V>& kv)                                                                                                                               
// * Description: adds the pair kv into the hash table                                                                                             
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers)  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> & kv)
{
  // auto & insertList = hTable[myhash(kv)];
  // if (find(begin(insertList), end(insertList), kv) != end(insertList))
  // {
  //   return false;
  // }
  if(match(kv))
  {
    return false;
  }
  auto & insertList = hTable[myhash(kv.first)];
  if (contains(kv.first))
  {
    for (auto i = insertList.begin(); i != insertList.end(); ++i)
    {
      if (i -> first == kv.first)
      {
        i -> second = kv.second;
        return true;
      }
    }
  }
  else
  {
    insertList.emplace(insertList.begin(), kv.first, kv.second);
    if(++cSize > hTable.size())
    {
      rehash();
    }
    return true;
  }
}

// ******************************************************************************************************************
// * Name: insert(const std::pair<K,V>&& kv)                                                                                                                               
// * Description: Move version of previous function                                                                                             
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers)  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> && kv)
{
    if(match(kv))
    {
      return false;
    }
    auto & insertList = hTable[myhash(kv.first)];
    if (contains(kv.first))
    {
      for (auto i = insertList.begin(); i != insertList.end(); ++i)
      {
        if (i -> first == kv.first)
        {
          i -> second = kv.second;
          return true;
        }
      }
    }
    else
    {
      insertList.emplace(insertList.begin(), move(kv.first), move(kv.second));
      if(++cSize > hTable.size())
      {
        rehash();
      }
      return true;
    }
}

// ******************************************************************************************************************
// * Name: remove(const K & k)                                                                                                                               
// * Description: Remove function, deleted key and corresponding val if it is in hashtable.
// * Reduces size of hashtable at the end.                                                                                            
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers)  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::remove(const K & k)
{
  if (hTable.empty())
  {
    return false;
  }
  if (!contains(k))
  {
    return false;
  }
  auto & removeList = hTable[myhash(k)];
  // auto i = find(begin(removeList), end(removeList), k);
  for (auto i = removeList.begin(); i != removeList.end(); ++i)
  {
    if (i -> first == k)
    {
      removeList.erase(i);
      break;
    }
  }

  --cSize;
  return true;
}

// ******************************************************************************************************************
// * Name: clear()                                                                                                                               
// * Description: empties the hashtable                                                                                             
// * Reference: None Used  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
void HashTable<K,V>::clear()
{
  makeEmpty();
}

// ******************************************************************************************************************
// * Name: size()                                                                                                                               
// * Description: Returns cSize (the current size)                                                                                             
// * Reference: none used  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
size_t HashTable<K,V>::size() const
{
  return cSize;
}

// ******************************************************************************************************************
// * Name: load(const char* filename)                                                                                                                               
// * Description: load the content of the file with the name filename.                                                                                             
// * Reference: COP3330/4530, cplusplus.com (for opening files)  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::load(const char* filename)
{
  clear();
  size_t count = 0;
  ifstream file;
  file.open(filename);
  pair<K,V> kv;
  while(file >> kv.first)
  {
    count++;
    file >> kv.second;
    insert(kv);
    if(count >= hTable.size())
    	rehash();
  }
  file.close();
}

// ******************************************************************************************************************
// * Name: write_to_file(const char* filename)                                                                                                                               
// * Description: write all elements from the hashtable into a file with the name of the variable filename                                                                                             
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char* filename) const
{
  ofstream myfile(filename);
  if (myfile.is_open())
  {
    for (auto i = 0; i < hTable.size(); i++)
    {
      for (auto writePair : hTable[i])
      {
        myfile << writePair.first << ' ' << writePair.second << endl;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

// *********************************************************************************************************************
// * Name: dump() const                                                                                                                               
// * Description: Displays all entires of the hashtable. After the first entry, any entries that are next to each other 
// * need to have a colon between them.                                                                                              
// * Reference: COP3330/4530  
// * Author: Samuel Lamb                                                                                                                      
// *********************************************************************************************************************
template <typename K, typename V>
void HashTable<K,V>::dump() const
{
  for (auto i = 0; i < hTable.size(); i++)
  {
    cout << "v[" << i << "]:";
    if (hTable[i].size() > 0)
    {
      auto j = hTable[i].begin();
      cout << " " << j -> first << " " << j -> second;
      j++;
      //////////////////////////////////////
      for (j ; j != hTable[i].end(); ++j)
      {
        cout << " : " << j -> first << " " << j -> second;
      }
      cout << endl;
    } 
    else
    {
      cout << endl;
    }
  }
}


/////////////////////////
//  Private Functions  //
/////////////////////////


// ******************************************************************************************************************
// * Name: myhash(const K & k)                                                                                                                               
// * Description: returns index of the vector entry where k should be stored.                                                                                             
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers) 
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K & k) const
{
  static hash<K> hf;
  return hf(k)%hTable.size();
}


// ******************************************************************************************************************
// * Name: makeEmpty()                                                                                                                               
// * Description: Deletes all elements in the hashtable, called by clear()                                                                                             
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers)    
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
{
  for (auto & thisList : hTable)
  {
    thisList.clear();
  }
}

// ******************************************************************************************************************
// * Name: rehash()                                                                                                                               
// * Description: rehash function, called when total elemetns in hash table is greater than vector size.                                                                                             
// * Reference: cop4530 ppt slides sections 5.4, 5.4, 5.5, 5.6 (Dr. Meyers)  
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
template <typename K, typename V>
void HashTable<K,V>::rehash()
{
  vector<list<pair<K,V>>> oldLists = hTable;
  hTable.resize(prime_below (2 * hTable.size()));
  for (auto & thisList : hTable)
  {
    thisList.clear();
  }
  cSize = 0;
  for (auto & thisList : oldLists)
  {
    for (auto & thisPair : thisList)
    {
      insert(move(thisPair));
      cout << endl;
    }
  }
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}