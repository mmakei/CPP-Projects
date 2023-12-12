#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Added to use rand() function

using namespace std;

// Define the PlayGuessingGame() function
int PlayGuessingGame()
{
    int input;
    int actNum;
    int numGuesses = 0;

    actNum = rand() % 91 + 10; // Using rand() from <cstdlib>
    cout << "Guess the number between 10 and 100: ";

    while (true)
    {
        cin >> input;
        numGuesses++;

        if (input < actNum)
        {
            cout << "Too low, guess again: ";
        }
        else if (input > actNum)
        {
            cout << "Too high, guess again: ";
        }
        else
        {
            cout << "You guessed it! The number was " << actNum << endl;
            return numGuesses;
        }
    }
}

class Player
{
public:
    Player(const string& name = "", int guesses = 0) : name(name), guesses(guesses) {}

    const string& getName() const { return name; }
    int getGuesses() const { return guesses; }

    void setName(const string& newName) { name = newName; }
    void setGuesses(int newGuesses) { guesses = newGuesses; }

private:
    string name;
    int guesses;
};

class Leaderboard
{
public:
    Leaderboard(const string& fileName) : fileName(fileName) {}

    void loadPlayers();
    void savePlayers();
    void addPlayer(const Player& player);
    void displayLeaders();

private:
    string fileName;
    Player players[5]; // Array to store the top 5 players
};

void Leaderboard::loadPlayers()
{
    ifstream file(fileName);
    if (file.is_open())
    {
        int index = 0;
        string playerName;  // Temporary variable to store the player's name
        int playerGuesses;

        while (index < 5 && file >> playerName >> playerGuesses)
        {
            players[index].setName(playerName);  // Set the player's name
            players[index].setGuesses(playerGuesses);
            index++;
        }
        file.close();
    }
}



void Leaderboard::savePlayers()
{
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            outFile << players[i].getName() << " " << players[i].getGuesses() << endl;
        }
        outFile.close();
    }
    else
    {
        cerr << "Cannot create the file" << endl;
    }
}

void Leaderboard::addPlayer(const Player& player)
{
    players[4] = player; // Add the new player to the last position

    // Sort the players array manually
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (players[i].getGuesses() > players[j].getGuesses())
            {
                swap(players[i], players[j]);
            }
        }
    }
}

void Leaderboard::displayLeaders()
{
    cout << "Current Leaders:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << players[i].getName() << " took " << players[i].getGuesses() << " guesses" << endl;
    }
}

// Rest of your code remains the same

int main()
{
    Leaderboard leaderboard("leaders.txt");
    leaderboard.loadPlayers();

    char userInput;
    string userName;
    int userGuesses;

    cout << "Welcome! Press 'q' to quit or any key to continue:";
    cin >> userInput;

    while (userInput != 'q')
    {
        cout << "Please enter your name to start:";
        cin >> userName;

        Player user(userName);

        userGuesses = PlayGuessingGame();
        user.setGuesses(userGuesses);

        leaderboard.addPlayer(user); // Add the user to the leaderboard
        leaderboard.displayLeaders(); // Display updated leaderboard

        cout << "Welcome! Press 'q' to quit or any key to continue:";
        cin >> userInput;
    }
}