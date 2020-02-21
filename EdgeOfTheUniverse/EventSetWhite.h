#pragma once
#include "IButton.h"
class Button;
class EventSetWhite : public IButton
{
public:
	EventSetWhite(Button* but);
	~EventSetWhite();
	Button* but;
	virtual void onClick() override;
	virtual void upClick() override;
	virtual void onHover() override;
	virtual void upHover() override;
	virtual void press() override;
};

