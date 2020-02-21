#pragma once
class IButton
{
public:
	void virtual onClick() = 0;
	void virtual upClick() = 0;
	void virtual onHover() = 0;
	void virtual upHover() = 0;
	void virtual press() = 0;
	bool blockClickLeft = false;
	bool blockUpClickLeft = false;
	bool blockClickRight = false;

};

