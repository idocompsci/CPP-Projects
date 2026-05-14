/******************************************                                                  
 ** File: Ong.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 4, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                             
 ** Date: 4/15/25                                                                             
                                                                                             
 ** Section 10/14                                                                            
                                                                                             
 ** Email: xl90213@umbc.edu                                                                  
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Ong class                                   
                                                                                             
 ** This file uses booleans, loops, and strings to                             
                                                                                             
 ** properly add and remove "ong" to and from strings                                                                        
 *****************************************/
#include "Ong.h"


// Name: Ong (Default Constructor)
  // Desc: Constructor to build an empty Ong Cipher
  // Preconditions - None
  // Postconditions - Creates a Ong cipher to be encrypted
  Ong::Ong():Cipher()
  {

  }

  // Name: Ong (Overloaded Constructor)
  // Desc: Constructor to build a populated Ong Cipher
  // Preconditions - Pass it the message and isEncrypted
  // Postconditions - Creates a Ong cipher to be encrypted
  Ong::Ong(string message, bool encrypted):Cipher(message, encrypted)
  {

  }

  // Name: Ong (Destructor)
  // Desc: Destructor - Anything unique to Ong to delete?
  // Preconditions - ~Ong exists
  // Postconditions - Ong destroyed
  Ong::~Ong()
  {

  }
  // Name: IsVowel (Helper function)
  // Desc: Returns true if vowel, space, or punctuation
  // Preconditions - Message exists
  // Postconditions - Returns true or false as above
  bool Ong::IsVowel(char letter)
  {
    
    return (letter == 'A' or letter == 'E' or letter == 'I' or letter == 'O'
     or letter == 'U' or letter == 'a' or letter == 'e' or letter == 'i' or 
     letter == 'o' or letter == 'u') and !IsPunct(letter);
  }

  bool Ong::IsPunct(char c)
  {
    return (c == '!' or c == '.' or c == ',' or c == '?' or c == '(' or c == ')'
    or c == ':' or c == '-' or c == '_' or c == ' ');
  }

  // Name: Encrypt
  // Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
  // If consonant then consonant and ong and dash displayed.
  // Preconditions - Message exists
  // Postconditions - Encrypts as above
  void Ong::Encrypt()
  {
    //create a variable for the length of the string
    int length = GetMessage().size();
    //create a variable for the new encrypted string
    string encrypted_message = "";

    string message = GetMessage();
    //loops through the entire message
    for(int i = 0; i < length; i++)
    {
      //if it's not a vowl, then add "ong" to the letter at the current position
      if(IsPunct(message[i]) == true)
      {
        encrypted_message += message[i];
      }
      else if(IsVowel(message[i]) == true)
      {
        encrypted_message += message[i];
      }
      else
      {
        encrypted_message += message[i];
        encrypted_message += "ong";
      }
      if(i != length - 1)
      {
        //if the character after the current index isn't a space, add a dash
        if(!IsPunct(message[i+1]) and !IsPunct(message[i]))
        {
          encrypted_message += "-";
        }
      }
      
    }
    SetMessage(encrypted_message);
    ToggleEncrypted();

  }

  // Name: Decrypt
  // Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
  // Double check words like "wrong" so that they work correctly!
  // Preconditions - Message exists
  // Postconditions - Original message is displayed
  void Ong::Decrypt()
  {
     //create a variable for the length of the string
    int length = GetMessage().size();
    //create a variable for the new encrypted string
    string decrypted_message = "";

    string message = GetMessage();

    for(int i = 0; i < length; i++)
    {
      if(message[i] == '-')
      {
       
      }
      else if(IsPunct(message[i]) == true)
      {
       decrypted_message += message[i];
      }
      else if(IsVowel(message[i]))
      {
        decrypted_message += message[i];
      }
      else
      {
        decrypted_message += message[i];
        i += 3;
      }
    }
    SetMessage(decrypted_message);
    ToggleEncrypted();

  }
  // Name: ToString
  // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (Ong in this case)
  string Ong::ToString()
  {
    return "Ong";
  }
  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - o, delimiter, isencrypted, delimiter,
  //                  message, delimiter, blank are output
  string Ong::FormatOutput()
  {
    string encryption = Cipher::GetIsEncrypted() ? "1" : "0";
    string output = "o";
    return output + DELIMITER + encryption + DELIMITER + GetMessage() + DELIMITER;
  }