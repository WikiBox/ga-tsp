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

 // Random double and integer interval
 
#include <cstdlib>
 
// Return random double d, 0 <= d < 1
inline double drand(void)
{
   return (double)rand()/((double)RAND_MAX + 1.0);
}

// Return random int i, 0 <= i < limit
inline int irand(int limit)
{
   return int(limit * drand());
}
