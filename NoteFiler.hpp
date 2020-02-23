#pragma once
#ifndef NOTEFILER_HPP
#define NOTEFILER_HPP
#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <unordered_map>

class Note {

  // Protected variables so only the derived class of encrypted note can access
  // these
protected:
  std::string title_;
  std::string body_;

public:
  // Destructor
  virtual ~Note();
  // Default Constructor
  Note() : Note("Untitled", "") {}
  // Constructor
  Note(const std::string &title, const std::string &body)
      : title_(title), body_(body) {}
  // Accessors and Mutators
  std::string title() const { return title_; }
  std::string body() const { return body_; }
  void set_title(const std::string &title) { title_ = title; }
  void set_body(const std::string &body) { body_ = body; }

  // Basic display method of notes
  // It is a virtual function because encrypted note display() can override this
  // display() function, AKA polymorphism
  virtual void display() const {
    std::cout << "[" << title_ << "]\n";
    std::cout << body_ << "\n\n";
  }

  // This function turns the note into a certain standard that will be inserted
  // into a text file
  virtual std::string serialize() const {
    return "[Note]\n" + title_ + "\n" + body_ + "\n";
  }
};

class EncryptedNote : public Note {
private:
  std::string password_;

public:
  // Destructor
  ~EncryptedNote() override;
  // Constructor
  EncryptedNote(const std::string &title, const std::string &body,
                const std::string &password)
      : Note(title, body), password_(password) {}
  // Default Constructor
  EncryptedNote() : EncryptedNote("Untitled", "", "") {}
  // Accessors and Mutators
  std::string password() const { return password_; }
  void set_password(const std::string &password) { password_ = password; }
  // This display function can override the note display()
  void display() const override;
  std::string serialize() const override {
    return "[EncNote]\n" + title_ + "\n" + body_ + "\n" + password_ + "\n";
  }
};

class Notebook {
private:
  int capacity_;
  int size_;
  // Pointer to pointer note array objects
  Note **notes_;

public:
  // Constructor
  Notebook(int capacity)
      : capacity_(capacity), size_(0), notes_(new Note *[capacity]) {}
  // Default Constructor
  Notebook() : capacity_(100), size_(0), notes_(new Note *[100]) {}
  // Accessors
  int capacity() const { return capacity_; }
  int size() const { return size_; }
  // Destructor that deletes the note pointers and sets the note objects
  // they were pointing to to nullptr
  ~Notebook() {
    delete[] notes_;
    notes_ = nullptr;
  }

  void add(Note *new_note);
  Note *get(int index) const;
  void list() const;
  void view() const;
  void save(const std::string &filename) const;
  void load(const std::string &filename);
};
Note *create_note();
EncryptedNote *create_encrypted_note();

// Everything below relates to the ANALYZING portion of the project (case 'A/a')
class WordFrequency {
public:
  // Constructor, more detailed comments in the .cpp file
  WordFrequency(std::istream &iStream = std::cin);
  std::size_t totalWords() const;
  std::size_t numberOfWords() const;
  std::size_t wordCount(const std::string &word) const;
  std::string mostFrequentWord() const;

private:
  // Hash Table
  std::unordered_map<std::string, std::size_t> word_count;
};
void Analyze();
#endif
