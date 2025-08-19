#ifndef LINE_H //Header guard
#define LINE_H //Header guard

#include <iostream>
#include <string>
using namespace std;

class Line {
 public:
  // Name - Line() - Default constructor
  // Desc - Creates an empty line (acts as linked list node)
  // Preconditions - None
  // Postconditions - Used to create a new line object with m_next as a nullptr
  Line();
  // Name - Line(string) - Overloaded constructor
  // Desc - Creates a line with the passed value and a nullptr (acts as linked list node)
  // Preconditions - None
  // Postconditions - Used to create a new line object
  Line(string);
  // Name - Getters and Setters
  // Desc - Used to access the private member variables in the line object
  // Preconditions - Object exists
  // Postconditions - Either returns m_text, m_next or sets m_text or m_next
  string GetText(); //Returns text in node
  Line* GetNext(); //Returns next line in document
  void SetText(string text); //Sets text in node
  void SetNext(Line* next); //Sets next line in document
 private:
  string m_text; //Stores the data for an individual line of data
  Line* m_next; //Stores the pointer to the next line (next node)
};

#endif
