#include "Menu.h"

Surface PlanetSettings(RenderWindow& window, bool& if_Menu) {
    Texture bg_texture;
    bg_texture.loadFromFile("images/background.png");
    bg_texture.setRepeated(true);
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });

    Object title("PlanetSettings.png", { 0, 0 }, 600, 100, 0);
    title.SetPosition({ (window_x() - title.GetWidth()) / 2, 20 }, 0);
    title.Sprite().setColor(Color(0x0000b0ff));

    int items_num = 5;
    float gap = (window_y() - title.GetHeight() - title.GetPosition().y - 300) / (items_num / 2 + 1);
    float space = window_x() / 2;
    std::vector<SettingsItem> items = {
                                             SettingsItem({ 100, 200 }, "Lakes"),
                                             SettingsItem({ 100, 200 + gap }, "Holes"),
                                             SettingsItem({ 100, 200 + 2 * gap }, "Gravity"),
                                             SettingsItem({ 100, 200 + 3 * gap }, "Ice"),
                                             SettingsItem({ 100 + space, 200 }, "Meteorites"),
                                             SettingsItem({ 100 + space, 200 + gap }, "Slopes"),
                                             SettingsItem({ 100 + space, 200 + 2 * gap }, "Snow"),
                                             SettingsItem({ 100 + space, 200 + 3 * gap }, "Atmosphere")
                                         };

    std::vector<Button> buttons;
    float x_mid = window_x() / 2 - 175;
    buttons.push_back(Button("Menu", { 100, float(window_y() - 130) }));
    buttons.push_back(Button("Random", { x_mid, float(window_y() - 130) }));
    buttons.push_back(Button("Next", { float(window_x() - 450), float(window_y() - 130) }));

    int obj_num = items.size() + buttons.size();
    bool selecting = 1;
    int selected = 0; //selected item or button

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
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    //Arrows pressed
                    if (selected < items.size()) {
                        if (items[selected].GetLeft().GetIntRect().contains(Mouse::getPosition(window))) {
                            items[selected].Dec(5);
                        }
                        if (items[selected].GetRight().GetIntRect().contains(Mouse::getPosition(window))) {
                            items[selected].Inc(5);
                        }
                    }
                }
            }
            //only keyboard
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    if_Menu = 1;
                    selecting = 0;
                }
                if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                    selected = (selected - 1 + obj_num) % obj_num;
                }
                if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                    selected = (selected + 1) % obj_num;
                }
                if (selected < items.size()) {
                    if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left) {
                        items[selected].Dec(5);
                    }
                    if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right) {
                        items[selected].Inc(5);
                    }
                }
            }
            //keyboard or mouse Key Released
            if (event.type == Event::KeyReleased || event.type == Event::MouseButtonReleased) {
                if (event.key.code == Keyboard::Enter || event.mouseButton.button == Mouse::Left) {
                    //Buttons pressed
                    if (selected >= items.size()) {
                        switch (selected - items.size()) {
                        case 0: //back to Menu
                            if_Menu = 1;
                            selecting = 0;
                            break;
                        case 1: //random
                            for (auto& item : items) {
                                item.SetValue(rand() % 21 * 5);
                            }
                            break;
                        case 2: //next
                            if_Menu = 0;
                            selecting = 0;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < items.size(); ++i) {
            IntRect b_rect = items[i].GetIntRect();
            if (b_rect.contains(Mouse::getPosition(window))) {
                selected = i;
            }
            items[i].SetSelected(0);
        }
        for (int i = 0; i < buttons.size(); ++i) {
            IntRect b_rect(buttons[i].GetPosition().x, buttons[i].GetPosition().y,
                buttons[i].GetWidth(), buttons[i].GetHeight());
            if (b_rect.contains(Mouse::getPosition(window))) {
                selected = i + items.size();
            }
            buttons[i].SetSelected(0);
        }

        if (selected >= items.size()) {
            buttons[selected - items.size()].SetSelected(1);
        }
        else {
            items[selected].SetSelected(1);
        }

        window.clear();
        window.draw(bg_sprite);
        for (auto& item : items) {
            item.Draw(window);
        }
        for (auto& button : buttons) {
            button.Draw(window);
        }
        title.Draw(window);

        window.display();
    }

    std::map<Hole, int> probability = {     { Hole::LAKE, items[0].GetValue() },
                                            { Hole::EMPTY_U, items[1].GetValue()/2  },
                                            { Hole::EMPTY_V, items[1].GetValue()/2 },
                                            { Hole::ICE, items[3].GetValue() },
                                            { Hole::METEORITE, items[4].GetValue() },
    };
    int rough = 10;
    int max_angle = items[5].GetValue() / 100.0 * 70; //slopes
    int snow_coverage = items[6].GetValue();
    int gravity = items[2].GetValue();
    int air_density = items[7].GetValue();
    return Surface("surface.png", rough, snow_coverage, probability, max_angle, gravity, air_density);
}