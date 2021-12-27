#include "field.h"
#include "Resourse.h"
#include "Utils.h"
#include "Text.h"
#include "pawn.h"
#include "player.h"
#include "Drawer.h"

void Field::DrawSelf()
{

}
void Field::UpdateSelf(const float dt)
{
	mPlayerController->Update(dt);
}

bool Field::OnEventSelf(GameEventBase* event)
{
	if (event->GetType() == eEventType::MouseClicked && IsGamePlayable())
	{
		auto ev = static_cast<GameEventMouseClicked*>(event);
		mPlayerController->MakeControlledMove(GetCell(GetCoordFromMouse(ev->GetMousePos())));
		return true;
	}
	return true; // i dont need events go to children now
}


void Field::CreateCells()
{
	auto data = ResourseManager->GetData<ItemData>("field");
	bool black = data->GetData("start") == "black";
	for (size_t y = 0; y < mFieldSize; y++)
	{
		for (size_t x = 0; x < mFieldSize; x++)
		{
			Cell* cell = new Cell(this, mCellSize, sf::Vector2i(x, y));
			cell->SetColor(black ? sf::Color::Blue : sf::Color::White);
			mCellsData[x + y * mFieldSize] = cell;
			cell->SetPosition(sf::Vector2f(x * mCellSize.x, y * mCellSize.y) + mTextIndentSize);
			AddChild(cell);
			black = !black;
		}
		if (mFieldSize % 2 == 0)
		{
			black = !black;
		}
	}
}

void Field::CreateFigures()
{
	auto data = ResourseManager->GetData<ItemData>("field");
	auto figuresData = data->GetData("figures");
	auto figures = Utils::Split(figuresData, ";");
	std::vector<std::string> colors = { "black", "white" }; // can be moved to config in future
	for (const auto& color : colors) {
		const ePlayerColor c = color == "black" ? ePlayerColor::Black : ePlayerColor::White; // i want magic_enum here :(
		for (const auto& figureName : figures)
		{
			// figure fabric
			Figure* figure = nullptr;
			auto positionsData = data->GetData(color + "_" + figureName);
			auto positions = Utils::Split(positionsData, ";");
			for (const auto& pos : positions)
			{
				const int x = pos[0] - 'a';
				const int y = mFieldSize - pos[1] + '0';
				if (figureName == "pawn")
				{
					figure = new Pawn(c, mCellSize, mTextIndentSize + sf::Vector2f(x * mCellSize.x, y * mCellSize.y));
				}
				//else if { etc etc }
				auto cell = GetCell(x, y);
				cell->SetFigure(figure);
				mTargets[Utils::AntiPlayerColor(c)].push_back(cell);
			}
		}
	}
}

Field::Field(const sf::Vector2f resolution)
	: Entity("field")
	, mFieldSize(8)
	, mResoultion(resolution)
	, mGameWon(false)
{
	EventManager->RegisterListener(this);
	SetTopOwner();
	auto data = ResourseManager->GetData<ItemData>("field");
	mFieldSize = std::stoi(data->GetData("size"));
	mCellsData.resize(mFieldSize * mFieldSize, nullptr);
	{
		auto fieldFill = data->GetData("field_fill");
		auto split = Utils::Split(fieldFill, "x");
		if (split.size() == 2)
		{
			mPlayFieldSize.x = resolution.x * std::stof(split[0]);
			mPlayFieldSize.y = resolution.y * std::stof(split[1]);
		}
		mTextIndentSize = (resolution - mPlayFieldSize) / 2.f;
	}

	mCellSize = sf::Vector2f(static_cast<float>(mPlayFieldSize.x / mFieldSize), static_cast<float>(mPlayFieldSize.y / mFieldSize));
	CreateCells();
	CreateLabels();
	CreateFigures();

	mPlayerController = std::make_unique<PlayerController>(this);
}

void Field::CreateLabels()
{
	sf::Font font = ResourseManager->GetData<ItemFont>("TimesNewRoman")->GetData();
	float offsetX = mTextIndentSize.x + mCellSize.x / 2.f - 2.f;
	float offsetY = mTextIndentSize.y + mPlayFieldSize.y - mCellSize.y / 2.f - 17.f;
	for (size_t i = 0; i < mFieldSize; i++)
	{
		const char c = 'a' + i;
		//top
		AddChild(new Text(std::string(1, c), sf::Vector2f(offsetX, 0.f), font));
		//bottom
		AddChild(new Text(std::string(1, c), sf::Vector2f(offsetX, mTextIndentSize.y + mPlayFieldSize.y), font));
		//left
		AddChild(new Text(std::to_string(i + 1), sf::Vector2f(mTextIndentSize.x / 2.f, offsetY), font));
		//right
		AddChild(new Text(std::to_string(i + 1), sf::Vector2f(4.f + mTextIndentSize.x + mPlayFieldSize.x, offsetY), font));

		offsetX += mCellSize.x;
		offsetY -= mCellSize.y;
	}
}

void Field::OnEnded()
{

}

Cell* Field::GetCell(const int x, const int y)
{
	if (x < 0 || x >= mFieldSize || y < 0 || y >= mFieldSize)
	{
		return nullptr;
	}
	return mCellsData[x + y * mFieldSize];
}

Cell* Field::GetCell(Cell* cell, eDirection dir)
{
	if (!cell)
	{
		return nullptr;
	}
	auto coord = cell->GetCoord();
	switch (dir)
	{
	case eDirection::Top: return GetCell(coord.x, coord.y - 1);
	case eDirection::Right: return GetCell(coord.x + 1, coord.y);
	case eDirection::Bottom: return GetCell(coord.x, coord.y + 1);
	case eDirection::Left: return GetCell(coord.x - 1, coord.y);
	}
	return nullptr;
}

Field::~Field()
{
	OnEnded();
}

void Field::RenderWinText()
{
	if (mGameWon)
	{
		sf::Font font = ResourseManager->GetData<ItemFont>("TimesNewRoman")->GetData();
		sf::Text text(mWinText, font, mResoultion.y / 10);
		text.setPosition({ mResoultion.x / 2.f - text.getLocalBounds().width / 2.f, mResoultion.y / 2.f - mResoultion.y / 10 });
		text.setFillColor(sf::Color::Red);
		Drawer->Add(text);
	}
}

std::vector<Cell*> Field::GetFreeCells(Cell* cell)
{
	std::vector<Cell*> res;
	if (cell)
	{
		for (size_t i = 0, size = static_cast<size_t>(eDirection::Count); i < size; i++)
		{
			auto subCell = GetCell(cell, static_cast<eDirection>(i));
			if (subCell)
			{
				if (!subCell->HasFigure())
					res.push_back(subCell);
			}
		}
	}
	return res;
}

void Field::UnselectCells()
{
	for (auto& cell : mCellsData)
	{
		cell->SetSelected(false);
	}
}

std::vector<Cell*> Field::GetOccupiedCells(ePlayerColor color)
{
	std::vector<Cell*> res;
	for (const auto& cell : mCellsData)
	{
		if (cell && cell->HasFigure())
		{
			if (auto figure = cell->GetFigure())
			{
				if (figure->GetPlayerColor() == color)
				{
					res.push_back(cell);
				}
			}
		}
	}
	return res;
}

void Field::CheckWinCondition(ePlayerColor color)
{
	for (auto& cell : mTargets[color])
	{
		if (auto figure = cell->GetFigure())
		{
			if (figure->GetPlayerColor() != color)
			{
				return;
			}
		}
		else { return; }
	}
	mGameWon = true;
	mWinText = "Player ";
	mWinText += color == ePlayerColor::Black ? "black" : "white";
	mWinText += " won";
}

sf::Vector2i Field::GetCoordFromMouse(const sf::Vector2i& mouse)
{
	auto vec = mouse - sf::Vector2i(mTextIndentSize.x, mTextIndentSize.y);
	vec.x /= mCellSize.x;
	vec.y /= mCellSize.y;
	return vec;
}

