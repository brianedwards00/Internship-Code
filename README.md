# Welcome to Project __Text Filer 9000!__
### The Basics

This project will revolve around the use of text files. My project can accomplish the following:
- Create a Note
- Create an Encrypted Note
- List all of the Notes
- View a specific Note
- Save all the Notes into one text file that will be created
- Load a text file with all the Notes to the current running program (__Note:__ This program will only load text files __if__ they have the same Note format that my project creates. It will not load anything if that is not the case.)
- Analyze Notes - This option will lead to more options which are:
 - Upload a Note to the current running program (__Note:__ On the other hand, this can take __ANY__ text file, whether it was created by this program or not. I have included a text file of this nature in GitHub. Make sure it is in the same folder as the code.)
 - Display the total word count of the text file
 - Display the total number of _unique_ words
 - Display the word count of a word of your choice

 - Displays the most frequent word


 I have provided comments throughout all of my code with more details.

### Running the Project
#### Linux

It would be most beneficial to put __all__ of the files from GitHub into a new empty folder.

After doing so, we will now compile the code! So now, open your terminal in a Linux environment and type in

`cd <Folder Name>` to go into the folder with the code.

After that, you will type

`g++ main.cpp NoteFiler.cpp` to compile

After doing so, simply type in

`./a.out` to execute!

And you're in! Read each instruction carefully!

#### Windows
We will now open Visual Studio and "Create a New Empty Project"

After, add 2 "New C++ (.cpp) Files", 1 "New Header (.hpp) File", and any number of "Text Files (.txt)" with the __same__ names as presented in GitHub and then, copy the code into the corresponding files.

Run the code!

### Tools/Libraries/Packages
- __Tools:__ Atom on a Linux Environment
- __Libraries (Standard C++):__
 - iostream
 - string
 - fstream
 - istream
 - locale
 - unordered_map
 - cstddef
- __Packages:__
 - Namespace
 - Std

### Reason
This project is created out of two separate coding assignments that I combined together (the Note Menu and the Analyzer Menu). This project came into being because I wanted to challenge my coding skills by cleaning up some of my past code that needed some improvements. I soon realized I could combine the common theme of the Note Menu and the Analyzer Menu into one project.

### What I've Learned
This project gave me more knowledge in the areas of:
 - Defining Functions
 - Pointers and References
 - Writing and Reading Files
 - Implementation
 - Preventing code from crashing from various user inputs
 - Objects
 - Inheritance
 - Polymorphism
 - Data Structures (Hash Table and Arrays used in this project)



### Duration of Project
The Note Menu was a semester long project where we created/edited more code every milestone into the final product. The Analyzer Menu was a 2 week assignment. Combing/Fixing the two programs took about 12 more hours.

---
### Notice
There is __ONE__ function that comes from my professor (line 238 in NoteFiler.cpp). My code came from my assignments, from which my professor had to initialize a few things in the beginning, but I can guarantee that everything else on this project is 100% ME.
