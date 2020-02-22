#include <fstream>
#include <iostream>
#include <string>

#include "NoteFiler.hpp"

int main() {
  char choice;
  Note *note;
  EncryptedNote *enc_note;
  Notebook notebook;
  std::string filename;
  std::cout << "Welcome to the Text Filer 9000!\nWhere you can do almost "
               "anything related to text files!\n\n";
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
      std::string file_to_analyze;
      int option = 0;
      bool exit1 = false;
      bool exit2 = false;
      std::string word;
      do {
        exit1 = true;
        std::cout
            << "What text file would you like to analyze? (Can be "
               "ANY)\nHowever,make "
               "sure "
               "the appropriate text file is in this program's folder.\n"
               "Additionally, make sure to copy "
               "the file name word for word, including capital letters and a "
               ".txt at the end:\n";
        std::getline(std::cin, file_to_analyze);
        std::ifstream fin(file_to_analyze);

        if (!fin.is_open()) {
          std::cout
              << "\n\nEither you think you can fool me or you made a silly "
                 "spelling mistake. Please try again.\n\n\n";
          exit1 = false;
        }
      } while (exit1 != true);
      std::ifstream fin(file_to_analyze);
      WordFrequency file(fin);
      std::cout << "\nUpload to hash table complete.\n\n";
      while (exit2 != true) {
        std::cout
            << "What would you like to "
               "learn about your file?\n[1]The total word count?\n[2]The total "
               "number of unique words?\n[3]The "
               "word count of your choice?\n[4]The most frequent word in the "
               "file?\n[5]The size of the largest bucket?\n[6]Exit\n";
        std::cin >> option;
        std::cout << "\n\n";
        while (std::cin.fail()) {
          std::cout
              << "I can not be fooled that easily. Be select a valid NUMBER: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin >> option;
          std::cout << "\n\n";
        }
        switch (option) {
        case 1:
          std::cout << "The total word count is " << file.totalWords()
                    << ".\n\n\n";
          break;
        case 2:
          std::cout
              << "The total number of unique words are " << file.numberOfWords()
              << ".\nAlso, don't bother checking, I'm always right.\n\n\n";
          break;

        case 3:
          std::cout << "What word do you choose?\n";
          std::cin >> word;
          std::cout << "This word has appeared " << file.wordCount(word)
                    << " times. No more, no less.\n\n\n";
          break;

        case 4:
          std::cout << "The most frequent word is \"" << file.mostFrequentWord()
                    << "\".\nI know, I know, I'm impeccable.\n\n\n";
          break;

        case 5:
          std::cout << "The size of the largest bucket of the hash table is "
                    << file.maxBucketSize() << ".\n\n\n";
          break;

        case 6:
          exit2 = true;
          std::cout << "Thank You for using this program!\n\n";
          break;

        default:
          std::cout << "Nice try, no bugs exist here. Please try again.\n\n\n";
        }
      }
      std::cin.ignore();
      break;
    }
    default:
      std::cout << "\nInvalid choice. Please try again.\n\n";
    }
  } while (choice != 'e' && choice != 'E');

  return 0;
}
