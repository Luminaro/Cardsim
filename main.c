#include "main.h"
#include <stdlib.h>




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
    int outline_weight = 10;
    Color outline_color = BLACK;
    for(int i=0; i<num_cards; i++){
        Card card = cards[i];
        Rectangle outline = {card.rec.x - outline_weight/2, card.rec.y - outline_weight/2,
                             card.rec.width + outline_weight, card.rec.height + outline_weight};
        DrawRectanglePro(outline, card.origin, card.rotation, outline_color);
        DrawRectanglePro(card.rec, card.origin, card.rotation, card.color);
        
    }
}
void moveCards(Card* cards, int num_cards, int speed){
    for(int i=0; i<num_cards; i++){
        moveCard(&(cards[i]), speed);
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
        Vector2 dest = {10*i, 100};
        Card card = {rec, dest, 0, BLUE, origin};
        cards[i] = card;
    }
    
    
    // constants
    const int drag_speed = 10;
    
    // variables
    bool holding = false;
    
    
    while(!WindowShouldClose()){        
        if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
            int clicked_card_index = -1;
            for(int i=num_cards-1; i>=0; i--){
                if(mouseOnCard( &(cards[i]) )){
                    clicked_card_index = i;
                    break;
                }
            }
            if(clicked_card_index != -1){
                holding = !holding;
            }
            
            if(holding){
                Card clicked_card = cards[clicked_card_index];
                for(int i=clicked_card_index; i<num_cards-1; i++){
                    cards[i] = cards[i+1];
                }
                cards[num_cards-1] = clicked_card;
            }
        }
        
        if(holding){
            cards[num_cards-1].dest = GetMousePosition();   
        }
        moveCards(cards, num_cards, drag_speed);
        BeginDrawing();
            ClearBackground(WHITE);
            drawCards(cards, num_cards);
        EndDrawing();
    }
    CloseWindow();
}