# Text Editor  

A console-based text editor implemented in modern C++.  
It utilizes linked list data structures to efficiently manage and manipulate text.  
The editor provides core functionality including inserting, deleting, and editing lines, keyword search, and file persistence through saving and loading documents.  

---

## ✨ Features
- Insert new lines at specific positions  
- Delete existing lines  
- Edit lines in place  
- Search for words within the document  
- Display the document contents  
- Save and load documents from text files  

---

## 📂 Project Structure
```
TextEditor/
├── proj3.cpp          # Entry point of the program
├── Document.h         # Defines the Document class
├── Document.cpp       # Implements Document methods
├── Line.h             # Defines the Line (linked list node) class
├── Line.cpp           # Implements Line methods
├── TextEditor.h       # Defines the TextEditor class
├── TextEditor.cpp     # Implements the editor logic
└── README.md          # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++, clang++, MSVC, etc.)

### Compilation
Run the following command to build:
```bash
g++ proj3.cpp Document.cpp Line.cpp TextEditor.cpp -o text_editor
```

### Running
After compilation:
```bash
./text_editor
```

---

## 🎮 Usage
When you run the program, you’ll see a menu like this:
```
1. Insert Line
2. Delete Line
3. Edit Line
4. Display Document
5. Search Word
6. Save to File
7. Load from File
8. Exit
```

Choose an option by entering its number. For example, selecting **1** lets you insert a new line into the document.

---

## 📖 Example
```text
Enter choice: 1
Enter line number: 1
Enter text: Hello World!

Enter choice: 4
Document contents:
1: Hello World!
```

---

## 📜 License
This project is open source under the MIT License.

---

## 📬 Contact
Created by Ali Amir — feel free to reach out if you have questions or feedback.  
- GitHub: [TheAliAmir28](https://github.com/TheAliAmir28)  
- Email: codepirate2028@gmail.com
