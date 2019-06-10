

#include <iostream>
#include <functional>
#include <cstddef>

//header
template<class K>
class node
/***
node on a linked list for a dictionary
***/
{
public:
  node<K>* next;
  K data;
  node(K);
  ~node();
  friend std::ostream& operator << (std::ostream& os, const node& nd)
  {
    os << nd.data;
    return os;
  };
};

template<class K>
class entry
{
  node<K>* root;
  node<K>** current;
public:
  entry();
  ~entry();
  void addNode(K);
  void removeNode(K);
  bool hasKey(K);
  node<K>* currentNode();
  void nextNode();
  void restart();
  friend std::ostream& operator << (std::ostream& os, const entry<K>& en)
  {
    if(!en.root)
    {
      return os;
    }
    //________else
    node<K>* x = en.root;
    while(x->next)
    {
      os << *x<<", ";
      x=x->next;
    }
    os <<*x;
    return os;
  };

};

template<class K>
class hashSet
{
  entry<K>* entries;
  int numEntries;
  int card;
  void _add(K);
  int redundancy();
  void resize(int);
  std::size_t hash(K);
public:
  hashSet();
  ~hashSet();
  void add(K);
  void remove(K);
  bool hasKey(K);
  int size();
  friend std::ostream& operator << (std::ostream& os, const hashSet<K>& ht)
  {
    int first = 0;
    while (!ht.entries[first].currentNode())
    {
      first++;
    }
    os<<"{"<<ht.entries[first];
    for (int i=first+1;i<ht.numEntries;i++)
    {
      if (ht.entries[i].currentNode())
      {
        os<<", "<<ht.entries[i];
      }
    }
    os<<"}";
  };
};

//end header

//begin implementation


// node methods

template<class K>
node<K>::node(K key)
{
  data=key;
  next=nullptr;
}

template<class K>
node<K>::~node()
{
  if (next)
  {
    delete next;
  }
}
// end node methods


// entry methods
template<class K>
entry<K>::entry()
{
  root = nullptr;
  current=&root;
}
template<class K>
entry<K>::~entry()
{
  if (root)
  {
    delete root;
  }
}

template<class K>
void entry<K>::addNode(K key)
{
  if (!root)
  {
    root = new node<K>(key);
    return;
  }
  //__________

  node<K>* x = root;
  while (x->data != key)
  {
    if (x->next)
    {
      x=x->next;
    }
    else
    {
      x->next = new node<K>(key);
      return;
    }
  }
}

template<class K>
void entry<K>::removeNode(K key)
{
  if (!root){return;} //if there's no root, then there is no data here and you can't delete the key
  //______________________

  if (root->data==key) //if the root has the key, delete the root and rearrange
  {
    node<K>* old = root;
    root = root->next;
    old->next=nullptr;
    delete old;
    return;
  }
  //______________________

  // if the root doesn't have the data, we need to search through the children
  node<K>* x = root;
  while(x->next)
  {
    if (x->next->data == key)
    {
      node<K>* old = x->next;
      x->next = x->next->next;
      old->next=nullptr;
      delete old;
      return;
    }
    x=x->next;
  }
}

template<class K>
bool entry<K>::hasKey(K key)
{
  node<K>* x = root;
  while (x)
  {
    if (x->data==key){return true;}
    x=x->next;
  }
  return false;
}

template<class K>
node<K>* entry<K>::currentNode()
{
  return *current;
}

template<class K>
void entry<K>::nextNode()
{
  current=&((*current)->next);
}

template<class K>
void entry<K>::restart()
{
  current = &root;
}


//end entry



//begin hashSet

template<class K>
hashSet<K>::hashSet()
{
  numEntries=10;
  card=0;
  entries= new entry<K>[numEntries];
}

template<class K>
hashSet<K>::~hashSet()
{
  delete[] entries;
}

template<class K>
std::size_t hashSet<K>::hash(K key)
{
  return (std::hash<K>{}(key))%numEntries;
}

template<class K>
void hashSet<K>::_add(K key)
{
  std::size_t address = hash(key);
  entries[address].addNode(key);
  card++;
}

template<class K>
void hashSet<K>::add(K key)
{
  //std::cout<<redundancy()<<std::endl;
  if (redundancy()>3)
  {
    resize(card+1);
  }
  _add(key);
}

template<class K>
void hashSet<K>::remove(K key)
{
  std::size_t address = hash(key);
  entries[address].removeNode(key);
  card--;
}

template<class K>
bool hashSet<K>::hasKey(K key)
{
  std::size_t address = hash(key);
  return entries[address].hasKey(key);
}

template<class K>
int hashSet<K>::redundancy()
{
  return card/numEntries;
}

template<class K>
void hashSet<K>::resize(int newSize)
{
  entry<K>* oldEntries = entries;
  int oldNumEntries = numEntries;

  numEntries = newSize;
  entries = new entry<K>[numEntries];

  for (int i=0;i<oldNumEntries;i++)
  {
    while(oldEntries[i].currentNode())
    {
      add(oldEntries[i].currentNode()->data);
      oldEntries[i].nextNode();
    }
  }
  delete[] oldEntries;

}


template<class K>
int hashSet<K>::size()
{
  return card;
}






//end hashSet
