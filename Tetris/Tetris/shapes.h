#pragma once
class text : public sf::Text
{
public:
    sf::Text t;
    text(std::string s = "Hello World", unsigned int size = 20, sf::Uint8 r = 255, sf::Uint8 g = 255, sf::Uint8 b = 255, sf::Uint8 a = 255)
    {
        t.setFont(tetris_font);
        t.setString(s);
        t.setCharacterSize(size);
        t.setFillColor(sf::Color(r, g, b, a));
    }
    void fill(sf::Uint8 r = 255, sf::Uint8 g = 255, sf::Uint8 b = 255, sf::Uint8 a = 255)
    {
        t.setFillColor(sf::Color(r, g, b, a));
    }
    void pos(float x, float y) {
        t.setPosition(x, y);
    }
    void font(sf::Font& f)
    {
        t.setFont(f);
    }
    void draw()
    {
        window.draw(t);
    }
};

class rect : public sf::RectangleShape
{
public:
    sf::RectangleShape R;
    rect(float x=0, float y=0, float w=0, float h=0)
    {
        R.setPosition(sf::Vector2f(x, y));
        R.setSize(sf::Vector2f(w, h));
    }

    void size(float w, float h)
    {
        R.setSize(sf::Vector2f(w, h));
    }

    void stroke(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
    {
        R.setOutlineThickness(1);
        R.setOutlineColor(sf::Color(r, g, b, a));
    }
    void outline(float size)
    {
        R.setOutlineThickness(size);
    }
    void nostroke()
    {
        R.setOutlineThickness(0);
        R.setOutlineColor(sf::Color::Transparent);
    }

    void nofill()
    {
        R.setFillColor(sf::Color::Transparent);
    }

    void fill(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
    {

        R.setFillColor(sf::Color(r, g, b, a));
    }

    void draw()
    {
        window.draw(R);
    }

    void pos(float x, float y)
    {
        R.setPosition(sf::Vector2f(x, y));
    }

  

};
