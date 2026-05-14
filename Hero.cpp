#include "Hero.h"

// Name: Hero(const string& name)
  // Description: Constructs a new Hero with the specified name.
  // Preconditions: name must be a valid, non‐empty string.
  // Postconditions: m_name is initialized; inventory map is empty.
  Hero::Hero(const string& name)
  {
    m_name = name;
  }

  // Name: ~Hero()
  // Description: Destructor for Hero.
  // Preconditions: None.
  // Postconditions: Releases any dynamically allocated items in Hero.
  //                 None in this case.
  Hero::~Hero()
  {

  }

  // Name: GetName()
  // Description: Retrieves the hero’s name.
  // Preconditions: None.
  // Postconditions: Returns the value of m_name.
  string Hero::GetName() const
  {
    return m_name;
  }

  // Name: SetName(const string& name)
  // Description: Updates the hero’s name.
  // Preconditions: name must be a valid string.
  // Postconditions: m_name is set to the new value.
  void Hero::SetName(const string& name)
  {
    m_name = name;
  }

  // Name: DisplayInventory()
  // Description: Prints the hero’s current inventory using overloaded << operator
  // Preconditions: Inventory map has been initialized.
  // Postconditions: Inventory contents are displayed.
  void Hero::DisplayInventory() const
  {
    cout<<"******* INVENTORY *******\n";
    cout<<m_inventory<<endl;
  }

  // Name: CollectItem(const string& item)
  // Description: If the item exists, in m_inventory, uses Update to increment quantity
  //              If the item does not exist in m_inventory, inserts it.
  // Preconditions: item must be a valid item name.
  // Postconditions: Inventory count for item is incremented by 1.
  // Note: Uses try and catch (const out_of_range&) and inserts if caught.
  void Hero::CollectItem(const string& item)
  {
    
    try 
    {
      m_inventory.Update(item,  m_inventory.ValueAt(item) + 1);
    } catch (const out_of_range &err)
     {
      // they don't have this item
      // and are just now collecting it.
      m_inventory.Insert(item, 1);
    }
  }

  // Name: CanCraft(const vector<string>& requirements)
  // Description: Iterators through the requirements to see if they have quantity in m_inventory
  // Preconditions: Requirements vector populated with item names.
  // Postconditions: Returns true if every required item has count ≥1.
  // Note: Uses try and catch (const out_of_range&) and returns false if caught.
  bool Hero::CanCraft(const vector<string>& requirements) const
  {
    //loop through the vector
    for(unsigned int i = 0; i < requirements.size(); i++)
    {
      if(requirements[i] != "None" and m_inventory.ValueAt(requirements[i]) < 1)
      {
         
        try
        {
          m_inventory.At(requirements[i]);
        }
        catch(out_of_range& err)
        {
          cout<<err.what();
        }
        return false;

      }
      
    }
    //return true as default
    return true;
  }

  // Name: Craft(const string& result, const vector<string>& requirements)
  // Description: Consumes the listed requirements and adds the
  //              crafted "result" (iterates through requirements and Updates)
  // Preconditions: Call to CanCraft(requirements) must return true.
  // Postconditions: Each requirement’s count is decremented by 1;
  //                 Result of crafting is added.
  void Hero::Craft(const string& result, const vector<string>& requirements)
  {
    //put the new item  you just crafted in your inventory
    CollectItem(result);
    cout << "Crafted: " << result <<"!"<< endl;

    for(unsigned int i = 0; i < requirements.size(); i++)
    {
      //decrement the quantity of the item used to craft
      if (requirements[i] != "None")
      {
        m_inventory.Update(requirements[i], m_inventory.ValueAt(requirements[i]) - 1);
      }
    }
  }

  // Name: Raw()
  // Description: Simulates mining for raw materials. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random raw material
  //                 to inventory or reports none found.
  void Hero::Raw()
  {
    string found = "You searched and harvested some ";
    string notFound = "You searched and found nothing.\n";
    Gather(RawProducts, notFound, found);
  }

  // Name: Natural()
  // Description: Simulates foraging for natural resources. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random natural resource
  //                 or reports none found.
  void Hero::Natural()
  {
    string found = "You searched and harvested some ";
    string notFound = "You searched and found nothing.\n";
    Gather(NaturalProducts, notFound, found);
  }

  // Name: Food()
  // Description: Simulates gathering food items. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random food item or reports none found.
  void Hero::Food()
  {
    string found = "You searched and harvested some ";
    string notFound = "You searched and found nothing.\n";
    Gather(FoodProducts, notFound, found);
  }

  // Name: Hunt()
  // Description: Simulates hunting for creature drops. Passes values
  //              and calls Gather function.
  // Preconditions: Random number generator seeded.
  // Postconditions: Possibly adds a random creature drop
  //                 or reports none found.
  void Hero::Hunt()
  {

    string found = "You went hunting and found some ";
    string notFound = "You went hunting and found nothing.\n";
    Gather(HuntProducts, notFound, found);
  } 

//Name: Gather
  // Description: Randomly selects an item from vector products passed.
  //              If selection equals list size, prints 'noItemMsg';
  //              otherwise prints foundMsg + item and adds it
  //              to the hero's inventory.
  // Preconditions: 'products' must contain valid item names.
  // Postconditions: Inventory is incremented for the selected
  //               item if found; message printed.
  void Hero::Gather(const vector<string>& products, const string& noItemMsg, const string& foundMsg)
        {
         unsigned int random = rand() % (products.size());
          if(random < products.size())
          {
            string found = products.at(random);

            try {
              // try to increment the current amount if it exists
              m_inventory.Update(found, m_inventory.ValueAt(found) + 1);
            } catch (out_of_range &err){
              // there was no current amount to increment
              // insert it for the first time
              m_inventory.Insert(found, 1);
            }
            cout<<foundMsg<<" "<<found<<"!"<<endl;
          }
          else
          {
            cout<<noItemMsg<<endl;
          }


        }
