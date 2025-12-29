#include "Blockchain.h"
#include <iostream>
#include <limits>
using namespace std;

void displayMenu(bool firstTime = true){
  if(firstTime){
    cout << "Hello there! Welcome to your Panther Blockchain Ledger! :" << endl;
  } else{
    cout << "✨✨ Menu ✨✨:" << endl;
  }
  cout << "1. Add a New Block" << endl;
  cout << "2. Display the Blockchain" << endl;
  cout << "3. Validate the Blockchain" << endl;
  cout << "4. Save Blockchain to File" << endl;
  cout << "5. Load Blockchain from File" << endl;
  cout << "6. Exit" << endl;
  cout << "Enter your choice: ";
}

int main(){
  Blockchain* blockchain = new Blockchain();
  int choice = 0;
  string input;
  bool firstMenu = true;
  bool hasLoadedFile = false;

  while(choice != 6){
    displayMenu(firstMenu && !hasLoadedFile);
    firstMenu = false;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

    switch(choice){
      case 1: {
        cout << "Enter block data: ";
        getline(cin, input);
        blockchain->addBlock(input);
        break;
      }
      case 2: {
        blockchain->displayBlockchain();
        break;
      }
      case 3: {
        cout << "Performing blockchain validation..." << endl;
        if(blockchain->validateBlockchain()){
          cout << "Result: Blockchain is valid! yay!" << endl;
        } else{
          cout << "Result: Blockchain is invalid!" << endl;
        }
        break;
      }
      case 4: {
        cout << "Enter filename to save the blockchain: ";
        getline(cin, input);
        blockchain->saveToFile(input);
        break;
      }
      case 5: {
        cout << "Enter filename to load the blockchain: ";
        getline(cin, input);
        blockchain->loadFromFile(input);
        hasLoadedFile = true;
        break;
      }
      case 6: {
        cout << "Exiting..." << endl;
        break;
      }
      default: {
        cout << "Invalid choice. Please try again." << endl;
        break;
      }
    }
    cout << endl;
  }

  delete blockchain;
  return 0;
}