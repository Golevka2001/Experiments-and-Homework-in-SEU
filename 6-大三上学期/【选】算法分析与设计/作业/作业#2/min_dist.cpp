#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#define N 5
#define X_MAX 1000
#define Y_MAX 1000
#define INFINITE (X_MAX + Y_MAX)

// nuclear power plant or special agent:
struct obj
{
  // position:
  int x;
  int y;
  // type of node: 0-nuclear power plant; 1-special agent
  bool type;

  // operator < :
  bool operator<(const obj &o) const
  {
    if (x == o.x) return y < o.y;
    return x < o.x;
  }
};

// generate random position for nodes:
void gen_rand_pos(struct obj &o)
{
  o.x = rand() % X_MAX + 1;
  o.y = rand() % Y_MAX + 1;
}

// print type and position of objects:
void print_obj(const struct obj &o)
{
  if (o.type)  // special agent
    cout << "SA-(";
  else  // nuclear power plant
    cout << "NPP-(";
  cout << o.x << ", " << o.y << ")\n";
}

// calculate the distance between 2 objects:
double get_dist(const struct obj o1, const struct obj o2)
{
  if (o1.type == o2.type)  // the same type
    return INFINITE;
  else
    return sqrt(double(pow(o1.x - o2.x, 2) + pow(o1.y - o2.y, 2)));
}

// solve:
double solve(const int l, const int r, struct obj o[])
{
  double dist = INFINITE;
  if (l >= r)  // wrong index
    return dist;
  if (l + 1 == r)  // only 1 nuclear power plant and 1 special agent
    return get_dist(o[l], o[r]);

  // recurse:
  int mid = (l + r) / 2;
  dist = min(solve(l, mid, o), solve(mid + 1, r, o));

  // sort, according to y:
  struct obj temp[2 * N];
  int cnt = 0;
  int ll = l, rr = mid + 1;
  while (ll < mid && rr < r)
  {
    if (o[ll].y <= o[rr].y)
      temp[cnt++] = o[ll++];
    else
      temp[cnt++] = o[rr++];
  }
  while (ll <= mid) temp[cnt++] = o[ll++];
  while (rr <= r) temp[cnt++] = o[rr++];
  for (int i = l, j = 0; i < r; ++i, ++j) o[i] = temp[j];

  // middle part:
  cnt = 0;
  for (int i = l; i < r; ++i)
    if (o[i].x >= o[mid].x - dist && o[i].x <= o[mid].x + dist)
      temp[cnt++] = o[i];

  // update distance:
  for (int i = 0; i < cnt; ++i)
    for (int j = cnt - 1; j >= 0 && temp[i].y - temp[j].y <= dist; --j)
      dist = min(dist, get_dist(temp[i], temp[j]));

  return dist;
}

int main()
{
begin:
  srand(time(0));

  // declare:
  // 0~N-1: nuclear power plants
  // N~2N-1: special agents
  struct obj objs[2 * N];

  // initialize:
  for (int i = 0; i < N; ++i) objs[i].type = 0;
  for (int i = N; i < 2 * N; ++i) objs[i].type = 1;

  // generate position:
  for (int i = 0; i < 2 * N; ++i) gen_rand_pos(objs[i]);

  // print:
  cout << "Initial:\n";
  for (int i = 0; i < 2 * N; ++i)
  {
    cout << '[' << i << ']';
    print_obj(objs[i]);
  }

  // sort:
  sort(objs, objs + 2 * N);

  // solve:
  double dist = solve(0, 2 * N - 1, objs);

  // print:
  cout << "\nAfter solving:\n";
  for (int i = 0; i < 2 * N; ++i)
  {
    cout << '[' << i << ']';
    print_obj(objs[i]);
  }
  cout << "\nMinimum distance: " << dist << endl;

  // verify:
  cout << "\nVerify:\n";
  for (int i = 0; i < 2 * N; ++i)
    if (objs[i].type)
      for (int j = 0; j < 2 * N; ++j)
        if (!objs[j].type)
          cout << '(' << i << ", " << j << "): " << get_dist(objs[i], objs[j])
               << endl;

  system("pause");
  goto begin;

  return 0;
}
