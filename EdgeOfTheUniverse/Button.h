#pragma once
#include "UI.h"
#include "vector"
#include "IButton.h"
#include "Cursor.h"
#include "EventSetWhite.h"
#include "ButtonGroup.h"
class Button : public UI
{
public:
	Button();
	Button(vec2 size);
	~Button();
	void addDelegates(IButton* obj);
	std::vector<IButton*> Delegates;
	EventSetWhite* whiteEvent;
	ButtonGroup* buttonGroup;
	int indexInGroup;
	vec4 hoverColor = vec4(255, 255, 255, 255);
	vec4 pressColor = vec4(255, 255, 255, 255);
	vec4 activetedColor = vec4(255, 255, 255, 255);
	vec4 hoverActivetedColor = vec4(255, 255, 255, 255);
	vec4 pressActivetedColor = vec4(255, 255, 255, 255);
	bool whiteEventActive = true;
	bool hoverBool;
	bool pressBool;
	bool clickBool;
	bool pressOnButtonBool;
	bool isActive;
	bool Activable = true;
	bool* eventBool = new bool[4];
	virtual void Draw(Renderer* renderer, Alterable alters) override;
protected:
	void DelegateUpdate();
};

