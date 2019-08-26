/***************************************************************************
 *   Copyright (C) 2004 by Anders Larsen                                   *
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

 // A simple text based test program to show how to use the GA.
 // A graphical display of the solutions would be nicer...
 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "ga.h"
#include "tsp.h"

#include <iostream>
#include <cstdlib>

const int CITIES = 500;        // Try 10 - 500  (memory and time constrained)  
const int POPSIZE = 2000;       // Try 20 - 1000 (memory and time constrained)
const int ELITISM = 5;         // Try 0-10
const double PRESSURE = 1.5;   // Try 1.1 - 3.0
const double MUTATION = 0.001; // Try 0.001 - 0.1

int main(int argc, char *argv[]) {
      
   Tsp mytsp(CITIES); 
   Ga testga(&mytsp, POPSIZE, ELITISM, PRESSURE, MUTATION);
   
   double first = testga.begin()->first;
   double best = first + 1;
   int generation = 0;
   
   for(;;) {
            
      if(testga.begin()->first < best) {
         best = testga.begin()->first;
         std::cout << "\n\n        ******** GA TSP stats *********" 
                   << "\n              Cities: " << CITIES 
                   << "\n          Population: " << POPSIZE 
                   << "\nShortest tour so far: " << best
                   << "\n  Inital random tour: " << first
                   << "\n          Generation: " << generation
                   << "\n          Crossovers: " << testga.getCrossovers()
                   << "\n         Improvement: " << 100.0 *(first - best) / first << "%";
                   
         SolIter s = testga.begin()->second.begin();
         
         std::cout << "\nBest solution so far: \n";
         
         for (int i = 0; i != std::min(40, CITIES); i++, s++)
            std::cout << "[" << *s << "] ";
                   
         std::cout << "\n";
      }
      
      /******************************************************
         Examples of how to access information about any 
         solution in order to calculate statistics about 
         the population or to draw some solution to screen.
         This code is commented out and only provided fyi. 
         
      // Get performance of the median solution like this:
      PopIter p = testga.first();
      std::advance(p, CITIES / 2);
      std::cout << "\nMedian Performance : " << p->first;
      
      // Draw the second best solution to screen like this: 
      // Note that 0 <= coords < 10000. Also note that you
      // must provide the myMoveTo and myDrawTo functions.
      PopIter q = testga.first();
      q++;             // Advance to second best solution

      // Set pen at the coord for the last city ...
      int last_x = mytsp.x(q->second.back());
      int last_y = mytsp.y(q->second.back());
      myMoveTo(last_x, last_y);
      
      // ... and draw lines to all the cities from there.
      for(int i = 0; i < q->second.size(); i++) {
         int next_x = mytsp.x(q->second[i]);
         int next_y = mytsp.y(q->second[i]);
         myLineTo(next_x, next_y);
      }            
            
      *******************************************************/
      
      testga.generation();
      
      generation++;
   }
   
   return EXIT_SUCCESS; 
}
