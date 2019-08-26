/***************************************************************************
 *   Copyright (C) Anders Larsen                                           *
 *   anders.larsen@spray.se                                                *
 *                                                                         *
 *   Use of a Genetic Algoritm to solve a Traveling Salesman Problem.      *
 *   The code can easily be adapted to other types problems as long as     *
 *   solutions  can be expressed as fixed length arrays of integers.       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "tsp.h"
#include <assert.h>
#include <math.h>
#include <vector>
#include <algorithm>

// To disable the asserts use:
// #define NDEBUG

// Max value for coords - change to match (virtual) screen size if you plot?
const int maxx = 10000;
const int maxy = 10000;

// In the constructor we create a random tsp
Tsp::Tsp(int n) {
   noOfCities = n;

   // Generate random coords
   for(int i = 0; i < noOfCities; i++)
      coords.push_back(std::make_pair(irand(maxx), irand(maxy)));

   // Create distance table
   std::vector<double> row(noOfCities);
   distances.insert(distances.begin(), noOfCities, row);

   // And store all distances
   for(int i = 0; i < noOfCities; i++) {
      for(int j = 0; j != noOfCities; j++) {
         int dx = coords[i].first - coords[j].first;
         int dy = coords[i].second - coords[j].second;
         distances[i][j] = sqrt(dx * dx + dy * dy);
      }
   }
}

// To encode a tsp-solution we must be able to
// generate a random valid tour &s
void Tsp::encode(Sol &s) {
   s.resize(noOfCities);

   for(int i = 0; i < noOfCities; i++)
      s[i] = i;

   std::random_shuffle(s.begin(), s.end());
}

// The genetic algorithm must know how to mutate a solution
void Tsp::mutate(Sol &s) {
   // Random choice of different types of mutation
   switch(irand(3)) {
      case 0: {  // Reverse random sequence
         int pos = irand(noOfCities);
         int len = 2 + irand(noOfCities / 3);
         int sop = pos + len;

         while(pos < sop) {
            std::swap(s[pos % noOfCities], s[sop % noOfCities]);
            pos++; sop--;
         }
         break;
      }
      case 1: {  // Swap two random sequences
         int pos1 = irand(noOfCities);
         int pos2 = irand(noOfCities);
         int len = irand(noOfCities / 2);

         for(int i = 0; i < len; i++) {
            std::swap(s[(pos1 + i) % noOfCities],
                 s[(pos2 + i) % noOfCities]);
         }
         break;
      }
      case 2: {  // Random "jumping" cities
         int pos1 = irand(noOfCities);
         int pos2 = irand(noOfCities);
         int n = 1 + irand(noOfCities / 10);

         while(n--) {
            pos1 += 1 + irand(noOfCities / 10);
            pos2 -= 1 + irand(noOfCities / 10);

            if(pos1 >= noOfCities) pos1 -= noOfCities;
            if(pos2 < 0) pos2 += noOfCities;

            std::swap(s[pos1], s[pos2]);
         }
         break;
      }
   }
}


// For highly optimized PMX use:
#define PMX_lookup 1
#ifdef PMX_lookup

// Use the tours in a and b to create new in c and d using random PMX
// This version of PMX is optimized for large problems
// (many cities) using lookup tables into the solutions.
// It's possible to unroll some loops as well for even more speed.
// PMX = Partially matched/mixed(?) crossover.
void Tsp::crossover(const Sol &a, const Sol &b, Sol &c, Sol &d) {
   assert(a.size() == b.size());

   const int n = a.size();

   // static to avoid realloc every call
   static std::vector<int> lookup_c;
   static std::vector<int> lookup_d;

   lookup_c.resize(n);
   lookup_d.resize(n);
   c.resize(n);
   d.resize(n);

   // Create lookup tables and initialize c and d
   for(int i = 0; i != n; i++) {
      c[i] = a[i];
      lookup_c[c[i]] = i;

      d[i] = b[i];
      lookup_d[d[i]] = i;
   }

   // Crossover random sequence of at least n / 4 and at most 3/4 * n cities
   const int start = irand(n);
   const int end = start + (n / 4) + irand(n / 2);

   // Do the PMX
   for(int i = start; i != end; i++) {
      const int j = i % n; // i mod n

      const int posb = lookup_c[b[j]];
      std::swap(c[posb], c[j]);
      lookup_c[c[posb]] = posb;

      const int posa = lookup_d[a[j]];
      std::swap(d[posa], d[j]);
      lookup_d[d[posa]] = posa;
   }
}

#else // No optimized PMX - provided for testing and comparision

// Use the tours in a and b to create new in c and d using random PMX
// This is the plain unoptimized PMX: Use of linear find in innermost
// loop may be expensive if solutions are large (many cities).
// But this avoids the overhead of having to create lookup tables.

void Tsp::crossover(const Sol &a, const Sol &b, Sol &c, Sol &d) {
   assert(a.size() == b.size());
   
   c = a;
   d = b;

   const int n = a.size();
   assert(n = 10);
   // Crossover random sequence of at least n / 4 and at most 3/4 * n cities
   const int start = irand(n);
   const int end = start + (n / 4) + irand(n / 2);
   
   // PMX
   for(int i = start; i != end; i++) {
      int j = i % n; // i mod n
      std::swap(c[j], *(find(c.begin(), c.end(), b[j])));
      std::swap(d[j], *(find(d.begin(), d.end(), a[j])));
   }
}

#endif

// Fast tour evaluation because we have pre-calculated all distances
double Tsp::evaluate(Sol &s) {
   // Distance from last to first city...
   double sum = distances[s.back()][s.front()];

   // ...and the rest of the distances...
   for(SolIter i = s.begin(); i != (s.end() - 1); i++)
      sum += distances[*i][*(i+1)];

   return sum;
}
