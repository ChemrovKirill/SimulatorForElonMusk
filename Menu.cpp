#include "Menu.h"
#include "Surface.h"

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
			buttons[i].Sprite().setColor(Color(0x0000f0ff));
		}

		buttons[selected_button].Sprite().setColor(Color(0xf00000ff));
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

Surface SurfaceSelection(RenderWindow& window) {
    std::map<Hole, int> p = {   { Hole::EMPTY_U, 0 },
                                { Hole::EMPTY_V, 0 },
                                { Hole::ICE, 50 },
                                { Hole::LAKE, 0 },
                                { Hole::METEORITE, 100 }
                            };
    int rough = 10;
    int snow_coverage = 50;
	return Surface("surface.png", rough, snow_coverage, p);
}

void StartGame(RenderWindow& window) {
	Surface s = SurfaceSelection(window);

    float dt = 0, time = 0;
    Clock deltaTime;

    Ship lander("Lunar_Lander_Mark1.png", RigidBodyParameters(Vector2f(0, s.YtoX(200) - 500), 170, 138, 0, 0.4, 100, Vector2f(0.5, 0.5),
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