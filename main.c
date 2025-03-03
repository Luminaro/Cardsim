#include "main.h"
#include <stdlib.h>
// CardArray START ======================================================================
CardArray __init__CardArray(int length){
    Card* arr = malloc(sizeof(Card)*length*2);
    CardArray CA = {arr, length};
    return CA;
}
void __delete__CardArray(CardArray CA){
    free(CA.arr);
}

Card __get__CardArray(CardArray CA, int index){
    if(index < 0 || index >= CA.length){
        exit(-1);
    }
    return CA.arr[index];
}


// CardArray END ========================================================================




void moveCard(Card* card, int speed){
    rotateCardRelativeToDistanceFromDest(card);
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
    Rectangle real_rec = {
        card->rec.x - card->rec.width/2, card->rec.y - card->rec.height/2,
        card->rec.width, card->rec.height
    };
    return CheckCollisionPointRec(GetMousePosition(), real_rec);
}

int main(){
    // setup window
    InitWindow(800, 800, "Cardsim");
    SetTargetFPS(60);
    
    // create card
    Rectangle rec = {rec.width/2, rec.height/2, 100, 150};
    Vector2 dest = {400, 400};
    Vector2 origin = {rec.width/2, rec.height/2};
    Card card = {rec, dest, 0, BLUE};
    
    // constants
    const int drag_speed = 10;
    
    // variables
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
        
        
        moveCard(&card, drag_speed);
        
        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectanglePro(card.rec, origin, card.rotation, card.color);
        EndDrawing();
    }
    CloseWindow();
}