#pragma once
#ifndef COMMAND_H
#define COMMAND_H

/* Command pattern */

class GameObject;

class Command
{
public:
	// Executes the command
	virtual void execute(GameObject& obj) = 0;
};

#endif
