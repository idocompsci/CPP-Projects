/*Title: Map.cpp
  Description: This class defines the Map class
  Map is a templated associative container that stores
  key–value pairs in sorted order using a singly linked
  list, supporting insertion, lookup, update, and removal
  with O(n) traversal.
*/
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class Map {
public:
  // Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
  Map();
  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
  ~Map();
  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
  Map(const Map& other);
  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
  Map<K,V>& operator=(const Map& other);
  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
  void Insert(const K& key, const V& value);
  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
  void Update(const K& key, const V& value);
  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
  const V& ValueAt(const K& key) const;
  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
  Node<K,V>* At(const K& key) const;
  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
  int GetSize() const;
  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
  bool IsEmpty() const;
  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
  void Display() const;
  // Name: operator<<
  // Description: Streams all key:value pairs into os, one per line.
  // Preconditions: os is a valid ostream; map is a valid Map<K,V>.
  // Postconditions: os contains serialized map contents;
  //                returns os by reference.
  // PROVIDED
  friend ostream& operator<<(ostream& os, const Map<K, V>& map){
    Node<K,V>* current = map.m_head;
    while (current != nullptr) {
      os << current->GetKey() << ":" << current->GetValue() << endl;
      current = current->GetNext();
    }
    return os;
  }
private:
  // Name: Clear()
  // Description: Deletes all nodes in the linked list,
  //              freeing their memory and resetting the map.
  // Preconditions: None.
  // Postconditions: All dynamically allocated nodes are deleted;
  //                 m_head is set to nullptr; m_size is reset to 0.
  void Clear();  
  Node<K,V>* m_head; //Pointer to the first node in the Map
  int m_size; //Tracks the size of the Map (number of nodes)
};
#endif
//********IMPLEMENT MAP.CPP HERE DUE TO TEMPLATED CLASS*********
// Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
  template <typename K, typename V>
  Map<K,V>::Map()
  {
    m_head = nullptr;
    m_size = 0;
  }

  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
  template <typename K, typename V>
  Map<K,V>::~Map()
  {
    Clear();
  }

  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
  template <typename K, typename V>
  Map<K,V>::Map(const Map& other)
  {
    m_head = nullptr;
    m_size = 0;
    Node<K,V> *curr = other.m_head;
    while(curr != nullptr)
    {
      Insert(curr->GetKey(), curr->GetValue());
      curr = curr->GetNext();
    }
  }

  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
  template <typename K, typename V>
  Map<K,V>& Map<K,V>::operator=(const Map& other)
  {
    if(this == &other)
    {
      return *this;
    }
    if(this != &other)
    {
      Clear();
        Node<K,V> *curr = other.m_head;
        while(curr != nullptr)
        {
          Insert(curr->GetKey(), curr->GetValue());
          curr = curr->GetNext();
        }
    }
    return *this;

  }

  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
  template <typename K, typename V>
  void Map<K,V>::Insert(const K& key, const V& value)
  {
    Node<K,V> *node = new Node(key, value);
    //create a new node for traversing the list
    Node<K,V> *curr = m_head;
    //create a node to point to the previous node
    Node<K,V> *prev = m_head;
    
    //edge case: if the list is empty, then reassign m_head to the new node
    if(m_head == nullptr)
    {
     
      m_head = node;
     
    }
    //edge case: if theres only one node in the list, act accordingly
    else if(m_head->GetNext() == nullptr)
    {
     
      if(curr->GetKey() < key)
      {
       
        m_head->SetNext(node);
      
      }
      else
      {
        m_head = node;
        m_head->SetNext(curr);
      }
    }
    else 
    {

      if(curr->GetKey() > key)
      {
        m_head = node;
        m_head->SetNext(curr);
      }
      else
      {
          while(curr->GetNext() != nullptr and curr->GetKey() < key)
        {
          prev = curr;
          curr = curr -> GetNext();
        }
        //case for inserting at the end of the list
        if(curr->GetNext() == nullptr and curr->GetKey() < key)
        {
          curr->SetNext(node);
        }
        else
        {
          //set the previous node's next to the new node
        prev->SetNext(node);
        //set the new node's next to curr 
        node->SetNext(curr);
        }
        
      }
      
    }
     m_size++;

  }

  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
  template <typename K, typename V>
  void Map<K,V>::Update(const K& key, const V& value)
  {
    Node<K,V> *curr = m_head;
    while(curr != nullptr)
    {
      if(curr->GetKey() == key)
      {
        curr->SetValue(value);        
      }
      curr = curr->GetNext();
    }
  }

  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
  template <typename K, typename V>
  const V& Map<K,V>::ValueAt(const K& key) const
  {
     Node<K,V> *curr = m_head;
    while(curr != nullptr)
    {
      if(curr->GetKey() == key)
      {
         return curr->GetValue();
      }
      else
      {
        curr = curr->GetNext();
      }
    }
    throw out_of_range("No key was found.");
  }

  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
  template <typename K, typename V>
  Node<K,V>* Map<K,V>::At(const K& key) const
  {
    Node<K,V> *curr = m_head;
    //loop through the Hero's inventory
    while(curr != nullptr)
    {
      //if the passed in ingredients are equal to the ingredients required to craft the desired item, return it
      if(curr->GetKey() == key)
      {
        return curr;
      }
      //otherwise, keep looping through the inventory
      else
      {
        curr = curr->GetNext();
      }
    }
    //if you've looped through the entire inventory without finding a ingredient match, then throw out_of_range
    throw out_of_range("Cannot craft ");
  }

  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
  template <typename K, typename V>
  int Map<K,V>::GetSize() const
  {
    return m_size;
  }

  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
  template <typename K, typename V>
  bool Map<K,V>::IsEmpty() const
  {
    return m_size ? false : true;

  }

  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
  template <typename K, typename V>
  void Map<K,V>::Display() const
  {
    Node<K,V> *curr = m_head;
    while(curr != nullptr)
    {
      cout << *curr << endl;
      curr = curr->GetNext();
    }
  }


/*Name: Clear()
goes through the list and deletes all pointers in the linked list
Also sets m_head and m_size to their default values*/
  template <typename K, typename V>
  void Map<K,V>::Clear()
  {
    Node<K,V> *del = m_head;
    Node<K,V> *next = m_head;
    while(del != nullptr)
    {
      next = next->GetNext();
      delete del;
      del = next;
    }
    m_head = nullptr;
    m_size = 0;
  }


