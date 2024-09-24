#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>   // for rand and srand
#include <algorithm> // for shuffle
#include <iomanip>   // for setw
#include <string>

using namespace std;

class WordCrossGame
{
private:
    vector<string> words;          // Stores pairs of words
    vector<vector<string>> grid;   // Stores the hidden words
    vector<vector<bool>> revealed; // Tracks revealed words
    int size;                      // Size of the grid (n x n)
    int pairsFound;                // Number of matched pairs

    // Initializes the grid with shuffled words
    void initializeGrid()
    {
        vector<string> shuffledWords = words;
        random_shuffle(shuffledWords.begin(), shuffledWords.end());
        int index = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                grid[i][j] = shuffledWords[index++];
                revealed[i][j] = false;
            }
        }
    }

    // Prints the current game board
    void displayGrid() const
    {
        cout << "Current Grid:" << endl;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (revealed[i][j])
                {
                    cout << setw(10) << grid[i][j] << " ";
                }
                else
                {
                    cout << setw(10) << "?" << " ";
                }
            }
            cout << endl;
        }
    }

    // Checks if the game is finished
    bool isGameFinished() const
    {
        return pairsFound == (size * size) / 2;
    }

public:
    // Constructor initializes the game with n x n grid (n must be even)
    WordCrossGame(int gridSize) : size(gridSize), pairsFound(0)
    {
        if (size % 2 != 0)
        {
            cout << "Grid size must be even!" << endl;
            exit(1);
        }

        // Generate word pairs (for simplicity, we use letters "A", "B", ...)
        char letter = 'A';
        for (int i = 0; i < (size * size) / 2; ++i)
        {
            string word(1, letter);
            words.push_back(word);
            words.push_back(word); // Add the pair
            letter++;
        }

        grid.resize(size, vector<string>(size));
        revealed.resize(size, vector<bool>(size, false));
        initializeGrid();
    }

    // Plays a round of the game
    void play()
    {
        while (!isGameFinished())
        {
            displayGrid();
            int r1, c1, r2, c2;

            // Get first guess
            cout << "Enter the row and column of the first cell (e.g., 0 1): ";
            cin >> r1 >> c1;
            if (revealed[r1][c1])
            {
                cout << "This cell is already revealed! Choose another." << endl;
                continue;
            }
            revealed[r1][c1] = true;
            displayGrid();

            // Get second guess
            cout << "Enter the row and column of the second cell (e.g., 0 2): ";
            cin >> r2 >> c2;
            if (revealed[r2][c2])
            {
                cout << "This cell is already revealed! Choose another." << endl;
                revealed[r1][c1] = false; // Hide the first cell again
                continue;
            }
            revealed[r2][c2] = true;
            displayGrid();

            // Check if the words match
            if (grid[r1][c1] == grid[r2][c2])
            {
                cout << "It's a match!" << endl;
                pairsFound++;
            }
            else
            {
                cout << "Not a match! Try again." << endl;
                revealed[r1][c1] = false;
                revealed[r2][c2] = false;
            }
        }
        cout << "Congratulations! You've matched all the pairs!" << endl;
    }
};

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random shuffle
    int gridSize;

    cout << "Welcome to Word Cross Memory Game!" << endl;
    cout << "Enter grid size (must be even, e.g., 4, 6): ";
    cin >> gridSize;

    WordCrossGame game(gridSize);
    game.play();

    return 0;
}
