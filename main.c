#include "raylib.h"

typedef struct Card{
    Rectangle rec;
    Vector2 dest;
    float rotation;
    Color color;
} Card;

void moveCard(Card* card, int speed){
    card->rec.x += (card->dest.x - card->rec.x)*speed*GetFrameTime();
    card->rec.y += (card->dest.y - card->rec.y)*speed*GetFrameTime();
}

void setDest(Card* card, float x, float y){
    card->dest.x = x;
    card->dest.y = y;
}

void setCardDestToCursor(Card* card){
    setDest(card, GetMouseX(), GetMouseY());
}

void rotateCardRelativeToDistanceFromDest(Card* card){
    int rotation_speed = 5;
    float max_rotation = 30;
    card->rotation += ((card->dest.x - card->rec.x) - card->rotation)*GetFrameTime()*rotation_speed;
    
    if( card->rotation >= 0 && card->rotation > max_rotation ){ 
        card->rotation = max_rotation; 
    }
    else if( card->rotation < 0 && card->rotation < -max_rotation ){
        card->rotation = -max_rotation;
    }
}

bool mouseOnCard(Card* card){
    return CheckCollisionPointRec(GetMousePosition(), card->rec);
}
int main(){
    InitWindow(800, 800, "Cardsim");
    Rectangle rec = {rec.width/2, rec.height/2, 100, 150};
    Vector2 dest = {rec.width/2, rec.height/2};
    Vector2 origin = {rec.width/2, rec.height/2};
    Card card = {rec, dest, 0, BLUE};
    int drag_speed = 10;
    SetTargetFPS(60);
    bool holding = false;
    
    while(!WindowShouldClose()){
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnCard(&card)){
            holding = true;
        }
        
        if(holding && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            holding = false;
        }
        
        if(holding){
            setCardDestToCursor(&card);
        }
        
        rotateCardRelativeToDistanceFromDest(&card);
        moveCard(&card, drag_speed);
        
        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectanglePro(card.rec, origin, card.rotation, card.color);
        EndDrawing();
    }
    CloseWindow();
}