#pragma once
#include <ge211.h>
#include "paddle.h"
#include "ball.h"
#include <vector>
#include "geometry.h"

struct Model
{
    //Constructor
    explicit Model(Geometry const& geometry = Geometry());

//PUBLIC

    //Make ball and paddles live
    void start_game();

    void pause_game();

    //Updates the model state for  one time step .
    void update (double, ge211::Mixer*);

    //Updates the position of either paddle
    void move_up_left_player(bool);
    void move_down_left_player(bool);
    void move_up_right_player(bool);
    void move_down_right_player(bool);
    void add_rock();

//Starts the game and sets the game to ‘over’ when the count is bigger than 20
    void set_game_over();


    Geometry const  geometry_;

//Left and right paddles
    Paddle right_player_;
    Paddle left_player_;

//Game ball
    Ball ball_ ;

//Vector of rocks in the game
    std::vector<Rock> rocks_;

    int winner_ = 0;

    //Returns the number of live rocks in the vector
    int rocks_number();

//Variables for game state
    bool pause = false;
    bool game_ended = false;
    bool game_started = false;


// Test access
    friend class Test_access;

};

