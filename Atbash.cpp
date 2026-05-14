/******************************************                                                  
 ** File: Atbash.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 4, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                             
 ** Date: 4/15/25                                                                             
                                                                                             
 ** Section 10/14                                                                            
                                                                                             
 ** Email: xl90213@umbc.edu                                                                  
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Atbash class                                   
                                                                                             
 ** This file uses constants, loops, and strings to                             
                                                                                             
 ** properly encrypt and decrypt messages                                                                           
 *****************************************/
#include "Atbash.h"
const int CAP_A_ASCII = 65;
const int LOW_A_ASCII = 97;
const int CAP_Z_ASCII = 90;
const int LOW_Z_ASCII = 122;

// Name: Atbash (Default Constructor)
  // Desc: Constructor to build an empty Atbash Cipher
  // Preconditions - None
  // Postconditions - Creates a Atbash cipher to be encrypted
  Atbash::Atbash(): Cipher()
  {

  }

  // Name: Atbash (Overloaded Constructor)
  // Desc: Constructor to build a populated Atbash Cipher
  // Preconditions - Pass it the message and isEncrypted
  // Postconditions - Creates a Atbash cipher to be encrypted
  Atbash::Atbash(string message, bool isEncrypted):Cipher(message, isEncrypted)
  {

  }

  // Name: Atbash (Destructor)
  // Desc: Destructor - Anything specific to Atbash to delete?
  // Preconditions - ~Atbash exists
  // Postconditions - Atbash destroyed
  Atbash::~Atbash()
  {

  }

  // Name: Encrypt
  // Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
  // Preconditions - Message exists
  // Postconditions - Reverses the characters. Ignores punctuation.
  void Atbash::Encrypt()
  {
    string new_message = Cipher::GetMessage();
    int length = Cipher::GetMessage().size();
  
    if(GetMessage() != "")
    {
      for(int i = 0; i < length; i++)
      {
        //flipping capital letters
        if(static_cast<int> (new_message[i]) >= CAP_A_ASCII and static_cast<int> (new_message[i]) <= CAP_Z_ASCII)
        {
          new_message[i] = static_cast <char> (CAP_Z_ASCII - (static_cast<int>(new_message[i]) - CAP_A_ASCII));
        }
        //flipping lower case letters
        else if(static_cast<int> (new_message[i]) >= LOW_A_ASCII and static_cast<int> (new_message[i]) <= LOW_Z_ASCII)
        {
          new_message[i] = static_cast <char> (LOW_Z_ASCII - (static_cast<int>(new_message[i]) - LOW_A_ASCII));
        }
       
      }
      //set the new message
      SetMessage(new_message);
      ToggleEncrypted();
    }

  }

  // Name: Decrypt
  // Desc: Reverses the alphabet (A ↔ Z, B ↔ Y, etc.)
  // Preconditions - Message exists
  // Postconditions - Reverses the characters. Ignores punctuation.
  void Atbash::Decrypt()
  {
    string new_message = Cipher::GetMessage();
  
  int length = Cipher::GetMessage().size();
    if(GetMessage() != "")
    {
      for(int i = 0; i < length; i++)
      {
        //flipping capital letters
        if(static_cast<int> (new_message[i]) >= CAP_A_ASCII and static_cast<int> (new_message[i]) <= CAP_Z_ASCII)
        {
          new_message[i] = static_cast <char> (CAP_Z_ASCII - (new_message[i] - CAP_A_ASCII));
        }
        //flipping lower case letters
        else if(static_cast<int> (new_message[i]) >= LOW_A_ASCII and static_cast<int> (new_message[i]) <= LOW_Z_ASCII)
        {
          new_message[i] = static_cast <char> (LOW_Z_ASCII - (new_message[i] - LOW_A_ASCII));
        }
       
      }
      //set the new message
      SetMessage(new_message);
      ToggleEncrypted();
    }
  }

  // Name: ToString
  // Desc - A function that returns the string of the object type
  // Preconditions - The object exists
  // Postconditions - The subtype is returned (Atbash in this case)
  string Atbash::ToString()
  {
    return "Atbash";
  }

  // Name: FormatOutput()
  // Desc - A function that returns the formatted output for Output function
  // Preconditions - The object exists (use stringstream)
  // Postconditions - c, delimiter, isencrypted, delimiter,
  //                  message, delimiter are returned for output
  string Atbash::FormatOutput()
  {
    // string is_enc = Cipher::GetIsEncrypted() ? "0" : "1";
    // string output = "a";
    // cout << output << endl;
    // output += DELIMITER;
    // output += is_enc+DELIMITER+GetMessage()+DELIMITER;
    // cout << output << endl;
    // return output;
    string encryption = Cipher::GetIsEncrypted() ? "1" : "0";
    string output = "a";
    return output + DELIMITER + encryption + DELIMITER + GetMessage() + DELIMITER;
  }