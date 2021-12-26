#pragma once

#include "model.h"
#include "view.h"
#include <ge211.h>
#include "paddle.h"
#include <string>

struct Controller : public ge211::Abstract_game
{

    explicit Controller(Model&);
    friend class Test_access;

protected:

    void on_frame(double dt) override;

    void on_key_down(ge211::Key) override;
    void on_key_up(ge211::Key) override;

    void draw(ge211::Sprite_set&) override;
    ge211::Dimensions initial_window_dimensions() const override;

private:
    Model& model_;
    View view_;
};