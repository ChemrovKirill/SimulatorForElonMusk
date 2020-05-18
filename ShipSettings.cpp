#include "Menu.h"

Ship* ShipSettings(RenderWindow& window, const Vector2f& position, bool& if_Menu) {

    Texture bg_texture;
    bg_texture.loadFromFile("images/background.png");
    bg_texture.setRepeated(true);
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });

    Object title("ShipSettings.png", { 0, 0 }, 600, 100, 0);
    title.SetPosition({ (window_x() - title.GetWidth()) / 2, 20 }, 0);
    title.Sprite().setColor(Color(0x0000b0ff));

    int stands_in_row = 4;
    float stand_size = 250;
    Vector2f gap;
    gap.x = (window_x()- stands_in_row * stand_size) / (stands_in_row+1);
    //gap.y = window_y()/2 - title.GetPosition().y - title.GetFloatRect().height - stand_size;

    std::vector<ShipStand> stands = {   ShipStand("Lunar_Lander_Mark1.png", "Mark 1", {gap.x, 250}),
                                        ShipStand("Dron.png", "Dron", {stand_size + 2*gap.x, 250}),
                                        ShipStand("Rick&Morty.png", "Rick & Morty", {2*stand_size + 3*gap.x, 250}),
                                        ShipStand("SuperPuperShip.png", "SuperPuperShip", {3*stand_size + 4*gap.x, 250}),
    };

    std::vector<Button> buttons;
    float x_mid = window_x() / 2 - 175;
    buttons.push_back(Button("Menu", { 100, float(window_y() - 130) }));
    buttons.push_back(Button("Random", { x_mid, float(window_y() - 130) }));
    buttons.push_back(Button("Start", { float(window_x() - 450), float(window_y() - 130) }));

    int obj_num = stands.size() + buttons.size();
    bool selecting = 1;
    int selected = 0; //selected item or button
    int chosen = 0;

    View view;
    while (selecting && window.isOpen()) {

        view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
        view.setSize(sf::Vector2f(window_x(), window_y()));
        window.setView(view);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            //only mouse
            if (event.type == Event::MouseButtonPressed) {

            }
            //only keyboard
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    //if_menu = 1;
                    selecting = 0;
                }
                if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                    selected = (selected - 1 + obj_num) % obj_num;
                }
                if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                    selected = (selected + 1) % obj_num;
                }
            }
            //keyboard or mouse Key Released
            if (event.type == Event::KeyReleased || event.type == Event::MouseButtonReleased) {
                if (event.key.code == Keyboard::Enter || event.mouseButton.button == Mouse::Left) {
                    //Buttons pressed
                    if (selected >= stands.size()) {
                        switch (selected - stands.size()) {
                        case 0: //menu
                            if_Menu = 1;
                            selecting = 0;
                            break;
                        case 1: //random
                            chosen = rand() % stands.size();
                            break;
                        case 2: //start
                            if_Menu = 0;
                            selecting = 0;
                            break;
                        default:
                            break;
                        }
                    }
                    else {
                        chosen = selected;
                    }
                }
            }
        }

        for (int i = 0; i < stands.size(); ++i) {
            IntRect b_rect = stands[i].GetIntRect();
            if (b_rect.contains(Mouse::getPosition(window))) {
                selected = i;
            }
            stands[i].SetSelected(0);
            stands[i].SetChosen(0);
        }
        for (int i = 0; i < buttons.size(); ++i) {
            IntRect b_rect(buttons[i].GetPosition().x, buttons[i].GetPosition().y,
                buttons[i].GetWidth(), buttons[i].GetHeight());
            if (b_rect.contains(Mouse::getPosition(window))) {
                selected = i + stands.size();
            }
            buttons[i].SetSelected(0);
        }

        if (selected >= stands.size()) {
            buttons[selected - stands.size()].SetSelected(1);
        }
        else {
            stands[selected].SetSelected(1);
        }
        if (chosen >= 0) {
            stands[chosen].SetChosen(1);
        }

        window.clear();
        window.draw(bg_sprite);
        
        for (const auto& button : buttons) {
            button.Draw(window);
        }
        title.Draw(window);
        for (const auto& stand : stands) {
            stand.Draw(window);
        }
        window.display();
    }

    //Ship* ship;
    switch (chosen) {
    case 0:
        return new Lunar_Lander_Mark1(position);
    case 1:
        return new Dron(position);
    case 2:
        return new RickAndMorty(position);
    case 3:
        return new SuperPuperShip(position);
    }
}