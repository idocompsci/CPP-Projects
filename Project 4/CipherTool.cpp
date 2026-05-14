/******************************************                                                  
 ** File: CipherTool.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 4, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                                                                                          
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the CipherTool class                                   
                                                                                             
 ** This file uses pointers, loops, and dymanic allocation to                             
                                                                                             
 ** properly encrypt, decrypt, and deallocate the ciphers in the vector                                                                           
 *****************************************/
#include "CipherTool.h"


// Name: CipherTool Constructor
  // Desc - Creates a new CipherTool and sets m_filename based on string passed
  // Preconditions - Input file passed and populated with Cipher
  // Postconditions - CipherTool created
  CipherTool::CipherTool(string name)
  {
    m_filename = name;
  }

  // Name: CipherTool Destructor
  // Desc - Calls destructor for all ciphers in m_ciphers
  // Preconditions - m_ciphers is populated
  // Postconditions - m_ciphers deallocated and vector emptied
  CipherTool::~CipherTool()
  {
    for( unsigned int i = 0; i < m_ciphers.size(); i++)
    {
      Cipher *temp = m_ciphers[i];
      delete temp;
      temp = nullptr;
    }
  }

  // Name: LoadFile
  // Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
  // and put into m_ciphers (a is Atbash, s is Scytale, and o is Ong)
  // Preconditions - Input file passed and populated with Ciphers
  // Postconditions - m_ciphers populated with Ciphers
  void CipherTool::LoadFile()
  {
    ifstream file(m_filename);
    string type = "", boolean = "", sentence ="", key = "";
    int keyNum = 0;
    while(getline(file, type, DELIMITER) and getline(file, boolean, DELIMITER) and
    getline(file, sentence, DELIMITER) and getline(file, key))
    {

       if(type == "a")
       {
          Atbash *temp = new Atbash(sentence, StringToBoolean(boolean));
          m_ciphers.push_back(temp);
       }
       else if(type == "o")
       {
        Ong *temp  = new Ong (sentence, StringToBoolean(boolean));
        m_ciphers.push_back(temp);
       }
       else if(type == "s")
       {
         keyNum = stoi(key); 
        Scytale *temp  = new Scytale(sentence, StringToBoolean(boolean), keyNum);
        m_ciphers.push_back(temp);
       }
    }
  }

  // Name: StringToBoolean
  // Desc - Helper function that converts a string to a boolean for reading in file
  // Preconditions - Passed string of either 0 or 1
  // Postconditions - Returns false if 0 else true
  bool CipherTool::StringToBoolean(string input)
  {
    return stoi(input) ? true : false;
  }

  // Name: DisplayCiphers
  // Desc - Displays each of the ciphers in the m_ciphers
  // Preconditions - Input file passed and m_ciphers populated
  // Postconditions - Displays ciphers
  void CipherTool::DisplayCiphers()
  {
    for(unsigned int i = 0; i < m_ciphers.size(); i++)
     {
      cout<<i+1<<". "<<m_ciphers[i]->GetMessage()<<"("<<m_ciphers[i]->ToString()<<")"<<endl;
      cout<<endl;
     }
     cout<<endl;
  }

  // Name: EncryptDecrypt
  // Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
  // Preconditions - Input file passed and m_ciphers populated
  // Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
  void CipherTool::EncryptDecrypt(bool isEncrypted)
  {
    int counter = 0;
    if(isEncrypted == false)
    {
     for(unsigned int i = 0; i < m_ciphers.size(); i++)
     {
      if(m_ciphers[i]->GetIsEncrypted())
      {
        m_ciphers[i]->Decrypt();
        counter++;
      }
       
     }

     cout<<counter<<" ciphers decrypted\n";
     cout<<endl;
    }
    else
    {

      for(unsigned int i = 0; i < m_ciphers.size(); i++)
     {
        
        if(!m_ciphers[i]->GetIsEncrypted())
        {
          m_ciphers[i]->Encrypt();
          counter++;
        }
      
     }
      cout<<counter<<" ciphers encrypted\n";
      cout<<endl;
    }

   
  }

  // Name: Export
  // Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
  // Preconditions - Input file passed and m_ciphers populated
  // Postconditions - All ciphers exported
  void CipherTool::Export()
  {
    string cipherFile = "";
    cout<<"What would you like to call the export file?\n";
    cin>>cipherFile;

    int counter = 0;
    //declare and open the file
     ofstream file(cipherFile);
     if(file.is_open())
     {
      for(unsigned int i = 0; i < m_ciphers.size(); i++)
      {
        string output = m_ciphers[i]->FormatOutput(); 
        file<<output<<endl;
        counter++;
      }
      //close the file
      file.close();
     }
     cout<<counter<<" ciphers exported\n";
    cout<<endl;
  }

  // Name: Menu
  // Desc - Displays menu and returns choice
  // Preconditions - m_ciphers all populated
  // Postconditions - Returns choice
  int CipherTool::Menu()
  {
    int choice = 0;
    do{
      cout<<"What would you like to do?\n"
      <<"1. Display All Ciphers\n"
      <<"2. Encrypt All Ciphers\n"
      <<"3. Decrypt All Ciphers\n"
      <<"4. Export All Ciphers\n"
      <<"5. Quit\n";
      cin>>choice;
      switch(choice)
      {
        case 1: DisplayCiphers();
      break;

          case 2: EncryptDecrypt(true); 
      break;

          case 3: EncryptDecrypt(false);
        break;

          case 4: Export();
        break;

        case 5: cout<<"Thanks for using UMBC Encryption\n";
        break;
      }
    }while(choice != 5);

    return choice;

  }

  // Name: Start
  // Desc - Loads input file, allows user to choose what to do
  // Preconditions - m_ciphers populated with ciphers
  // Postconditions - none
  void CipherTool::Start()
  {
    LoadFile();
    Menu();
  }