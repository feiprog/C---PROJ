#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m";

void printExplodingKitten() {
    cout << RED;
    cout << "   ('-.  ) (`-.       _ (`-.                       _ .-') _               .-') _                 .-. .-')          .-') _   .-') _     ('-.       .-') _  \n";
    cout << " _(  OO)  ( OO ).    ( (OO  )                     ( (  OO) )             ( OO ) )                \\  ( OO )        (  OO) ) (  OO) )  _(  OO)     ( OO ) ) \n";
    cout << BLUE;
    cout << "(,------.(_/.  \\_)-._.`     \\ ,--.     .-'),-----. \\     .'_  ,-.-') ,--./ ,--,' ,----.          ,--. ,--. ,-.-') /     '._/     '._(,------.,--./ ,--,'  \n";
    cout << " |  .---' \\  `.'  /(__...--'' |  |.-')( OO'  .-.  ',`'--..._) |  |OO)|   \\ |  |\\'  .-./-')       |  .'   / |  |OO)|'--...__)'--...__)|  .---'|   \\ |  |\\  \n";
    cout << GREEN;
    cout << " |  |      \\     /\\ |  /  | | |  | OO )   |  | |  ||  |  \\  ' |  |  \\|    \\|  | )  |_( O- )      |      /, |  |  \\'--.  .--'--.  .--'|  |    |    \\|  | ) \n";
    cout << YELLOW;
    cout << " |  '--.    \\   \\ | |  |_.' | |  |`-' \\_) |  |\\|  ||  |   ' | |  |(_/|  .     |/|  | .--, \\      |     ' _)|  |(_/   |  |     |  |  (|  '--. |  .     |/  \n";
    cout << CYAN;
    cout << " |  .--'   .'    \\_)|  .___.'(|  '---.' \\ |  | |  ||  |   / :,|  |_.'|  |\\    |(|  | '. (_/      |  .   \\ ,|  |_.'   |  |     |  |   |  .--' |  |\\    |   \n";
    cout << MAGENTA;
    cout << " |  `---. /  .'.  \\ |  |      |      |   `'  '-'  '|  '--'  (_|  |   |  | \\   | |  '--'  |       |  |\\   (_|  |      |  |     |  |   |  `---.|  | \\   |   \n";
    cout << " `------''--'   '--'`--'      `------'     `-----' `-------'  `--'   `--'  `--'  `------'        `--' '--' `--'      `--'     `--'   `------'`--'  `--'   \n";
    cout << RESET;
    cout << "\n";
}

void waitForInput() {
    cout << CYAN;
    cout << "\t\t\t\t\tPlease enter any key to start the game.";
    cout << RESET;
    cin.get();
}

class Card {
private:
    int m_type;
    string m_name;

public:
    Card(int type = 0, string name = "") : m_type(type), m_name(name) {}

    string ToString() const {
        return m_name;
    }

    int GetType() const {
        return m_type;
    }
};

class Player {
private:
    string m_name;
    vector<Card> m_hand;
    bool m_lost;
    bool m_extraTurn;
    int m_draws;

public:
    Player(string name = "") : m_name(name), m_lost(false), m_extraTurn(false), m_draws(1) {}

    string GetName() const {
        return m_name;
    }

    void SetLost(bool lost) {
        m_lost = lost;
    }

    bool HasLost() const {
        return m_lost;
    }

    void SetExtraTurn(bool extraTurn) {
        m_extraTurn = extraTurn;
    }

    bool HasExtraTurn() const {
        return m_extraTurn;
    }

    void DisplayHand() const {
        cout << "Cards in hand for " << m_name << ":" << endl;
        for (size_t i = 0; i < m_hand.size(); ++i) {
            cout << i << ": " << m_hand[i].ToString() << endl;
        }
    }

    int GetNumberOfCards() const {
        return m_hand.size();
    }

    void AddToHand(const Card &card) {
        m_hand.push_back(card);
    }

    Card PlayCard(int index) {
        if (index >= 0 && index < m_hand.size()) {
            Card playedCard = m_hand[index];
            m_hand.erase(m_hand.begin() + index);
            return playedCard;
        }
        return Card();
    }

    Card LoseCard(int index) {
        if (index >= 0 && index < m_hand.size()) {
            Card lostCard = m_hand[index];
            m_hand.erase(m_hand.begin() + index);
            return lostCard;
        }
        return Card();
    }

    void AddDraws(int draws) {
        m_draws += draws;
    }

    int GetDraws() const {
        return m_draws;
    }

    void ResetDraws() {
        m_draws = 1;
    }

    bool HasCardOfType(int type) const {
        for (const auto &card : m_hand) {
            if (card.GetType() == type) {
                return true;
            }
        }
        return false;
    }

    int CountCardOfType(int type) const {
        int count = 0;
        for (const auto &card : m_hand) {
            if (card.GetType() == type) {
                count++;
            }
        }
        return count;
    }

    int FindCardOfType(int type) const {
        for (size_t i = 0; i < m_hand.size(); ++i) {
            if (m_hand[i].GetType() == type) {
                return i;
            }
        }
        return -1;
    }

    const Card& GetCard(int index) const {
        return m_hand[index];
    }

    void InsertCardAt(int index, const Card &card) {
        m_hand.insert(m_hand.begin() + index, card);
    }

    void ShuffleHand() {
        random_shuffle(m_hand.begin(), m_hand.end());
    }
};

class Game {
private:
    vector<Player> m_players;
    vector<Card> m_deck;
    vector<Card> m_discard;
    vector<Card> m_explodingKittens;
    int m_numPlayers;

    void InitializeDeck() {
        vector<Card> baseDeck = {
            {2, "attack"}, {3, "skip"}, {4, "see_the_future"}, {5, "shuffle"},
            {6, "taco_cat"}, {7, "rainbow_cat"}, {8, "potato_cat"}, {9, "beard_cat"}, {10, "favor"}, {11, "nope"}
        };
        for (int i = 0; i < 4; ++i) {
            m_deck.insert(m_deck.end(), baseDeck.begin(), baseDeck.end());
        }
        for (int i = 0; i < (6 - m_numPlayers); ++i) { 
            m_deck.push_back({1, "defuse"});
        }
        m_explodingKittens.push_back({0, "exploding_kitten"});
        m_explodingKittens.push_back({0, "exploding_kitten"});
    }

public:
    Game();

    void SetNumPlayers();

    void Shuffle();

    void Peek();

    Card DrawCard();

    int HandleCard(int player, int cardIndex);

    void PlayGame();

    bool PromptNope(int currentPlayer, int playingPlayer);

    void RequestCardFromPlayer(int requestingPlayer, int targetPlayer, const string &cardName);
};

Game::Game() {
    m_numPlayers = 2;
    InitializeDeck();
    srand(time(0));
}

void Game::SetNumPlayers() {
    cout << "Enter number of players (2-5): ";
    cin >> m_numPlayers;
    while (m_numPlayers < 2 || m_numPlayers > 5) {
        cout << "Invalid number of players. Please enter a number between 2 and 5: ";
        cin >> m_numPlayers;
    }
}

void Game::Shuffle() {
    random_shuffle(m_deck.begin(), m_deck.end());
}

void Game::Peek() {
    cout << "Top three cards of the deck: " << endl;
    for (size_t i = 0; i < 3 && i < m_deck.size(); ++i) {
        cout << m_deck[i].ToString() << endl;
    }
}

Card Game::DrawCard() {
    Card drawnCard = m_deck.back();
    m_deck.pop_back();
    return drawnCard;
}

int Game::HandleCard(int player, int cardIndex) {
    Player &currentPlayer = m_players[player];
    Card playedCard = currentPlayer.PlayCard(cardIndex);
    m_discard.push_back(playedCard);

    if (playedCard.GetType() == 2) {
        currentPlayer.AddDraws(2);
    } else if (playedCard.GetType() == 3) {
        currentPlayer.ResetDraws();
        currentPlayer.SetExtraTurn(true);
    } else if (playedCard.GetType() == 4) {
        Peek();
    } else if (playedCard.GetType() == 5) {
        Shuffle();
    }

    return playedCard.GetType();
}

void Game::PlayGame() {
    SetNumPlayers();

    for (int i = 0; i < m_numPlayers; ++i) {
        string name;
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> name;
        m_players.emplace_back(name);
    }

    for (int i = 0; i < m_numPlayers; ++i) {
        m_players[i].AddToHand({1, "defuse"});
    }

    Shuffle();

    for (int i = 0; i < m_numPlayers; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_players[i].AddToHand(DrawCard());
        }
    }

    for (int i = 0; i < m_explodingKittens.size(); ++i) {
        m_deck.push_back(m_explodingKittens[i]);
    }

    Shuffle();

    int currentPlayer = 0;
    bool gameOver = false;
    while (!gameOver) {
        Player &player = m_players[currentPlayer];

        cout << "It's " << player.GetName() << "'s turn!" << endl;
        player.DisplayHand();

        int choice;
        cout << "Choose a card to play or -1 to draw: ";
        cin >> choice;

        if (choice >= 0 && choice < player.GetNumberOfCards()) {
            int cardType = HandleCard(currentPlayer, choice);
            if (cardType == 3) {
                currentPlayer = (currentPlayer + 1) % m_numPlayers;
                continue;
            }
        } else {
            for (int i = 0; i < player.GetDraws(); ++i) {
                Card drawnCard = DrawCard();
                cout << "Drew a " << drawnCard.ToString() << endl;

                if (drawnCard.GetType() == 0) {
                    if (player.HasCardOfType(1)) {
                        cout << "You drew an Exploding Kitten but have a defuse card. Using defuse." << endl;
                        player.LoseCard(player.FindCardOfType(1));
                        player.AddToHand(drawnCard);
                    } else {
                        cout << "You drew an Exploding Kitten and have no defuse card. You lose!" << endl;
                        player.SetLost(true);
                        m_numPlayers--;
                        if (m_numPlayers == 1) {
                            gameOver = true;
                        }
                    }
                } else {
                    player.AddToHand(drawnCard);
                }
            }
            player.ResetDraws();
        }

        if (!player.HasExtraTurn()) {
            do {
                currentPlayer = (currentPlayer + 1) % m_numPlayers;
            } while (m_players[currentPlayer].HasLost());
        } else {
            player.SetExtraTurn(false);
        }

        if (m_numPlayers == 1) {
            gameOver = true;
        }
    }

    for (const auto &player : m_players) {
        if (!player.HasLost()) {
            cout << "Congratulations, " << player.GetName() << "! You are the winner!" << endl;
            break;
        }
    }
}

bool Game::PromptNope(int currentPlayer, int playingPlayer) {
    for (int i = 0; i < m_numPlayers; ++i) {
        if (i != currentPlayer && i != playingPlayer && !m_players[i].HasLost() && m_players[i].HasCardOfType(11)) {
            cout << m_players[i].GetName() << ", do you want to play a Nope card? (yes/no): ";
            string response;
            cin >> response;
            if (response == "yes") {
                m_players[i].LoseCard(m_players[i].FindCardOfType(11));
                m_discard.push_back({11, "nope"});
                cout << "Nope card played!" << endl;
                return true;
            }
        }
    }
    return false;
}

void Game::RequestCardFromPlayer(int requestingPlayer, int targetPlayer, const string &cardName) {
    int cardIndex = m_players[targetPlayer].FindCardOfType(10);
    if (cardIndex >= 0) {
        Card requestedCard = m_players[targetPlayer].LoseCard(cardIndex);
        m_players[requestingPlayer].AddToHand(requestedCard);
        cout << "Card " << requestedCard.ToString() << " taken from " << m_players[targetPlayer].GetName() << " by " << m_players[requestingPlayer].GetName() << endl;
    } else {
        cout << "Requested card not found in " << m_players[targetPlayer].GetName() << "'s hand." << endl;
    }
}

int main() {
    printExplodingKitten();
    waitForInput();

    Game game;
    game.PlayGame();
    
    return 0;
}
