#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class TextEditor
{
private:
    string currentText;
    stack<string> undoStack;
    stack<string> redoStack;

public:
    void addText()
    {
        string text;

        cout << "\nEnter Text : ";
        cin.ignore();
        getline(cin, text);

        undoStack.push(currentText);

        while (!redoStack.empty())
        {
            redoStack.pop();
        }

        currentText += text;

        cout << "\nText Added Successfully!\n";
    }
    void displayText()
    {
        if (currentText.empty())
        {
            cout << "\nEditor is Empty!\n";
            return;
        }

        cout << "\n========== CURRENT TEXT ==========\n";
        cout << currentText << endl;
    }
    void clearText()
    {
        if (currentText.empty())
        {
            cout << "\nEditor is already empty!\n";
            return;
        }

        // Save current text for Undo
        undoStack.push(currentText);

        // Clear Redo history
        while (!redoStack.empty())
        {
            redoStack.pop();
        }

        currentText.clear();

        cout << "\nText Cleared Successfully!\n";
    }

    void openFile()
    {
        string fileName;

        cout << "\nEnter file name: ";

        // Clear the previous input
        cin.ignore(10000, '\n');

        getline(cin, fileName);

        // Open the file
        ifstream file(fileName);

        // Check whether file exists
        if (!file)
        {
            cout << "\nFile could not be opened!\n";
            return;
        }

        // Read the complete file
        stringstream buffer;
        buffer << file.rdbuf();

        string newText = buffer.str();

        file.close();

        // Save current text for Undo
        undoStack.push(currentText);

        // Clear Redo history
        while (!redoStack.empty())
        {
            redoStack.pop();
        }

        // Replace current text with file contents
        currentText = newText;

        cout << "\nFile opened successfully!\n";
    }

    void undo()
    {
        if (undoStack.empty())
        {
            cout << "\nNothing to Undo!\n";
            return;
        }

        // Save current text in Redo Stack
        redoStack.push(currentText);

        // Restore previous text
        currentText = undoStack.top();

        // Remove restored state from Undo Stack
        undoStack.pop();

        cout << "\nUndo Successful!\n";
    }

    void wordCharacterCounter(string text)
    {
        int characters = text.length();
        int charactersWithoutSpaces = 0;
        int spaces = 0;
        int lines = 0;
        int words = 0;

        // Count characters, spaces and lines
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ' && text[i] != '\n' && text[i] != '\t')
            {
                charactersWithoutSpaces++;
            }

            if (text[i] == ' ')
            {
                spaces++;
            }

            if (text[i] == '\n')
            {
                lines++;
            }
        }

        // Count words
        stringstream ss(text);
        string word;

        while (ss >> word)
        {
            words++;
        }

        // If text is not empty, count the final line
        if (text.length() > 0)
        {
            lines++;
        }

        // Display results
        cout << "\n===== TEXT STATISTICS =====\n";

        cout << "Total Characters: "
             << characters << endl;

        cout << "Characters Without Spaces: "
             << charactersWithoutSpaces << endl;

        cout << "Total Words: "
             << words << endl;

        cout << "Total Spaces: "
             << spaces << endl;

        cout << "Total Lines: "
             << lines << endl;

        cout << "===========================\n";
    }
    string getText()
    {
        return currentText;
    }

    void redo()
    {
        if (redoStack.empty())
        {
            cout << "\nNothing to Redo!\n";
            return;
        }

        // Save current text for Undo
        undoStack.push(currentText);

        // Restore next state
        currentText = redoStack.top();

        // Remove it from Redo Stack
        redoStack.pop();

        cout << "\nRedo Successful!\n";
    }
};
int main()
{
    TextEditor editor;
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "      UNDO / REDO TEXT EDITOR\n";
        cout << "=====================================\n";
        cout << "1. Add Text\n";
        cout << "2. Display Text\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Clear Text\n";
        cout << "6. Word and Character Counter\n";
        cout << "7. Open File\n";
        cout << "8. Exit\n";
        cout << "=====================================\n";

        cout << "Enter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            editor.addText();
            break;

        case 2:
            editor.displayText();
            break;

        case 3:
            editor.undo();
            break;

        case 4:
            editor.redo();
            break;

        case 5:
            editor.clearText();
            break;
        case 6:
            editor.wordCharacterCounter(editor.getText());
            break;
        case 7:
            editor.openFile();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}