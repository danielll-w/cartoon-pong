#include "controller.h"

Controller::Controller(Model& model)
        : model_(model)
        , view_(model_)
{ }

void Controller::draw(ge211::Sprite_set& s)
{
    view_.draw(s);
}

void Controller::on_frame(double dt)
{
    model_.update(dt, Abstract_game::get_mixer());
}

//Key inputs to move paddles and start and pause game
void Controller::on_key_up(ge211::Key key)
{
    if (key==ge211::Key::up())
        model_.move_up_left_player(false);
    if (key==ge211::Key::down())
        model_.move_down_left_player(false);
    if (key.code()=='w')
        model_.move_up_right_player(false);
    if (key.code()=='s')
        model_.move_down_right_player(false);
}

void Controller::on_key_down(ge211::Key key)
{
    if (key==ge211::Key::up())
        model_.move_up_left_player(true);
    if (key==ge211::Key::down())
        model_.move_down_left_player(true);
    if (key.code()=='w')
        model_.move_up_right_player(true);
    if (key.code()=='s')
        model_.move_down_right_player(true);


    if (key.code()=='p')
        model_.pause_game();

    if (key.code()==' ')
        model_.start_game();
}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return ge211::Dimensions{1024, 768};
}
