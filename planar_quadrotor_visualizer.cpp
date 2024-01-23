#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    int Screen_X = 480;
    int Screen_Y = 1024;
    q_x = state[0] + Screen_Y/2;
    q_y = state[1] + Screen_X/2;
    q_theta = state[2]/2;

    unsigned int bar = 100;

    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
    
    thickLineColor(gRenderer.get(),
    q_x + bar * cos(q_theta),
    q_x - bar * cos(q_theta),
    q_y + bar * sin(q_theta) + 175,
    q_y - bar * sin(q_theta), 20, 0xFF1C529E);

    unsigned int distance = 80, h = 50;

    thickLineColor(gRenderer.get(),
    q_x + 100 * cos(q_theta),
    q_x - 100 * cos(q_theta) - 180,
    q_y + 100 * sin(q_theta) + 175,
    q_y - 100 * sin(q_theta) + 200, 20, 0xFF1C529E);
    
    filledCircleColor(gRenderer.get(), q_x, q_y + 90, 20, 0xFFC7D132);

    thickLineColor(gRenderer.get(),
    q_x - distance * cos(q_theta),
    q_y + distance * sin(q_theta),
    q_x - distance * cos(q_theta) - h * sin(q_theta),
    q_y + distance * sin(q_theta) - h * cos(q_theta), 3, 0xFF000000);

    thickLineColor(gRenderer.get(),
    q_x + distance * cos(q_theta),
    q_y - distance * sin(q_theta),
    q_x + distance * cos(q_theta) - h * sin(q_theta),
    q_y - distance * sin(q_theta) - h * cos(q_theta), 3, 0xFF000000);

    unsigned int num = 30, lenght = 35;

    filledEllipseColor(gRenderer.get(),
    q_x - distance * cos(q_theta) - h *sin(q_theta) - lenght + lenght * abs (sin(q_x - Screen_Y)),
    q_y + distance * sin(q_theta) - h * cos(q_theta), lenght, 8, 0xFFe4ff5e);

    filledEllipseColor(gRenderer.get(),
    q_x - distance * cos(q_theta) - h * sin(q_theta) + lenght - lenght * abs(sin(q_x - Screen_Y)),
    q_y + distance * sin(q_theta) - h * cos(q_theta), lenght, 8, 0xFFa4ff5e);
    filledEllipseColor(gRenderer.get(), 
    q_x + distance * cos(q_theta) - h * sin(q_theta) - lenght + lenght * abs(sin(q_x - Screen_Y  - M_PI)),
    q_y - distance * sin(q_theta) - h * cos(q_theta), lenght, 8, 0xFFe4ff5e);
    filledEllipseColor(gRenderer.get(),
    q_x + distance * cos(q_theta) - h * sin(q_theta) + lenght - lenght * abs(sin(q_x - Screen_Y  - M_PI)),
    q_y - distance * sin(q_theta) - h * cos(q_theta), lenght, 8, 0xFFa4ff5e);
}
