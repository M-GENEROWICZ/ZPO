//
// Created by Marek Generowicz on 16/12/2024.
//
#ifndef HELPERS_HPP_
#define HELPERS_HPP_

#include "types.hpp"
#include <functional>
#include <random>

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;

#endif /* HELPERS_HPP_ */
