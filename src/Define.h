#pragma once

const int FPSH = 8; // fixed-point shift to convert pixels/subpixels
const int FPM = 0xff; // fixed-point mask to get subpixels
const int PX = 1<<FPSH; // how many subpixels in one pixel

const int WIDTH = 400; // game surface width
const int HEIGHT = 240; // game surface height

const int FPS  = 60; // frames per second

const int MAX_PARTICLES = 2048;

