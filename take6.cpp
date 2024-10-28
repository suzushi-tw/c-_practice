#include <stdio.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 50
#define MAX_ROWS 4
#define MAX_CARDS_PER_ROW 5

// Structure to represent a card play
typedef struct {
    int player;
    int card;
} CardPlay;

// Function to calculate cattle heads for a card
int get_cattle_heads(int card) {
    if (card == 55) return 7;
    if (card % 11 == 0) return 5;
    if (card % 10 == 0) return 3;
    if (card % 5 == 0) return 2;
    return 1;
}

// Compare function for qsort
int compare_card_plays(const void* a, const void* b) {
    return ((CardPlay*)a)->card - ((CardPlay*)b)->card;
}

// Function to find the best row for a card
int find_best_row(int card, int rows[][MAX_CARDS_PER_ROW], int row_sizes[], int P) {
    int best_row = -1;
    int smallest_diff = 999999;
    
    for (int i = 0; i < P; i++) {
        if (row_sizes[i] == 0) continue;
        
        int last_card = rows[i][row_sizes[i] - 1];
        if (card > last_card && (card - last_card) < smallest_diff) {
            smallest_diff = card - last_card;
            best_row = i;
        }
    }
    
    return best_row;
}

// Function to calculate total cattle heads in a row
int calculate_row_cattle_heads(int row[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += get_cattle_heads(row[i]);
    }
    return total;
}

int main() {
    int N, M, P;
    scanf("%d %d %d", &N, &M, &P);
    
    // Initialize rows
    int rows[MAX_ROWS][MAX_CARDS_PER_ROW];
    int row_sizes[MAX_ROWS] = {0};
    
    // Read starting cards for each row
    for (int i = 0; i < P; i++) {
        scanf("%d", &rows[i][0]);
        row_sizes[i] = 1;
    }
    
    // Read player cards
    int player_cards[MAX_PLAYERS][MAX_CARDS];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &player_cards[i][j]);
        }
    }
    
    // Initialize player scores
    int player_scores[MAX_PLAYERS] = {0};
    
    // Process each round
    for (int round = 0; round < M; round++) {
        // Collect all cards played this round
        CardPlay plays[MAX_PLAYERS];
        for (int i = 0; i < N; i++) {
            plays[i].player = i;
            plays[i].card = player_cards[i][round];
        }
        
        // Sort plays by card value
        qsort(plays, N, sizeof(CardPlay), compare_card_plays);
        
        // Process each play in order
        for (int i = 0; i < N; i++) {
            int current_player = plays[i].player;
            int current_card = plays[i].card;
            
            // Find best row for card
            int best_row = find_best_row(current_card, rows, row_sizes, P);
            
            // If card is smaller than all row ends
            if (best_row == -1) {
                // Find row with highest last card
                int highest_row = 0;
                for (int j = 1; j < P; j++) {
                    if (rows[j][row_sizes[j] - 1] > rows[highest_row][row_sizes[highest_row] - 1]) {
                        highest_row = j;
                    }
                }
                
                // Take all cards in that row
                player_scores[current_player] += calculate_row_cattle_heads(rows[highest_row], row_sizes[highest_row]);
                
                // Replace with new card
                rows[highest_row][0] = current_card;
                row_sizes[highest_row] = 1;
            }
            // If would be 6th card in row
            else if (row_sizes[best_row] == 5) {
                // Take all cards in row
                player_scores[current_player] += calculate_row_cattle_heads(rows[best_row], row_sizes[best_row]);
                
                // Replace with new card
                rows[best_row][0] = current_card;
                row_sizes[best_row] = 1;
            }
            // Normal case
            else {
                rows[best_row][row_sizes[best_row]] = current_card;
                row_sizes[best_row]++;
            }
        }
    }
    
    // Print final scores
    for (int i = 0; i < N; i++) {
        printf("%d\n", player_scores[i]);
    }
    
    return 0;
}