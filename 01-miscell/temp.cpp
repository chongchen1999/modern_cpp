#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

class CardGameSimulator {
public:
    // Configuration constants
    static constexpr int NUM_PLAYERS = 3;
    static constexpr int CARDS_PER_PLAYER = 17;
    static constexpr int TOTAL_CARDS = 54;
    static constexpr int RESERVE_CARDS = 3;
    static constexpr int PARAMETER_COUNT = 23;
    static constexpr int EPOCHS = 100;
    static constexpr int ROUNDS_PER_EPOCH = 50;
    static constexpr int GAMES_PER_ROUND = 6;

    using Card = short;

private:
    // Game state
    std::array<Card, TOTAL_CARDS> deck_;
    std::array<std::vector<Card>, NUM_PLAYERS> player_hands_;
    std::vector<Card> reserve_cards_;
    std::array<int, NUM_PLAYERS> scores_;
    std::array<int, NUM_PLAYERS> player_order_;

    // AI/ML parameters
    std::array<double, PARAMETER_COUNT> parameters_;
    std::array<std::array<double, PARAMETER_COUNT>, NUM_PLAYERS>
        parameter_changes_;

    // File paths and bot names
    std::string input_file_;
    std::string output_file_;
    std::string debug_path_;
    std::array<std::string, NUM_PLAYERS> bot_executables_;

    // Random number generator
    std::mt19937 rng_;

    int current_position_;

public:
    CardGameSimulator()
        : input_file_("in.txt"), output_file_("out.txt"),
          debug_path_("\\Debug\\"), rng_(std::time(nullptr)),
          current_position_(0) {

        // Initialize player order
        std::iota(player_order_.begin(), player_order_.end(), 0);

        // Initialize scores and parameters
        scores_.fill(0);
        parameters_.fill(0.0);

        // Clear parameter changes
        for (auto& changes : parameter_changes_) {
            changes.fill(0.0);
        }

        // TODO: Set bot executable names
        bot_executables_[0] = "bot0.exe";
        bot_executables_[1] = "bot1.exe";
        bot_executables_[2] = "bot2.exe";
    }

    void run_simulation() {
        for (int epoch = 0; epoch < EPOCHS; ++epoch) {
            std::cout << "Starting epoch " << epoch + 1 << "/" << EPOCHS
                      << std::endl;

            initialize_epoch_parameters();

            for (int round = 0; round < ROUNDS_PER_EPOCH; ++round) {
                run_round();

                // Early termination condition
                if (round == ROUNDS_PER_EPOCH / 2 && scores_[0] == 0 &&
                    scores_[1] == 0) {
                    break;
                }
            }

            finalize_epoch();
        }
    }

private:
    void shuffle_deck() {
        std::iota(deck_.begin(), deck_.end(), 0);
        std::shuffle(deck_.begin(), deck_.end(), rng_);
    }

    void deal_cards() {
        // Clear previous hands
        for (auto& hand : player_hands_) {
            hand.clear();
        }
        reserve_cards_.clear();

        // Deal cards to players
        for (int i = 0; i < CARDS_PER_PLAYER * NUM_PLAYERS; i += NUM_PLAYERS) {
            for (int player = 0; player < NUM_PLAYERS; ++player) {
                player_hands_[player].push_back(deck_[i + player]);
            }
        }

        // Set reserve cards
        for (int i = CARDS_PER_PLAYER * NUM_PLAYERS; i < TOTAL_CARDS; ++i) {
            reserve_cards_.push_back(deck_[i]);
        }
    }

    void initialize_epoch_parameters() {
        // Initialize parameter changes for players 0 and 2
        initialize_player_parameters(0);
        initialize_player_parameters(2);
    }

    void initialize_player_parameters(int player) {
        std::uniform_int_distribution<int> param_dist(3, PARAMETER_COUNT - 1);
        std::uniform_int_distribution<int> sign_dist(0, 1);

        int changes_to_make = param_dist(rng_);

        while (changes_to_make > 0) {
            int param_index = std::uniform_int_distribution<int>(
                0, PARAMETER_COUNT - 1)(rng_);

            if (std::abs(parameter_changes_[player][param_index]) < 1e-5) {
                double sign = sign_dist(rng_) ? 1.0 : -1.0;
                parameter_changes_[player][param_index] =
                    sign * compute_gradient(parameters_[param_index]);
                --changes_to_make;
            }
        }
    }

    double compute_gradient(double value) {
        // Placeholder gradient function - implement your specific gradient
        // logic
        return std::tanh(value) * 0.1; // Example: scaled tanh
    }

    void run_round() {
        shuffle_deck();
        deal_cards();

        for (int game = 0; game < GAMES_PER_ROUND; ++game) {
            play_game();
            std::next_permutation(player_order_.begin(), player_order_.end());
        }

        clear_game_state();
    }

    void play_game() {
        std::array<std::vector<Card>, NUM_PLAYERS> current_hands =
            player_hands_;
        std::array<std::vector<Card>, NUM_PLAYERS> played_cards;
        std::vector<int> bids;

        int landlord_position = 0;
        int max_bid = 0;
        int final_bid = 0;
        int final_score = 0;

        // Bidding phase
        conduct_bidding_phase(bids, landlord_position, max_bid, final_bid);

        // Playing phase
        conduct_playing_phase(current_hands, played_cards, landlord_position,
                              final_bid, final_score);

        // Score calculation
        update_scores(landlord_position, final_score);

        display_current_scores();
    }

    void conduct_bidding_phase(std::vector<int>& bids, int& landlord_position,
                               int& max_bid, int& final_bid) {
        for (int player = 0; player < NUM_PLAYERS; ++player) {
            current_position_ = player;

            std::string request = create_bid_request(player, bids);
            int bid = get_bot_response_bid(player, request);

            bids.push_back(bid);

            if (bid > max_bid) {
                max_bid = bid;
                landlord_position = player;
            }

            if (max_bid == 3)
                break;
        }

        final_bid = std::max(1, max_bid);
    }

    void conduct_playing_phase(
        std::array<std::vector<Card>, NUM_PLAYERS>& hands,
        std::array<std::vector<Card>, NUM_PLAYERS>& played_cards,
        int landlord_position, int final_bid, int& final_score) {

        // Give reserve cards to landlord
        hands[landlord_position].insert(hands[landlord_position].end(),
                                        reserve_cards_.begin(),
                                        reserve_cards_.end());

        final_score = final_bid;
        int turn = 2; // Start from turn 2 (after bidding)

        while (true) {
            bool game_ended = false;

            for (int player = 0; player < NUM_PLAYERS; ++player) {
                current_position_ = player;

                std::string request =
                    create_play_request(player, played_cards, hands[player],
                                        landlord_position, final_bid, turn);

                std::vector<Card> cards_played =
                    get_bot_response_cards(player, request);
                played_cards[player] = cards_played;

                // Update hand
                update_player_hand(hands[player], cards_played);

                // Check for special multipliers
                update_score_multipliers(cards_played, final_score);

                if (hands[player].empty()) {
                    game_ended = true;
                    break;
                }
            }

            if (game_ended)
                break;
            ++turn;
        }
    }

    std::string create_bid_request(int player, const std::vector<int>& bids) {
        return R"("requests":[{)" +
               create_card_list_json("own", player_hands_[player]) + "," +
               create_int_list_json("bid", bids) + "}";
    }

    std::string create_play_request(
        int player,
        const std::array<std::vector<Card>, NUM_PLAYERS>& played_cards,
        const std::vector<Card>& player_hand, int landlord_position,
        int final_bid, int turn) {

        std::string request = R"("requests":[)";

        if (turn == 2) {
            request += "{";
        } else {
            request += ",{";
        }

        request += create_history_json(played_cards) + "," +
                   create_card_list_json("own", player_hand);

        if (turn == 2) {
            request += "," +
                       create_card_list_json("publiccard", reserve_cards_) +
                       R"(,"landlord":)" + std::to_string(landlord_position) +
                       R"(,"pos":)" + std::to_string(player) +
                       R"(,"finalbid":)" + std::to_string(final_bid);
        }

        request += "}";
        return request;
    }

    std::string create_card_list_json(const std::string& key,
                                      const std::vector<Card>& cards) {
        std::string result = "\"" + key + "\":[";

        if (!cards.empty()) {
            for (size_t i = 0; i < cards.size() - 1; ++i) {
                result += std::to_string(cards[i]) + ",";
            }
            result += std::to_string(cards.back());
        }

        result += "]";
        return result;
    }

    std::string create_int_list_json(const std::string& key,
                                     const std::vector<int>& values) {
        std::string result = "\"" + key + "\":[";

        if (!values.empty()) {
            for (size_t i = 0; i < values.size() - 1; ++i) {
                result += std::to_string(values[i]) + ",";
            }
            result += std::to_string(values.back());
        }

        result += "]";
        return result;
    }

    std::string create_history_json(
        const std::array<std::vector<Card>, NUM_PLAYERS>& played_cards) {
        std::string result = "\"history\":[";

        // Show other players' cards relative to current position
        result += create_card_list_json(
                      "", played_cards[(current_position_ + 1) % NUM_PLAYERS]) +
                  "," +
                  create_card_list_json(
                      "", played_cards[(current_position_ + 2) % NUM_PLAYERS]);

        result += "]";
        return result;
    }

    int get_bot_response_bid(int player, const std::string& request) {
        write_input_file(request, R"("responses":[)");
        set_player_parameters(player);
        execute_bot(player);
        return read_bid_from_output();
    }

    std::vector<Card> get_bot_response_cards(int player,
                                             const std::string& request) {
        write_input_file(request, R"("responses":[)");
        set_player_parameters(player);
        execute_bot(player);
        return read_cards_from_output();
    }

    void write_input_file(const std::string& request,
                          const std::string& response) {
        std::ofstream file(input_file_);
        file << "{" << request << "]," << response << "]}";
        file.flush();

        // Also log to debug file
        std::ofstream log("log.txt", std::ios::app);
        log << "{" << request << "]," << response << "]}" << std::endl;
    }

    void set_player_parameters(int player) {
        std::ofstream file("score.txt");
        for (int i = 0; i < PARAMETER_COUNT; ++i) {
            file << parameters_[i] +
                        parameter_changes_[player_order_[player]][i]
                 << " ";
        }
        file.flush();
    }

    void execute_bot(int player) {
        std::string command = bot_executables_[player_order_[player]] + " < " +
                              input_file_ + " > " + output_file_;
        std::system(command.c_str());
    }

    int read_bid_from_output() {
        std::ifstream file(output_file_);
        char ch;

        // Find first digit
        do {
            ch = file.get();
        } while (ch < '0' || ch > '9');

        return ch - '0';
    }

    std::vector<Card> read_cards_from_output() {
        std::ifstream file(output_file_);
        std::vector<Card> cards;
        int card;
        char ch;

        while (true) {
            ch = file.peek();
            if (ch == ']')
                break;

            if (ch < '0' || ch > '9') {
                file.get();
                continue;
            }

            file >> card;
            cards.push_back(card);
        }

        return cards;
    }

    void update_player_hand(std::vector<Card>& hand,
                            const std::vector<Card>& played_cards) {
        std::sort(hand.begin(), hand.end());

        std::vector<Card> sorted_played = played_cards;
        std::sort(sorted_played.begin(), sorted_played.end());

        std::vector<Card> new_hand(hand.size() - played_cards.size());
        std::set_difference(hand.begin(), hand.end(), sorted_played.begin(),
                            sorted_played.end(), new_hand.begin());

        hand = std::move(new_hand);
    }

    void update_score_multipliers(const std::vector<Card>& played_cards,
                                  int& final_score) {
        // Double jokers (cards 52 and 53)
        if (played_cards.size() == 2 && played_cards[0] == 52 &&
            played_cards[1] == 53) {
            final_score *= 2;
        }
        // Four of a kind
        else if (played_cards.size() == 4 &&
                 std::all_of(played_cards.begin() + 1, played_cards.end(),
                             [&](Card card) {
                                 return card / 4 == played_cards[0] / 4;
                             })) {
            final_score *= 2;
        }
    }

    void update_scores(int landlord_position, int final_score) {
        if (landlord_position == current_position_) {
            // Landlord wins
            scores_[player_order_[landlord_position]] += final_score * 2;
            scores_[player_order_[(landlord_position + 1) % NUM_PLAYERS]] -=
                final_score;
            scores_[player_order_[(landlord_position + 2) % NUM_PLAYERS]] -=
                final_score;
        } else {
            // Farmers win
            scores_[player_order_[landlord_position]] -= final_score * 2;
            scores_[player_order_[(landlord_position + 1) % NUM_PLAYERS]] +=
                final_score;
            scores_[player_order_[(landlord_position + 2) % NUM_PLAYERS]] +=
                final_score;
        }
    }

    void display_current_scores() {
        for (int i = 0; i < NUM_PLAYERS; ++i) {
            std::cout << "Bot " << player_order_[i] << ": "
                      << scores_[player_order_[i]] << std::endl;
        }
    }

    void clear_game_state() {
        for (auto& hand : player_hands_) {
            hand.clear();
        }
        reserve_cards_.clear();

        std::ofstream log("log.txt");
        log.close();
    }

    void finalize_epoch() {
        // Find winning bot
        int winner = 0;
        int max_score = scores_[0];

        for (int i = 1; i < NUM_PLAYERS; ++i) {
            std::cout << "Bot " << i << ": " << scores_[i] << std::endl;
            if (scores_[i] > max_score) {
                winner = i;
                max_score = scores_[i];
            }
        }

        std::cout << "Bot " << winner << " wins with score " << max_score
                  << std::endl;

        // Update parameters based on winner
        std::cout << "Updated parameters: ";
        for (int i = 0; i < PARAMETER_COUNT; ++i) {
            parameters_[i] += parameter_changes_[winner][i];
            std::cout << parameters_[i] << " ";
        }
        std::cout << std::endl;

        // Reset for next epoch
        reset_epoch_state();
    }

    void reset_epoch_state() {
        for (auto& changes : parameter_changes_) {
            changes.fill(0.0);
        }
        scores_.fill(0);
    }
};

int main() {
    try {
        CardGameSimulator simulator;
        simulator.run_simulation();

        std::cout << "Simulation completed successfully!" << std::endl;
        std::system("pause");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::system("pause");
        return 1;
    }

    return 0;
}