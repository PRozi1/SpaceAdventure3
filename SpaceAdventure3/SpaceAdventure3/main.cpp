#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define DTR  0.0174532925     // zamiana stopni na radiany

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
    void setMove(sf::RenderWindow &w, std::vector<int> p){
        int value = rand() % 4;
        if(value == 0){
            sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
            move_x = -p.at(12);
            move_y = 0;
        }
        if(value == 1){
            sprite_.setPosition(rand()%w.getSize().x, 0);
            move_x = 0;
            move_y = p.at(12);
        }
        if(value == 2){
            sprite_.setPosition(0, rand()%w.getSize().y);
            move_x = p.at(12);
            move_y = 0;
        }
        if(value == 3){
            sprite_.setPosition(rand()%w.getSize().x, w.getSize().y);
            move_x = 0;
            move_y = -p.at(12);
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
        //  bulletPower_ = 20;
    }
};

class Asteroid : public Game_objects
{
public:

    bool is_indestructible_;
    int asteroidPower_;
    int asteroidPowerInestructible_;
    Asteroid(const std::string &filename, bool is_indestructible = false) :  Game_objects(filename), is_indestructible_(is_indestructible){
        is_alive_ = true;
    };
    void setMoveAsteroidIndesctutibile(sf::RenderWindow &w, std::vector<int> p){
        int value = rand() % 4;
        if(value == 0){
            sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
            move_x = -p.at(13);
            move_y = 0;
        }
        if(value == 1){
            sprite_.setPosition(rand()%w.getSize().x, 0);
            move_x = 0;
            move_y = p.at(13);
        }
        if(value == 2){
            sprite_.setPosition(0, rand()%w.getSize().y);
            move_x = p.at(13);
            move_y = 0;
        }
        if(value == 3){
            sprite_.setPosition(rand()%w.getSize().x, w.getSize().y);
            move_x = 0;
            move_y = -p.at(13);
        }
    }
    void setMoveAsteroid(sf::RenderWindow &w, std::vector<int> p){
        int value = rand() % 4;
        if(value == 0){
            sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
            move_x = -p.at(12);
            move_y = 0;
        }
        if(value == 1){
            sprite_.setPosition(rand()%w.getSize().x, 0);
            move_x = 0;
            move_y = p.at(12);
        }
        if(value == 2){
            sprite_.setPosition(0, rand()%w.getSize().y);
            move_x = p.at(12);
            move_y = 0;
        }
        if(value == 3){
            sprite_.setPosition(rand()%w.getSize().x, w.getSize().y);
            move_x = 0;
            move_y = -p.at(12);
        }
    }
};

class Bullet : public Game_objects
{
public:

    int powerSpaceCraft_;
    int powerEnemy_;
    Bullet(const std::string &filename, int powerSpaceCraft = 0, int powerEnemy = 0) : Game_objects(filename), powerSpaceCraft_(powerSpaceCraft), powerEnemy_(powerEnemy){
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
    int EnemyShipPower_;
    float bulletsMoveX_;
    float bulletsMoveY_;
    EnemyShip(const std::string filename) : Game_objects(filename){
        is_alive_ = true;
        hp_ = 100;
        EnemyShipPower_ = 60;
    };
    void setMoveEnemy(Spacecraft *s, sf::RenderWindow &w, std::vector<int> &p){
        int value = rand() % 4;
        if(value == 0){
            sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
            bulletsMoveX_ = -p.at(14);
            bulletsMoveY_ = 0;
            move_x = -p.at(13);
            if (s->sprite_.getPosition().y > sprite_.getPosition().y){
                move_y = p.at(13);
            }
            if (s->sprite_.getPosition().y < sprite_.getPosition().y){
                move_y = -p.at(13);
            }
            if (s->sprite_.getPosition().y == sprite_.getPosition().y){
                move_y = 0;
            }
        }
        if(value == 1){
            sprite_.setPosition(rand()%w.getSize().x, 0);
            sprite_.rotate(270);
            bulletsMoveX_ = 0;
            bulletsMoveY_ = p.at(14);
            if (s->sprite_.getPosition().x > sprite_.getPosition().y){
                move_x = p.at(13);
            }
            if (s->sprite_.getPosition().y < sprite_.getPosition().y){
                move_x = -p.at(13);
            }
            if (s->sprite_.getPosition().y == sprite_.getPosition().y){
                move_x = 0;
            }
            move_y = p.at(13);
        }
        if(value == 2){
            sprite_.setPosition(0, rand()%w.getSize().y);
            sprite_.rotate(180);
            bulletsMoveX_ = p.at(14);
            bulletsMoveY_ = 0;
            move_x = -p.at(13);
            sprite_.setPosition(w.getSize().x, rand()%w.getSize().y);
            move_x = -p.at(13);
            if (s->sprite_.getPosition().y > sprite_.getPosition().y){
                move_y = p.at(13);
            }
            if (s->sprite_.getPosition().y < sprite_.getPosition().y){
                move_y = -p.at(13);
            }
            if (s->sprite_.getPosition().y == sprite_.getPosition().y){
                move_y = 0;
            }
        }
        if(value == 3){
            sprite_.setPosition(rand()%w.getSize().x, w.getSize().y);
            sprite_.rotate(90);
            bulletsMoveX_ = 0;
            bulletsMoveY_ = -p.at(14);
            if (s->sprite_.getPosition().x > sprite_.getPosition().y){
                move_x = p.at(13);
            }
            if (s->sprite_.getPosition().y < sprite_.getPosition().y){
                move_x = -p.at(13);
            }
            if (s->sprite_.getPosition().y == sprite_.getPosition().y){
                move_x = 0;
            }
            move_y = -p.at(13);
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
     //   std::cout << "Game over!" << std::endl;
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
       // std::cout << "Game over!" << std::endl;
    }
}
void intersects_spacecraft_enemy(Spacecraft *s, std::vector<EnemyShip*> &e){
    for(size_t i = 0; i < e.size(); i++){
        if(s->sprite_.getGlobalBounds().intersects(e.at(i)->sprite_.getGlobalBounds()) && s->is_alive_ && e.at(i)->is_alive_){
            s->hp_ -= e.at(i)->EnemyShipPower_;
            e.at(i)->is_alive_ = false;
            if(s->hp_ <= 0){
                s->is_alive_ = false;
               // std::cout << "Game over!" << std::endl;
            }
        }}
}

void intersects_bullets_enemies(Bullet *b, std::vector<EnemyShip*> &e){
    for(size_t i = 0; i < e.size(); i++){
        if(b->sprite_.getGlobalBounds().intersects(e.at(i)->sprite_.getGlobalBounds()) && b->is_alive_ && e.at(i)->is_alive_){
            b->is_alive_ = false;
            e.at(i)->hp_ -= b->powerSpaceCraft_;
           // std::cout << "trafiono" << std::endl;
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
            //std::cout << "Colisions" << std::endl;
        }}}

void intersects_asteroidIndestructible_enemies(Asteroid *a, std::vector<EnemyShip*> &e){
    for(size_t i = 0; i < e.size(); i++){
        if(a->sprite_.getGlobalBounds().intersects(e.at(i)->sprite_.getGlobalBounds()) && e.at(i)->is_alive_){
            e.at(i)->is_alive_ = false;
            e.erase(e.begin()+i);
            //std::cout << "trafiono" << std::endl;
        }}
}
void intersects_asteroidIndestructible_bullets(Asteroid *a, std::vector<Bullet*> &b){
    for(size_t i = 0; i < b.size(); i++){
        if(a->sprite_.getGlobalBounds().intersects(b.at(i)->sprite_.getGlobalBounds()) && b.at(i)->is_alive_){
            b.at(i)->is_alive_ = false;
           // std::cout << "trafiono" << std::endl;
        }}
}
void intersects_asteroidIndestructible_asteroids(Asteroid *a, std::vector<Asteroid*> &ast){
    for(size_t i = 0; i < ast.size(); i++){
        if(a->sprite_.getGlobalBounds().intersects(ast.at(i)->sprite_.getGlobalBounds()) && ast.at(i)->is_alive_){
            ast.at(i)->is_alive_ = false;
            ast.erase(ast.begin()+i);
         //   std::cout << "trafiono" << std::endl;
        }}
}
void intersects_asteroidIndestructible_spacecraft(Asteroid *a, Spacecraft *s){
    if(a->sprite_.getGlobalBounds().intersects(s->sprite_.getGlobalBounds()) && s->is_alive_){
        s->hp_ -= a->asteroidPowerInestructible_;
        if(s->hp_ <= 0){
            s->is_alive_ = false;

            //std::cout << "Game over!" << std::endl;
        }}}



std::vector<int> loadParametesFromFile(const std::string &filename){
    std::vector<int> parameters;
    std::fstream file;
    int skip_line = 0;
    int parameter;
    std::string line;
    file.open(filename, std::ios::in);
    if(file.good() == true)
    {
        while(!file.eof())
        {
            for(int i = 0; i <= skip_line; i++){
                std::getline(file,line);
            }
            std::getline(file,line);
            parameter = std::stoi(line);
            parameters.emplace_back(parameter);
        }
        file.close();
    }
    else{
        std::cout<< "NIE UDALO SIE WCZYTAC PLIKU" << std::endl;
    }
    return parameters;
}

std::vector<int> chooseLevel(sf::Sprite &s1,sf::Sprite &s2, sf::Sprite &s3, sf::Vector2f &mp){
    std::vector<int> parameters;
    sf::FloatRect Bounds1 = s1.getGlobalBounds();
    sf::FloatRect Bounds2 = s2.getGlobalBounds();
    sf::FloatRect Bounds3 = s3.getGlobalBounds();
    if(mp.x < Bounds1.left + Bounds1.width && mp.x > Bounds1.left &&
            mp.y < Bounds1.top + Bounds1.height && mp.y > Bounds1.height){
        parameters = loadParametesFromFile("level_easy.txt");
    }
    else if(mp.x < Bounds2.left + Bounds2.width && mp.x > Bounds2.left &&
            mp.y < Bounds2.top + Bounds2.height && mp.y > Bounds2.height){
        parameters = loadParametesFromFile("level_medium.txt");
    }
    else if(mp.x < Bounds3.left + Bounds3.width && mp.x > Bounds3.left &&
            mp.y < Bounds3.top + Bounds3.height && mp.y > Bounds3.height){
        parameters = loadParametesFromFile("level_hard.txt");
    }
    return parameters;
}


std::vector<int>loadParametgers(){
    sf::Font font;
    font.loadFromFile("Times_New_Normal_Regular.ttf");

    sf::RenderWindow begin_window(sf::VideoMode(1000, 800), "Welcome in my game!");

    sf::Texture image1;
    image1.loadFromFile("legenda.png");
    sf::Sprite image1_;
    image1_.setTexture(image1);

    sf::Texture image2;
    image2.loadFromFile("sterowanie.png");
    sf::Sprite image2_;
    image2_.setTexture(image2);

    sf::Texture levelEasy;
    levelEasy.loadFromFile("LEVEL_EASY.png");
    sf::Sprite levelEasy_;
    levelEasy_.setTexture(levelEasy);
    levelEasy_.setOrigin(200, 50);
    levelEasy_.setPosition(505, 300);


    sf::Texture levelMedium;
    levelMedium.loadFromFile("LEVEL_MEDIUM.png");
    sf::Sprite levelMedium_;
    levelMedium_.setTexture(levelMedium);
    levelMedium_.setOrigin(200, 50);
    levelMedium_.setPosition(500, 450);

    sf::Texture levelHard;
    levelHard.loadFromFile("LEVEL_HARD.png");
    sf::Sprite levelHard_;
    levelHard_.setTexture(levelHard);
    levelHard_.setOrigin(200, 50);
    levelHard_.setPosition(520, 600);


    int licznik_image = 0;
    std::vector<int> parameters;
    sf::Vector2f mouse_position;

    bool skip_image;

    while (begin_window.isOpen()) {
        skip_image = false;
        sf::Event event;
        while (begin_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                begin_window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && licznik_image > 1 ){
                mouse_position = begin_window.mapPixelToCoords(sf::Mouse::getPosition(begin_window));
                begin_window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter ){
                skip_image = true;
                licznik_image++;
            }
        }

        begin_window.clear(sf::Color::Black);
        begin_window.setFramerateLimit(30);

        sf::Text text;
        text.setString("WYBIERZ POZIOM GRY");
        text.setPosition(300, 70);
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(40);
        text.setStyle(sf::Text::Bold);

        sf::Text text1;
        text1.setString("Wybierz uzywajac LEWEGO przycisku myszy");
        text1.setPosition(250, 700);
        text1.setFont(font);
        text1.setFillColor(sf::Color::White);
        text1.setCharacterSize(25);
        text1.setStyle(sf::Text::Bold);

        if(licznik_image == 0){
            begin_window.draw(image1_);
        }
        if(licznik_image == 1){
            begin_window.draw(image2_);
        }
        if(licznik_image > 1){

            begin_window.draw(levelEasy_);
            begin_window.draw(levelMedium_);
            begin_window.draw(levelHard_);

            begin_window.draw(text);
            begin_window.draw(text1);

            parameters = chooseLevel(levelEasy_, levelMedium_, levelHard_, mouse_position);
        }
        begin_window.display();

//        for(size_t i = 0; i < parameters.size(); i++){
//            parameters.at(i) = parameters.at(i);
//            std::cout << parameters.at(i) << " --" << std::endl;

//        }
    }
    return parameters;
};

int loop_game(std::vector<int> &parameters){
    int score = 0;
    int length_of_window = 1400;
    int height_of_window = 900;
    int ang = 3;
    sf::RenderWindow end_window(sf::VideoMode(800, 500), "Try again");
    sf::RenderWindow window(sf::VideoMode(length_of_window, height_of_window), "Space Aventure!");
    sf::Font font;
    font.loadFromFile("Times_New_Normal_Regular.ttf");


    sf::Clock clock;

    sf::Texture background;
    background.loadFromFile("background2.png");
    background.setRepeated(true);
    sf::Sprite sprite_background;
    sprite_background.setTexture(background);
    sprite_background.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    float delay_asteroid = 0;
    float delay_enemyCraft = 0;
    float delay_bulletEnemy = 0;
    float delay_asteroidInd = 0;
    int licznik = 0;

    std::vector<Bullet*> bullets;
    std::vector<Bullet*> bullets_enemy;
    std::vector<Asteroid*> asteroids;
    std::vector<Asteroid*> asteroids_indestructible;
    std::vector<EnemyShip*> enemies;
    std::vector<Gift*> gifts;

    Spacecraft *s = new Spacecraft("spacecraft.png");
    s->hp_ = parameters.at(0);
    s->bulletPower_ = parameters.at(2);
    s->sprite_.setPosition(window.getSize().x/2, window.getSize().y/2);
    s->sprite_.setRotation(90);


    bool move_u;
    bool move_d;

    while (window.isOpen()) {

        move_u = false;
        move_d = false;
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
                b->sprite_.setPosition(s->sprite_.getPosition().x - 1, s->sprite_.getPosition().y - 8);
                b->move_x = 10*cos(s->angle*DTR);
                b->move_y = 10*sin(s->angle*DTR);
                bullets.emplace_back(b);
                licznik++;
            }}


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
        if(s->hp_ <= parameters.at(16) && gifts.size() < 1){
            Gift *g = new Gift("live.png", parameters.at(9));
            g->setRandomPosition(window);
            gifts.emplace_back(g);
        }
        if(licznik == parameters.at(15) && gifts.size() < 2){
            Gift *gf = new Gift("update_bullet.png",0,parameters.at(10));
            gf->setRandomPosition(window);
            gifts.emplace_back(gf);
            licznik = 0;
        }

        size_t numberOfAstroids = parameters.at(6);

        if(asteroids.size() <= numberOfAstroids && delay_asteroid > 100){
            Asteroid *a = new Asteroid("asteroid.png");
            a->asteroidPower_ = parameters.at(4);
            a->sprite_.move(parameters.at(12), parameters.at(12));
            a->setMoveAsteroid(window, parameters);
            asteroids.emplace_back(a);
            delay_asteroid = 0;
        }
        else{
            delay_asteroid += clock.getElapsedTime().asSeconds();
        }

        size_t numberOfAstroidsInd = parameters.at(8);
        if(asteroids_indestructible.size() <= numberOfAstroidsInd && delay_asteroidInd > 300){
            Asteroid *ain = new Asteroid("asteroid_indestructible.png", true);
            ain->setMoveAsteroidIndesctutibile(window, parameters);
            ain->asteroidPowerInestructible_ = parameters.at(0);
            asteroids_indestructible.emplace_back(ain);
            delay_asteroidInd = 0;
        }
        else{
            delay_asteroidInd += clock.getElapsedTime().asSeconds();
        }

        size_t numberOfEnemies = parameters.at(7);
        if(enemies.size() <= numberOfEnemies && delay_enemyCraft > 1000 ){
            EnemyShip *e = new EnemyShip("enemy.png");
            e->hp_ = parameters.at(1);
            e->setMoveEnemy(s, window, parameters);
            enemies.emplace_back(e);
            delay_enemyCraft = 0;
        }
        else{
            delay_enemyCraft += clock.getElapsedTime().asSeconds();
        }

        if(delay_bulletEnemy > 1000){
            for(auto *e : enemies){
                Bullet *be = new Bullet("bullet_enemy.png");
                be->powerSpaceCraft_ = parameters.at(3);
                be->_getPosition(e);
                be->move_x = e->bulletsMoveX_;
                be->move_y = e->bulletsMoveY_;
                bullets_enemy.emplace_back(be);
            }
            delay_bulletEnemy = 0;
        }
        else{
            delay_bulletEnemy += clock.getElapsedTime().asSeconds();
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
            e->sprite_.move(e->move_x, e->move_y);
            if(e->is_alive_){
                e->_draw(window);
            }
            e->outsideObject(window);
        }
        for(auto *be : bullets_enemy){
            be->sprite_.move(1.5*be->move_x, 1.5*be->move_y);
            if(be->is_alive_){
                be->_draw(window);
            }
            be->removeBulletsOverWindow(bullets_enemy, window);
        }

        intersects_spacecraft_asteroid(s, asteroids);
        intersects_spacecraft_bullet(s, bullets_enemy);
        intersects_spacecraft_enemy(s, enemies);

        if(s->is_alive_){
            s->_draw(window);
            score += clock.getElapsedTime().asSeconds();
        }
        else{
            window.close();
        }

        std::vector<sf::Text> texts(5);
        std::string lifeSpaceCraft, bulletSpaceCraft, nextupdate;
        int nextupdate_ = parameters.at(15) - licznik;
        if( licznik >= parameters.at(15)){
            licznik = 0;
        }
        nextupdate = std::to_string(nextupdate_);
        lifeSpaceCraft = std::to_string(s->hp_);
        bulletSpaceCraft = std::to_string(s->bulletPower_);
        {
            sf::Text text;
            text.setString("Zycia:  ");
            text.setPosition(50, window.getSize().y - 50);
            texts.emplace_back(text);
        }
        {
            sf::Text text;
            text.setString(lifeSpaceCraft);
            text.setPosition(160, window.getSize().y - 50);
            texts.emplace_back(text);
        }
        {
            sf::Text text;
            text.setString("Moc pociskow:  ");
            text.setPosition(300, window.getSize().y - 50);
            texts.emplace_back(text);
        }
        {
            sf::Text text;
            text.setString(bulletSpaceCraft);
            text.setPosition(580, window.getSize().y - 50);
            texts.emplace_back(text);
        }
        {
            sf::Text text;
            text.setString("Nastepny updagte pociskow: ");
            text.setPosition(700, window.getSize().y - 50);
            texts.emplace_back(text);
        }
        {
            sf::Text text;
            text.setString(nextupdate);
            text.setPosition(1210, window.getSize().y - 50);
            texts.emplace_back(text);
        }

        for(size_t i = 0; i < texts.size()  ; i++){
            texts.at(i).setFont(font);
            texts.at(i).setFillColor(sf::Color::White);
            texts.at(i).setCharacterSize(40);
            texts.at(i).setStyle(sf::Text::Bold);
        }
        for(auto &i : texts){
            window.draw(i);
        }
        window.display();
    }
    return score;
}

void endWindow(int score){
    sf::RenderWindow end_window(sf::VideoMode(800, 500), "Try again");
    sf::Font font;
    font.loadFromFile("Times_New_Normal_Regular.ttf");

    while (end_window.isOpen()) {
        sf::Event event;
        while (end_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                end_window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter ){
                end_window.close();
            }
        }

        end_window.clear(sf::Color::Black);
        end_window.setFramerateLimit(30);

        sf::Text text, text1, text2, text3;;
        text.setString("GAME OVER");
        text.setPosition(250, 70);
        text.setFont(font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(60);
        text.setStyle(sf::Text::Bold);

        text1.setString("Wcisnij ENTER zeby zakonczyc");
        text1.setPosition(200, 400);
        text1.setFont(font);
        text1.setFillColor(sf::Color::White);
        text1.setCharacterSize(32);
        text1.setStyle(sf::Text::Bold);

        text2.setString("Twoj wynik: ");
        text2.setPosition(250, 200);
        text2.setFont(font);
        text2.setFillColor(sf::Color::White);
        text2.setCharacterSize(32);
        text2.setStyle(sf::Text::Bold);

        std::string score1 = std::to_string(score);
        text3.setString(score1);
        text3.setPosition(500, 200);
        text3.setFont(font);
        text3.setFillColor(sf::Color::White);
        text3.setCharacterSize(32);
        text3.setStyle(sf::Text::Bold);

        end_window.draw(text);
        end_window.draw(text1);
        end_window.draw(text2);
        end_window.draw(text3);

        end_window.display();
    }
}

int main(){
    std::vector<int> paramters = loadParametgers();
    int score = loop_game(paramters);
    endWindow(score);
    return 0;
}
