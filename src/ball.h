#pragma once
#include <ge211.h>
#include <paddle.h>


struct Rock
{
    ge211::Rectangle rock;
    bool onscreen_;
};


struct Ball
{
    //Constructor
    Ball(int r, ge211::Dimensions vel, ge211::Position c);

    // Returns the position of the top-left corner of the ball's "bounding box"
    ge211::Position top_left() const;

    // Returns a ball with updated position
    Ball next() const;

    //MEMBER VARIABLES

    // the radius of the ball
    int radius_;

    // The velocity of the ball in pixels per tick.
    ge211::Dimensions velocity_;

    //The position of the center of the ball.
    ge211::Position center_;

    // Returns whether the ball is live (launched) or not (not launched or the game is over)
    bool live_;

// Returns the ball 's position.
    ge211::Position get_ball_position() const;


// Determines whether the ball hits the top, bottom or sides of the screen, a paddle, or a rock
    bool ball_hits_top () const;
    bool ball_hits_bottom(int screen_height) const;
    bool ball_hits_paddle(Paddle p) const;

    bool ball_hits_left_side() const;

    bool ball_hits_right_side(int screen_width) const;

    bool ball_hits_rock(Rock const&) const;



// Removes the rock from the screen
    bool destroy_rock(std::vector<Rock>&);

// Reflects the ball
    void reflect_vertical ();
    void reflect_horizontal ();
    void reflect_off_paddle(Paddle);
};

