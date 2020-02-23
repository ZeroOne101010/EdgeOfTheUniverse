#include "Controller.h"
#include "World.h"
Controller::Controller()
{
}

Controller::Controller(Entity* target)
{
	this->target = target;
}

void Controller::setTarget(Entity* target)
{
	this->target = target;
}

void Controller::Controll()
{
    if (RenderWindow::getKeyState(GLFW_KEY_W) || RenderWindow::getKeyState(GLFW_KEY_SPACE))
    {
        if (target->velocity.y == 0)
        {
            target->W(target->Wf);
        }
    }

        if (RenderWindow::getKeyState(GLFW_KEY_D))
        {
            target->D(target->Df);
        }
        else if (RenderWindow::getKeyState(GLFW_KEY_A))
        {
            target->A(target->Af);
        }
        else
        {
            target->velocity.x = 0;
        }
}
void Controller::Interpol(float k)
{
    vec2 distance = target->Position - Camera;
    camVelosity = k * distance;
}
void Controller::UpdateController(World* world)
{
    Interpol(0.1f);
    Camera += camVelosity;
	zeroCamera = Camera - vec2(RenderWindow::width / 2, RenderWindow::height / 2);
    Controll();
	world->Position = -zeroCamera;
}



