#include "raylib.h"

typedef struct Card{
    Rectangle rec;
    Vector2 dest;
    float rotation;
    Color color;
} Card;

void moveCard(Card* card, int speed);
void setDest(Card* card, float x, float y);
void setCardDestToCursor(Card* card);
void rotateCardRelativeToDistanceFromDest(Card* card);
bool mouseOnCard(Card* card);