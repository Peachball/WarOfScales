#pragma once
//#include "main.h"
#include "SDL.h"
#include "LinkedList.h"
#include "Point.h"
#include <malloc.h>

enum ElementClass
{
	Basic,
	//main menu
	StartButton,
	LevelSelectButton,
	ControlsButton,
	QuitButton,
};
enum ElementFlags
{
	visible = 1,
	active = 2,
	button = 4,
	window = 8,
	draggable = 16,
	circular = 32,
};
typedef struct UIElement 
{
	int *nullptr;
	int class, flags, frame, outlineWidth;
	BOOLEAN play, refreshTexture, visible, pressed, breakMouse, outline;
	double frametimer, animationspeed;
	Point pos, lastpos, dim, framedim, texturedim;
	SDL_Color outlineColor;
	char* path;
	SDL_Texture* texture;
	struct UIElement* parent;
	NodeList* children;
}UIElement;

void UIElement_Init(UIElement* element);
UIElement* UIElement_Create(int class, int flags, Point* pos, Point* dim, char* path);
void UIElement_Set(UIElement* element, int class, int flags, Point pos, Point dim, char* path);
void UIElement_EnableFlags(UIElement* element, int flags);
void UIElement_DisableFlags(UIElement* element, int flags);
void UIElement_ToggleFlags(UIElement* element, int flags);
void UIElement_Destroy(UIElement* element);
void UIElement_GetFinalPos(Point* out, UIElement* element);
void UIElement_Parent(UIElement* parent, UIElement* child);
void UIElement_HandleEvents(UIElement* element, SDL_Event* event);
void UIElement_Update(UIElement* element, double frametime);
void UIElement_UpdateReverse(UIElement* element);
void UIElement_UpdateAnimation(UIElement* element, double frametime);
void UIElement_UpdateLastPos(UIElement* element);
void UIElement_UpdateParentRelationship(UIElement* element);
void UIElement_OnButtonPress(UIElement* element);
void UIElement_Message(UIElement* element, char* message);
void UIElement_Draw(SDL_Renderer* renderer, UIElement* element);
void UIElement_DrawOutline(SDL_Renderer* renderer, UIElement* element);
BOOLEAN UIElement_SDL_PointIsInside(UIElement* element, SDL_Point* p);