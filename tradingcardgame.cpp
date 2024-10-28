#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 100000
#define MAX_TOTAL_CARDS 1000000

typedef struct {
    int player;
    int slot;
} CardLocation;

CardLocation card_locations[MAX_TOTAL_CARDS + 1];
int player_cards[MAX_N][MAX_M];
int player_sizes[MAX_N];
int N, T, Q;

void trade_cards(int x1, int y1, int x2, int y2) {
    int card1 = player_cards[x1-1][y1-1];
    int card2 = player_cards[x2-1][y2-1];
    
    player_cards[x1-1][y1-1] = card2;
    player_cards[x2-1][y2-1] = card1;
    
    card_locations[card1].player = x2;
    card_locations[card1].slot = y2;
    card_locations[card2].player = x1;
    card_locations[card2].slot = y1;
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &player_sizes[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < player_sizes[i]; j++) {
            scanf("%d", &player_cards[i][j]);
            card_locations[player_cards[i][j]].player = i + 1;
            card_locations[player_cards[i][j]].slot = j + 1;
        }
    }

    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        trade_cards(x1, y1, x2, y2);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int query;
        scanf("%d", &query);
        printf("%d %d\n", card_locations[query].player, card_locations[query].slot);
    }

    return 0;
}