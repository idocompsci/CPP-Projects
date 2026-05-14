#include "DoodleGod.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Name: DoodleGod() - Default Constructor
  // Desc: Used to build a new DoodleGod
  // Preconditions - None
  // Postconditions - Creates a new DoodleGod and sets default values to 0 for all integers
   DoodleGod::DoodleGod()
  {
      m_myName="";
     m_attempts=0;
     m_repeats=0;
     m_numElements=0;
   
  }

// Name: DoodleGod(name) - Overloaded constructor
  // Desc - Used to build a new DoodleGod
  // Preconditions - Requires name
  // Postconditions - Creates a new DoodleGod and sets default values to 0 for all integers
   DoodleGod::DoodleGod(string name)
  {
    SetName(name);
    
  }

  // Name: GetName()
  // Desc - Getter for DoodleGod name
  // Preconditions - DoodleGod exists
  // Postconditions - Returns the name of the DoodleGod
  string DoodleGod::GetName()
  {
    return m_myName;
  }

  // Name: SetName(string)
  // Desc - Allows the user to change the name of the DoodleGod
  // Preconditions - DoodleGod exists
  // Postconditions - Sets name of DoodleGod
  void DoodleGod::SetName(string name)
  {
    m_myName=name;
  }


  // Name: DisplayElements()
  // Desc - Displays a numbered list of all elements known by the DoodleGod
  // Preconditions - DoodleGod exist
  // Postconditions - Displays numbered list of all known elements
  void DoodleGod::DisplayElements()
  {
    for(int i=0; i<m_numElements; i++)
    {
      cout<<i+1<<". "<<m_myElements[i].m_name<<endl;
    }
  }

// Name: GetNumElements()
  // Desc - Returns number of elements known by the DoodleGod
  // Preconditions - DoodleGod exists
  // Postconditions - Returns the integer value of all known elements
  int DoodleGod::GetNumElements()
  {
    return m_numElements;
  }

  // Name: CheckElement(Element)
  // Desc - Checks to see if the DoodleGod had identified an element
  // Preconditions - DoodleGod already has elements
  // Postconditions - Returns true if DoodleGod has element else false
  bool DoodleGod::CheckElement(Element element)
  {
    if(m_numElements==0)
    {
      return false;
    }
    else
    {
      for(int i=0; i<m_numElements; i++)
      {
        //comparing the name of the found element vs elements already in the list
        if(m_myElements[i].m_name==element.m_name)
        {
          return true;
          AddRepeat();
        }
      }
      return false;
    }
    
  }

  // Name: AddElement(Element)
  // Desc - Adds element to m_myElements if not known and increases numElements
  // Preconditions - DoodleGod exists and new element not already known
  // Postconditions - Adds element to m_myElements
  void DoodleGod::AddElement(Element element)
  {
    if(CheckElement(element)==false)
    {
      m_myElements[m_numElements]=element;
      m_numElements++;
    }

  }

  // Name: GetElement(int)
  // Desc - Checks to see if the DoodleGod has an element
  // Preconditions - DoodleGod already has elements
  // Postconditions - Returns element at index
  Element DoodleGod::GetElement(int index)
  {
    

    return m_myElements[index];
  }

  // Name: AddAttempt
  // Desc - Increments attempts
  // Preconditions - DoodleGod attempts a merge
  // Postconditions - Increments every time a merge is attempted
  void DoodleGod::AddAttempt()
  {
    m_attempts++;
  }

  // Name: GetAttempts()
  // Desc - Returns number of attempts for that DoodleGod
  // Preconditions - DoodleGod exists
  // Postconditions - Returns total number of attempts
  int DoodleGod::GetAttempts()
  {
    return m_attempts;
  }

  // Name: AddRepeat()
  // Desc - Increments repeats for every time an element has already been found
  // Preconditions - DoodleGod attempts a merge
  // Postconditions - Increments every time a merge yields an element already found
  void DoodleGod::AddRepeat()
  {
    m_repeats++;
  }
  // Name: GetRepeats()
  // Desc - Returns number of repeats for that DoodleGod
  // Preconditions - DoodleGod exists
  // Postconditions - Returns total number of repeats
  int DoodleGod::GetRepeats()
  {
    return m_repeats;
  }
