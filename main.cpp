#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define DTR  0.0174532925     // change degrees to radians


class Game_objects : public sf::Sprite
{
public:
sf::Texture texture_;
sf:: Sprite sprite_;
bool is_alive_;
float move_x;
float move_y;
public:

    Game_objects(const std::string &filename){
    texture_.loadFromFile(filename);
    texture_.setRepeated(true);
    texture_.setSmooth(true);
    sprite_.setTexture(texture_);
    is_alive_ = true;
    };
    void _move(float x, float y, float r = 0){
        sprite_.move(x,y);
        sprite_.rotate(r);
    }
    void _draw(sf::RenderWindow &w){
        w.draw(sprite_);
    }
    void _setPosition(float x, float y){
        sprite_.setPosition(x, y);
    }
    void _getPosition(Game_objects *g){
        sprite_.setPosition(g->sprite_.getPosition().x, g->sprite_.getPosition().y);
    }
    void setMove(sf::RenderWindow &w){
        int value = rand() % 4;
        if(value == 0){
        sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
        move_x = -8;
        move_y = 0;
        }
        if(value == 1){
        sprite_.setPosition(rand()%w.getSize().x, 0);
        move_x = 0;
        move_y = 8;
        }
        if(value == 2){
        sprite_.setPosition(0, rand()%w.getSize().y);
        move_x = 8;
        move_y = 0;
        }
        if(value == 3){
        sprite_.setPosition(rand()%w.getSize().x, w.getSize().y);
        move_x = 0;
        move_y = -8;
        }
    }
    void outsideObject(sf::RenderWindow &w){
        if(sprite_.getPosition().x < 0){
        _setPosition(w.getSize().x, rand()%w.getSize().y);
        }
        if(sprite_.getPosition().x > w.getSize().x){
        _setPosition(0, rand()%w.getSize().y);
        }
        if(sprite_.getPosition().y > w.getSize().y){
        _setPosition(rand()%w.getSize().x, 0);
        }
        if(sprite_.getPosition().y < 0){
        _setPosition(rand()%w.getSize().x, w.getSize().y);
        }
    }
};


class Spacecraft : public Game_objects
{
public:
    int angle = 0;
    int hp_;
    int bulletPower_;
    Spacecraft(const std::string filename) : Game_objects(filename){
        texture_.loadFromFile(filename);
        sprite_.setTexture(texture_);
        is_alive_ = true;
        hp_ = 100;
        bulletPower_ = 20;
    }
};

class Asteroid : public Game_objects
{
public:

    bool is_indestructible_;
    int asteroidPower_;
    Asteroid(const std::string &filename, bool is_indestructible = false) :  Game_objects(filename), is_indestructible_(is_indestructible){
        is_alive_ = true;
        asteroidPower_ = 50;
    };

};

class Bullet : public Game_objects
{
public:

    int powerSpaceCraft_;
    int powerEnemy_;
    Bullet(const std::string &filename, int powerSpaceCraft = 20, int powerEnemy = 10) : Game_objects(filename), powerSpaceCraft_(powerSpaceCraft), powerEnemy_(powerEnemy){
        is_alive_ = true;
    };
    void removeBulletsOverWindow(std::vector<Bullet*> &v, sf::RenderWindow &w){
        if (sprite_.getPosition().x < 0 || sprite_.getPosition().x > w.getSize().x || sprite_.getPosition().y < 0
                || sprite_.getPosition().y > w.getSize().y){
            v.erase(v.begin());
        }
    }

};

class EnemyShip : public Game_objects
{
public:
    int hp_;
    float bulletsMoveX_;
    float bulletsMoveY_;
    EnemyShip(const std::string filename) : Game_objects(filename){
        is_alive_ = true;
        hp_ = 100;
    };
    void setMoveEnemy(Spacecraft *s, sf::RenderWindow &w){
        int value = rand() % 4;
        if(value == 0){
        sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
        bulletsMoveX_ = -5;
        bulletsMoveY_ = 0;
        move_x = -5;
        if (s->sprite_.getPosition().y > sprite_.getPosition().y){
        move_y = 5;
        }
        if (s->sprite_.getPosition().y < sprite_.getPosition().y){
        move_y = -5;
        }
        if (s->sprite_.getPosition().y == sprite_.getPosition().y){
        move_y = 0;
        }
        }
        if(value == 1){
        sprite_.setPosition(rand()%w.getSize().x, 0);
        sprite_.rotate(270);
        bulletsMoveX_ = 0;
        bulletsMoveY_ = 5;
        if (s->sprite_.getPosition().x > sprite_.getPosition().y){
        move_x = 5;
        }
        if (s->sprite_.getPosition().y < sprite_.getPosition().y){
        move_x = -5;
        }
        if (s->sprite_.getPosition().y == sprite_.getPosition().y){
        move_x = 0;
        }
        move_y = 5;
        }
        if(value == 2){
        sprite_.setPosition(0, rand()%w.getSize().y);
        sprite_.rotate(180);
        bulletsMoveX_ = 5;
        bulletsMoveY_ = 0;
        move_x = -5;
        sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
        move_x = -5;
        if (s->sprite_.getPosition().y > sprite_.getPosition().y){
        move_y = 5;
        }
        if (s->sprite_.getPosition().y < sprite_.getPosition().y){
        move_y = -5;
        }
        if (s->sprite_.getPosition().y == sprite_.getPosition().y){
        move_y = 0;
        }
        }
        if(value == 3){
        sprite_.setPosition(rand()%w.getSize().x, w.getSize().y);
        sprite_.rotate(90);
        bulletsMoveX_ = 0;
        bulletsMoveY_ = -5;
        if (s->sprite_.getPosition().x > sprite_.getPosition().y){
        move_x = 5;
        }
        if (s->sprite_.getPosition().y < sprite_.getPosition().y){
        move_x = -5;
        }
        if (s->sprite_.getPosition().y == sprite_.getPosition().y){
        move_x = 0;
        }
        move_y = -5;
        }
    }
    void UpdateRotation(sf::RenderWindow &w){
        if(sprite_.getPosition().x < 0){
        _setPosition(w.getSize().x, rand()%w.getSize().y);
        }
        if(sprite_.getPosition().x > w.getSize().x){
        _setPosition(0, rand()%w.getSize().y);
        }
        if(sprite_.getPosition().y > w.getSize().y){
        _setPosition(rand()%w.getSize().x, 0);
        }
        if(sprite_.getPosition().y < 0){
        _setPosition(rand()%w.getSize().x, w.getSize().y);
        }
    }
};

class Gift : public Game_objects
{
public:
int updateHp_;
int updateBullet_;
Gift (const std::string filename, int updateHp = 0, int updateBullet = 0) : Game_objects(filename), updateHp_(updateHp), updateBullet_(updateBullet){
    is_alive_ = true;
};
void setRandomPosition(sf::RenderWindow &w){
    sprite_.setPosition(rand() % w.getSize().x, rand() % w.getSize().y);
};


};

void intersect_spacecraft_gift(Spacecraft *s, Gift *g){
    if (s->sprite_.getGlobalBounds().intersects(g->sprite_.getGlobalBounds()) && s->is_alive_ && g-> is_alive_){
        s->hp_ += g->updateHp_;
        s->bulletPower_ += g->updateBullet_;
        g->is_alive_ = false;
    }
}

void intersects_spacecraft_asteroid(Spacecraft *s, std::vector<Asteroid*> &a){
    for(size_t i = 0; i < a.size(); i++){
       if(s->sprite_.getGlobalBounds().intersects(a.at(i)->sprite_.getGlobalBounds()) && s->is_alive_ && a.at(i)->is_alive_){
           s->hp_ -= a.at(i)->asteroidPower_;
           a.at(i)->is_alive_ = false;
       }}
        if(s->hp_ <= 0){
        s->is_alive_ = false;
        std::cout << "Game over!" << std::endl;
       }
}
void intersects_spacecraft_bullet(Spacecraft *s, std::vector<Bullet*> &b){
    for(size_t i = 0; i < b.size(); i++){
       if(s->sprite_.getGlobalBounds().intersects(b.at(i)->sprite_.getGlobalBounds()) && s->is_alive_ && b.at(i)->is_alive_){
           s->hp_ -= b.at(i)->powerEnemy_;
           b.at(i)->is_alive_ = false;
       }}
       if(s->hp_ <= 0){
           s->is_alive_ = false;
           std::cout << "Game over!" << std::endl;
       }
}
void intersects_spacecraft_enemy(Spacecraft *s, std::vector<EnemyShip*> &e){
    for(size_t i = 0; i < e.size(); i++){
       if(s->sprite_.getGlobalBounds().intersects(e.at(i)->sprite_.getGlobalBounds()) && s->is_alive_ && e.at(i)->is_alive_){
       s->is_alive_ = false;
       e.at(i)->is_alive_ = false;
       std::cout << "Game over!" << std::endl;
       }}
}

void intersects_bullets_enemies(Bullet *b, std::vector<EnemyShip*> &e){
    for(size_t i = 0; i < e.size(); i++){
       if(b->sprite_.getGlobalBounds().intersects(e.at(i)->sprite_.getGlobalBounds()) && b->is_alive_ && e.at(i)->is_alive_){
           b->is_alive_ = false;
           e.at(i)->hp_ -= b->powerSpaceCraft_;
           std::cout << "trafiono" << std::endl;
       if(e.at(i)->hp_ <= 0){
           e.at(i)->is_alive_ = false;
           e.erase(e.begin()+i);
       }
       }}
}
void intersects_bullets_bullets(Bullet *b, std::vector<Bullet*> &bul){
    for(size_t i = 0; i < bul.size(); i++){
       if(b->sprite_.getGlobalBounds().intersects(bul.at(i)->sprite_.getGlobalBounds()) && b->is_alive_ && bul.at(i)->is_alive_){
           b->is_alive_ = false;
           bul.at(i)->is_alive_ = false;}}
}
void intersects_bullet_asteroids(Bullet *b, std::vector<Asteroid*> &a){
 for(size_t i = 0; i < a.size(); i++){
    if(b->sprite_.getGlobalBounds().intersects(a.at(i)->sprite_.getGlobalBounds()) && b->is_alive_){
        auto item = a.begin()+i;
        a.erase(item);
        b->is_alive_ = false;
        std::cout << "Colisions" << std::endl;
    }}}

void intersects_asteroidIndestructible_enemies(Asteroid *a, std::vector<EnemyShip*> &e){
    for(size_t i = 0; i < e.size(); i++){
       if(a->sprite_.getGlobalBounds().intersects(e.at(i)->sprite_.getGlobalBounds()) && e.at(i)->is_alive_){
           e.at(i)->is_alive_ = false;
           e.erase(e.begin()+i);
           std::cout << "trafiono" << std::endl;
       }}
}
void intersects_asteroidIndestructible_bullets(Asteroid *a, std::vector<Bullet*> &b){
    for(size_t i = 0; i < b.size(); i++){
       if(a->sprite_.getGlobalBounds().intersects(b.at(i)->sprite_.getGlobalBounds()) && b.at(i)->is_alive_){
           b.at(i)->is_alive_ = false;
           std::cout << "trafiono" << std::endl;
       }}
}
void intersects_asteroidIndestructible_asteroids(Asteroid *a, std::vector<Asteroid*> &ast){
    for(size_t i = 0; i < ast.size(); i++){
       if(a->sprite_.getGlobalBounds().intersects(ast.at(i)->sprite_.getGlobalBounds()) && ast.at(i)->is_alive_){
           ast.at(i)->is_alive_ = false;
           ast.erase(ast.begin()+i);
           std::cout << "trafiono" << std::endl;
       }}
}
void intersects_asteroidIndestructible_spacecraft(Asteroid *a, Spacecraft *s){
       if(a->sprite_.getGlobalBounds().intersects(s->sprite_.getGlobalBounds()) && s->is_alive_){
           s->is_alive_ = false;
           s->hp_ = 0;
           std::cout << "Game over!" << std::endl;
       }}

int main(){

int length_of_window = 1500;
int height_of_window = 1100;
int ang = 3;
sf::RenderWindow window(sf::VideoMode(length_of_window, height_of_window), "Space Aventure!");
sf::Clock clock;

sf::Texture background;
background.loadFromFile("background1.png");
background.setRepeated(true);
sf::Sprite sprite_background;
sprite_background.setTexture(background);
sprite_background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));


float accumulated_time = 0;
float accumulated_time1 = 0;
float accumulated_time2 = 0;
float accumulated_time3 = 0;

std::vector<Bullet*> bullets;
std::vector<Bullet*> bullets_enemy;
std::vector<Asteroid*> asteroids;
std::vector<Asteroid*> asteroids_indestructible;
std::vector<EnemyShip*> enemies;
std::vector<Gift*> gifts;


Spacecraft *s = new Spacecraft("spacecraft.png");
s->sprite_.setRotation(90);
s->sprite_.setPosition(window.getSize().x/2, window.getSize().y/2);


//Gift *g = new Gift("update_bullet.png", 50);
//g->setRandomPosition(window);

while (window.isOpen()) {

    bool move_u = false;
    bool move_d = false;


    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
        window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W ){
        move_u = true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S ){
        move_d = true;
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D){
        s->angle += ang;
        s->sprite_.rotate(ang);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A ){
        s->angle -= ang;
        s->sprite_.rotate(-ang);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
        Bullet *b = new Bullet("bullet.png", s->bulletPower_);
        b->sprite_.setPosition(s->sprite_.getPosition().x, s->sprite_.getPosition().y - 10);
        b->move_x = 10*cos(s->angle*DTR);
        b->move_y = 10*sin(s->angle*DTR);
        bullets.emplace_back(b);

        }
    }
window.setFramerateLimit(30);
window.clear(sf::Color::Black);
window.draw(sprite_background);

s->sprite_.setOrigin(18, 25);
if(move_u){
s->sprite_.move(10*cos(s->angle*DTR), 10*sin(s->angle*DTR));
}
if(move_d){
s->sprite_.move(-10*cos(s->angle*DTR), -10*sin(s->angle*DTR));
}
if(s->hp_ < 90 && gifts.size() < 1){
Gift *g = new Gift("live.png", 50);
g->setRandomPosition(window);
gifts.emplace_back(g);
}

//std::cout << s->sprite_.getOrigin().x << " ; " << s->sprite_.getOrigin().y << std::endl;
if(asteroids.size() < 5 && accumulated_time > 100){
    Asteroid *a = new Asteroid("asteroid.png");
    a->setMove(window);
    asteroids.emplace_back(a);
    accumulated_time = 0;
}
else{
    accumulated_time += clock.getElapsedTime().asSeconds();
}
if(asteroids_indestructible.size() < 4 && accumulated_time3 > 300){
    Asteroid *ain = new Asteroid("asteroid_indestructible.png", true);
    ain->setMove(window);
    asteroids_indestructible.emplace_back(ain);
    accumulated_time3 = 0;
}
else{
    accumulated_time3 += clock.getElapsedTime().asSeconds();
}
if(enemies.size() < 2 && accumulated_time1 > 1000 ){
    EnemyShip *e = new EnemyShip("enemy.png");
    e->setMoveEnemy(s, window);
    enemies.emplace_back(e);
    accumulated_time1 = 0;

}
else{
    accumulated_time1 += clock.getElapsedTime().asSeconds();
//    std::cout << accumulated_time1 << std::endl;
//    std::cout << "enemies size: " <<enemies.size() << std::endl;
}
if( accumulated_time2 > 1000){
    for(auto *e : enemies){
    Bullet *be = new Bullet("bullet_enemy.png");
    be->_getPosition(e);
    be->move_x = e->bulletsMoveX_;
    be->move_y = e->bulletsMoveY_;
    bullets_enemy.emplace_back(be);
        }
accumulated_time2 = 0;
}
else{
    accumulated_time2 += clock.getElapsedTime().asSeconds();
}


if(s->is_alive_){
for(auto *b : bullets){
   b->sprite_.move(b->move_x, b->move_y);
   b->removeBulletsOverWindow(bullets, window);
   if(b->is_alive_){
   b->_draw(window);
   }
   intersects_bullet_asteroids(b, asteroids);
   intersects_bullets_enemies(b, enemies);
   intersects_bullets_bullets(b, bullets_enemy);
}}
for( size_t i = 0; i < gifts.size(); i++){
if(gifts.at(i)->is_alive_){
gifts.at(i)->_draw(window);
}
intersect_spacecraft_gift(s , gifts.at(i));
if(!gifts.at(i)->is_alive_){
    gifts.erase(gifts.begin()+i);
}}


for(auto *a : asteroids){
   a->sprite_.move(a->move_x,a->move_y);
   if(a->is_alive_){
   a->_draw(window);
   }
   a->outsideObject(window);
//   if(a->sprite_.getPosition().x < 0){
//   a->_setPosition(length_of_window, rand()%height_of_window);
//   }
//   if(a->sprite_.getPosition().x > length_of_window){
//   a->_setPosition(0, rand()%height_of_window);
//   }
//   if(a->sprite_.getPosition().y > height_of_window){
//   a->_setPosition(rand()%length_of_window, 0);
//   }
//   if(a->sprite_.getPosition().y < 0){
//   a->_setPosition(rand()%length_of_window, height_of_window);
//   }
}
for(auto *ain : asteroids_indestructible){
    ain->sprite_.move(ain->move_x,ain->move_y);
    ain->_draw(window);
    ain->outsideObject(window);
    intersects_asteroidIndestructible_enemies(ain, enemies);
    intersects_asteroidIndestructible_asteroids(ain, asteroids);
    intersects_asteroidIndestructible_bullets(ain, bullets);
    intersects_asteroidIndestructible_bullets(ain, bullets_enemy);
    intersects_asteroidIndestructible_spacecraft(ain, s);
}

for(auto *e : enemies){
//   if(s->sprite_.getPosition().y < e->sprite_.getPosition().y){
//   e->_move(-3,-3);
//   }
//   if(s->sprite_.getPosition().y == e->sprite_.getPosition().y){
//   e->_move(-1,0);
//   }
//   if(s->sprite_.getPosition().y > e->sprite_.getPosition().y){
//   e->_move(-3,3);
//   }
   e->sprite_.move(e->move_x, e->move_y);
   if(e->is_alive_){
   e->_draw(window);
   }
   e->outsideObject(window);
//   if(e->sprite_.getPosition().x < 0){
//   e->_setPosition(length_of_window, rand()%height_of_window);
//   }
}
for(auto *be : bullets_enemy){
  be->sprite_.move(1.5*be->move_x, 1.5*be->move_y);
  if(be->is_alive_){
  be->_draw(window);
  }
  be->removeBulletsOverWindow(bullets_enemy, window);
}

std::cout << "bullets size" << bullets.size() << std::endl;
std::cout << "bullets_enemy size" << bullets_enemy.size() << std::endl;

//intersects_spacecraft_object(s, asteroids);

intersects_spacecraft_asteroid(s, asteroids);
intersects_spacecraft_bullet(s, bullets_enemy);
intersects_spacecraft_enemy(s, enemies);
if(s->is_alive_){
s->_draw(window);
}

std::cout <<"s -> hp: " << s->hp_ << std::endl;

window.display();

}

return 0;
}
