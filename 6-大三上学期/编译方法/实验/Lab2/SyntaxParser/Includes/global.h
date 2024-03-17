/**
 * @File: main.cpp
 * @Brief: 一些全局辅助函数的声明
 * @Author:
 */

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

// DFA edge
struct Edge
{
  int next;
  int to;
  int w;
};

// LR(1) item:
struct Item
{
  int prod_idx = 0;              // production index
  int dot_pos = 1;               // . position
  unordered_set<int> first_set;  // first set
};

template <typename T>
unordered_set<T> &operator+=(unordered_set<int> &a, unordered_set<T> &b)
{
  a.insert(b.begin(), b.end());
  return a;
}

bool IsEqualItem(Item a, Item b);
bool IsItemInSet(Item a, vector<Item> b);
vector<Item> CombineSet(vector<Item> a, vector<Item> b);
bool IsEqualSet(vector<Item> a, vector<Item> b);
int FindSetInCollection(vector<Item> a, vector<vector<Item> > b);
