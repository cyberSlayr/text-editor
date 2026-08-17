#include <iostream>
#include <stack>
#include <string>

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
        cout << "6. Exit\n";
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
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}