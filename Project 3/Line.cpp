/******************************************                                                  
 ** File: Line.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 3, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                             
 ** Date: 4/1/25                                                                             
                                                                                             
 ** Section 10/14                                                                            
                                                                                             
 ** Email: xl90213@umbc.edu                                                                  
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Line class                                   
                                                                                             
 ** This file uses getters, setters, and constructors to access                           
                                                                                             
 ** key parts of the document details so the program as a whole can function properly                                                                         
 *****************************************/
#include "Line.h"

// Name - Line() - Default constructor
  // Desc - Creates an empty line (acts as linked list node)
  // Preconditions - None
  // Postconditions - Used to create a new line object with m_next as a nullptr
  Line::Line()
  {
     m_text = "";
     m_next = nullptr;

  }

  // Name - Line(string) - Overloaded constructor
  // Desc - Creates a line with the passed value and a nullptr (acts as linked list node)
  // Preconditions - None
  // Postconditions - Used to create a new line object
  Line::Line(string line)
  {
    m_text = line;
    m_next = nullptr;
  }
  
  // Name - Getters and Setters
  // Desc - Used to access the private member variables in the line object
  // Preconditions - Object exists
  // Postconditions - Either returns m_text, m_next or sets m_text or m_next
  string Line::GetText() //Returns text in node
  {
    return m_text;
  }

  Line* Line::GetNext() //Returns next line in document
  {
    return m_next;
  }

  void Line::SetText(string text) //Sets text in node
  {
    m_text = text;
  }

  void Line::SetNext(Line* next) //Sets next line in document
  {
    m_next = next;
  }
