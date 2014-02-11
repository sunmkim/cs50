//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle
#define PHEIGHT 13
#define PWIDTH 70

// height and width of bricks
#define BHEIGHT 10
#define BWIDTH 31

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 8

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);


int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int number_of_bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // sets velocity of ball
    double y_velocity = 4;
    double velocity = drand48()*2.3;
    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && number_of_bricks > 0)
    {
        // TODO
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows cursor
                double x = getX(event) - getWidth(paddle)/2;
                double y = HEIGHT - 40;
                if (getX(event)- PWIDTH/2 > 0 && getX(event)+PWIDTH/2 < 400)
                {
                    setLocation(paddle, x, y);
                }
            }
         }
                
        // move the ball
        move(ball, velocity, y_velocity);
        
        GObject object = detectCollision(window, ball);
        
        // bounce off paddle
        if (object == paddle)
        {  
            double x = getX(ball);
            double y = getY(ball);
            
            if (object == getGObjectAt(window, x+2*RADIUS+5, y+RADIUS+5) || object == getGObjectAt(window,x-5, y+RADIUS+5))
            {    
                y_velocity = -y_velocity;
            }
        }
        
        // make bricks disappear if collision detected
        if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0 && object != paddle)
            {
                removeGWindow (window, object);
                points++;
                updateScoreboard(window, label, points);
                number_of_bricks--;
                y_velocity = -y_velocity;
                // I intentionally made x-velocity change when ball hits a brick using drand48() so the game will be a bit more difficult and more fun.
                velocity = drand48()*2.3;
                velocity = -velocity;
            }
        }
        
       
        // bounce off top edge of window
        if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        { 
            velocity = -velocity;
        }
        
        // bounce off right edge of window
        else if (getX(ball) + 2*RADIUS >= WIDTH)
        {  
            velocity = -velocity;
        }

        // linger before moving again
        pause(12);  
        
        // loses life if paddle misses ball
        if (getY(ball) >= HEIGHT)
        {
            lives = lives - 1; 
            ball = initBall(window);
            removeGWindow (window, paddle);
            paddle = initPaddle(window);
            waitForClick();    
        }  
    }
              
    // game over
    pause(12);  
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    int w_space = 0;
    int h_space = 0;
    
    for (int i=0; i < ROWS; i++)
    {   
        h_space = h_space + 10 + BHEIGHT;
        w_space = 8;
        
        for (int j=0; j < COLS; j++)
        {
            GRect brick = newGRect(w_space, h_space, BWIDTH, BHEIGHT);
            setColor(brick, "RED");
            setFilled(brick, true);
            add(window, brick);
            w_space = w_space + BWIDTH + 8;
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    
    GOval ball= newGOval(WIDTH/2 - RADIUS, HEIGHT/2 - RADIUS, RADIUS*2, RADIUS*2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    
    GRect paddle = newGRect(WIDTH/2 - PWIDTH/2, HEIGHT-40, PWIDTH, PHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    
    double x, y;
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-30");
    x = (getWidth(window) - getWidth(label)) / 2;
    y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
