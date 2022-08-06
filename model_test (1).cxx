#include "model.hxx"
#include <catch.hxx>
#include "shape.hxx"

Game_config const config;
//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//



//first test: initialize the game, test if the starting block has the correct
// posn_set;test if the occupied_posn is empty; test if score is zero; test
// the game_over and game_paused states.


TEST_CASE("Test_initialization")
{
    Model m(config);
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 87.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 12.5);
    CHECK(m.get_occupied_posn().size() == 0);
    CHECK(m.get_score() == 0);
    CHECK(!m.get_game_paused());
    CHECK(!m.check_game_over());
}
// second test: (destroy row test)
//create a full row in model, update time, check if row cleared, update
// score, check score

TEST_CASE("DESTROY ROW")
{
    Model m(config);
    CHECK(m.get_occupied_posn().size() == 0);
    for (float i = 12.5; i < 250; i += 25){
        m.add_occupied_posn({i,487.5});
    }
    CHECK(m.get_score() == 0);
    CHECK(m.get_occupied_posn().size() == 10);
    m.add_occupied_posn({12.5,462.5});
    CHECK(m.get_occupied_posn()[0].x == 12.5);
    CHECK(m.get_occupied_posn()[9].x == 237.5);
    CHECK(m.get_occupied_posn()[6].y == 487.5);
    m.on_frame(1.05);
    CHECK(m.get_occupied_posn().size()== 1);
    CHECK(m.get_occupied_posn()[0].x == 12.5);
    CHECK(m.get_occupied_posn()[0].y == 487.5);
    CHECK(m.get_score() ==1);

}


//third test: test if the next position for a falling block is the expected
// for all of our 4 shapes.
TEST_CASE("UPDATE SHAPES AND FALL DOWN")
{
    Model m(config);
    //first shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 87.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 12.5);
    m.on_frame(1.05);
    //checking first shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5+25);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 87.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 37.5+25);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5+25);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 12.5+25);
    m.immediate_fall();
    m.on_frame(1.05);
    //second shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 62.5);
    m.on_frame(1.05);
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 62.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 87.5);
    m.immediate_fall();
    m.on_frame(1.05);
    //third shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5);
    m.on_frame(1.05);
    //checking third shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    m.immediate_fall();
    m.on_frame(1.05);
    //fourth shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 37.5);
    m.on_frame(1.05);
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5+25);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5+25);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5+25);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 37.5+25);
}
// fourth test: test when a shape is on the right, it cannot move to the
// right but can move to the left

TEST_CASE("move_right_and_left")
{
    Model m(config);
    for (int i = 0; i < 4; i++)
    {
        m.actually_move_right();
    }
    CHECK(m.get_falling_block().right_next(config).hits_right_side(config));
    CHECK(m.get_falling_block().get_pivot().x == 212.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    m.actually_move_right();
    CHECK(m.get_falling_block().get_pivot().x == 212.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    m.actually_move_left();
    CHECK(m.get_falling_block().get_pivot().x == 212.5-25);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
}

//fifth test: check rotated falling_shapes at their expected position.

TEST_CASE("rotation"){
    Model m(config);
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 87.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 12.5);
    m.actually_rotate();
    //checking first shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5+25);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5);
    m.immediate_fall();
    m.on_frame(1.05);
    //second shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 62.5);
    m.actually_rotate();
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 87.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    m.immediate_fall();
    m.on_frame(1.05);
    //third shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5);
    m.actually_rotate();
    //checking third shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5);
    m.immediate_fall();
    m.on_frame(1.05);
    //fourth shape
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 37.5);
    m.actually_rotate();
    CHECK(m.get_falling_block().get_pivot().x == 112.5);
    CHECK(m.get_falling_block().get_pivot().y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[1].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[1].y == 12.5);
    CHECK(m.get_falling_block().get_posn_set()[2].x == 112.5);
    CHECK(m.get_falling_block().get_posn_set()[2].y == 37.5);
    CHECK(m.get_falling_block().get_posn_set()[3].x == 137.5);
    CHECK(m.get_falling_block().get_posn_set()[3].y == 37.5);
}