#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)
    {
        setPosition(position);

    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }
    void animate(const sf::Time &elapsed){
        bouncce();
        float dt = elapsed.asMicroseconds();
        move(x_speed_*dt,y_speed_*dt);
        rotate(ro_speed_*dt);
    }
    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }
    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key)
    {
        float dt = elapsed.asSeconds();
        if (key == sf::Keyboard::Left)
        {
           bouncce();
          move(-abs(x_speed_)*dt,0);
        }
        else if (key == sf::Keyboard::Right)
        {
            bouncce();
          move(abs(x_speed_)*dt,0);
        }
        else if (key == sf::Keyboard::Up){
            bouncce();
            move(0, -abs(y_speed_)*dt);
        }
        else if (key == sf::Keyboard::Down){
            bouncce();
            move(0, abs(y_speed_)*dt);
        }
    }

    bool isClicked(sf::Vector2i &mouse_position, sf::Vector2f &rec_position) const{

        sf::FloatRect rectangle_bounds = getGlobalBounds();
        float xrange = rectangle_bounds.width/2;
        float yrange = rectangle_bounds.height/2;
        if((mouse_position.x>= rec_position.x-xrange && mouse_position.x<= rec_position.x+xrange) &&
                (mouse_position.y>= rec_position.y-yrange && mouse_position.y<= rec_position.y+yrange))
        {
            return true;
        }

               return false;
    }

private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;


    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= l_bound_ ){
           x_speed_ = abs(x_speed_);
           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }


};


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Vector2f size(120.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle_inh(size, position);
    rectangle_inh.setFillColor(sf::Color(150, 100, 50));
    rectangle_inh.setSpeed(100, 150, 10);

    sf::Clock clock;
    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();

        rectangle_inh.setBounds(0, window.getSize().x, 0, window.getSize().y);

         // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2i mouse_position;
        if(event.type == sf::Event::KeyPressed){
            rectangle_inh.moveInDirection(elapsed, event.key.code);
        }
        else if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                mouse_position = sf::Mouse::getPosition(window);
            }
        }
 auto pos = rectangle_inh.getPosition();
        if(rectangle_inh.isClicked(mouse_position,pos)){
            rectangle_inh.setFillColor(sf::Color(rand() % 256,rand() % 256,rand() % 256));
        }


//
        // clear the window with black color
        window.clear(sf::Color::Black);
        // draw everything here...

        window.draw(rectangle_inh);
        // end the current frame
        window.display();
    }

    return 0;
}
