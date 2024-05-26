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
    cout << endl << "MEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOW" << endl
         << "Welcome to Exploding Kittens!" << endl
         << "MEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOWMEOW" << endl;

    SetNumPlayers();

    for (int i = 0; i < m_numPlayers; ++i) {
        string playerName;
        cout << "Enter name for Player " << (i + 1) << ": ";
        cin >> playerName;
        m_players.push_back(Player(playerName));
    }

    InitializeDeck();
    cout << "Shuffling Cards..." << endl;
    Shuffle();

    cout << "Dealing Cards..." << endl;
    for (int i = 0; i < m_numPlayers; ++i) {
        m_players[i].AddToHand({1, "defuse"});
        for (int j = 0; j < 6; j++) {
            m_players[i].AddToHand(m_deck.back());
            m_deck.pop_back();
        }
    }

    m_deck.insert(m_deck.end(), m_explodingKittens.begin(), m_explodingKittens.end());
    Shuffle();

    PlayGame();
}

void Game::SetNumPlayers() {
    cout << " " << endl
         << "How many players would you like?" << endl
         << "Choose 2 - 4 players: " << endl;

    while (true) {
        if (cin >> m_numPlayers && m_numPlayers >= 2 && m_numPlayers <= 4) {
            break;
        } else {
            cout << "Error, please choose a number of players 2 - 4: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Game::Shuffle() {
    srand(static_cast<unsigned>(time(nullptr)));
    random_shuffle(m_deck.begin(), m_deck.end());
}

void Game::Peek() {
    cout << "Top 3 cards in the deck:" << endl;
    for (int i = 0; i < 3 && i < m_deck.size(); i++) {
        cout << m_deck.at(m_deck.size() - 1 - i).ToString() << endl;
    }
}

Card Game::DrawCard() {
    if (!m_deck.empty()) {
        Card drawnCard = m_deck.back();
        m_deck.pop_back();
        return drawnCard;
    }
    return Card();
}

int Game::HandleCard(int player, int cardIndex) {
    if (cardIndex < 0 || cardIndex >= m_players[player].GetNumberOfCards()) {
        cout << "Invalid card selection." << endl;
        return 0;
    }

    Card currentCard = m_players[player].GetCard(cardIndex);
    int theType = currentCard.GetType();

    if (theType == 11) {
        cout << "Nope cards cannot be played directly." << endl;
        return 0;
    }

    if (theType == 6 || theType == 7 || theType == 8 || theType == 9) {
        cout << "You selected a cat card. Select another matching cat card to play a pair (or type -1 to go back): " << endl;
        m_players[player].PlayCard(cardIndex);  
        m_players[player].DisplayHand();
        int secondCardIndex;
        cin >> secondCardIndex;

        if (secondCardIndex == -1) {
            m_players[player].AddToHand(currentCard);  
            return 0;
        }

        if (secondCardIndex >= 0 && secondCardIndex < m_players[player].GetNumberOfCards() &&
            m_players[player].GetCard(secondCardIndex).GetType() == theType) {

            m_discard.push_back(currentCard);
            m_discard.push_back(m_players[player].PlayCard(secondCardIndex));

            cout << "You played a pair! You can now steal a card from another player!" << endl;
            cout << "Select a Player: " << endl;

            for (int i = 0; i < m_numPlayers; i++) {
                if (i != player)
                    cout << i << " " << m_players[i].GetName() << endl;
            }

            int selectPlayer;
            cin >> selectPlayer;

            while (selectPlayer < 0 || selectPlayer >= m_numPlayers || selectPlayer == player) {
                cout << "Invalid selection. Choose a valid player:" << endl;
                cin >> selectPlayer;
            }

            if (PromptNope(selectPlayer, player)) {
                return 0;
            }

            int noOfCards = m_players[selectPlayer].GetNumberOfCards();

            if (noOfCards > 0) {
                cout << "Shuffling the cards of " << m_players[selectPlayer].GetName() << "..." << endl;
                m_players[selectPlayer].ShuffleHand();

                cout << "Select a card to steal: " << endl;
                for (int i = 0; i < noOfCards; i++) {
                    cout << "Card " << i << endl;
                }

                int theCard;
                cin >> theCard;

                while (theCard < 0 || theCard >= noOfCards) {
                    cout << "Invalid selection. Choose a valid card:" << endl;
                    cin >> theCard;
                }

                Card stolenCard = m_players[selectPlayer].LoseCard(theCard);
                if (stolenCard.GetType() != 0) {
                    m_players[player].AddToHand(stolenCard);
                    cout << m_players[player].GetName() << " stole a " << stolenCard.ToString() << " card from " << m_players[selectPlayer].GetName() << "!" << endl;
                } else {
                    cout << "Stolen card is an Exploding Kitten, reinserting it into the deck!" << endl;
                    m_deck.push_back(stolenCard);
                    Shuffle();
                }
            } else {
                cout << m_players[selectPlayer].GetName() << " has no cards to steal!" << endl;
            }
            return 0;
        } else {
            cout << "These cards don't match! Please try again!" << endl;
            m_players[player].AddToHand(currentCard);  
            
            return 0;
        }
    }

    m_discard.push_back(m_players[player].PlayCard(cardIndex));

    if (PromptNope(player, player)) {
        m_players[player].AddToHand(currentCard);
        return 0;
    }

    int nextPlayer = (player + 1) % m_numPlayers;

    switch (theType) {
        case 1:
            cout << "You can't play your defuse card now! Save it for if you encounter an Exploding Kitten!" << endl;
            return 0;
        case 2: {
            cout << "You attacked " << m_players[nextPlayer].GetName() << "!" << endl;
            for (int i = 0; i < 2; ++i) {
                if (!m_deck.empty()) {
                    Card drawnCard = DrawCard();
                    cout << m_players[nextPlayer].GetName() << " drew: " << drawnCard.ToString() << endl;
                    m_players[nextPlayer].AddToHand(drawnCard);
                    if (drawnCard.GetType() == 0) {
                        cout << "Oh No! " << m_players[nextPlayer].GetName() << " drew Exploding Kitten: "
                             << drawnCard.ToString() << endl
                             << "Sorry! You're out of the game!" << endl;

                        m_players[nextPlayer].SetLost(true);

                        bool defused = false;
                        for (size_t j = 0; j < m_players[nextPlayer].GetNumberOfCards(); ++j) {
                            if (m_players[nextPlayer].GetCard(j).GetType() == 1) {
                                defused = true;
                                cout << "But " << m_players[nextPlayer].GetName() << " used a Defuse card!" << endl;
                                m_discard.push_back({1, "defuse"});
                                break;
                            }
                        }

                        if (!defused) {
                            cout << m_players[nextPlayer].GetName() << " has been eliminated!" << endl;
                            break;
                        } else {
                            cout << "Reinserting Exploding Kitten into the deck..." << endl;
                            m_deck.push_back(drawnCard);
                            Shuffle();
                            m_players[nextPlayer].SetLost(false);
                        }
                    }
                } else {
                    cout << "The deck is empty! No more cards to draw!" << endl;
                }
            }
            return 0;
        }
        case 3:
            cout << "You Played a Skip Card" << endl
                 << "Now you don't risk drawing an Exploding Kitten!" << endl;
            return 4;
        case 4:
            cout << " " << endl
                 << "You played a See-the-Future Card!" << endl
                 << "Lets see what cards are coming up next!" << endl;
            Peek();
            return 0;
        case 5:
            cout << "You played a Shuffle Card!" << endl
                 << "Now Shuffling Cards!" << endl;
            Shuffle();
            return 0;
        case 10:
            cout << "You played a Favor Card! You can request a card from another player." << endl
                 << "Select a Player: " << endl;

            for (int i = 0; i < m_numPlayers; i++) {
                if (i != player)
                    cout << i << " " << m_players[i].GetName() << endl;
            }

            int targetPlayer;
            cin >> targetPlayer;

            while (targetPlayer < 0 || targetPlayer >= m_numPlayers || targetPlayer == player) {
                cout << "Invalid selection. Choose a valid player:" << endl;
                cin >> targetPlayer;
            }

            if (PromptNope(targetPlayer, player)) {
                return 0;
            }

            if (m_players[targetPlayer].GetNumberOfCards() > 0) {
                cout << "Shuffling the cards of " << m_players[targetPlayer].GetName() << "..." << endl;
                m_players[targetPlayer].ShuffleHand();

                cout << m_players[targetPlayer].GetName() << ", please select a card to give to " << m_players[player].GetName() << ":" << endl;
                m_players[targetPlayer].DisplayHand();
                int cardToGive;
                cin >> cardToGive;

                while (cardToGive < 0 || cardToGive >= m_players[targetPlayer].GetNumberOfCards()) {
                    cout << "Invalid selection. Choose a valid card:" << endl;
                    cin >> cardToGive;
                }

                Card givenCard = m_players[targetPlayer].LoseCard(cardToGive);
                m_players[player].AddToHand(givenCard);
                cout << m_players[player].GetName() << " received a " << givenCard.ToString() << " card from " << m_players[targetPlayer].GetName() << "!" << endl;
            } else {
                cout << m_players[targetPlayer].GetName() << " has no cards to give!" << endl;
            }
            return 0;
        case 11:
            cout << "Nope cards cannot be played directly." << endl;
            return 0; 
    }
    return 0;
}

bool Game::PromptNope(int currentPlayer, int playingPlayer) {
    for (int i = 0; i < m_numPlayers; ++i) {
        if (i != currentPlayer && i != playingPlayer && !m_players[i].HasLost() && m_players[i].HasCardOfType(11)) {
            char response;
            cout << m_players[i].GetName() << ", do you want to play a Nope card? (y/n): ";
            cin >> response;
            if (response == 'y' || response == 'Y') {
                for (size_t j = 0; j < m_players[i].GetNumberOfCards(); ++j) {
                    if (m_players[i].GetCard(j).GetType() == 11) {
                        cout << m_players[i].GetName() << " played a Nope card!" << endl;
                        m_discard.push_back({11, "nope"});
                        return true; 
                    }
                }
            }
        }
    }
    return false;
}

void Game::RequestCardFromPlayer(int requestingPlayer, int targetPlayer, const string &cardName) {
    bool cardFound = false;
    for (size_t i = 0; i < m_players[targetPlayer].GetNumberOfCards(); ++i) {
        if (m_players[targetPlayer].GetCard(i).ToString() == cardName) {
            Card requestedCard = m_players[targetPlayer].LoseCard(i);
            m_players[requestingPlayer].AddToHand(requestedCard);
            cout << m_players[requestingPlayer].GetName() << " received a " << requestedCard.ToString() << " card from " << m_players[targetPlayer].GetName() << "!" << endl;
            cardFound = true;
            break;
        }
    }
    if (!cardFound) {
        cout << m_players[targetPlayer].GetName() << " does not have a " << cardName << " card!" << endl;
    }
}

void Game::PlayGame() {
    bool extraT = false;
    for (int i = 0; i < m_numPlayers; i++) {
        m_players[i].SetExtraTurn(extraT);
    }
    int thePlayer = 0;
    int losers = 0;
    int userChoice = 0;

    while (losers != m_numPlayers - 1) {
        userChoice = 0;
        losers = 0;

        while (userChoice != 3 && !m_players[thePlayer].HasLost()) {
            cout << "Number of Cards Left: " << m_deck.size() << " " << endl;
            cout << endl
                 << "It's " << m_players[thePlayer].GetName() << "'s turn!" << endl
                 << "What would you like to do?" << endl
                 << "1. View Cards" << endl
                 << "2. Play A Card" << endl
                 << "3. Draw A Card" << endl
                 << "4. Exit" << endl;
            cin >> userChoice;

            if (userChoice == 4) {
                cout << "Exiting game..." << endl;
                return;
            }

            while (userChoice > 3 || userChoice < 1) {
                cout << endl
                     << "Invalid entry, enter a number 1-3" << endl
                     << m_players[thePlayer].GetName() << ", what would you like to do?" << endl
                     << "1. View Cards" << endl
                     << "2. Play A Card" << endl
                     << "3. Draw A Card" << endl;
                cin >> userChoice;
            }

            switch (userChoice) {
                case 1:
                    m_players[thePlayer].DisplayHand();
                    break;
                case 2:
                    if (m_players[thePlayer].GetNumberOfCards() != 0) {
                        cout << "Select a card to play (or type -1 to go back): " << endl;
                        m_players[thePlayer].DisplayHand();
                        int cardIndex;
                        cin >> cardIndex;

                        if (cardIndex == -1) {
                            break;
                        }

                        if (cardIndex >= 0 && cardIndex < m_players[thePlayer].GetNumberOfCards()) {
                            int result = HandleCard(thePlayer, cardIndex);
                            if (result == 4 || result == 1) {
                                thePlayer = (thePlayer + 1) % m_numPlayers;
                                break;
                            }
                        } else {
                            cout << "Invalid card selection." << endl;
                        }
                    } else {
                        cout << "You have no more cards! Draw a card" << endl;
                    }
                    break;
                case 3:
                    for (int i = 0; i < m_players[thePlayer].GetDraws(); ++i) {
                        if (!m_deck.empty()) {
                            Card drawnCard = DrawCard();
                            cout << "You drew: " << drawnCard.ToString() << endl;
                            if (drawnCard.GetType() == 0) {
                                cout << "Oh No! You drew Exploding Kitten: "
                                     << drawnCard.ToString() << endl
                                     << "Sorry! You're out of the game!" << endl;

                                m_players[thePlayer].SetLost(true);

                                bool defused = false;
                                for (size_t j = 0; j < m_players[thePlayer].GetNumberOfCards(); ++j) {
                                    if (m_players[thePlayer].GetNumberOfCards() > 0 && m_players[thePlayer].GetCard(j).GetType() == 1) {
                                        defused = true;
                                        cout << "But you used a Defuse card!" << endl;
                                        m_discard.push_back({1, "defuse"});
                                        break;
                                    }
                                }

                                if (!defused) {
                                    cout << m_players[thePlayer].GetName() << " has been eliminated!" << endl;
                                    break;
                                } else {
                                    cout << "Reinserting Exploding Kitten into the deck..." << endl;
                                    m_deck.push_back(drawnCard);
                                    Shuffle();
                                    m_players[thePlayer].SetLost(false);
                                }
                            } else {
                                m_players[thePlayer].AddToHand(drawnCard);
                            }
                        } else {
                            cout << "The deck is empty! No more cards to draw!" << endl;
                        }
                    }
                    m_players[thePlayer].ResetDraws();
                    break;
            }
        }

        if (m_players[thePlayer].HasExtraTurn() && !m_players[thePlayer].HasLost()) {
            m_players[thePlayer].SetExtraTurn(false);
        } else {
            thePlayer = (thePlayer + 1) % m_numPlayers;
        }

        for (int i = 0; i < m_numPlayers; i++) {
            if (m_players[i].HasLost())
                losers++;
        }
    }

    for (int i = 0; i < m_numPlayers; i++) {
        if (!m_players[i].HasLost()) {
            cout << m_players[i].GetName() << " is the winner!" << endl;
            break;
        }
    }
}

int main() {
    Game game;
    system("clear");
    printExplodingKitten();
    waitForInput();
    
    return 0;
}