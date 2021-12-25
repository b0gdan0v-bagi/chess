#include "Engine.h"

#include "Resourse.h"
#include "Utils.h"

void Engine::OnStarted()
{
	ResourseManager->Start();
	SetWindow();

	mField = std::make_unique<Field>(&window, mResolution);
	_clock = sf::Clock();
	EventManager->SetWindow(&window);
}

void Engine::OnRestarted()
{
	// dont needed now
}

void Engine::OnEnded()
{
	ResourseManager->Stop();
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
	_timeDiv = std::stof(screen->GetData("clock_const"));
	window.create(sf::VideoMode(mResolution.x, mResolution.y), "Chess", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0.f, 0.f, mResolution.x, mResolution.y)));
}

void Engine::Draw()
{
	window.clear(sf::Color(77, 83, 140));
	mField->Draw();
	window.display();
}

void Engine::Input()
{
	EventManager->HandleSFMLEvents();
}

void Engine::Update()
{
	float time = _clock.getElapsedTime().asMicroseconds();
	_clock.restart();
	time = time / _timeDiv;
	mField->Update(time);
}

Engine::Engine()
	:mResolution(640.f, 480.f) // default
	, mField(nullptr)
	, _timeDiv(800)
{}

Engine::~Engine()
{
}

void Engine::Start()
{
	OnStarted();

	while (window.isOpen())
	{
		Input();
		Update();
		Draw();
	}

	OnEnded();
}



