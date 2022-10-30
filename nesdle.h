
#define TOP_KEYBOARD_Y 20
#define TOP_KEYBOARD_X 6

#define MID_KEYBOARD_Y 22
#define MID_KEYBOARD_X 8

#define BOTTOM_KEYBOARD_Y 24
#define BOTTOM_KEYBOARD_X 10

#pragma bss-name(push, "ZEROPAGE")

enum
{
	CHECK_UNUSED,
	CHECK_MISS,
	CHECK_CLOSE,
	CHECK_HIT,
};

enum
{
	MODE_TITLE,
	MODE_GAME,
	MODE_RESULT,
};

// GLOBAL VARIABLES
unsigned char pad1;
unsigned char pad1_new;

unsigned char cursor_x_start;
unsigned char cursor_x;
unsigned char cursor_y;
unsigned char cursor_y_level;
unsigned char cursor_x_level;
unsigned char index;
unsigned char temp_y;
unsigned char game_mode;
unsigned int tempint;

unsigned char word_to_guess[5] = "CARGO";

unsigned char guess_1_1;
unsigned char guess_1_1_status;
unsigned char guess_1_2;
unsigned char guess_1_2_status;
unsigned char guess_1_3;
unsigned char guess_1_3_status;
unsigned char guess_1_4;
unsigned char guess_1_4_status;
unsigned char guess_1_5;
unsigned char guess_1_5_status;

unsigned char guess_2_1;
unsigned char guess_2_1_status;
unsigned char guess_2_2;
unsigned char guess_2_2_status;
unsigned char guess_2_3;
unsigned char guess_2_3_status;
unsigned char guess_2_4;
unsigned char guess_2_4_status;
unsigned char guess_2_5;
unsigned char guess_2_5_status;

unsigned char guess_3_1;
unsigned char guess_3_1_status;
unsigned char guess_3_2;
unsigned char guess_3_2_status;
unsigned char guess_3_3;
unsigned char guess_3_3_status;
unsigned char guess_3_4;
unsigned char guess_3_4_status;
unsigned char guess_3_5;
unsigned char guess_3_5_status;

unsigned char guess_4_1;
unsigned char guess_4_1_status;
unsigned char guess_4_2;
unsigned char guess_4_2_status;
unsigned char guess_4_3;
unsigned char guess_4_3_status;
unsigned char guess_4_4;
unsigned char guess_4_4_status;
unsigned char guess_4_5;
unsigned char guess_4_5_status;

unsigned char guess_5_1;
unsigned char guess_5_1_status;
unsigned char guess_5_2;
unsigned char guess_5_2_status;
unsigned char guess_5_3;
unsigned char guess_5_3_status;
unsigned char guess_5_4;
unsigned char guess_5_4_status;
unsigned char guess_5_5;
unsigned char guess_5_5_status;

unsigned char guess_6_1;
unsigned char guess_6_1_status;
unsigned char guess_6_2;
unsigned char guess_6_2_status;
unsigned char guess_6_3;
unsigned char guess_6_3_status;
unsigned char guess_6_4;
unsigned char guess_6_4_status;
unsigned char guess_6_5;
unsigned char guess_6_5_status;

unsigned char guess_X_1;
unsigned char guess_X_1_status;
unsigned char guess_X_2;
unsigned char guess_X_2_status;
unsigned char guess_X_3;
unsigned char guess_X_3_status;
unsigned char guess_X_4;
unsigned char guess_X_4_status;
unsigned char guess_X_5;
unsigned char guess_X_5_status;

unsigned char cur_guess_level;
unsigned char cur_guess_char;
unsigned char cur_guess_space;
unsigned char cur_guess_one;
unsigned char cur_guess_two;
unsigned char cur_guess_three;
unsigned char cur_guess_four;
unsigned char cur_guess_five;

unsigned char check_one;
unsigned char check_two;
unsigned char check_three;
unsigned char check_four;
unsigned char check_five;

const unsigned char keyboard_zero[] = "QWERTYUIOP";
const unsigned char keyboard_one[] = "ASDFGHJKL";
const unsigned char keyboard_two[] = "ZXCVBNM";

#pragma bss-name(push, "BSS")

const unsigned char palette_bg[] = {
		0x0f, 0x00, 0x30, 0x38, // black, light-gray, white, X
		0x0f, 0x2D, 0x30, 0x38, // black, dark-gray, white, X
		0x0f, 0x28, 0x30, 0x38, // black, orange, white, X
		0x0f, 0x1A, 0x30, 0x38, // black, green, white, X
};

const unsigned char palette_sp[] = {
		0x0f, 0x38, 0x30, 0x38, // black, yellow, white, X <--- used for selection
		0x0f, 0x00, 0x30, 0x38, // black, dark-gray, white, X
		0x0f, 0x28, 0x30, 0x38, // black, orange, white, X
		0x0f, 0x1A, 0x30, 0x38, // black, green, white, X

};

// PROTOTYPES
void draw_sprites(void);
void draw_keyboard_selection(void);
void draw_guesses(void);
void draw_cur_guess(void);
void draw_keyboard(void);
void keyboard_movement(void);
void init_game(void);
void reset_cur_level(void);
void submit_guess(void);
void select_word(void);