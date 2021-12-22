#include "Engine.h"

#include "Resourse.h"
#include "Utils.h"

void Engine::OnStarted()
{
	ResourseManager->Start();
	SetWindow();

	mField = new Field(&window, mResolution);
}

void Engine::OnRestarted()
{
	// dont needed now
}

void Engine::SetWindow()
{
	auto screen = ResourseManager->GetData<ItemData>("screen");
	auto resolution = screen->GetData("resolution");
	auto split = Utils::Split(resolution, "x");
	if (split.size() == 2)
	{
		mResolution.x = std::stoi(split[0]);
		mResolution.y = std::stoi(split[1]);
	}
	window.create(sf::VideoMode(mResolution.x, mResolution.y), "Chess", sf::Style::Close);
}

void Engine::Draw()
{
	window.clear(sf::Color(77, 83, 140));
	mField->Draw();
	window.display();
}

void Engine::Update(const float dt)
{
	mField->Update(dt);
}

Engine::Engine()
	:mResolution(640.f, 480.f) // default
	,mField(nullptr)
{}

Engine::~Engine()
{
	ResourseManager->Stop();
}

int Engine::Start()
{
	OnStarted();
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
				return 0;
			}
		}
		Draw();
	}
}



