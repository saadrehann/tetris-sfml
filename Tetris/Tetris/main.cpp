/*
            [   TETRIS  BY  ]

    MUHAMMAD HUSNAIN FRAZ
    SYED MUHAMMAD SAAD
    ALYAN SHAHID
    AHMAD ZAHEER

    EXE FILE IS IN X64 -> RELEASE
*/



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define GRID_W 322
#define GRID_H 647
#define BLOCK_SIZE 28
#define WINDOW_WIDTH 662
#define WINDOW_HEIGHT 692
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris", sf::Style::None);
sf::Font tetris_font;
unsigned int width;
unsigned int height;
int offsetx = 0, offsety = 0;
const int rows = GRID_W / BLOCK_SIZE;
const int cols = GRID_H / BLOCK_SIZE;

#include "./block.h"
#include "./Blocks.h"
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <string>

Block* blocks[rows];
Blocks* current_block;
Blocks* next_block;
Blocks* outline_block;
sf::Event event; // TO STORE EVENTS
sf::Music main_music, lose_music;
sf::SoundBuffer break_sound_buffer, move_sound_buffer, place_sound_buffer, menuselect_sound_buffer;
sf::Sound break_sound, move_sound, place_sound, menuselect_sound;
sf::Texture bg_t;
sf::Sprite bg;
text menuItem1, menuItem2, menuItem3, exitItem1;
bool windowdrag = false, game = false, onetimepress = true;
sf::Vector2i mouseoffset;
sf::Vector2i mousePos;
void make_drag(sf::Event e);
void display_grid();
void show_blocks();
void setGrid();
void end();
void boundry(Block b);
void ground();
void keyboard(sf::Event e);
void select(Blocks*& ptr);
void Break();
void poll_event();
void chk_end_game();
bool collides(Block b);
void do_outline();
void setup();
int player_score = 0;


int main()
{

    if (!tetris_font.loadFromFile("Tetris.ttf")) window.close(); // IF ERROR LOADING CLOSE WINDOW
    width = window.getSize().x;
    height = window.getSize().y;

    srand((int)time(0));
    setGrid();
    /*
    select(current_block);
    select(next_block);
    current_block->pos(3, 1);
    do_outline();
    */

    sf::Clock c1;
    sf::Time elapsed1;
    if (!main_music.openFromFile("./M1.mp3")) return -1;
    if (!lose_music.openFromFile("./LM1.mp3")) return -1;
    if (!move_sound_buffer.loadFromFile("./Move.wav")) return -1;
    if (!break_sound_buffer.loadFromFile("./Break.wav")) return -1;
    if (!place_sound_buffer.loadFromFile("./Place.wav")) return -1;
    if (!menuselect_sound_buffer.loadFromFile("./Menu.wav")) return -1;
    
    if (!bg_t.loadFromFile("bg.png")) return -1;
    bg.setTexture(bg_t);
    move_sound.setBuffer(move_sound_buffer);
    break_sound.setBuffer(break_sound_buffer);
    place_sound.setBuffer(place_sound_buffer);
    menuselect_sound.setBuffer(place_sound_buffer);
    main_music.setVolume(10);
    move_sound.setVolume(9);
    place_sound.setVolume(9);
    menuselect_sound.setVolume(10);
    // Create the menu items 
    menuItem1 = text("Start Game", 25, 254, 72, 25, 255);
    menuItem1.font(tetris_font);
    menuItem1.pos(250, 200);

    menuItem2 = text("Options", 25, 254, 72, 25, 255);
    menuItem2.font(tetris_font);
    menuItem2.pos(275, 300);

    menuItem3 = text("Exit", 25, 254, 72, 25, 255);
    menuItem3.font(tetris_font);
    menuItem3.pos(300, 400);


    exitItem1 = text("Main  Menu", 25, 254, 72, 25, 255);
    exitItem1.font(tetris_font);
    exitItem1.pos(GRID_W + 100, GRID_H - 137);

    while (window.isOpen()) // WHILE WINDOW IS OPEN
    {
        window.clear(sf::Color::Black);

        poll_event();
        window.draw(bg);
        // Draw the menu items
        menuItem1.draw();
        menuItem2.draw();
        menuItem3.draw();
        window.display();



        while (game)
        {
            elapsed1 = c1.getElapsedTime();
            window.clear(sf::Color::Black);


            poll_event();

            if (elapsed1.asMilliseconds() >= 450) {

                if (main_music.getStatus() != sf::Music::Status::Playing)
                    main_music.play();
                current_block->pos(current_block->i, current_block->j + 1);

                c1.restart();
            }

            for (int i = 0; i < current_block->blocks_amount; i++)
                boundry(*current_block->blocks[i]);
            Break();

            show_blocks();
            current_block->draw();
            display_grid();
            next_block->draw();
            outline_block->draw(2);
            exitItem1.draw();
            window.display();
            chk_end_game();
        }
    }


    return 0;
}

void poll_event()
{

    mousePos = sf::Mouse::getPosition();
    while (window.pollEvent(event)) // WHILE EVENTS 
    {


        make_drag(event);

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mp((float)mousePos.x, (float)mousePos.y);

        if (event.type == sf::Event::MouseMoved)
        {
            
            menuItem1.fill(254, 72, 25, 255);
            menuItem2.fill(254, 72, 25, 255);
            menuItem3.fill(254, 72, 25, 255);
            exitItem1.fill(254, 72, 25, 255);
            if (menuItem1.t.getGlobalBounds().contains(mp))
            {
                menuItem1.fill(255, 120, 65, 255);
            }
            else if (menuItem2.t.getGlobalBounds().contains(mp))
            {
                menuItem2.fill(255, 120, 65, 255);
            }
            else if (menuItem3.t.getGlobalBounds().contains(mp))
            {
                menuItem3.fill(255, 120, 65, 255);
            }
            else if (exitItem1.t.getGlobalBounds().contains(mp))
            {
                exitItem1.fill(255, 120, 65, 255);
            }
        }
        
           
       

        if (event.type == sf::Event::MouseButtonPressed)
        {

            if (event.mouseButton.button == sf::Mouse::Left)
            {

                if (menuItem1.t.getGlobalBounds().contains(mp))
                {
                    game = true;
                    setup();
                    if(menuselect_sound.getStatus() != sf::Sound::Playing)menuselect_sound.play();
                    main_music.play();

                }
                else if (menuItem2.t.getGlobalBounds().contains(mp))
                {
                    if (menuselect_sound.getStatus() != sf::Sound::Playing)menuselect_sound.play();
                }
                else if (menuItem3.t.getGlobalBounds().contains(mp))
                {
                    if (menuselect_sound.getStatus() != sf::Sound::Playing)menuselect_sound.play();
                    Sleep(100);
                    end();
                }
                else if (exitItem1.t.getGlobalBounds().contains(mp))
                {
                    setup();
                    if (menuselect_sound.getStatus() != sf::Sound::Playing)menuselect_sound.play();
                    game = false;
                }
            }
        }

        keyboard(event);
        if (event.type == sf::Event::Closed) end();
    }
}

void setup()
{
    main_music.stop();
    place_sound.stop();
    break_sound.stop();
    move_sound.stop();
    srand((int)time(0));
    setGrid();

    select(current_block);
    select(next_block);
    current_block->pos(3, 1);
    do_outline();
    player_score = 0;
  
}
void chk_end_game()
{

    for (int i = 2; i < 6; i++) {

        for (int j = 0; j < 2; j++) {
            if (blocks[i][j].alpha > 0)
            {
                game = false;
                main_music.stop();
                Sleep(200);
                lose_music.play();
                Sleep(3000);
                lose_music.stop();
                break;
            }
        }
        if (game == false)break;

    }
}

void boundry(Block b)
{
    if (b.i >= rows - 1)
    {
        current_block->pos(current_block->i - 1, current_block->j);
        move_sound.stop();
        do_outline();
    }
    if (b.i < 1) {
        current_block->pos(current_block->i + 1, current_block->j);
        move_sound.stop();
        do_outline();
    }
    if (b.j >= cols - 1)
    {
        current_block->pos(current_block->i, current_block->j - 1);
        move_sound.stop();
        ground();
    }
    else
    {
        if (collides(b))
        {
            current_block->pos(current_block->i, current_block->j - 1);
            move_sound.stop();
            ground();
        }
    }


}

bool collides(Block b)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (b.collides(blocks[i][j]) && blocks[i][j].alpha > 0) return 1;

        }
    }
    return 0;
}


void do_outline()
{

    outline_block = current_block->copy(current_block->state);
    outline_block->pos(current_block->i, current_block->j);
    bool has_collided = false;
    int amount = outline_block->blocks_amount;

    while (!has_collided)
    {
        outline_block->pos(outline_block->i, outline_block->j + 1);

        for (int i = 0; i < amount; i++)
        {
            Block b = *(outline_block->blocks[i]);
            if (b.j >= cols - 1 || collides(b))
            {
                has_collided = true;
                break;
            }
        }
    }
    outline_block->pos(outline_block->i, outline_block->j - 1);
}


void keyboard(sf::Event e)
{
    int changey = 0;
    int changex = 0;

    if (e.type == sf::Event::KeyReleased)
    {
        if (!onetimepress) onetimepress = true;

    }

    if (e.type == sf::Event::KeyPressed)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) end();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            changex = -1;
            move_sound.play();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            changex = 1;
            move_sound.play();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            changey = 1;
            player_score += 1;
            move_sound.play();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onetimepress)
        {
            bool can_rotate = true;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (blocks[current_block->i + i][current_block->j + j].alpha > 0)
                    {
                        can_rotate = false;
                        break;
                    }
                }
            }
            if (can_rotate)
            {
                onetimepress = false;
                current_block->rotate();
                current_block->setup();
            }
        }

        current_block->pos(current_block->i + changex, current_block->j + changey);
        do_outline();
        for (int i = 0; i < current_block->blocks_amount; i++) {
            Block b = *current_block->blocks[i];
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (b.collides(blocks[i][j]) && blocks[i][j].alpha > 0)
                    {

                        current_block->pos(current_block->i - changex, current_block->j - changey);
                        do_outline();
                        break;
                    }
                }
            }
        }



    }
}

void select(Blocks*& ptr)
{
    int type = rand() % 15;
    int x = 15;
    int y = 10;

    switch (type)
    {
    case 2:
    case 11:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new LLshape(x, y, BLOCK_SIZE, 72, 93, 197, 255);
        break;
    case 1:
    case 5:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new LRshape(x, y, BLOCK_SIZE, 254, 72, 25, 255);
        break;
    case 0:
    case 14:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new Sshape(x, y, BLOCK_SIZE, 254, 251, 52, 255);
        break;
    case 3:
    case 8:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new ZRshape(x, y, BLOCK_SIZE, 221, 10, 178, 255);
        break;
    case 4:
    case 10:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new ZLshape(x, y, BLOCK_SIZE, 83, 218, 63, 255);
        break;
    case 6:
    case 13:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        break;
    case 12:
    case 7:
    case 15:
        //current_block = new Ishape(x, y, BLOCK_SIZE, 1, 237, 250, 255);
        ptr = new Tshape(x, y, BLOCK_SIZE, 234, 20, 28, 255);
        break;
    default:
        ptr = new Tshape(x, y, BLOCK_SIZE, 234, 20, 28, 255);
        break;
    }
}

void ground()
{
    for (int i = 0; i < current_block->blocks_amount; i++)
    {
        blocks[current_block->blocks[i]->i][current_block->blocks[i]->j] = *(current_block->blocks[i]);
    }
    current_block = next_block;
    current_block->pos(3, 1);
    select(next_block);
    do_outline();
    place_sound.play();
}

void Break()
{
    int count = 0;
    int line_no = -1;
    for (int i = 0; i < cols; i++)
    {
        count = 0;
        for (int j = 0; j < rows; j++)
        {
            if (blocks[j][i].alpha > 0) count++;
        }
        if (count == 9) {
            player_score += 100;
            line_no = i;
            break;
        }
    }

    if (line_no >= 0 && count == 9)
    {
        for (int j = 0; j < rows; j++)
        {
            blocks[j][line_no] = NULL;
        }
        break_sound.play();
        line_no--;
        while (line_no > 0)
        {
            for (int j = 0; j < rows; j++)
            {
                blocks[j][line_no].set(blocks[j][line_no].i, blocks[j][line_no].j + 1);
                blocks[j][line_no + 1] = blocks[j][line_no];

            }
            line_no--;
        }
    }
}

void end()
{
    game = false;
    window.close();
}

void setGrid()
{
    for (int i = 0; i < rows; i++)
    {
        blocks[i] = new Block[cols];
    }
}


void show_blocks()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            blocks[i][j].draw();
        }
    }
}

void display_grid()
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1)
            {
                rect r((i * (BLOCK_SIZE + 2.0F) + 2.0F), (j * (BLOCK_SIZE + 2.0F) + 2.0F), BLOCK_SIZE, BLOCK_SIZE);
                r.fill(64, 64, 64, 255);
                r.stroke(30, 30, 30, 255);
                r.outline(2);
                r.draw();

            }
            else
            {
                rect r((i * (BLOCK_SIZE + 2.0F)) + 2.0F, (j * (BLOCK_SIZE + 2.0F)) + 2.0F, BLOCK_SIZE, BLOCK_SIZE);
                r.nofill();
                r.stroke(44, 166, 172, 70);
                r.outline(1);
                r.draw();
            }
        }
    }

    for (int i = rows; i < 25; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            //BLACK SQUARE RIGHT HAND SIDE OF SCREEN
            rect r((i * (BLOCK_SIZE + 2.0F) + 2.0F), (j * (BLOCK_SIZE + 2.0F) + 2.0F), BLOCK_SIZE, BLOCK_SIZE);
            r.stroke(44, 166, 172, 70);
            r.fill(44, 73, 102, 70);
            r.draw();

        }
    }

    {
        //LIGHTER SQUARE BEHIND NEXT SQUARE
        rect r(next_block->x - 50, next_block->y - 40, 200, 150);
        r.stroke(199, 0, 57, 150);
        r.fill(144, 12, 63, 150);
        r.outline(2);
        r.draw();

        text next("Next", 20, 72, 93, 197, 255);
        next.font(tetris_font);
        next.pos(next_block->x + 20, next_block->y - 90);
        next.draw();

    }
    int s = 40;
    float characx = GRID_W + s + 10.0F;
    float characy = (WINDOW_HEIGHT / 10);
    text tl("T", s, 72, 93, 197, 255);
    tl.font(tetris_font);
    tl.pos(characx, characy);
    characx += s;

    text el("E", s, 254, 72, 25, 255);
    el.font(tetris_font);
    el.pos(characx, characy);
    characx += s;

    text t1l("T", s, 254, 251, 52, 255);
    t1l.font(tetris_font);
    t1l.pos(characx, characy);
    characx += s;

    std::string s1 = "Score : ";
    std::string s2 = std::to_string(player_score);
    std::string sc = s1 + s2;
    text score(sc, 20, 72, 93, 197, 255);
    score.font(tetris_font);
    score.pos(characx - 50, characy + 80.0F);
    score.draw();

    text rl("R", s, 221, 10, 178, 255);
    rl.font(tetris_font);
    rl.pos(characx, characy);
    characx += s;

    text il("I", s, 83, 218, 63, 255);
    il.font(tetris_font);
    il.pos(characx, characy);
    characx += s;

    text sl("S", s, 234, 20, 28, 255);
    sl.font(tetris_font);
    sl.pos(characx, characy);
    characx += s;

    tl.draw();
    el.draw();
    t1l.draw();
    rl.draw();
    il.draw();
    sl.draw();
    score.draw();
}


void make_drag(sf::Event e)
{

    if (e.type == sf::Event::MouseButtonPressed && (mousePos.x >= window.getPosition().x && mousePos.y <= window.getPosition().x + (int)width) && (mousePos.y >= window.getPosition().y && mousePos.y <= window.getPosition().y + (int)height))
    {
        windowdrag = true;
        mouseoffset = mousePos;
    }
    else if (e.type == sf::Event::MouseMoved && windowdrag)
    {
        sf::Vector2i a;
        a = mousePos - mouseoffset;
        window.setPosition(window.getPosition() + a);
        mouseoffset = mousePos;
    }
    else if (e.type == sf::Event::MouseButtonReleased)
    {
        windowdrag = false;
    }

}