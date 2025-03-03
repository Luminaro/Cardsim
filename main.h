#include "raylib.h"

// structs
typedef struct Card{
    Rectangle rec;
    Vector2 dest;
    float rotation;
    Color color;
} Card;

typedef struct CardArray{
    Card* arr;
    int length;
} CardArray;


// methods
void moveCard(Card* card, int speed);
void setDest(Card* card, float x, float y);
void setCardDestToCursor(Card* card);
void rotateCardRelativeToDistanceFromDest(Card* card);
bool mouseOnCard(Card* card);

// CardArray
CardArray __init__CardArray(int length);
Card __get__CardArray(CardArray CA, int index);
void __set__CardArray(CardArray CA, int index, Card value);
void __append__CardArray(CardArray* CA, Card value);
void __delete__CardArray();
