#pragma once

#ifndef TESTHEADER_H
#define TESTHEADER_H

#include <iostream>
#include <string>

void testInput(void);
void testInput(std::string);
void testLevel(levelEntity);
void testLevel(levelEntity, std::string);
void testOutput(std::string);
void testOutput(std::string, std::string);
void testOutput(char);
void testOutput(char, std::string);
void testOutput(int);
void testOutput(int, std::string);

void pause(void);

#endif //TESTHEADER_H
