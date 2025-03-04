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
void drawCards(Card* cards, int num_cards){
    for(int i=0; i<num_cards; i++){
        Card card = cards[i];
        DrawRectanglePro(card.rec, origin, card.rotation, card.color);
    }
}
void moveCards(Card* cards, int num_cards, int speed){
    for(int i-0; i<num_cards; i++){
        moveCard(&(card[i]), speed);
    }
}
int main(){
    // setup window
    InitWindow(800, 800, "Cardsim");
    SetTargetFPS(60);
    
    // create card array
    int num_cards = 20;
    Card cards[num_cards];
    Rectangle rec = {50, 50, 100, 150};
    Vector2 origin = {rec.width/2, rec.height/2};
    for(int i=0; i<20; i++){
        Card card = {rec, dest, 0, BLUE};
        Vector2 dest = {400, 400 + 10*i};
    }
    
    
    // constants
    const int drag_speed = 10;
    
    // variables
    bool holding = false;
    
    
    while(!WindowShouldClose()){        
        
        BeginDrawing();
            ClearBackground(WHITE);
            drawCards(cards, num_cards, drag_speed);
        EndDrawing();
    }
    CloseWindow();
}