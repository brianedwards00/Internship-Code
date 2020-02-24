#include "NoteFiler.hpp"
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

// This function dynamically allocates a note and returns the pointer to it
Note *create_note() {
  // Makes a pointer object of Note
  Note *note = new Note;
  std::string title, body;
  std::cout << "\nPlease enter the note's title: ";
  std::getline(std::cin, title);
  (*note).set_title(title);
  std::cout << "Please enter the note: ";
  std::getline(std::cin, body);
  (*note).set_body(body);
  std::cout << "\nNote added!\n\n";
  return note;
}

// Note Destructor
Note::~Note() {}

// This function asks the user for the password of the encrypted note they are
// trying to access.
void EncryptedNote::display() const {
  std::string password;
  std::cout << "Please enter password to view note: ";
  std::getline(std::cin, password);
  // Checks password of EncryptedNote
  if (password == password_) {
    Note::display();
  } else {
    std::cout << "Sorry, you do not have the permission to view note.\n\n";
  }
}

// This function dynamically allocates an encrypted note and returns the pointer
// to it
EncryptedNote *create_encrypted_note() {
  std::string title, body, password;
  std::cout << "\nPlease enter the note's title: ";
  // Makes a pointer object of EncryptedNote
  EncryptedNote *enc_note = new EncryptedNote;
  std::getline(std::cin, title);
  enc_note->set_title(title);
  std::cout << "Please enter the note: ";
  std::getline(std::cin, body);
  enc_note->set_body(body);
  std::cout << "Please enter the password: ";
  std::getline(std::cin, password);
  enc_note->set_password(password);
  std::cout << "\nEncrypted Note added!\n\n";
  return enc_note;
}

// Encrypted Note Destructor
EncryptedNote::~EncryptedNote() {}

// This function adds a pointer to a note to its corresponding index in the
// notebook, based on the size of the notebook beforehand
void Notebook::add(Note *new_note) {
  notes_[size_] = new_note;
  size_++;
}

// This function simply retrieves a pointer to a note based on the index in the
// parameter
Note *Notebook::get(int index) const { return notes_[index]; }

// This function looks at the size of the notebook, then determines what to list
// out. If notes do exist, it loops to fetch each title in every notebook
// index to print out
void Notebook::list() const {
  if (size_ == 0) {
    std::cout << "\nNo notes have been added.\n\n";
  } else {
    std::cout << "\nNotes\n";
    for (int j = 0; j < size_; j++) {
      std::cout << j + 1 << ". " << notes_[j]->title() << "\n";
    }
    std::cout << "\n";
  }
}

// This function will call the previous function to list the notes out, but now,
// the user will be asked to input a note index. When the user does, it will
// show that input's note description
void Notebook::view() const {
  int index = 0;
  list();
  if (size_ > 0) {
    std::cout << "Please input note index: ";
    std::cin >> index;
    std::cin.ignore();
    if (index - 1 >= size_) {
      std::cout << "\nInvalid note index.\n\n";
    } else {
      std::cout << "\n";
      // Displays note based on what type of note it is (a normal or encrypted
      // one)
      notes_[index - 1]->display();
    }
  }
}

// This function will create a text file in the same location of the project and
// will write all the notes into one file
void Notebook::save(const std::string &filename) const {
  std::ofstream save_file;
  save_file.open(filename);
  save_file << size_ << "\n";
  for (int i = 0; i < size_; i++) {
    save_file << notes_[i]->serialize();
  }
  save_file.close();
  std::cout << "Notes saved!\n\n";
}

// This function will retrieve the text file of whatever the user inputted
// It will use the the number of notes (size) to create a loop that adds the
// notes to the program
void Notebook::load(const std::string &filename) {
  std::ifstream load_file;
  int size = 0;
  load_file.open(filename);
  load_file >> size;
  std::string line1, line2, line3, type, nothing;
  std::getline(load_file, nothing);
  for (int i = 0; i < size; i++) {
    std::getline(load_file, type);
    std::getline(load_file, line1);
    std::getline(load_file, line2);
    if (type == "[Note]") {
      // Dynamically allocates a note based on what was inputted in the text
      // file
      Note *temp_note = new Note(line1, line2);
      add(temp_note);
    } else {
      std::getline(load_file, line3);
      EncryptedNote *temp_encnote = new EncryptedNote(line1, line2, line3);
      add(temp_encnote);
    }
  }
  load_file.close();
  std::cout << "\nNotes loaded(if any).\n\n";
}

// The functions below describe the ANALYZING portion of the program
void Analyze() {
  std::string file_to_analyze;
  int option = 0;
  bool exit1 = false;
  bool exit2 = false;
  std::string word;
  // This do-while will loop until the user inputs a valid file name that opens
  do {
    exit1 = true;
    std::cout << "\nWhat text file would you like to analyze? (Can be "
                 "ANY)\nHowever,make "
                 "sure "
                 "the appropriate text file is in this program's folder.\n"
                 "Additionally, make sure to copy "
                 "the file name word for word as shown, including capital "
                 "letters and a "
                 ".txt at the end. Or simply type \"Exit\" \n";
    std::getline(std::cin, file_to_analyze);
    if (file_to_analyze == "Exit" || file_to_analyze == "exit") {
      return;
    }
    std::ifstream fin(file_to_analyze);
    if (!fin.is_open()) {
      std::cout << "\n\nEither you think you can fool me or you made a silly "
                   "spelling mistake. Please try again.\n\n\n";
      exit1 = false;
    }
  } while (exit1 != true);

  std::ifstream fin(file_to_analyze);
  WordFrequency file(fin);
  std::cout << "\nUpload to hash table complete.\n\n";
  // Will loop until case 5 is activated
  while (exit2 != true) {
    std::cout
        << "What would you like to "
           "learn about your file?\n[1]The total word count?\n[2]The total "
           "number of unique words?\n[3]The "
           "word count of your choice?\n[4]The most frequent word in the "
           "file?\n[5]Exit\n";
    std::cin >> option;
    std::cout << "\n\n";
    // This will loop until the user puts in a valid number between 1-5
    while (std::cin.fail()) {
      std::cout
          << "I can not be fooled that easily. Be select a valid NUMBER: ";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cin >> option;
      std::cout << "\n\n";
    }
    switch (option) {
    case 1:
      std::cout << "The total word count is " << file.totalWords() << ".\n\n\n";
      break;
    case 2:
      std::cout << "The total number of unique words are "
                << file.numberOfWords()
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
      exit2 = true;
      break;

    default:
      std::cout << "Nice try, no bugs exist here. Please try again.\n\n\n";
    }
  }
  std::cin.ignore();
}

// This function below is NOT MY CODE! My code came from my assignments,
// from which my professor had to initialize a few things in the beginning, but
// I can guarantee that everything else on this project is 100% ME!
namespace {
std::string cleanse(const std::string &word) {
  constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";
  static std::locale locality;
  auto startIndex = word.find_first_not_of(bad_char);
  if (startIndex == std::string::npos)
    startIndex = word.size();
  std::size_t count = 0;
  auto endIndex = word.find_last_not_of(bad_char);
  if (endIndex != std::string::npos)
    count = endIndex - startIndex + 1;
  auto result = word.substr(startIndex, count);
  for (auto &c : result)
    c = std::tolower(c, locality);
  return result;
}
} // namespace

// This function above is NOT MY CODE! My code came from my assignments,
// from which my professor had to initialize a few things in the beginning, but
// I can guarantee that everything else on this project is 100% ME!

// This function below is a default constructor that takes a reference to an
// input stream as a parameter. One by one, each word is read until the end of
// the file. Everytime it comes across a word, it 'cleanse' it to take out the
// unnecessary chars such as () or {}. After that, it will check if that word is
// already in the has table. If the word is not in the table, it will add itself
// to the table as the key and the initialize the frequency as the value. If the
// word is in the table, it will increment the frequency by one to keep tally.
WordFrequency::WordFrequency(std::istream &iStream) {
  std::string word, san_word;
  while (iStream >> word) {
    san_word = cleanse(word);
    auto it = word_count.find(san_word);
    if (it != word_count.end()) {
      it->second++;
    } else {
      word_count[san_word] = 1;
    }
  }
}

// Goes through the whole map to calculate the number of words by incrementing
// the total by 1 if the bucket is not empty.
std::size_t WordFrequency::numberOfWords() const {
  std::size_t total = 0;
  for (auto it = word_count.begin(); it != word_count.end(); ++it) {
    if (it->second > 0) {
      total++;
    }
  }
  return total;
}

// After sanitizing the word, the search is then started to check if the word is
// in the map and by getting its count if it exists.
std::size_t WordFrequency::wordCount(const std::string &word) const {
  std::string san_word;
  san_word = cleanse(word);
  if (word_count.find(san_word) != word_count.end()) {
    std::size_t the_count = word_count.at(san_word);
    return the_count;
  } else {
    return 0;
  }
}

// This function checks each value and compares it to the biggest value it
// currently has and replaces that value if it is bigger. At the end, it returns
// the word that comes with the largest value.

std::string WordFrequency::mostFrequentWord() const {
  std::string most_freq;
  std::size_t number = 0;
  for (auto it = word_count.begin(); it != word_count.end(); ++it) {
    if (it->second > number) {
      number = it->second;
      most_freq = it->first;
    }
  }
  if (number == 0) {
    return "none. The file is empty";
  }
  return most_freq;
}

// This function will loop through the whole hash table, counting the values
// that each key holds and adding it to the total.
std::size_t WordFrequency::totalWords() const {
  std::size_t total = 0;
  for (auto it = word_count.begin(); it != word_count.end(); ++it) {
    total += it->second;
  }
  return total;
}
