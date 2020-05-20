#include "Menu.h"

void Settings(RenderWindow& window, Music& music) {
    Texture bg_texture;
    bg_texture.loadFromFile("images/background.png");
    bg_texture.setRepeated(true);
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });

    Object title("Settings.png", { 0, 0 }, 600, 100, 0);
    title.SetPosition({ (window_x() - title.GetWidth()) / 2, 20 }, 0);
    title.Sprite().setColor(Color(0x0000b0ff));

    int items_num = 2;
    float gap = (window_y() - title.GetHeight() - title.GetPosition().y - 300) / (items_num / 2 + 1);
    float _x = window_x() / 2 - 300;
    std::vector<SettingsItem> items = {
                                             SettingsItem({ _x, 200 }, "Music", MusicVolume),
                                             SettingsItem({ _x, 200 + gap }, "Sound", SoundVolume),
    };


    std::vector<Button> buttons;
    float x_mid = window_x() / 2 - 175;
    buttons.push_back(Button("Back", { 100, float(window_y() - 130) }));

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
                    return;
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
                            return;
                        default:
                            break;
                        }
                    }
                }
            }

            MusicVolume = items[0].GetValue();
            music.setVolume(MusicVolume);
            SoundVolume = items[1].GetValue();

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
}