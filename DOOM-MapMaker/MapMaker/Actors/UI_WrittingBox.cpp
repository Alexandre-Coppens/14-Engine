#include "UI_WrittingBox.h"

#include "MapMaker/Engine.h"

UI_WrittingBox::UI_WrittingBox(): 
	location(), 
	isHovering(false)
{
}

UI_WrittingBox::~UI_WrittingBox()
{
}

void UI_WrittingBox::Draw()
{
	if (!enabled) return;
	DrawText(name.c_str(), location.x + 5.0f, location.y + 5.0f, 5.0f, RAYWHITE);
	DrawRectangle(location.x + 5.0f, location.y + 17.0f, 100.0f, 15.0f, RAYWHITE);
	DrawText(contentString.c_str(), location.x + 100.0f - ( TextLength(contentString.c_str()) * 6.0f), location.y + 20.0f, 5.0f, isHovering ? RED : BLACK);
}

void UI_WrittingBox::Update()
{
	if (CheckCollisionPointRec(GetMousePosition(), Rectangle{location.x + 5.0f, location.y + 17.0f, 100.0f, 15.0f})) isHovering = true;
	else isHovering = false;
	if (isHovering)
	{
		if (IsKeyPressed(KEY_BACKSPACE))
		{
			if (contentString.length() > 0) contentString.erase(contentString.length() - 1);
		}
		else
		{
			int key = GetCharPressed();
			if (type == WrittingBoxType::Int || type == WrittingBoxType::Float)
			{
				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 44) && (key <= 57) && (contentString.length() < maxCharacters))
					{
						if (contentString.length() > 0) if (stof(contentString) == 0.0f) contentString = "";
						contentString += (char)key;
						Engine::instance->ChangeItem(name, contentString);
					}
					
					key = GetCharPressed();  // Check next character in the queue
				}
			}
			else
			{
				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (contentString.length() < maxCharacters))
					{
						contentString += (char)key;
						Engine::instance->ChangeItem(name, contentString);
					}
					
					key = GetCharPressed();  // Check next character in the queue
				}
			}
		}
	}
}

void UI_WrittingBox::Clicked()
{
}
