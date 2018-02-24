#include "stdafx.h"
#include "Game.h"


/*
TODO:   Power-Ups
		Separate timer from scoreboard
		Unpause message
		Score -> Rounds (Scoring System)
		Load objects using text files
		Players shoot balls instead of spawning them
		Move option functions to Option from Game
		Main menu and option menu in header
		?Add console commands/messages
		?Add functions to player and ball that get lists (LoadSecondary atm)
		?Avoid reaching 0 velocity / Increment
		*Create separated class for game object manager
		*Create separated class for game state manager
		*Change from file loading to one texture for multiple balls
		*Fix camera
		*Point out-of-screen balls
		*Larger playground
		*Create ball creation function (spawner)
		*Particle trail
		*Countdown
		*ObjectScale bug
		*Fix reflextor direction angle (by point)
		*Reflector transparent edges
		*Add start menu
		*Reset timer at reset
		*Add more functions for sprite manipulation / Remove them

NOTE:   Bounding boxes increase area when rotated
		ALL bounding boxes are...boxes
		Not using Precompiled Headers
*/
int main() {
	Game g;
	g.StartGame();
	
	return 0;
}