#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <fstream>
#include <iostream>
using namespace std;

class Blockchain{
public:
  Blockchain();
  virtual ~Blockchain();

  void addBlock(string data);
  void displayBlockchain();
  bool validateBlockchain();
  void saveToFile(string filename);
  void loadFromFile(string filename);

private:
  Block* m_head;
  Block* m_tail;
  int m_size;

  Block* getLastBlock();
};

Blockchain::Blockchain(){
  m_size = 0;
  m_head = NULL;
  m_tail = NULL;

  // create genesis block
  Block* genesisBlock = new Block(0, "Genesis Block", "0");
  m_head = genesisBlock;
  m_tail = genesisBlock;
  m_size = 1;

  cout << "✨✨ Genesis Block Created! ✨✨" << endl;
  cout << "Index: " << genesisBlock->getIndex() << endl;
  cout << "Timestamp: " << genesisBlock->getTimestamp() << endl;
  cout << "Data: " << genesisBlock->getData() << endl;
  cout << "Previous Hash: " << genesisBlock->getPrevHash() << endl;
  cout << "Hash: " << genesisBlock->getHash() << endl;
}

Blockchain::~Blockchain(){
  Block* current = m_head;
  while(current != NULL){
    Block* next = current->m_next;
    delete current;
    current = next;
  }
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
}

Block* Blockchain::getLastBlock(){
  return m_tail;
}

void Blockchain::addBlock(string data){
  Block* prevBlock = getLastBlock();
  Block* newBlock = new Block(m_size, data, prevBlock->getHash());

  m_tail->m_next = newBlock;
  m_tail = newBlock;
  ++m_size;

  cout << "✨✨ New Block Added! ✨✨" << endl;
  cout << "Index: " << newBlock->getIndex() << endl;
  cout << "Timestamp: " << newBlock->getTimestamp() << endl;
  cout << "Data: " << newBlock->getData() << endl;
  cout << "Previous Hash: " << newBlock->getPrevHash() << endl;
  cout << "Hash: " << newBlock->getHash() << endl;
}

void Blockchain::displayBlockchain(){
  cout << "✨✨ Blockchain State ✨✨" << endl;
  Block* current = m_head;
  while(current != NULL){
    cout << "Index: " << current->getIndex() << endl;
    cout << "Timestamp: " << current->getTimestamp() << endl;
    cout << "Data: " << current->getData() << endl;
    cout << "Previous Hash: " << current->getPrevHash() << endl;
    cout << "Hash: " << current->getHash() << endl;
    current = current->m_next;
  }
}

bool Blockchain::validateBlockchain(){
  Block* current = m_head->m_next; // start from second block
  Block* prev = m_head;

  while(current != NULL){
    // check if current hash is valid first
    string calculatedHash = current->calculateHash();
    if(current->getHash() != calculatedHash){
      cout << "Block " << current->getIndex() << " has an invalid current hash!" << endl;
      return false;
    }

    // check if previous hash matches
    if(current->getPrevHash() != prev->getHash()){
      cout << "Block " << current->getIndex() << " has an invalid previous hash!" << endl;
      return false;
    }

    prev = current;
    current = current->m_next;
  }

  return true;
}

void Blockchain::saveToFile(string filename){
  ofstream outFile(filename);

  if(!outFile.is_open()){
    cout << "Error: Could not open file for writing." << endl;
    return;
  }

  Block* current = m_head;
  while(current != NULL){
    outFile << current->getIndex() << "|"
            << current->getTimestamp() << "|"
            << current->getData() << "|"
            << current->getPrevHash() << "|"
            << current->getHash();

    if(current->m_next != NULL){
      outFile << endl;
    }

    current = current->m_next;
  }

  outFile.close();
  cout << "Blockchain saved to file: " << filename << endl;
}

void Blockchain::loadFromFile(string filename){
  ifstream inFile(filename);

  if(!inFile.is_open()){
    cout << "Error: Could not open file for reading." << endl;
    return;
  }

  // clear existing blockchain
  Block* current = m_head;
  while(current != NULL){
    Block* next = current->m_next;
    delete current;
    current = next;
  }
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;

  string line;
  bool firstBlock = true;

  while(getline(inFile, line)){
    // parse the line: index|timestamp|data|prevHash|hash
    stringstream ss(line);
    string indexStr, timestamp, data, prevHash, hash;

    getline(ss, indexStr, '|');
    getline(ss, timestamp, '|');
    getline(ss, data, '|');
    getline(ss, prevHash, '|');
    getline(ss, hash, '|');

    int index = stoi(indexStr);

    // create block with loaded data
    Block* newBlock = new Block(index, data, prevHash);
    newBlock->m_timestamp = timestamp;
    newBlock->setHash(hash);

    if(firstBlock){
      m_head = newBlock;
      m_tail = newBlock;
      firstBlock = false;
    } else{
      m_tail->m_next = newBlock;
      m_tail = newBlock;
    }
    ++m_size;
  }

  inFile.close();
  cout << "✨Blockchain loaded from file: " << filename << endl;
}

#endif