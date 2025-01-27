#include <iostream>  // Including input-output stream library
#include <cstdlib>   // Including standard library for miscellaneous functions
#include <ctime>     // Including C time library for time functions
#include <cstring>   // Including C string library for string manipulation

using namespace std;  // Using standard namespace for simpler code

class Player {  // Defining a class named Player
private:
    string username;  // Private member variable for storing username
    string gameName;  // Private member variable for storing game name
    int score;        // Private member variable for storing player's score

public:
    // Constructor initializing username, gameName, and setting score to 0
    Player(string uname, string gname) : username(uname), gameName(gname), score(0) {}

    string getUsername() const {  // Member function to retrieve username
        return username;
    }
    string getGameName() const {  // Member function to retrieve game name
        return gameName;
    }
    int getScore() const {  // Member function to retrieve player's score
        return score;
    }

    void updateScore(int points) {  // Member function to update player's score
        score += points;
    }
};

class Game {  // Defining a base class named Game
protected:
    Player* player;  // Pointer to a Player object
    string difficulty;  // String variable to hold game difficulty

public:
    // Constructor taking a Player pointer and initializing difficulty to an empty string
    Game(Player* p) : player(p), difficulty("") {}

    virtual void start() = 0;  // Pure virtual function to start the game
    virtual void end() = 0;    // Pure virtual function to end the game
    virtual void rules() = 0;  // Pure virtual function to display game rules
};

class FindSynonym : public Game {  // Defining a derived class named FindSynonym inheriting from Game
private:
    string words[5] = { "happy", "angry", "big", "small", "fast" };  // Array of words
    string synonyms[5] = { "joyful", "furious", "large", "tiny", "quick" };  // Array of synonyms
    string selectedWord;  // String variable to hold a selected word
    string selectedSynonym;  // String variable to hold the synonym of the selected word
    int remainingAttempts;  // Integer variable to store remaining attempts

public:
    // Constructor inheriting from Game and setting remainingAttempts to 0
    FindSynonym(Player* p) : Game(p), remainingAttempts(0) {}

    void start() override {  // Overridden function to start the Find Synonym game
        cout << "Welcome to Find Synonym Game!\n";  // Output welcome message
        rules();  // Display game rules
        selectWord();  // Select a word from the arrays
        playGame();  // Begin playing the game
    }

    void end() override {  // Overridden function to end the game
        cout << player->getUsername() << ", your score is: " << player->getScore() << endl;  // Output player's score
    }

    void rules() override {  // Overridden function to display game rules
        cout << "Game Rules:\n";  // Output game rules
        cout << "You need to guess the synonym of a word.\n";  // Instructions for the game
        cout << "You have limited attempts based on difficulty level.\n";  // Information about limited attempts
    }

    void selectWord() {  // Function to randomly select a word and its synonym
        int index = rand() % 5;  // Generate a random index
        selectedWord = words[index];  // Select a word from the array using the index
        selectedSynonym = synonyms[index];  // Select the corresponding synonym
    }

    void playGame() {  // Function to play the Find Synonym game
        cout << "Selected word: " << selectedWord << endl;  // Display the selected word
        cout << "Guess the synonym of the word: ";  // Prompt the user to guess the synonym

        cout << "\nChoose difficulty level:\n";  // Prompt for selecting difficulty level
        cout << "1. Easy (5 guesses)\n";  // Display option for easy difficulty
        cout << "2. Medium (4 guesses)\n";  // Display option for medium difficulty
        cout << "3. Hard (3 guesses)\n";  // Display option for hard difficulty
        int choice;  // Variable to store user's choice
        cin >> choice;  // Read user input for difficulty level

        // Set remaining attempts based on the selected difficulty
        switch (choice) {
        case 1:
            remainingAttempts = 5;
            break;
        case 2:
            remainingAttempts = 4;
            break;
        case 3:
            remainingAttempts = 3;
            break;
        default:
            cout << "Invalid choice. Setting difficulty to Easy.\n";
            remainingAttempts = 5;
            break;
        }

        // Loop to handle guessing the synonym with limited attempts
        while (remainingAttempts > 0) {
            string guess;  // Variable to store user's guess
            cin >> guess;  // Read user's guess

            if (guess == selectedSynonym) {  // Check if the guess is correct
                cout << "Congratulations! You guessed it right.\n";  // Output success message
                player->updateScore(remainingAttempts);  // Update player's score based on remaining attempts
                break;  // Exit the loop if guessed correctly
            }
            else {
                cout << "Wrong guess. Try again.\n";  // Output message for wrong guess
                remainingAttempts--;  // Decrement remaining attempts
                cout << "Attempts left: " << remainingAttempts << endl;  // Display remaining attempts
            }
        }

        if (remainingAttempts == 0) {  // Check if attempts are exhausted
            cout << "Game over! The correct synonym was: " << selectedSynonym << endl;  // Output the correct synonym
        }
    }
};


class GuessMovie : public Game {  // Defining a derived class GuessMovie inheriting from Game
private:
    string movies[6] = { "Fight Club", "Toy Story", "The Shawshank Redemption", "The Dark Knight", "Catch Me If You Can", "The Silence of the Lambs" };  // Array of movie titles
    string selectedMovie;  // String variable to hold the selected movie title
    string hiddenMovie;  // String variable to store the movie title with hidden letters
    int remainingAttempts;  // Integer variable to store remaining attempts

public:
    GuessMovie(Player* p) : Game(p), remainingAttempts(0) {}  // Constructor inheriting from Game and initializing remainingAttempts to 0

    void start() override {  // Overridden function to start the Guess Movie game
        cout << "Welcome to Guess Movie Game!\n";  // Output welcome message
        rules();  // Display game rules
        selectMovie();  // Select a movie to play
        playGame();  // Begin playing the game
    }

    void end() override {  // Overridden function to end the game
        cout << player->getUsername() << ", your score is: " << player->getScore() << endl;  // Output player's score
    }

    void rules() override {  // Overridden function to display game rules
        cout << "Game Rules:\n";  // Output game rules
        cout << "Guess the name of the movie by revealing its letters or guess the whole movie name.\n";  // Instructions for the game
        cout << "You have limited attempts based on difficulty level.\n";  // Information about limited attempts
    }

    void selectMovie() {  // Function to select a movie based on difficulty level
        int index;  // Integer variable to store the index of the selected movie

        cout << "\nChoose difficulty level:\n";  // Prompt for selecting difficulty level
        cout << "1. Easy (2 words movies)\n";  // Display option for easy difficulty
        cout << "2. Medium (3 words movies)\n";  // Display option for medium difficulty
        cout << "3. Hard (4 words movies)\n";  // Display option for hard difficulty

        int choice;  // Variable to store user's choice
        cin >> choice;  // Read user input for difficulty level

        switch (choice) {  // Determine the index based on the selected difficulty
        case 1:
            index = rand() % 2;  // Randomly select index for easy difficulty
            break;
        case 2:
            index = 2 + rand() % 2;  // Randomly select index for medium difficulty
            break;
        case 3:
            index = 4 + rand() % 2;  // Randomly select index for hard difficulty
            break;
        default:
            cout << "Invalid choice. Setting difficulty to Easy.\n";
            index = rand() % 2;  // Set default to easy difficulty
            break;
        }

        selectedMovie = movies[index];  // Assign the selected movie title
        hiddenMovie = selectedMovie;  // Initialize hiddenMovie with the selected movie title

        // Replace letters with asterisks in hiddenMovie
        for (char& c : hiddenMovie) {
            if (c != ' ')
                c = '*';  // Replace non-space characters with asterisks
        }
    }

    void playGame() {  // Function to play the Guess Movie game
        cout << "Selected movie: " << hiddenMovie << endl;  // Display the hidden movie title

        bool guessedCorrectly = false;  // Boolean variable to track if movie is guessed correctly

        while (!guessedCorrectly && remainingAttempts < 5) {  // Loop until movie is guessed correctly or attempts are exhausted
            cout << "\n1. Guess a letter\n";  // Prompt for guessing a letter
            cout << "2. Guess the movie\n";  // Prompt for guessing the entire movie
            int choice;  // Variable to store user's choice
            cin >> choice;  // Read user input for choice

            if (cin.fail()) {  // Check for input failure
                cin.clear();  // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
                cout << "Invalid input. Please enter a valid option.\n";  // Prompt for valid input
                continue;  // Restart the loop
            }

            if (choice == 1) {  // If user chooses to guess a letter
                char letter;  // Variable to store guessed letter
                cout << "Enter a letter: ";
                cin >> letter;  // Read user's guessed letter

                bool found = false;  // Boolean variable to track if guessed letter is found
                for (int i = 0; i < selectedMovie.length(); ++i) {  // Iterate through characters in the movie title
                    if (tolower(selectedMovie[i]) == tolower(letter)) {  // Check if guessed letter matches any character in the movie title
                        hiddenMovie[i] = selectedMovie[i];  // Reveal the correctly guessed letter
                        found = true;  // Update found status
                    }
                }

                if (found) {  // If the guessed letter is found in the movie title
                    cout << "Correct guess! Updated movie: " << hiddenMovie << endl;  // Output success message and updated movie title
                }
                else {  // If the guessed letter is not found
                    cout << "Letter not found. Try again.\n";  // Output message for wrong guess
                    remainingAttempts++;  // Increment attempts count
                    cout << "Attempts left: " << 5 - remainingAttempts << endl;  // Display remaining attempts
                }

            }
            else if (choice == 2) {  // If user chooses to guess the entire movie
                char guess[100];  // Array to store user's guessed movie title
                cin.ignore();  // Ignore the newline character in the input buffer
                cout << "Guess the movie: " << endl;  // Prompt for guessing the entire movie
                cout << "(Pay attention to uppercase and lowercase letters.) : ";
                cin.get(guess, sizeof(guess));  // Take the entire line as input for guessed movie title

                if (guess == selectedMovie) {  // If guessed movie title matches the selected movie title
                    cout << "Congratulations! You guessed it right.\n";  // Output success message
                    player->updateScore(5 - remainingAttempts);  // Update player's score based on remaining attempts
                    break;  // Exit the loop
                }
                else {  // If guessed movie title is incorrect
                    cout << "Wrong guess. Try again.\n";  // Output message for wrong guess
                    remainingAttempts++;  // Increment attempts count
                    cout << "Attempts left: " << 5 - remainingAttempts << endl;  // Display remaining attempts
                }
            }
            else {  // If user enters an invalid choice
                cout << "Invalid choice. Try again.\n";  // Output message for invalid choice
            }
        }

        if (remainingAttempts == 5) {  // If attempts are exhausted
            cout << "Game over! The correct movie was: " << selectedMovie << endl;  // Output the correct movie title
        }
    }
};


class PredictionNumber : public Game {  // Defining a derived class PredictionNumber inheriting from Game
private:
    int secretNumber;  // Variable to store the secret number to be guessed
    int maxNumber;  // Variable to store the maximum number in the guessing range
    int attemptsLeft;  // Variable to store the remaining attempts

public:
    PredictionNumber(int difficulty) : Game(nullptr), secretNumber(0), maxNumber(0), attemptsLeft(0) {  // Constructor taking a difficulty level
        switch (difficulty) {  // Determine the maximum number based on the difficulty level
        case 1:
            maxNumber = 10;  // Set the max number for easy difficulty
            break;
        case 2:
            maxNumber = 25;  // Set the max number for medium difficulty
            break;
        case 3:
            maxNumber = 50;  // Set the max number for hard difficulty
            break;
        default:
            cout << "Invalid difficulty level. Setting to Easy by default." << endl;  // Output message for invalid difficulty level
            maxNumber = 10;  // Set default max number for easy difficulty
            break;
        }
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
        secretNumber = rand() % maxNumber + 1;  // Generate a random secret number within the range
        attemptsLeft = 5;  // Initialize attempts left to 5
    }

    void start() override {  // Overridden function to start the Guess Number game
        cout << "Welcome to Guess Number Game!\n";  // Output welcome message
        rules();  // Display game rules
        playGame();  // Begin playing the game
    }

    void end() override {  // Overridden function to end the game
        cout << player->getUsername() << ", your score is: " << player->getScore() << endl;  // Output player's score
    }

    void rules() override {  // Overridden function to display game rules
        cout << "Game Rules: \n";  // Output game rules
        cout << "Guess the number in the range ";  // Instruction to guess the number
        cout << "You have range varies depending on difficulty \n";  // Information about the range based on difficulty
    }

    void playGame() {  // Function to play the Guess Number game
        int guess;  // Variable to store user's guess

        while (attemptsLeft > 0) {  // Loop until attempts are exhausted
            cout << "Enter your guess (between 1 and " << maxNumber << "): ";  // Prompt for user's guess within the range
            cin >> guess;  // Read user's guess

            if (guess == secretNumber) {  // If user's guess matches the secret number
                cout << "Congratulations! You guessed the correct number: " << secretNumber << endl;  // Output success message
                cout << "Your score: " << attemptsLeft << endl;  // Output remaining attempts as score
                return;  // Exit the function
            }
            else if (guess < secretNumber) {  // If user's guess is smaller than the secret number
                cout << "The number is larger than your guess." << endl;  // Output message indicating the number is larger
            }
            else {  // If user's guess is larger than the secret number
                cout << "The number is smaller than your guess." << endl;  // Output message indicating the number is smaller
            }

            attemptsLeft--;  // Decrement attempts left
            if (attemptsLeft > 0) {  // If attempts are still available
                cout << "Attempts left: " << attemptsLeft << endl;  // Output remaining attempts
            }
            else {  // If attempts are exhausted
                cout << "Sorry, you have used all your attempts. The correct number was: " << secretNumber << endl;  // Output the correct number
            }
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random number generator

    string username;  // Variable to store user's username
    cout << "Enter your username: ";  // Prompt for user's username
    cin >> username;  // Read user's input for username

    Player* player = new Player(username, "Game1");  // Create a new Player object with the entered username and a default game name

    FindSynonym* findSynonymGame = new FindSynonym(player);  // Create a FindSynonym game object associated with the player
    GuessMovie* guessMovieGame = new GuessMovie(player);  // Create a GuessMovie game object associated with the player

    int choice;  // Variable to store user's choice for game selection
    PredictionNumber* predictionNumberGame;  // Pointer to PredictionNumber game object

    do {
        cout << "\nChoose a game to play:\n";  // Prompt for game selection
        cout << "1. Find Synonym\n";  // Option for Find Synonym game
        cout << "2. Guess Movie\n";  // Option for Guess Movie game
        cout << "3. Number Prediction\n";  // Option for Number Prediction game
        cout << "4. Exit\n";  // Option to exit
        cout << "Choice : ";  // Prompt for user's choice
        cin >> choice;  // Read user's choice

        switch (choice) {  // Switch statement to handle different game choices
        case 1:
            findSynonymGame->start();  // Start the Find Synonym game
            findSynonymGame->end();  // End the Find Synonym game
            break;
        case 2:
            guessMovieGame->start();  // Start the Guess Movie game
            guessMovieGame->end();  // End the Guess Movie game
            break;
        case 3:
            int difficulty;  // Variable to store user's choice of difficulty level
            cout << "Choose the difficulty level:" << endl;  // Prompt for choosing difficulty level for Prediction Number game
            cout << "1. Easy (1-10)" << endl;  // Option for easy difficulty
            cout << "2. Medium (1-25)" << endl;  // Option for medium difficulty
            cout << "3. Hard (1-50)" << endl;  // Option for hard difficulty
            cin >> difficulty;  // Read user's input for difficulty level

            predictionNumberGame = new PredictionNumber(difficulty);  // Create a new PredictionNumber game object with the chosen difficulty level
            predictionNumberGame->start();  // Start the PredictionNumber game
            predictionNumberGame->end();  // End the PredictionNumber game
            delete predictionNumberGame;  // Delete the PredictionNumber game object after the game ends
            break;
        case 4:
            cout << "Exiting the game. Thank you for playing!\n";  // Message to indicate exiting the game
            break;
        default:
            cout << "Invalid choice. Please try again.\n";  // Output for invalid input
            break;
        }
    } while (choice != 4);  // Repeat the loop until the user chooses to exit

    delete player;  // Delete the Player object to free memory
    delete findSynonymGame;  // Delete the Find Synonym game object to free memory
    delete guessMovieGame;  // Delete the Guess Movie game object to free memory

    return 0;  // Return 0 to indicate successful program execution
}
