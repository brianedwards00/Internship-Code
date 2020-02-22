#pragma once
#ifndef NOTEFILER_HPP
#define NOTEFILER_HPP
#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <unordered_map>
class WordFrequency {
public:
  // Default Constructor, more detailed comments in the .cpp file
  WordFrequency(std::istream &iStream = std::cin);
  std::size_t totalWords() const;
  std::size_t numberOfWords() const;
  std::size_t wordCount(const std::string &word) const;
  std::string mostFrequentWord() const;
  std::size_t maxBucketSize() const;

private:
  // Hash Table
  std::unordered_map<std::string, std::size_t> word_count;
};



class Note {

protected:
  std::string title_;
  std::string body_;

public:
  virtual ~Note();
  Note() : Note("Untitled", "") {}
  Note(const std::string &title, const std::string &body)
      : title_(title), body_(body) {}
  std::string title() const { return title_; }
  std::string body() const { return body_; }
  void set_title(const std::string &title) { title_ = title; }
  void set_body(const std::string &body) { body_ = body; }
  virtual void display() const {
    std::cout << "[" << title_ << "]\n";
    std::cout << body_ << "\n\n";
  }
  virtual std::string serialize() const {
    return "[Note]\n" + title_ + "\n" + body_ + "\n";
  }
};
class EncryptedNote : public Note {
private:
  std::string password_;

public:
  ~EncryptedNote() override;
  EncryptedNote(const std::string &title, const std::string &body,
                const std::string &password)
      : Note(title, body), password_(password) {}
  EncryptedNote() : EncryptedNote("Untitled", "", "") {}
  std::string password() const { return password_; }
  void set_password(const std::string &password) { password_ = password; }
  void display() const override;
  std::string serialize() const override {
    return "[EncNote]\n" + title_ + "\n" + body_ + "\n" + password_ + "\n";
  }
};
class Notebook {
private:
  int capacity_;
  int size_;
  Note **notes_;

public:
  Notebook(int capacity)
      : capacity_(capacity), size_(0), notes_(new Note *[capacity]) {}
  Notebook() : capacity_(100), size_(0), notes_(new Note *[100]) {}
  int capacity() const { return capacity_; }
  int size() const { return size_; }
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
#endif
