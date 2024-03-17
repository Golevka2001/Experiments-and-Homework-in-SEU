/**
 * @File: main.cpp
 * @Brief: 一些全局辅助函数的实现
 * @Author:
 */

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#include "../Includes/global.h"

// Return true if item a == item b:
bool IsEqualItem(Item a, Item b)
{
  if (a.first_set == b.first_set && a.dot_pos == b.dot_pos &&
      a.prod_idx == b.prod_idx)
    return true;
  return false;
}

// Return true if item a is in set b:
bool IsItemInSet(Item a, vector<Item> b)
{
  for (int i = 0; i < b.size(); i++)
    if (IsEqualItem(a, b[i])) return true;
  return false;
}

// Combine two sets:
vector<Item> CombineSet(vector<Item> a, vector<Item> b)
{
  for (int i = 0; i < b.size(); i++)
  {
    if (IsItemInSet(b[i], a))
      continue;
    else
      a.push_back(b[i]);
  }
  return a;
}

// Return true if set a == set b:
bool IsEqualSet(vector<Item> a, vector<Item> b)
{
  if (a.size() != b.size()) return false;
  for (int i = 0; i < a.size(); i++)
    if (!IsItemInSet(a[i], b)) return false;
  return true;
}

// Return index of the set in the collection, return -1 if not found:
int FindSetInCollection(vector<Item> a, vector<vector<Item> > b)
{
  for (int i = 0; i < b.size(); i++)
    if (IsEqualSet(a, b[i])) return i;
  return -1;
}
