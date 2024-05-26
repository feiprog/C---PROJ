#include <iostream>
#include <windows.h>
#include <conio.h>  // for _getch()

using namespace std;

// Define color codes
#define RED     12
#define BLUE    9
#define GREEN   10
#define YELLOW  14
#define CYAN    11
#define MAGENTA 13
#define RESET   7

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void PrintColoredText() {
    // Set color and print the text
    SetColor(RED);
    cout << "   ('-.  ) (`-.       _ (`-.                       _ .-') _               .-') _                 .-. .-')          .-') _   .-') _     ('-.       .-') _  \n";
    cout << " _(  OO)  ( OO ).    ( (OO  )                     ( (  OO) )             ( OO ) )                \\  ( OO )        (  OO) ) (  OO) )  _(  OO)     ( OO ) ) \n";
    
    SetColor(BLUE);
    cout << "(,------.(_/.  \\_)-._.`     \\ ,--.     .-'),-----. \\     .'_  ,-.-') ,--./ ,--,' ,----.          ,--. ,--. ,-.-') /     '._/     '._(,------.,--./ ,--,'  \n";
    cout << " |  .---' \\  `.'  /(__...--'' |  |.-')( OO'  .-.  ',`'--..._) |  |OO)|   \\ |  |\\'  .-./-')       |  .'   / |  |OO)|'--...__)'--...__)|  .---'|   \\ |  |\\  \n";
    
    SetColor(GREEN);
    cout << " |  |      \\     /\\ |  /  | | |  | OO )   |  | |  ||  |  \\  ' |  |  \\|    \\|  | )  |_( O- )      |      /, |  |  \\'--.  .--'--.  .--'|  |    |    \\|  | ) \n";
    
    SetColor(YELLOW);
    cout << " |  '--.    \\   \\ | |  |_.' | |  |`-' \\_) |  |\\|  ||  |   ' | |  |(_/|  .     |/|  | .--, \\      |     ' _)|  |(_/   |  |     |  |  (|  '--. |  .     |/  \n";
    
    SetColor(CYAN);
    cout << " |  .--'   .'    \\_)|  .___.'(|  '---.' \\ |  | |  ||  |   / :,|  |_.'|  |\\    |(|  | '. (_/      |  .   \\ ,|  |_.'   |  |     |  |   |  .--' |  |\\    |   \n";
    
    SetColor(MAGENTA);
    cout << " |  `---. /  .'.  \\ |  |      |      |   `'  '-'  '|  '--'  (_|  |   |  | \\   | |  '--'  |       |  |\\   (_|  |      |  |     |  |   |  `---.|  | \\   |   \n";
    cout << " `------''--'   '--'`--'      `------'     `-----' `-------'  `--'   `--'  `--'  `------'        `--' '--' `--'      `--'     `--'   `------'`--'  `--'   \n";
    
    SetColor(RESET);
    cout << "\n";
}

int main() {
    // Clear the console screen
    system("cls");

    // Prompt the user to press any key to continue
    cout << "Press any key to see the colored text..." << endl;
    _getch();  // Wait for a key press

    // Clear the screen again
    system("cls");

    // Print the colored text
    PrintColoredText();

    return 0;
}
