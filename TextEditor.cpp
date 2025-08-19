#include "TextEditor.h"

// Name - TextEditor - default constructor
// Desc - Set m_fileName to empty
// Preconditions - None
// Postconditions - Set m_fileName to empty. Creates document (m_editor)
TextEditor::TextEditor() : m_fileName("") {}

// Name - MainMenu
// Desc - Displays options:
//        1. Insert Line, 2. Delete Line, 3. Edit Line, 4. Display Document
//        5. Search Word, 6. Save to File, 7. Load from File, 8. Exit
// Preconditions - None
// Postconditions - Returns valid choice (1-8)
int TextEditor::MainMenu() {
    int menuChoice;
    do {
        cout << "\n--- Simple Text Editor ---" << endl;
        cout << "1. Insert Line" << endl;
        cout << "2. Delete Line" << endl;
        cout << "3. Edit Line" << endl;
        cout << "4. Display Document" << endl;
        cout << "5. Search Word" << endl;
        cout << "6. Save to File" << endl;
        cout << "7. Load from File" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> menuChoice;
        //Menu choice validation
    } while (menuChoice < 1 || menuChoice > 8);
    return menuChoice;
}
// Name - GetLineNumber
// Desc - Allows user to choose a specific line number from document.
//        For functions such as DeleteLine and EditLine, the line number must be exact
//            (between 1 and the number of lines in the document)
//        For InsertLine, the line must be between 1 and the number of lines + 1
// Preconditions - Document (m_editor) exists
// Postconditions - Returns line chosen
int TextEditor::GetLineNumber(bool isExact) {
    int choice = 0;
    //If we are dealing with delete line or edit line functionality
    if (isExact) {
        cout << "Enter line number:" << endl;
        cin >> choice;
        //Validate input
        while (choice < 1 || choice > m_editor.GetLineCount()) {
            cout << "\nMust be between 1 and " << m_editor.GetLineCount() << endl;
            //Display all lines
            m_editor.DisplayDocument();
            cout << "Enter line number:" << endl;
            cin >> choice;
        }
        //Otherwise, if we are dealing with insertion functionality
    } else {
        cout << "Enter line number:" << endl;
        cin >> choice;
        //Validate input
        while (choice < 1 || choice > m_editor.GetLineCount() + 1) {
            cout << "\nMust be between 1 and " << m_editor.GetLineCount() + 1 << endl;
            //Dislay all lines
            m_editor.DisplayDocument();
            cout << "Enter line number:" << endl;
            cin >> choice;
        }
    }
    return choice;
}
// Name - GetFileName
// Desc - Prompts user for file name. Stores in m_fileName
// Preconditions - None
// Postconditions - Returns file name entered
string TextEditor::GetFileName() {
    //Variable to store file name
    string filename;
    cout << "Enter the file name:" << endl;
    cin >> filename;
    return filename;
}
// Name - Start
// Desc - Calls MainMenu. Takes menu response and uses switch statement to
//        call corresponding function (display just calls DisplayDocument)
//        Keeps calling until user enters 8 (quit).
// Preconditions - None
// Postconditions - Keeps asking user what to do until they enter 8 (quit).
void TextEditor::Start() {
    int userMenuChoice = 0;
    //While the user doesn't select 'Exit'
    while (userMenuChoice != 8) {
        userMenuChoice = MainMenu();
        //Execute the proper function according to the input
        if (userMenuChoice == 1) {
            InsertLine();
        } else if (userMenuChoice == 2) {
            DeleteLine();
        } else if (userMenuChoice == 3) {
            EditLine();
        } else if (userMenuChoice == 4) {
            cout << "\n**Display Document**" << endl;
            m_editor.DisplayDocument();
        } else if (userMenuChoice == 5) {
            SearchDocument();
        } else if (userMenuChoice == 6) {
            SaveFile();
        } else if (userMenuChoice == 7) {
            LoadFile();
        }
    }
    //If the user decides to exit, print a final message.
    cout << "\nThank you for using the UMBC Text Editor" << endl;
}
// Name - InsertLine
// Desc - Inserts a new line into the document(m_editor). Asks user where to
//        insert the new line by calling GetLineNumber. Inserts the new line before
//        the line chosen.
// Preconditions - None
// Postconditions - Inserts line into document (m_editor).
void TextEditor::InsertLine() {
    cout << "\n**Insert Line**" << endl;
    bool isExact = false;
    
    //If no line exists, then we do not need to get line number from user.
    if (m_editor.GetLineCount() < 1) {
        string text;
        cout << "Enter text: ";
        
        //Clear buffer
        if (cin.peek() == '\n') {
            cin.ignore();
        }
        getline(cin, text);
        m_editor.InsertLine(text, 1);
    //If lines do exist prior to function call...
    } else {
        //Display all lines to help chose where to insert new line
        m_editor.DisplayDocument();
        int line = GetLineNumber(isExact);
        string text;
        cout << "\nEnter text: ";
        //Clear buffer
        if (cin.peek() == '\n') {
            cin.ignore();
        }
        getline(cin, text);
        m_editor.InsertLine(text, line);
    }
}
// Name - DeleteLine
// Desc - Checks to make sure the document(m_editor) has lines. If it does,
//        calls GetLineNumber. Then deletes line from document.
// Preconditions - Document has at least one line.
// Postconditions - Removes line from document (m_editor).
void TextEditor::DeleteLine() {
    //If no lines exist, we cannot delete.
    if (m_editor.GetLineCount() < 1) {
        cout << "No lines exist to delete" << endl;
        return;
    }
    cout << "\n**Delete Line**" << endl;
    //Display all lines 
    m_editor.DisplayDocument();
    bool isExact = true;
    //Get line number to delete
    int line = GetLineNumber(isExact);
    m_editor.DeleteLine(line);
    
}
// Name - EditLine
// Desc - Checks to make sure the document(m_editor) has lines. If it does,
//        calls GetLineNumber. Updates the text in the chosen line.
// Preconditions - Document has at least one line.
// Postconditions - Updates line from document (m_editor).
void TextEditor::EditLine() {
    //If no lines exist, we cannot use the edit function
    if (m_editor.GetLineCount() < 1) {
        cout << "No lines found" << endl;
        return;
    }
    cout << "\n**Edit Line**" << endl;
    //Display all lines
    m_editor.DisplayDocument();
    bool isExact = true;
    //Get line number to edit
    int line = GetLineNumber(isExact);
    
    string newText;
    //Ask for new text to replace old text at the specified line.
    cout << "\nEnter new text: ";
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    //Clear buffer
    getline(cin, newText);
    m_editor.EditLine(line, newText);
}
// Name - SearchDocument
// Desc - Checks to make sure the document(m_editor) has lines. If it does,
//        asks user which text to search for. Displays all lines that have
//        the matching text.
// Preconditions - Document has at least one line.
// Postconditions - Displays line from document (m_editor).
void TextEditor::SearchDocument() {
    //If no lines exist, there is no point of searching for a word.
    if (m_editor.GetLineCount() < 1) {
        cout << "No lines exist to perform search" << endl;
        return;
    }
    cout << "\n**Search Document**" << endl;
    
    string word;
    //Ask for word to search
    cout << "Enter a word to search:" << endl;
    //Clear buffer
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, word);
    m_editor.SearchWord(word);
}
// Name - LoadFile
// Desc - Asks user for the file name. Opens file. Inserts lines from file
//        into existing document (m_editor). Appends document (m_editor).
// Preconditions - None
// Postconditions - Inserts text from file into document (m_editor).
void TextEditor::LoadFile() {
    cout << "\n**Load File**" << endl;
    string filename;
    //Retrieve file name
    cout << "Enter file name:" << endl;
    //Clear buffer
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, filename);
    //Load file
    m_editor.LoadFromFile(filename);
}
// Name - SaveFile
// Desc - Asks user for the file name. Opens file. Writes out all lines from
//        document (m_editor) to the file.
// Preconditions - None
// Postconditions - Inserts text from document (m_editor) into file.
void TextEditor::SaveFile() {
    cout << "\n**Save File**" << endl;
    string filename;
    //Get file name
    cout << "Enter file name:" << endl;
    //Clear buffer
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, filename);
    //Save lines to desired file
    m_editor.SaveToFile(filename);
    //Print message upon completion
    cout << "File saved successfully!" << endl;
}
