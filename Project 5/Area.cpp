/******************************************                                                  
 ** File: Area.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 5, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                                                                                                                                                                                        
 ** Section REDACTED                                                                           
                                                                                             
 ** Email: REDACTED                                                                 
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Area class                                   
                                                                                             
 ** This file uses getters, constructors, and chars to                             
                                                                                             
 ** properly run all the functions for Area                                                                       
 *****************************************/
#include "Area.h"

//Name: Area (Overloaded Constructor)
  //Precondition: Must have valid input for each part of a area
  // First int is the unique identifier for this particular area.
  // The first string is the name of the area
  // The second string is the description of the area
  // The last four ints are the unique identifier for adjacent areas
  //     (-1 = no path)
  // North, East, South, and West
  //Postcondition: Creates a new area
  Area::Area(int ID, string name, string desc, int north, int east, int south, int west)
  {
    m_ID = ID;
    m_name = name;
    m_desc = desc;
    m_direction[n] = north;
    m_direction[e] = east;
    m_direction[s] = south;
    m_direction[w] = west;
  }

  //Name: GetName
  //Precondition: Must have valid area
  //Postcondition: Returns area name as string
  string Area::GetName()
  {
    return m_name;
  }

  //Name: GetID
  //Precondition: Must have valid area
  //Postcondition: Returns area id as int
  int Area::GetID()
  {
       return m_ID; 
  }
  
  //Name: GetDesc
  //Precondition: Must have valid area
  //Postcondition: Returns area desc as string
  string Area::GetDesc()
  {
    return m_desc;
  }

  //Name: CheckDirection
  //Precondition: Must have valid area
  //You pass it a char (N/n, E/e, S/s, or W/w) and if that is a valid exit it
  //returns the ID of the area in that direction
  //Postcondition: Returns id of area in that direction if the exit exists
  //If there is no exit in that direction, returns -1
  int Area::CheckDirection(char myDirection)
  {
    direction curr;
    if(myDirection == ('n' or 'N') or ('e' or 'E') or ('s' or 'S') or ('w' or'W'))
    {
      switch(myDirection)
      {
    
        case 'n': curr = n;
        break;
        case 'N': curr = N;
        break;
        case 'e': curr = e;
        break;
        case 'E': curr = E;
        break;
        case 's': curr = s;
        break;
        case 'S': curr = S;
        break;
        case 'w': curr = w;
        break;
        case 'W': curr = W;
        break;
      }
    }
    return m_direction[curr];
  }

  //Name: PrintArea
  //Precondition: Area must be complete
  //Postcondition: Outputs the area name, area desc, then possible exits
  void Area::PrintArea()
  {
    const char dir[] = {'N','E','S','W'} ;
    int length = sizeof(dir)/ sizeof(dir[0]);
    cout<<m_name<<endl;
    cout<<m_desc<<endl;

    cout<<"Possible Exits: ";
    
    for(int i = 0; i < length; i++)
    {
      if(CheckDirection(dir[i]) != -1)
      {
        cout<<dir[i]<<" ";
      }
    }
    cout<<endl;

  }


