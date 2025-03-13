/*
* File: Strategy.cpp
* Author: trung.la
* Date: 03-13-2025
* Description: This file is implementation of strategy pattern
*/

/**
 * What is Strategy Pattern?
 * 
 * Strategy Pattern is a behavioral design pattern that enables selecting
 * an algorithm at runtime.
 * 
 * When we use it?
 * 
 * When we have multiple variations of an algorithm and want to select one dynamically.
 * When we want to avoid multiple conditional statement.
 * When we want to separate and encapsulate concerns, make the code more maintainable.
 * 
 * How it works?
 * 
 * 1. Strategy Interface: Defines a common interface for algorithms
 * 2. Concrete Strategies: Implement different variations of the algorithm.
 * 3. Context Class: Uses a Strategy object and delegates works to it.
 */
