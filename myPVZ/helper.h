#pragma once

//states:
//0 : dying state 
//1 : basic state 
//2 : attack state
//3 : go down
//4 : go up

//UserType + 
//1:zombie		2:flying zombie
//10:plants		11:wallnut			12:Pea				13:cactus		14:mapBlock		15:spikeweed		16:sunflower		17:sun

//Z Value:
//0:map		1:plants		2:zombies


#define MAX_CARDS 6
#define MAP_COLUMNS 9
#define MAP_ROWS 5

#define CELL_WIDTH 158
#define CELL_HEIGHT 196
#define PLANT_WIDTH 100
#define PLANT_HEIGHT 120

#define ZOMBIES 4
#define WIN_NUM 10

//sun
#define BEGIN_SUN 500
#define ADD_SUN 50

//time related const
#define TIMER_SPAN 50
#define END_GAME_SPAN 40

//Plants HP
#define WALLNUT_HP 500
#define PEASHOOTER_HP 50
#define CACUS_HP 50

//Plants ATK
#define WALLNUT_ATK 1
#define PEA_ATK 50
#define SPINE_ATK 50

//Zombies HP
#define NORMALZOMBIE_HP 100

//Zombies ATK
#define NORMALZOMBIE_ATK 1

//Zombies Speed
#define NORMALZOMBIE_SPEED 2
#define BALLOONZOMBIE_SPEED 2