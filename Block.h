#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

class Block{
public:
  Block(int index, string data, string prevHash);
  virtual ~Block();

  int getIndex();
  string getTimestamp();
  string getData();
  string getPrevHash();
  string getHash();

  void setData(string data);
  void setHash(string hash);

  string calculateHash();
  string intToHexStream(unsigned int num);

  friend class Blockchain;

private:
  int m_index;
  string m_timestamp;
  string m_data;
  string m_prevHash;
  string m_hash;

  Block* m_next;

  string generateTimestamp();
};

Block::Block(int index, string data, string prevHash){
  m_index = index;
  m_data = data;
  m_prevHash = prevHash;
  m_timestamp = generateTimestamp();
  m_hash = calculateHash();
  m_next = NULL;
}

Block::~Block(){
  m_next = NULL;
}

int Block::getIndex(){
  return m_index;
}

string Block::getTimestamp(){
  return m_timestamp;
}

string Block::getData(){
  return m_data;
}

string Block::getPrevHash(){
  return m_prevHash;
}

string Block::getHash(){
  return m_hash;
}

void Block::setData(string data){
  m_data = data;
}

void Block::setHash(string hash){
  m_hash = hash;
}

string Block::generateTimestamp(){
  time_t now = time(0);
  string timestamp = ctime(&now);
  // remove the newline character at the end
  if(!timestamp.empty() && timestamp[timestamp.length()-1] == '\n'){
    timestamp.erase(timestamp.length()-1);
  }
  return timestamp;
}

string Block::intToHexStream(unsigned int num){
  stringstream ss;
  ss << hex << num;
  return ss.str();
}

string Block::calculateHash(){
  stringstream ss;
  ss << m_index << m_timestamp << m_data << m_prevHash;
  string combined = ss.str();

  // sum ASCII values
  unsigned int sum = 0;
  for(int i = 0; i < combined.length(); ++i){
    sum += (unsigned int)combined[i];
  }

  // convert to hexadecimal
  return intToHexStream(sum);
}

#endif