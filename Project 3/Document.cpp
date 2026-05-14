/******************************************                                                  
 ** File: Document.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 3, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                             
 ** Date: 4/1/25                                                                             
                                                                                             
 ** Section 10/14                                                                            
                                                                                             
 ** Email: xl90213@umbc.edu                                                                  
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Document class                                   
                                                                                             
 ** This file uses pointers, loops, and dymanic allocation to                             
                                                                                             
 ** properly add and remove lines into the desired document                                                                           
 *****************************************/
#include "Document.h"
#include <vector>

// Name - Document() - Default constructor
  // Desc - Creates an empty Document (linked list)
  // Preconditions - None
  // Postconditions - Sets m_head to nullptr and m_lineCount = 0
  Document::Document()
  {
    m_head = nullptr;
    m_lineCount = 1 ;
  }

  // Name - ~Document() - Destructor
  // Desc - Removes all lines from Document (removes all nodes from linked list)
  // Preconditions - None
  // Postconditions - Removes all lines and sets m_head to nullptr
  //                  and m_lineCount = 0
  Document::~Document()
  {
    //create another pointer and assign it to m_head
    Line* temp = m_head;
    Line* prev = m_head;
    /*create a while loop to loop through the linked list and delete
    all nodes untill the temp pointer equals nullptr*/
    while(temp != nullptr)
    {
      //make temp pointer point to the next node in the list
      prev = temp;
      temp = temp->GetNext();
      //delete the node
      delete prev;
      //assign m_head to temp so it can move along the list
      prev = nullptr;
    }
    m_head = nullptr;
    m_lineCount=0;
  }

  // Name - InsertLine(string,int)
  // Desc - Inserts a new line (node) into the Document (linked list)
  //        Dynamically allocates new line and inserts line in position
  //        indicated. Inserts the line **before** the position.
  //        For example, if position 1 then inserts a new first line to the Document
  // Preconditions - Document exists
  // Postconditions - New line inserted into the Document
  void Document::InsertLine(string text, int position)
  {
    //create a new node and pointer
    Line *curr = new Line(text);
    Line *prev = m_head;
    if( m_head == nullptr)
    {
    
      m_head = curr;
      
    }
    else
    {
        /*make a if statement checking if the positon is equal to 1*/
        if(position == 1)
        {
          Line* node = new Line(text);
          node->SetNext(m_head);
          m_head = node;
        }
        else
        {
          //loop to desired position
          for(int i = 1; i < position - 1; i++)
          {
            prev = prev->GetNext();
          }

        
          /*put the new node in the linked list, create a temp variable
          then, set the temp to the node after prev*/ 
          Line* temp = prev->GetNext();
          /*set the new next of prev to the node we're adding*/
          prev->SetNext(curr);
          /*Finally, set the new node's next to the node that prev was
          initially pointing at*/
          curr->SetNext(temp);
        }
      
      

    }
      //increment count
      m_lineCount++;
  }

  // Name - DeleteLine(int)
  // Desc - Deletes a line from the Document at a provided position
  //        Deletes the exact line chosen.
  //        Indicates the document is empty if the Document has no lines
  // Preconditions - Document exists and line exists
  // Postconditions - Line removed from Document
  void Document::DeleteLine(int position)
  {
    //create new pointers
    Line* curr = m_head;
    Line* prev = m_head;
    
    if(position == 1)
    {
      Line* temp = m_head->GetNext();
      delete m_head;
      m_head = temp;

    }
    else
    {
        //loop to desired position
      for(int i = 1; i < position; i++)
      {
        prev = curr;
        curr = curr->GetNext(); //setting curr to the next node ahead
      }
      //point prev to the node after current
      prev->SetNext(curr->GetNext());
      //delete current
      delete curr;
      //set current to nullptr
      curr = nullptr;
    }
       //decrement count
      m_lineCount--;
    
  }

  // Name - EditLine(int, string)
  // Desc - Edits the text in a specific Line at a provided position (line number).
  //        Updates the string in a specific Line. Uses the exact line number.
  //        Indicates the document is empty if the Document has no Lines
  // Preconditions - Document exists and line exists.
  // Postconditions - Line text updated at a provided position
  void Document::EditLine(int position, string newText)
  {
     //create a new pointer
    Line *curr = m_head;

    if(m_head == nullptr)
    {
      cout<<"There is nothing to edit.\n";
      return;
    }
    

    //loop to desired position
    for(int i = 1; i < position; i++)
    {
      curr = curr->GetNext(); //setting curr to the next node ahead
    }
    curr->SetText(newText);
  }

  // Name - DisplayDocument
  // Desc - Iterates through the Document and displays all data in Line
  //        Indicates the document is empty if the Document has no lines
  // Preconditions - Document exists
  // Postconditions - Displays all lines in Document
  void Document::DisplayDocument()
  {
    if(m_head == nullptr)
    {
      cout<<"There is nothing to display.\n";
      return;
    }
    
    //create a temp pointer
    Line *temp = m_head;
    
    //loop through the list and display all the content
    int i=1;
    while(temp != nullptr)
    {
      cout<<i<<". "<<temp->GetText()<<endl;
      temp = temp->GetNext();
      i++;
    }
  }

  // Name - SearchWord(string)
  // Desc - Iterates through the Document and searches for provided text
  //        Uses the "find" command in string
  //        Returns any complete word or any substring.
  //        For example, if you search for 'a' then it will
  //           return any line that has an 'a' in any word.
  //        Details: https://cplusplus.com/reference/string/string/find/
  //        Indicates if string not found
  // Preconditions - Document exists
  // Postconditions - Indicates line number where found or not
  void Document::SearchWord(string word)
  {
    //create a new pointer
    Line *temp = m_head;
    int lineNum = 1;

    while(temp != nullptr)
    {
      if(temp->GetText().find(word) != string::npos)
      {
        cout<<"Word found in line "<<lineNum<<": "<<temp->GetText()<<endl;
       
      }
      temp = temp->GetNext();
      lineNum++;
    }
     cout<<endl;

  }

  // Name - SaveToFile(string)
  // Desc - Iterates through the Document and saves all lines to
  //        provided filename
  // Preconditions - Document exists
  // Postconditions - Writes all lines in Document to file
  void Document::SaveToFile(string filename)
  {
    //make a new pointer
    Line *temp = m_head;

    //declare and open the file
     ofstream myfile(filename);
     if(myfile.is_open())
     {
      while(temp != nullptr)
      {
        /*get the text at the current pointer position*/
        myfile<<temp->GetText()<<endl;

        //go to the next node
        temp = temp->GetNext();
      }
      //close the file
      myfile.close();
     }
     cout<<"File saved successfully!\n";
    cout<<endl;
  }

  // Name - LoadFromFile(string)
  // Desc - For each line in the input file, inserts one line
  //        into the Document
  // Preconditions - Document exists
  // Postconditions - Writes all from file to Document
  void Document::LoadFromFile(string filename)
  {
    string text = "";
    //create a vector
    vector <string> words;
    
    fstream myfile(filename);
    while(getline(myfile, text))
    {
       InsertLine(text, m_lineCount + 1);

    }
    cout<<m_lineCount<<endl;
    cout<<"File loaded successfully!\n";
    cout<<endl;

  }

  // Name - GetLineCount();
  // Desc - Returns m_lineCount
  // Preconditions - Document exists
  // Postconditions - Returns m_lineCount
  int Document::GetLineCount()
  {
    return m_lineCount;
  }