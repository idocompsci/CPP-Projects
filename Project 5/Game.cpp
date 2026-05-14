/******************************************                                                  
 ** File: Game.cpp                                                                           
                                                                                             
 ** Assignment: CMSC 202 Project 5, Spring 2025                                                    
                                                                                             
 ** Author: EJ Nyameh                                                                        
                                                                                                                                                                         
                                                                                             
 ** Section REDACTED                                                                           
                                                                                             
 ** Email: REDACTED                                                               
                                                                                             
 **                                                                                          
                                                                                             
 ** This file contains the functions for the Game class                                   
                                                                                             
 ** This file uses pointers, loops, and dymanic allocation to                             
                                                                                             
 ** properly run the game as a whole                                                                          
 *****************************************/
#include "Game.h"

// Name: Game(string filename) - Overloaded Constructor
  // Description: Creates a new Game
  // Preconditions: None
  // Postconditions: Initializes all game variables to defaults (constants)
  // including m_myHero (null), mapFile (passed value), craftFile (passed)
  // and starting area (START_AREA)
  Game::Game(string area, string craft)
  {
    m_myHero = nullptr;
    m_craftFile = craft;
    m_areaFile = area;
    m_curArea = 0;

  }

  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated
  //                 in Game
  Game::~Game()
  {
    for(unsigned int i = 0; i < m_areas.size(); i++)
    {
      Area *temp = m_areas[i];
      delete temp;
      temp = nullptr;
    }
    for(unsigned int i = 0; i < m_items.size(); i++)
    {
      Item *temp = m_items[i];
      delete temp;
      temp = nullptr;
    }
    delete m_myHero;
    m_myHero = nullptr;
  }

  // Name: LoadMap()
  // Description: Reads area data from the map file and dynamically
  //             creates Area objects. Inserts each new Area into
  //             m_areas in the order encountered.
  // Preconditions: m_mapFile is set to a valid filename;
  //             the file exists and is formatted correctly.
  // Postconditions: m_areas contains all loaded Area pointers;
  //             file stream is closed.
  void Game::LoadMap()
  {
    char DELIMITER = '|';
    string ID = "", name = "", desc = "", North = "", East = "", South = "", West = "";
    //declare and open file
    ifstream myfile(m_areaFile);
    if(myfile.is_open())
    {
      while(getline(myfile,ID,DELIMITER) and 
       getline(myfile,name,DELIMITER) and 
       getline(myfile,desc,DELIMITER) and 
       getline(myfile,North,DELIMITER) and 
       getline(myfile,East,DELIMITER) and 
       getline(myfile,South,DELIMITER) and 
       getline(myfile,West,DELIMITER))
      {
         int identifier = stoi(ID);
        int n = stoi(North);
          int e = stoi(East);
            int s = stoi(South);
              int w = stoi(West);
        Area *aArea= new Area(identifier, name, desc, n, e, s, w);
        m_areas.push_back(aArea);
      }
    } myfile.close();
  }

  // Name: LoadCraft()
  // Description: Reads crafting definitions from the craft file and
  //              creates Item objects. Parses each line into an
  //              item name and its requirement list.
  // Preconditions: m_craftFile is set to a valid filename;
  //              the file exists and uses DELIMITER.
  // Postconditions: m_items contains new Item pointers for
  //              every recipe; file stream is closed.
  void Game::LoadCraft()
  {
    char DELIMITER='|';
    string name = "";
    string craftContents = "";
    bool isName = true;
  
    //declare and open file
    ifstream myfile(m_craftFile);
    if(myfile.is_open())
    {
      vector<string> ingredients;
      while(getline(myfile,craftContents,DELIMITER))
      {
        if(isName)
        {
          name = craftContents;
          isName = false;
        }
        else
        {
          if(craftContents[0] == '\n')
          {
             Item *aItem = new Item(name, ingredients);
             m_items.push_back(aItem);
            //starting a new item

            name = craftContents.substr(1);
            ingredients = {};

          } else 
          {
            ingredients.push_back(craftContents);
          }
          
        }
        
      }
      if(ingredients.size() > 0)
      {
        Item *aItem = new Item(name, ingredients);
         m_items.push_back(aItem);
      }
    }
    myfile.close();

  }

  // Name: HeroCreation()
  // Description: Prompts the player to enter a hero name and
  //              constructs a new Hero.
  // Preconditions: Standard input (cin) is available.
  // Postconditions: m_myHero points to a newly allocated Hero
  //              with the entered name.
  void Game::HeroCreation()
  {
    string name = "";
    cout<<"Hero name: ";
    cin>>name;
    m_myHero = new Hero(name);
    
  }

  // Name: Look()
  // Description: Displays the current Area’s name, description,
  //              and possible exits.
  // Preconditions: m_curArea is a valid index into m_myMap.
  // Postconditions: Current area details are printed to stdout.
  void Game::Look()
  {
    m_areas[m_curArea]->PrintArea();

  }

  // Name: StartGame()
  // Description: Initializes game flow by loading map and crafting
  //              data, creating the hero, then showing the
  //              starting area and entering the main loop.
  // Preconditions: m_mapFile and m_craftFile are set; files exist.
  // Postconditions: Game state is initialized and Action() is called.
  void Game::StartGame()
  {
    LoadMap();
    LoadCraft();
    HeroCreation();
    Action();
  }

  // Name: Action()
  // Description: Presents the player with the main menu
  //              (Look, Move, Use Area, Craft, Inventory, Quit)
  //              and drives game interactions until the player quits.
  // Preconditions: Hero and map are initialized.
  // Postconditions: Continues looping until user selects Quit.
  void Game::Action()
  { 
    int choice = 0;
    cout<<"Welcome to UMBC Runescape!\n";
    Look();
    do{
        cout<<"What would you like to do?\n"
        <<"1. Look\n"
        <<"2. Move\n"
        <<"3. Use Area\n"
        <<"4. Craft Item\n"
        <<"5. Display Inventory\n"
        <<"6. Quit\n";
        cin>>choice;

        switch(choice)
        {
          case 1: Look();
          break;

          case 2: Move();
          break;

          case 3: UseArea();
          break;

          case 4: CraftItem();
          break;

          case 5: m_myHero->DisplayInventory();
          break;
        }

    }while(choice != 6);
    cout<<"Good bye!\n";
  }

  // Name: Move()
  // Description: Prompts the player for a direction (N/E/S/W),
  //              validates the move, updates m_curArea, and
  //              calls Look() to show the new area.
  // Preconditions: m_curArea is valid; m_myMap contains
  //              adjacent Area pointers.
  // Postconditions: m_curArea is updated to the new area index.
  void Game::Move()
  {
    char direction = 'a';
    cout<<"Which direction? (N E S W)\n";
    cin>>direction;
    int area = (m_areas.at(m_curArea))->CheckDirection(direction);
    if(area != -1)
    {
      m_curArea = area;
    }
    Look();
  }

  // Name: CraftItem()
  // Description: Displays all craftable items, prompts for a selection,
  //              and attempts crafting via Hero’s CanCraft/Craft methods.
  // Preconditions: m_items is populated with Item pointers.
  // Postconditions: If crafting succeeds, inventory is
  //              updated; otherwise prints error.
  void Game::CraftItem()
  {
    unsigned int craftable = 0;
    cout<<"Which item would you like to craft?\n";
    for(unsigned int i = 0; i < m_items.size(); i++)
    {
    
        cout<< i + 1 << ". "<<m_items[i]->GetName() << endl;
    }
    do
    {
      cout<<"Which item would you like to craft?\n";
      //clear the buffer just in case
      if(cin.peek() == '\n')
    {
      cin.ignore();
    }
      cin>>craftable;
    }while(craftable < 1 or craftable > m_items.size());

    if(m_myHero->CanCraft(m_items[craftable-1]->GetReq()))
    {
      m_myHero->Craft(m_items[craftable-1]->GetName(), m_items[craftable-1]->GetReq());
    }
    else
    {
      cout<<"Cannot craft "<<m_items[craftable - 1]->GetName()<<". Missing requirements.\n";
    }
    
  }

  // Name: UseArea()
  // Description: Prompts the player to choose a search action
  //              (Raw, Natural, Food, Hunt)
  //              and forwards that request to the Hero.
  // Preconditions: Hero exists and has methods Raw/Natural/Food/Hunt.
  // Postconditions: One gather action is performed and the result printed.
  void Game::UseArea()
  {
    int lookFor = 0;
    do
    {
      cout<<"What would you like to look for?\n"
      <<"1. Raw Materials (Mining)\n"
      <<"2. Natural Resources (Woodcutting/Foraging)\n"
      <<"3. Food (Fishing/Farming)\n"
      <<"4. Hunt\n";
      cin>>lookFor;
    }while(lookFor < 1 or lookFor > 4);
    switch(lookFor)
      {
        case 1: m_myHero->Raw();
        break;

        case 2: m_myHero->Natural();
        break;

        case 3: m_myHero->Food();
        break;

        case 4: m_myHero->Hunt();
        break;
      }
  }