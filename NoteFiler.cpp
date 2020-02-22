#include "NoteFiler.hpp"
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

namespace {
std::string cleanse(const std::string &word) {
  constexpr char bad_char[] =
      " \t\n\b\v_-\"'(){}+/*,=.!?:;"; // leading and trailing characters to be
                                      // removed
  static std::locale locality;

  // start with the first non-bad character
  auto startIndex = word.find_first_not_of(bad_char);
  // if the word contains only bad characters ...
  if (startIndex == std::string::npos)
    startIndex = word.size();
  // assume the word contains only bad characters ...
  std::size_t count = 0;
  // end with the first non-bad characte
  auto endIndex = word.find_last_not_of(bad_char);

  if (endIndex != std::string::npos)
    // number of characters to use in results
    count = endIndex - startIndex + 1;

  // strip the leading and trailing bad characters
  auto result = word.substr(startIndex, count);
  // convert to lower case
  for (auto &c : result)
    c = std::tolower(c, locality);

  return result;
}
} // namespace

// This function below is a default contstructor that takes a reference to an
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

// This function compares each bucket size to the biggest size the function is
// currently holding. This value gets replaced if the bucket_size(i) is bigger
// than that value (number).

std::size_t WordFrequency::maxBucketSize() const {
  std::string most_freq;
  std::size_t number = 0;
  int i = 0;
  for (auto it = word_count.begin(); it != word_count.end(); ++it) {
    if (word_count.bucket_size(i) > number) {
      number = word_count.bucket_size(i);
    }
    i++;
  }
  return number;
}

std::size_t WordFrequency::totalWords() const {
  std::size_t total = 0;
  for (auto it = word_count.begin(); it != word_count.end(); ++it) {
    total += it->second;
  }
  return total;
}

void EncryptedNote::display() const {
  std::string password;
  std::cout << "Please enter password to view note: ";
  std::getline(std::cin, password); // Checks password of EncryptedNote
  if (password == password_) {
    Note::display();
  } else {
    std::cout << "Sorry, you do not have the permission to view note.\n\n";
  }
}
EncryptedNote *create_encrypted_note() {
  std::string title, body, password;
  std::cout << "\nPlease enter the note's title: ";
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
  return enc_note; // Makes a pointer object of EncryptedNote
}
Note::~Note() {}
EncryptedNote::~EncryptedNote() {}
Note *create_note() {
  Note *note = new Note;
  std::string title, body;
  std::cout << "\nPlease enter the note's title: ";
  std::getline(std::cin, title);
  (*note).set_title(title);
  std::cout << "Please enter the note: ";
  std::getline(std::cin, body);
  (*note).set_body(body);
  std::cout << "\nNote added!\n\n";
  return note; // Makes a pointer object of Note
}
void Notebook::add(Note *new_note) {
  notes_[size_] = new_note;
  size_++;
}

Note *Notebook::get(int index) const { return notes_[index]; }

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
      notes_[index - 1]->display();
    }
  }
}

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
      Note *temp_note = new Note(line1, line2);

      add(temp_note);
    } else {
      std::getline(load_file, line3);
      EncryptedNote *temp_encnote = new EncryptedNote(line1, line2, line3);
      add(temp_encnote);
    }
  }
  load_file.close();
  std::cout << "Notes loaded!\n\n";
}
