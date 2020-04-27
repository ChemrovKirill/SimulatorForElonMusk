#include "Menu.h"


using namespace sf;

void Menu(RenderWindow & window) {
	bool isMenu = true;
	std::vector<Button> buttons;
    float x_pos = window_x() / 2 - 175;
    buttons.push_back(Button( "Start", { x_pos, 200 } ));
    buttons.push_back(Button( "Exit", { x_pos, 400 } ));
	Texture bg_texture;
	bg_texture.loadFromFile("images/background.png");
	bg_texture.setRepeated(true);
	Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });

	int selected_button = 0;

	while (isMenu) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				isMenu = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
					selected_button = (selected_button + 1) % buttons.size();
				}
				if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
					selected_button = (selected_button - 1) % buttons.size();
				}
			}
		}

		window.clear();
		window.draw(bg_sprite);

		for (int i = 0; i < buttons.size(); ++i) {
            IntRect b_rect = buttons[i].GetIntRect();
			if (b_rect.contains(Mouse::getPosition(window))) {
				selected_button = i;
			}
			buttons[i].SetColor(Color(0x0000f09f));
		}

		buttons[selected_button].SetColor(Color(0x0000f0ff));
		for (int i = 0; i < buttons.size(); ++i) {
			buttons[i].Draw(window);
		}

		window.display();

		if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Enter)) {
			switch (selected_button) {
			case 0:
				StartGame(window);
				//isMenu = false;
				break;	
			case 1:
				window.close();
				isMenu = false;
				break;
			default:
				break;
			}
		}
	}
}

Surface SurfaceSelection(RenderWindow& window, bool& if_back) {
    Texture bg_texture;
    bg_texture.loadFromFile("images/background.png");
    bg_texture.setRepeated(true);
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setTextureRect({ 0, 0, int(window_x()), int(window_y()) });
    
    Object title("PlanetSettings.png", { 0, 0 }, 783, 138, 0);
    title.SetPosition({ (window_x() - title.GetWidth())/2, 30}, 0);
    title.Sprite().setColor(Color(0x0000b0ff));

    int items_num = 5;
    float gap = (window_y() -  title.GetHeight() - title.GetPosition().y - 300)/(items_num/2 +1);
    float space = window_x() / 2 - 100;
    std::vector<SettingsItem> items = { 
                                             SettingsItem({ 100, 200 }, "Lakes"),
                                             SettingsItem({ 100, 200 +   gap }, "Holes U"),
                                             SettingsItem({ 100, 200 + 2*gap }, "Holes V"),
                                             SettingsItem({ 100, 200 + 3*gap }, "Ice"),
                                             SettingsItem({ 100 + space, 200 }, "Meteorites"),
                                             SettingsItem({ 100 + space, 200 +     gap }, "Slopes"),
                                             SettingsItem({ 100 + space, 200 + 2 * gap }, "Snow"),
                                             SettingsItem({ 100 + space, 200 + 3 * gap }, "Atmosphere")
                                           };

    std::vector<Button> buttons;
    float x_mid = window_x() / 2 - 175;
    buttons.push_back(Button("Back", { 100, float(window_y() - 150) }));
    buttons.push_back(Button("Random", { x_mid, float(window_y() - 150) }));
    buttons.push_back(Button("Next", { float(window_x()-450), float(window_y() - 150) }));

    int obj_num = items.size() + buttons.size();
    bool selecting = 1;
    int selected = 0; //selected item or button

    while (selecting) {
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
                    if_back = 1;
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
            //keyboard or mouse
            if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed) {
                if(event.key.code == Keyboard::Enter || Mouse::isButtonPressed(Mouse::Left)) {
                    //Buttons pressed
                    if(selected >= items.size()) {
                        switch (selected - items.size()) {
                        case 0: //back
                            if_back = 1;
                            selecting = 0;
                            break;
                        case 1: //random
                            for (auto& item : items) {
                                item.SetValue(rand()%21 * 5);
                            }
                            break;
                        case 2: //next
                            if_back = 0;
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
            items[i].SetColor(Color(0x0000f09f));
        }
        for (int i = 0; i < buttons.size(); ++i) {
            IntRect b_rect(buttons[i].GetPosition().x, buttons[i].GetPosition().y,
                buttons[i].GetWidth(), buttons[i].GetHeight());
            if (b_rect.contains(Mouse::getPosition(window))) {
                selected = i + items.size();
            }
            buttons[i].SetColor(Color(0x0000f09f));
        }

        if (selected >= items.size()) {
            buttons[selected -items.size()].SetColor(Color(0x0000f0ff));
        }
        else {
            items[selected].SetColor(Color(0x0000f0ff));
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
                                            { Hole::EMPTY_U, items[1].GetValue()  },
                                            { Hole::EMPTY_V, items[2].GetValue() },
                                            { Hole::ICE, items[3].GetValue() },
                                            { Hole::METEORITE, items[4].GetValue() },
                                            { Hole::FLAT, 100 }
                                        };
    int rough = 10;
    int max_angle = items[5].GetValue()/100.0 * 70; //slopes
    int snow_coverage = items[6].GetValue();
    return Surface("surface.png", rough, snow_coverage, probability, max_angle);
}

void StartGame(RenderWindow& window) {
    bool if_back = 0;
    Surface s = SurfaceSelection(window, if_back);
    if(if_back) {
        return;
    }

    float dt = 0, time = 0;
    Clock deltaTime;

    Ship lander("Rick&Morty.png", RigidBodyParameters(Vector2f(0, s.YtoX(200) - 500), 200, 118, 0, 0.4, 100, Vector2f(0.5, 0.5),
        Vector2f(0, 0), Vector2f(0, 0), 0, 0));

    lander.AddEngine(Engine(Object("test3.png", Vector2f(10, 10), 20, 60, 0), Vector2f(0.5, 1),
        Force(false, 400, Vector2f(0, -1), Vector2f(0.5, 1)), 10), "1");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0, 0),
        Force(false, 200, Vector2f(-1, 0), Vector2f(0, 0)), 10), "3");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(1, 0),
        Force(false, 200, Vector2f(1, 0), Vector2f(1, 0)), 10), "4");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(1, 1),
        Force(false, 200, Vector2f(1, 0), Vector2f(1, 1)), 10), "5");
    lander.AddEngine(Engine(Object("test3.png", Vector2f(0, 0), 30, 10, 180), Vector2f(0, 1),
        Force(false, 200, Vector2f(-1, 0), Vector2f(0, 1)), 10), "6");
    lander.AddForce("0", Force(true, 100, Vector2f(0, 400), Vector2f(0, 0)));
    lander.ForceOn("0");

    View view;
    view.setCenter(sf::Vector2f(window_x() / 2, window_y() / 2));
    view.setSize(sf::Vector2f(window_x(), window_y()));


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) {
                    window.setView(View({0, 0, float(window_x()), float(window_y())}));
                    return;
                }
            }
        }

       if (dt > 0.5){
            dt = 0;
            //deltaTime.restart().asSeconds();
            continue;
       }

        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            lander.ForceOn("1");
        }
        else {
            lander.ForceOff("1");
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            lander.ForceOn("3");
            lander.ForceOn("5");
        }
        else {
            lander.ForceOff("3");
            lander.ForceOff("5");
        }
        if (Keyboard::isKeyPressed(Keyboard::E)) {
            lander.ForceOn("4");
            lander.ForceOn("6");
        }
        else {
            lander.ForceOff("4");
            lander.ForceOff("6");
        }
        if (Keyboard::isKeyPressed(Keyboard::Num1)) {
            lander.SetEngineThrust("1", 1);
        }
        if (Keyboard::isKeyPressed(Keyboard::Num2)) {
            lander.SetEngineThrust("1", 0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::Num3)) {
            lander.SetEngineThrust("1", 0.25);
        }
        if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::A)) {
            lander.SetEngineThrustAngle("1", 0);
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            lander.SetEngineThrustAngle("1", 1);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D)) {
            lander.SetEngineThrustAngle("1", -1);
        }
        else {
            lander.SetEngineThrustAngle("1", 0);
        }

        lander.UpdateShipPosition(dt);

        lander.DrawShip(window);

        lander.DrawMassPosition(window);
        //lander.DrawBodyWay(window);
        lander.DrawSpeed(window);
        lander.DrawForce(window, lander.GetForce("1"));
        lander.DrawForce(window, lander.GetForce("3"));
        lander.DrawForce(window, lander.GetForce("4"));
        lander.DrawForce(window, lander.GetForce("5"));
        lander.DrawForce(window, lander.GetForce("6"));
        lander.DrawForce(window, lander.GetForce("0"));
        lander.DrawForce(window, lander.GetForce("reaction"));

        view.setCenter(lander.GetCenterPosition());
        window.setView(view);

        s.Update(dt);
        s.Draw(window);

        lander.CollisionDetection(s, window);
        lander.CollisionModelDrow(window);

        window.display();

        time += dt;
        //std::cout << dt << std::endl;
        dt = deltaTime.restart().asSeconds();
        while (Keyboard::isKeyPressed(Keyboard::Space)) { dt = deltaTime.restart().asSeconds(); }
    }
}