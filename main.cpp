#include <fstream>
#include <iostream>
#include <string>

#include "NoteFiler.hpp"

// Main.cpp displays the menu for this program. Its simplistic design allows for
// easy viewing.
int main() {
  char choice;
  Note *note;
  EncryptedNote *enc_note;
  Notebook notebook;
  std::string filename;
  std::cout << "Welcome to the Text Filer 9000!\nWhere you can do almost "
               "anything related to text files! What do you want to do?\n\n";
  do {
    std::cout << "[C] Create a note\n";
    std::cout << "[N] Create an encrypted note\n";
    std::cout << "[L] List notes\n";
    std::cout << "[V] View note\n";
    std::cout << "[S] Save notes\n";
    std::cout << "[O] Load notes\n";
    std::cout << "[A] Analyze notes\n";
    std::cout << "[E] Exit\n";
    std::cout << "Choice: ";
    std::cin.get(choice);
    std::cin.ignore();
    // Switch statement that redirects a certain input to its corresponding case
    switch (choice) {
    case 'c':
    case 'C':
      note = create_note();
      notebook.add(note);
      break;
    case 'n':
    case 'N':
      enc_note = create_encrypted_note();
      notebook.add(enc_note);
      break;
    case 'l':
    case 'L':
      notebook.list();
      break;
    case 'e':
    case 'E':
      std::cout << "\nThank you for using Text Filer 9000!\n";
      break;
    case 'v':
    case 'V':
      notebook.view();
      break;
    case 's':
    case 'S':
      std::cout << "\nPlease enter filename: ";
      std::getline(std::cin, filename);
      notebook.save(filename);
      break;
    case 'o':
    case 'O': {
      std::cout << "\nPlease enter a filename that YOU have created in this "
                   "program (as it will not load other files): ";
      std::getline(std::cin, filename);
      notebook.load(filename);
      break;
    case 'a':
    case 'A':
      Analyze();
      break;
    }
    default:
      std::cout << "\nInvalid choice. Please try again.\n\n";
    }
  } while (choice != 'e' && choice != 'E');

  return 0;
}
