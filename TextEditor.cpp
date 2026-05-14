/******************************************                                                  
 ** File: TextEditor.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 3, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                             
 ** Date: 4/1/25                                                                             
                                                                                             
 ** Section 10/14                                                                            
                                                                                             
 ** Email: xl90213@umbc.edu                                                                  
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Document class                                   
                                                                                             
 ** This file uses function calls and switch cases to                              
                                                                                             
 ** properly run the program                                                                           
 *****************************************/
#include "TextEditor.h"

// Name - TextEditor - default constructor
  // Desc - Set m_fileName to empty
  // Preconditions - None
  // Postconditions - Set m_fileName to empty. Creates document (m_editor)
  TextEditor::TextEditor()
  {
    m_fileName = "";
  }

  // Name - MainMenu
  // Desc - Displays options:
  //        1. Insert Line, 2. Delete Line, 3. Edit Line, 4. Display Document
  //        5. Search Word, 6. Save to File, 7. Load from File, 8. Exit
  // Preconditions - None
  // Postconditions - Returns valid choice (1-8)
  int TextEditor::MainMenu()
  {
    int choice=0;
    
        cout<<"--- Simple Text Editor ---\n"
            <<"1. Insert Line\n"
            <<"2. Delete Line\n"
            <<"3. Edit Line\n"
            <<"4. Display Document\n"
            <<"5. Search Word\n"
            <<"6. Save to File\n"
            <<"7. Load from File\n"
            <<"8. Exit\n";
            cin>>choice;
   

    return choice;
  }

  // Name - GetLineNumber
  // Desc - Allows user to choose a specific line number from document.
  //        For functions such as DeleteLine and EditLine, the line number must be exact
  //            (between 1 and the number of lines in the document)
  //        For InsertLine, the line must be between 1 and the number of lines + 1
  // Preconditions - Document (m_editor) exists
  // Postconditions - Returns line chosen
  int TextEditor::GetLineNumber(bool isExact)
  {
    int lineChoice=0;
    cout<<"Enter line number: ";
    cin>>lineChoice;
    if(isExact == true)
    {
      while(lineChoice < 1 or lineChoice > m_editor.GetLineCount())
      {
        cout<<"Must be between 1 and "<<m_editor.GetLineCount()<<endl;
        m_editor.DisplayDocument();
        cout<<"Enter line number: ";
        cin>>lineChoice;
      }
    }
    else
    {
      while(lineChoice < 1 or lineChoice > m_editor.GetLineCount())
      {
        cout<<"Must be between 1 and "<<m_editor.GetLineCount()<<endl;
        m_editor.DisplayDocument();
        cout<<"Enter line number: ";
        cin>>lineChoice;
      }
    }

    return lineChoice;
  }

  // Name - GetFileName
  // Desc - Prompts user for file name. Stores in m_fileName
  // Preconditions - None
  // Postconditions - Returns file name entered
  string TextEditor::GetFileName()
  {
    return m_fileName;
  }

  // Name - Start
  // Desc - Calls MainMenu. Takes menu response and uses switch statement to
  //        call corresponding function (display just calls DisplayDocument)
  //        Keeps calling until user enters 8 (quit).
  // Preconditions - None
  // Postconditions - Keeps asking user what to do until they enter 8 (quit).
  void TextEditor::Start()
  {
    int choice = 0;
    do{
          choice = MainMenu();
          switch(choice)
          {

                  case 1: 
                  cout<<"**Insert Line**\n";
                  InsertLine();
                  break;

                  case 2: 
                  cout<<"**Delete Line**\n";
                  DeleteLine();
                  break;

                  case 3: 
                  cout<<"**Edit Line**\n";
                  EditLine();
                  break;

                  case 4:
                  cout<<"**Display Document**\n";
                   m_editor.DisplayDocument();
                  break;

                  case 5: 
                  cout<<"**Search Document**\n";
                  SearchDocument();
                  break;

                  case 6:
                  cout<<"**Save File**\n";
                   SaveFile();
                  break;

                  case 7: 
                  cout<<"**Load File**\n";
                  LoadFile();
                  break;

                  case 8: cout<<"Thank you for using the UMBC Text Editor\n";
                  break;

          }
      }while(choice != 8);
  }

  // Name - InsertLine
  // Desc - Inserts a new line into the document(m_editor). Asks user where to
  //        insert the new line by calling GetLineNumber. Inserts the new line before
  //        the line chosen.
  // Preconditions - None
  // Postconditions - Inserts line into document (m_editor).
  void TextEditor::InsertLine()
  {
    string text = "";
      //get the desired line position to insert at    
      int lineNum = GetLineNumber(false); 
      //clear the buffer just in case
      if(cin.peek() == '\n')
    {
      cin.ignore();
    }
    cout<<"Enter a line of text: ";
    getline(cin, text);
    m_editor.InsertLine(text, lineNum);
    
  }

  // Name - DeleteLine
  // Desc - Checks to make sure the document(m_editor) has lines. If it does,
  //        calls GetLineNumber. Then deletes line from document.
  // Preconditions - Document has at least one line.
  // Postconditions - Removes line from document (m_editor).
  void TextEditor::DeleteLine()
  {
    if(m_editor.GetLineCount() == 0)
    {
      cout<<"There is no content to delete.\n";
      return;
    }
    if(m_editor.GetLineCount() != 0)
    {
      //get the desired line to be deleted
       int lineNum = GetLineNumber(true); 
      
      m_editor.DeleteLine(lineNum);
    }
     
    

  }

  // Name - EditLine
  // Desc - Checks to make sure the document(m_editor) has lines. If it does,
  //        calls GetLineNumber. Updates the text in the chosen line.
  // Preconditions - Document has at least one line.
  // Postconditions - Updates line from document (m_editor).
  void TextEditor::EditLine()
  {
    if(m_editor.GetLineCount() == 0)
    {
      cout<<"There is no file loaded to edit.\n";
      return;
    }
    string newText="";
    if(m_editor.GetLineCount() != 0)
    {
      //display the contents of the document
      m_editor.DisplayDocument();
      //get the desired line to be edited
      int line = GetLineNumber(true);
      //clear the buffer just in case
      if(cin.peek() == '\n')
    {
      cin.ignore();
    }
      cout<<"Enter new text: ";
      getline(cin, newText);

      m_editor.EditLine(line, newText);

    }
  }

  // Name - SearchDocument
  // Desc - Checks to make sure the document(m_editor) has lines. If it does,
  //        asks user which text to search for. Displays all lines that have
  //        the matching text.
  // Preconditions - Document has at least one line.
  // Postconditions - Displays line from document (m_editor).
  void TextEditor::SearchDocument()
  {
    if(m_editor.GetLineCount() == 0)
    {
      cout<<"There is no content currently in this file.\n";
      return;
    }
    string word="";
    if(m_editor.GetLineCount() != 0)
    {
      cout<<"Enter a word to search: \n";
      cin>>word;
      cout<<endl;
      m_editor.SearchWord(word);

    }
  }

  // Name - LoadFile
  // Desc - Asks user for the file name. Opens file. Inserts lines from file
  //        into existing document (m_editor). Appends document (m_editor).
  // Preconditions - None
  // Postconditions - Inserts text from file into document (m_editor).
  void TextEditor::LoadFile()
  {
    string name="";
    cout<<"What is the name of the file?\n";
    cin>>name;
    m_editor.LoadFromFile(name);
  }

  // Name - SaveFile
  // Desc - Asks user for the file name. Opens file. Writes out all lines from
  //        document (m_editor) to the file.
  // Preconditions - None
  // Postconditions - Inserts text from document (m_editor) into file.
  void TextEditor::SaveFile()
  {
    if(m_editor.GetLineCount() == 0)
    {
      cout<<"There is no file loaded to save.\n";
      return;
    }
    string name="";
    cout<<"What is the name of the file?\n";
    cin>>name;
    m_editor.SaveToFile(name);
  }