#include "Document.h"
// Name - Document() - Default constructor
// Desc - Creates an empty Document (linked list)
// Preconditions - None
// Postconditions - Sets m_head to nullptr and m_lineCount = 0
Document::Document() : m_head(nullptr), m_lineCount(0) {}
// Name - ~Document() - Destructor
// Desc - Removes all lines from Document (removes all nodes from linked list)
// Preconditions - None
// Postconditions - Removes all lines and sets m_head to nullptr
//                  and m_lineCount = 0
Document::~Document() {
    //Curr will iterate through the linked list (line-getter).
    Line* curr = m_head;
    while (curr != nullptr) {
        //Let m_head be the current line
        m_head = curr; 
        //Iterate curr for m_head to be reset afterwards.
        curr = curr->GetNext();
        //Delete current line
        delete m_head;
    }
    //At the end, set m_head to nullptr and m_lineCount to 0 to indicate an empty list
    m_head = nullptr;
    m_lineCount = 0;
}
// Name - InsertLine(string,int)
// Desc - Inserts a new line (node) into the Document (linked list)
//        Dynamically allocates new line and inserts line in position
//        indicated. Inserts the line **before** the position.
//        For example, if position 1 then inserts a new first line to the Document
// Preconditions - Document exists
// Postconditions - New line inserted into the Document
void Document::InsertLine(string text, int position) {
    //If the list is empty...
    if (m_lineCount < 1) {
        Line* newLine = new Line(text);
        //Let m_head point to first line
        m_head = newLine;
        //Increment line counter
        m_lineCount++;
        //If we want to insert a line as the first line...
    } else if (position == 1) {
        Line* newLine = new Line(text);
        //Let newLine hold the addrress of the line that m_head was already holding.
        newLine->SetNext(m_head);
        //Let m_head point to newLine since that is now the first line.
        m_head = newLine;
        //Increment line counter
        m_lineCount++;
        //If we want to insert a line at the end...
    } else if (position == m_lineCount) {
        //Start a loop that reaches the final line (tail).
        Line* curr = m_head;
        while (curr->GetNext() != nullptr) {
            curr = curr->GetNext();
        }
        //Create new line.
        Line* newNode = new Line(text);
        //Let the final line hold the address to the newly created line.
        curr->SetNext(newNode);
        //Increment line counter
        m_lineCount++;
        //If we are inserting a new line in between...
    } else {
        int i = 0;
        //Double line tracking for proper link-management.
        Line* curr = m_head;
        Line* prev = m_head;
        //curr will always be one ahead of prev
        curr = curr->GetNext();
        //Reach the position
        while (i != position-2) {
            prev = prev->GetNext();
            curr = curr->GetNext();
            i++;
        }
        //Create the new line
        Line* newLine = new Line(text);
        //Let prev hold the address to the newly created line
        prev->SetNext(newLine);
        //Let the newly created line hold the address to curr
        newLine->SetNext(curr);
        //Increment line counter
        m_lineCount++;
    }
}
// Name - DeleteLine(int)
// Desc - Deletes a line from the Document at a provided position
//        Deletes the exact line chosen.
//        Indicates the document is empty if the Document has no lines
// Preconditions - Document exists and line exists
// Postconditions - Line removed from Document
void Document::DeleteLine(int position) {
    //If no lines exist, print a message saying so.
    if (m_lineCount < 1) {
        cout << "Document is empty!" << endl;
        return;
    }
    //If we are deleting the first line...
    if (position == 1) {
        //Let curr point to the first line
        Line* curr = m_head;
        //Let m_head point to the second line.
        m_head = curr->GetNext();
        //Delete curr, which holds the address of the first line.
        delete curr;
        m_lineCount--;
        //If we want to remove the final line.
    } else if (position == m_lineCount) {
        //Double line tracking
        Line* curr = m_head;
        Line* prev = m_head;
        //Curr will be ahead of prev
        curr = curr->GetNext();
        //Traverse until curr reaches the end
        while (curr->GetNext() != nullptr) {
            prev = prev->GetNext();
            curr = curr->GetNext();
        }
        //Delete curr (final line)
        delete curr;
        //let the line before curr (prev) point to nullptr to set the new final line
        prev->SetNext(nullptr);
        //Decrement line counter
        m_lineCount--;
        //If we want to remove a line in between...
    } else {
        int i = 0;
        //Double line tracking 
        Line* curr = m_head;
        Line* prev = m_head;
        //Curr will be ahead of prev
        curr = curr->GetNext();
        //Traverse until we reach the position
        while (i != position-2) {
            prev = prev->GetNext();
            curr = curr->GetNext();
            i++;
        }
        //Let the previous line point to the line that the current line was pointing to.
        prev->SetNext(curr->GetNext());
        //Delete current line
        delete curr;
        //Decrement line counter
        m_lineCount--;
    }
}
// Name - EditLine(int, string)
// Desc - Edits the text in a specific Line at a provided position (line number).
//        Updates the string in a specific Line. Uses the exact line number.
//        Indicates the document is empty if the Document has no Lines
// Preconditions - Document exists and line exists.
// Postconditions - Line text updated at a provided position
void Document::EditLine(int position, string newText) {
    //If the document if empty, there exist no line to edit.
    if (m_lineCount < 1) {
        cout << "Document is empty!" << endl;
        return;
    }
    int i = 0;
    Line* curr = m_head;
    //Reach the position
    while (i != position-1) {
        curr = curr->GetNext();
        i++;
    }
    //Change the text of the line to the new text
    curr->SetText(newText);
}
// Name - DisplayDocument
// Desc - Iterates through the Document and displays all data in Line
//        Indicates the document is empty if the Document has no lines
// Preconditions - Document exists
// Postconditions - Displays all lines in Document
void Document::DisplayDocument() {
    if (m_lineCount < 1) {
        cout << "Document is empty" << endl;
    }
    //Assign current line
    Line* curr = m_head;
    //Initiate traversal
    for (int i = 0; i < m_lineCount; i++) {
        //Print line # alongside line content
        cout << i+1 << ":" << " " << curr->GetText() << endl;
        //Move to the next line
        curr = curr->GetNext();
    }
}
// Name - SearchWord(string)
// Desc - Iterates through the Document and searches for provided text
//        Uses the "find" command in string
//        Returns any complete word or any substring.
//        For example, if you search for 'a' then it will
//           return any line that has an 'a' in any word.
//        Details: https://cplusplus.com/reference/string/string/find/
//        Indicates if string not found
// Preconditions - Document exists
// Postconditions - Indicates line number where found or not
void Document::SearchWord(string word) {
    //If the document is empty, there exist no line to search 'word' in
    if (m_lineCount < 1) {
        cout << "Document is empty!" << endl;
        return;
    }
    bool wordLocated = false;
    //Assign current line
    Line* curr = m_head;
    //Line # tracker
    int i = 1;
    cout << "\n";
    //Initiate traversal
    while (curr != nullptr) {
        long long unsigned wordFound = curr->GetText().find(word);
        //If the index of 'word' within the line is valid
        if (wordFound >= 0 && wordFound <= curr->GetText().length()) {
            //Print message
            cout << "Word found in line " << i << ":" << " " << curr->GetText() << endl;
            wordLocated = true;
        }
        //Move to the next line
        curr = curr->GetNext();
        //Increment line # tracker
        i++;
    }
    //If no word is found, print a message saying so.
    if (!wordLocated) {
        cout << "No word found" << endl;
    }
}
// Name - SaveToFile(string)
// Desc - Iterates through the Document and saves all lines to
//        provided filename
// Preconditions - Document exists
// Postconditions - Writes all lines in Document to file
void Document::SaveToFile(string filename) {
    //If the document is empty, there exist no line to save.
    if (m_lineCount < 1) {
        cout << "No lines found to save." << endl;
        return;
    }
    //Open a file of name 'filename'
    ofstream saveFile(filename);
    //Assign current line;
    Line* curr = m_head;
    //Traverse all lines
    while (curr != nullptr) {
        //Save the content of each line to the file
        saveFile << curr->GetText() << endl;
        //Move to the next line
        curr = curr->GetNext();
    }
    //Close file at the end
    saveFile.close();
}
// Name - LoadFromFile(string)
// Desc - For each line in the input file, inserts one line
//        into the Document
// Preconditions - Document exists
// Postconditions - Writes all from file to Document
void Document::LoadFromFile(string filename) {
    //Open desired file
    ifstream loadFile(filename);
    //Variable to hold extracted content from opened file
    string line;
    //Line # tracker
    int i = GetLineCount() + 1;
    //If the file exists
    if (loadFile) {
        //Extract info from file
        while (getline(loadFile, line)) {
            //Insert the new line at with respect to their position in the file
            InsertLine(line, i);
            //Increment line # tracker
            i++;
        }
        cout << "File loaded successfully!" << endl;
        //If the desired file does not exist, print a message saying so.   
    } else {
        cout << "File does not exist!" << endl;
    }
}
// Name - GetLineCount();
// Desc - Returns m_lineCount
// Preconditions - Document exists
// Postconditions - Returns m_lineCount
int Document::GetLineCount() {
    return m_lineCount;
}
