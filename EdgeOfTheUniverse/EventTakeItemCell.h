#pragma once
#include "IButton.h"
class UIPlayerInterface;
class EventTakeItemCell : public IButton
{
public:
	EventTakeItemCell(UIPlayerInterface* playerInterface);

	UIPlayerInterface* playerInterface;

	virtual void onClick() override;

	virtual void upClick() override;

	virtual void onHover() override;

	virtual void upHover() override;

	virtual void press() override;

};

