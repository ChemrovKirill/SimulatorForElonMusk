#include "Menu.h"


using namespace sf;

void Menu(RenderWindow & window) {
	bool isMenu = true;
	std::vector<Object> buttons;
	buttons.push_back(Object("Button_Start.png", { 500, 200 }, 489, 139, 0));
	buttons.push_back(Object("Button_Exit.png", { 500, 400 }, 489, 139, 0));
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
			IntRect b_rect(buttons[i].GetPosition().x, buttons[i].GetPosition().y,
							buttons[i].GetWidth(), buttons[i].GetHeight());
			if (b_rect.contains(Mouse::getPosition(window))) {
				selected_button = i;
			}
			buttons[i].Sprite().setColor(Color(0x0000f09f));
		}

		buttons[selected_button].Sprite().setColor(Color(0x0000f0ff));
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
    float gap = (window_y() - 2 * title.GetHeight() - 2 * title.GetPosition().y)/items_num;
    float space = window_x() / 2 - 100;
    std::map<String, SettingsItem> items = { {"Lakes", SettingsItem({ 100, 200 }, "Lakes")},
                                             {"Holes_U", SettingsItem({ 100, 200+gap }, "Holes_U")},
                                             {"Holes_V", SettingsItem({ 100, 200 + 2*gap }, "Holes_V")},
                                             {"Ice", SettingsItem({ 100, 200+3*gap }, "Ice")},
                                             {"Meteorites", SettingsItem({ 100 + space, 200 }, "Meteorites")},
                                             {"Slopes", SettingsItem({ 100 + space,200 + gap }, "Slopes")},
                                             {"Snow", SettingsItem({ 100 + space,200 + 2* gap }, "Snow")}
                                           };

    bool selecting = 1;
    while (selecting) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) {
                    if_back = 1;
                    selecting = 0;
                }
                if (event.key.code == Keyboard::Space) {
                    if_back = 0;
                    selecting = 0;
                }
                if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up) {
                    
                }
                if (event.key.code == Keyboard::S || event.key.code == Keyboard::Down) {
                    
                }
            }
        }
        window.clear();
        window.draw(bg_sprite);
        for (auto& item : items) {
            item.second.Draw(window);
        }
        title.Draw(window);
        window.display();
    }
    std::map<Hole, int> p = {   { Hole::EMPTY_U, 0 },
                                { Hole::EMPTY_V, 0 },
                                { Hole::ICE, 0 },
                                { Hole::LAKE, 100 },
                                { Hole::METEORITE, 100 },
                                { Hole::FLAT, 100 }
                            };
    int rough = 10;
    int snow_coverage = 50;
    return Surface("surface.png", rough, snow_coverage, p, 0);
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