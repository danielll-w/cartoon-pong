#pragma once
#include <ge211.h>

struct Paddle
{
    //Constructor
    Paddle(int x, int y, int width, int height);

    // Returns the rectangle representing the paddle
    ge211::Rectangle get_paddle_rectangle() const;

    void move(int v, double dt);

    //Set paddle able to move or not
    void set_live(bool b);

    //Increase score of paddle if point is scored
    void increment_score();

    bool up = false;
    bool down = false;



    //Member variables

    ge211::Rectangle p_;

    //Score for that player
    int score_;

    //If paddle can move with input keys
    bool able_to_move;
};