  #include "Game.h"
  // Name: Game() Default Constructor
  // Desc - Empty default constructor
  // Preconditions - None
  // Postconditions - None
  Game::Game()
  {

    m_myDoodleGod=DoodleGod();
    m_myDoodleGod.SetName("EJ");
    //set elements in the array to default element values
    for(int i=0; i<PROJ2_SIZE; i++)
    {
       m_elements[i]=Element();
    }
   
  }
  
   //Default Constructor
  // Name: LoadRecipes
  // Desc - A recipe is what elements are required to merge in order to create a new element
  //        For example, if you merge Fire and Earth, you get Lava.
  //        Loads each recipe from provided file (Must use getline)
  // Preconditions - Requires file with valid element/recipe data
  // Postconditions - m_elements is populated with valid recipe data
  void Game::LoadRecipes()
  {
    
    //make a delimiter for the comma
    char DELIMITER=',';
    int elementIndex=0;
    string name="", element1="", element2="";
    //declare and open file
    ifstream myfile("proj2_recipes.txt");
    if(myfile.is_open())
    {
      while(getline(myfile,name,DELIMITER) and
       getline(myfile,element1,DELIMITER) and 
       getline(myfile,element2,'\n'))
      {
        
          Element element(name, element1, element2);
          m_elements[elementIndex]=element;
          /*make sure the DoodleGod starts off with Air Warth Fire and Water. Check through the recipes
          for the starting elements and make them immediately available to DoodleGod*/
          if(m_elements[elementIndex].m_name=="Air" or
          m_elements[elementIndex].m_name=="Earth" or
          m_elements[elementIndex].m_name=="Fire" or
          m_elements[elementIndex].m_name=="Water")
          {
            m_myDoodleGod.AddElement(m_elements[elementIndex]);

          }
          elementIndex++;
        
      }
         cout<<elementIndex<<" elements Loaded.\n";
    }
    else
    {
       cout<<"Failed to load recipes.\n";
    }

  }
  // Name: StartGame()
  // Desc: 1. Loads all recipes into m_elements (by making elements)
  //       2. Asks user for their DoodleGod's name
  //          (store in m_myDoodleGod as m_myName)
  //       3. Adds Fire, Water, Air, and Earth to Doodle God's known element list
  //	      (in m_myDoodleGod)
  //       4. Manages the game itself including win conditions continually
  //         calling the main menu 
  // Preconditions - None
  // Postconditions - Continually checks to see if player has quit
  void Game::StartGame()
  {
    string name;
    GameTitle();
    LoadRecipes();


    cout<<"What is the name of the DoodleGod?\n";
    cin>>name;
    //store in m_myDoodleGod
    m_myDoodleGod.SetName(name);
    MainMenu();
    
  }

  // Name: DisplayMyElements()
  // Desc - Displays the current elements
  // Preconditions - Player has elements
  // Postconditions - Displays a numbered list of elements
  void Game::DisplayElements()
  {
    m_myDoodleGod.DisplayElements();
  }

  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Player has an DoodleGod
  // Postconditions - Returns number including exit
  int Game::MainMenu()
  {
    int choice=0;

    do
    {
      cout<<endl;
      cout<<"What would you like to do?\n"
      <<"1. Display the DoodleGod's Elements\n"
      <<"2. Attempt to Combine Elements\n"
      <<"3. See Score\n"
      <<"4. Quit\n";
      cin>>choice;
      
      switch(choice)
      {
        case 1: DisplayElements();
          break;

        case 2: CombineElements();
          break;

        case 3: CalcScore();
          break;

        case 4: cout<<"Thanks for playing the DoodleGod!\n";
          break;

          default: cout<<"Invalid Input\n";


      }
    }while(choice!=4);
    return 0;
  }

  // Name: CombineElements()
  // Desc - Attempts to combine known elements
  // Preconditions - DoodleGod is populated with elements
  // Postconditions - May add element to DoodleGod's list of elements
  void Game::CombineElements()
  {
    int element1Index, element2Index;
    bool flag=false;
    RequestElement(element1Index);
    RequestElement(element2Index);
    Element ele1 = m_myDoodleGod.GetElement(element1Index-1);
    Element ele2 = m_myDoodleGod.GetElement(element2Index-1);

    //find a match in the recipe by looping through
    for(int i=0; i<PROJ2_SIZE; i++)
    {
      
      /*check to see if the element entries match up with elements in the recipe list
       and check for swapped entries in the recipe list just incase*/
      if ((m_elements[i].m_element1 == ele1.m_name and m_elements[i].m_element2 == ele2.m_name) or
      (m_elements[i].m_element1 == ele2.m_name and m_elements[i].m_element2 == ele1.m_name))
      {
        if(m_myDoodleGod.CheckElement(m_elements[i])==true)
        {
          cout<<"Doodle God already knows this element."<<endl;
          m_myDoodleGod.AddAttempt();
          m_myDoodleGod.AddRepeat();
          cout<<endl;
          /*use return to make sure the rest of the code in this function doesn't execute*/
          return;
        }
        else
        {
          flag=true;
          cout<<endl;
          cout<<ele1.m_name<<" combined with "<<ele2.m_name<<" to make "<<m_elements[i].m_name<<"!\n"
              <<"\n"
              <<"The Doodle God now knows "<<m_elements[i].m_name<<endl;
          m_myDoodleGod.AddElement(m_elements[i]);
        }
        cout<<endl;
      }
      
    }
    if(flag==false)
      {
        cout<<"Nothing happened when you tried to combine "<<ele1.m_name<<" and "<<ele2.m_name<<"\n";
      }
     
    m_myDoodleGod.AddAttempt();

  }

  // Name: RequestElement()
  // Desc - Asks user to chose an element to try and merge.
  //        Checks to make sure value in range
  // Preconditions - DoodleGod has elements to try and merge
  // Postconditions - Updates choice (pass by reference)
  void Game::RequestElement(int &choice)
  {
    do {
        cout << "Which elements would you like to merge?\n"
        << "To list known elements enter -1\n";
        cin.ignore();
        cin>>choice;

        if (choice == -1)
        {
          DisplayElements();
        }
        else if((choice < 1) or (choice > m_myDoodleGod.GetNumElements()))
        {
          cout << "Invalid ingredient index." << endl;
        } 
    } while (choice < 1 or choice > m_myDoodleGod.GetNumElements());
  }

  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings passed
  // Preconditions - m_elements is populated
  // Postconditions - Returns int index of matching recipe
  int Game::SearchRecipes(string element1, string element2)
  {

    for(int i=0; i<PROJ2_SIZE; i++)
    {
      Element element=m_elements[i];
      if((element.m_element1==element1 and element.m_element2==element2) or 
         (element.m_element1==element2 and element.m_element2==element1))
      {

        return i;
      }
    
    }
    return -1;
  }

  // Name: CalcScore()
  // Desc - Displays current score for Doodle God
  // Preconditions - Doodle God is populated with elements
  // Postconditions - None
  void Game::CalcScore()
  {
    float percent=0.00;
    percent=(float)m_myDoodleGod.GetNumElements()/PROJ2_SIZE;
    cout << "***The Doodle God***" << endl;
    cout << "The Great Doodle God " <<m_myDoodleGod.GetName()<< endl;
    cout << "The Doodle God has tried to combine "<<m_myDoodleGod.GetAttempts()<< " elements" << endl;
    cout << "The Doodle God has repeated attempts "<<m_myDoodleGod.GetRepeats() << " times" << endl;
    cout << "The Doodle God found "<<m_myDoodleGod.GetNumElements()<<" out of 139 elements." << endl;
    cout << "You have completed "<<fixed<<showpoint<<setprecision(2)<<percent*100<<"% of the elements." << endl;

  }
