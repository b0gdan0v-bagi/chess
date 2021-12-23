#include "field.h"
#include "Resourse.h"
#include "Utils.h"
#include "Text.h"

void Field::DrawSelf()
{
	auto test = ResourseManager->GetData<ItemTexture>("black_pawn")->GetSprite();
	sf::Vector2f v = { test.getLocalBounds().width, test.getLocalBounds().height };
	auto scale = sf::Vector2f(mCellSize.x  / v.x, mCellSize.x / v.x);
	test.setScale(scale);
	_window->draw(test);
}

void Field::CreateCells()
{
	auto data = ResourseManager->GetData<ItemData>("field");
	bool black = data->GetData("start") == "black";
	for (size_t y = 0; y < mFieldSize; y++)
	{
		for (size_t x = 0; x < mFieldSize; x++)
		{
			Cell* cell = new Cell(this, _window, mCellSize, sf::Vector2i(x, y));
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
}

Field::Field(sf::RenderWindow* window, const sf::Vector2f resolution)
	: Entity("field", window)
	, mFieldSize(8)
	, mResoultion(resolution)
{
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
		AddChild(new Text(_window, std::string(1, c), sf::Vector2f(offsetX, 0.f), font));
		//bottom
		AddChild(new Text(_window, std::string(1, c), sf::Vector2f(offsetX, mTextIndentSize.y + mPlayFieldSize.y), font));
		//left
		AddChild(new Text(_window, std::to_string(i + 1), sf::Vector2f(mTextIndentSize.x / 2.f, offsetY), font));
		//right
		AddChild(new Text(_window, std::to_string(i + 1), sf::Vector2f(4.f + mTextIndentSize.x + mPlayFieldSize.x, offsetY), font));

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

