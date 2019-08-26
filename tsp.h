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

 // In this file we use the problem base class and declare a specific
 // tsp type problem. We store some data concerning the tsp inside the
 // tsp-class and also provide some extra functionality to display
 // information about the problem and solutions.
 
#ifndef TSP_H
#define TSP_H

#include "problem.h"
#include "gautility.h"

class Tsp: public Problem {
public:
   void encode(Sol &s);
   void mutate(Sol &s);
   void crossover(const Sol &a, const Sol &b, Sol &c, Sol &d);
   double evaluate(Sol &s);
private:
   int noOfCities;
   std::vector<std::pair<int, int> > coords;
   std::vector<std::vector<double> > distances;
public:
   Tsp(int n);
   
   // Use these functions to get coords to plot solutions
   int x(int n) { return coords[n].first; };
   int y(int n) { return coords[n].second; };
};

#endif
