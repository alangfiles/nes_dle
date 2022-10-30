/*	example code for cc65, for NES
 *  Scroll Right with metatile system
 *	using neslib
 *	Doug Fraker 2018
 */

#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "nesdle.h"

void main(void)
{
	game_mode = MODE_TITLE;
	ppu_off(); // screen off

	// load the palettes
	pal_bg(palette_bg);
	pal_spr(palette_sp);
	set_scroll_y(0xff); // shift the bg down 1 pixel

	// both bg and sprites are set to 0 by default
	// bank_spr(1);

	set_vram_buffer(); // do at least once, sets a pointer to a buffer

	ppu_on_all(); // turn on screen

	while (1)
	{
		if (game_mode == MODE_TITLE)
		{
			// infinite loop
			ppu_wait_nmi(); // wait till beginning of the frame
			multi_vram_buffer_horz("NES.DLE", 7, NTADR_A(10, 10));
			multi_vram_buffer_horz("Press Start to Play", 19, NTADR_A(7, 16));

			pad1 = pad_poll(0); // read the first controller
			pad1_new = get_pad_new(0);

			if (pad1_new & PAD_START)
			{
				init_game();
			}
		}
		if (game_mode == MODE_GAME)
		{

			// infinite loop
			ppu_wait_nmi(); // wait till beginning of the frame

			pad1 = pad_poll(0); // read the first controller
			pad1_new = get_pad_new(0);

			keyboard_movement();
			draw_sprites();
		}
	}
}

void draw_sprites(void)
{
	// clear all sprites from sprite buffer
	oam_clear();
	draw_keyboard_selection();
	draw_guesses();
	draw_cur_guess();
}

void draw_guesses(void)
{
	temp_y = 40;

	if (cur_guess_level != 0)
	{
		oam_spr(84, temp_y, guess_1_1, guess_1_1_status);
		oam_spr(100, temp_y, guess_1_2, guess_1_2_status);
		oam_spr(116, temp_y, guess_1_3, guess_1_3_status);
		oam_spr(132, temp_y, guess_1_4, guess_1_4_status);
		oam_spr(148, temp_y, guess_1_5, guess_1_5_status);
	}
	temp_y += 16;

	if (cur_guess_level != 1)
	{
		oam_spr(84, temp_y, guess_2_1, guess_2_1_status);
		oam_spr(100, temp_y, guess_2_2, guess_2_2_status);
		oam_spr(116, temp_y, guess_2_3, guess_2_3_status);
		oam_spr(132, temp_y, guess_2_4, guess_2_4_status);
		oam_spr(148, temp_y, guess_2_5, guess_2_5_status);
	}
	temp_y += 16;

	if (cur_guess_level != 2)
	{
		oam_spr(84, temp_y, guess_3_1, guess_3_1_status);
		oam_spr(100, temp_y, guess_3_2, guess_3_2_status);
		oam_spr(116, temp_y, guess_3_3, guess_3_3_status);
		oam_spr(132, temp_y, guess_3_4, guess_3_4_status);
		oam_spr(148, temp_y, guess_3_5, guess_3_5_status);
	}
	temp_y += 16;

	if (cur_guess_level != 3)
	{
		oam_spr(84, temp_y, guess_4_1, guess_4_1_status);
		oam_spr(100, temp_y, guess_4_2, guess_4_2_status);
		oam_spr(116, temp_y, guess_4_3, guess_4_3_status);
		oam_spr(132, temp_y, guess_4_4, guess_4_4_status);
		oam_spr(148, temp_y, guess_4_5, guess_4_5_status);
	}
	temp_y += 16;

	if (cur_guess_level != 4)
	{
		oam_spr(84, temp_y, guess_5_1, guess_5_1_status);
		oam_spr(100, temp_y, guess_5_2, guess_5_2_status);
		oam_spr(116, temp_y, guess_5_3, guess_5_3_status);
		oam_spr(132, temp_y, guess_5_4, guess_5_4_status);
		oam_spr(148, temp_y, guess_5_5, guess_5_5_status);
	}
	temp_y += 16;

	if (cur_guess_level != 5)
	{
		oam_spr(84, temp_y, guess_6_1, guess_6_1_status);
		oam_spr(100, temp_y, guess_6_2, guess_6_2_status);
		oam_spr(116, temp_y, guess_6_3, guess_6_3_status);
		oam_spr(132, temp_y, guess_6_4, guess_6_4_status);
		oam_spr(148, temp_y, guess_6_5, guess_6_5_status);
	}
}

void draw_cur_guess(void)
{

	temp_y = 40;
	for (index = 0; index < cur_guess_level; ++index)
	{
		temp_y += 16;
	}

	oam_spr(84, temp_y, cur_guess_one, 1);
	oam_spr(100, temp_y, cur_guess_two, 1);
	oam_spr(116, temp_y, cur_guess_three, 1);
	oam_spr(132, temp_y, cur_guess_four, 1);
	oam_spr(148, temp_y, cur_guess_five, 1);
}

void draw_keyboard_selection(void)
{
	// this is complexe because we keep track of
	// cursor_x_level and cursor_y_level in the code to simplify that
	// and now we expand them out.

	cursor_x = 0;
	for (index = 0; index < cursor_x_level; ++index)
	{
		cursor_x += 16;
	}

	cursor_y = 0;
	for (index = 0; index < cursor_y_level; ++index)
	{
		cursor_y += 16;
	}

	cursor_x_start = 0;
	if (cursor_y_level == 0)
	{
		cursor_x_start = 48;
	}
	if (cursor_y_level == 1)
	{
		cursor_x_start = 56;
	}
	if (cursor_y_level == 2)
	{
		cursor_x_start = 72;
	}

	// draw keyboard:
	oam_spr(cursor_x_start + cursor_x, 160 + cursor_y, ' ', 0);
}

void init_game(void)
{
	game_mode = MODE_GAME;
	cur_guess_level = 0;
	cursor_y_level = 0;
	cursor_x_level = 0;
	cursor_x = 0;
	cursor_y = 0;
	// cursor_x = 48;
	// cursor_y = 159;

	guess_1_1 = ' ';
	guess_1_2 = ' ';
	guess_1_3 = ' ';
	guess_1_4 = ' ';
	guess_1_5 = ' ';
	guess_2_1 = ' ';
	guess_2_2 = ' ';
	guess_2_3 = ' ';
	guess_2_4 = ' ';
	guess_2_5 = ' ';
	guess_3_1 = ' ';
	guess_3_2 = ' ';
	guess_3_3 = ' ';
	guess_3_4 = ' ';
	guess_3_5 = ' ';
	guess_4_1 = ' ';
	guess_4_2 = ' ';
	guess_4_3 = ' ';
	guess_4_4 = ' ';
	guess_4_5 = ' ';
	guess_5_1 = ' ';
	guess_5_2 = ' ';
	guess_5_3 = ' ';
	guess_5_4 = ' ';
	guess_5_5 = ' ';
	guess_6_1 = ' ';
	guess_6_2 = ' ';
	guess_6_3 = ' ';
	guess_6_4 = ' ';
	guess_6_5 = ' ';

	guess_1_1_status = 1;
	guess_1_2_status = 1;
	guess_1_3_status = 1;
	guess_1_4_status = 1;
	guess_1_5_status = 1;
	guess_2_1_status = 1;
	guess_2_2_status = 1;
	guess_2_3_status = 1;
	guess_2_4_status = 1;
	guess_2_5_status = 1;
	guess_3_1_status = 1;
	guess_3_2_status = 1;
	guess_3_3_status = 1;
	guess_3_4_status = 1;
	guess_3_5_status = 1;
	guess_4_1_status = 1;
	guess_4_2_status = 1;
	guess_4_3_status = 1;
	guess_4_4_status = 1;
	guess_4_5_status = 1;
	guess_5_1_status = 1;
	guess_5_2_status = 1;
	guess_5_3_status = 1;
	guess_5_4_status = 1;
	guess_5_5_status = 1;
	guess_6_1_status = 1;
	guess_6_2_status = 1;
	guess_6_3_status = 1;
	guess_6_4_status = 1;
	guess_6_5_status = 1;

	ppu_off();
	vram_adr(NAMETABLE_A);
	set_vram_update(0);
	set_vram_buffer();
	for (tempint = 0; tempint < 1024; ++tempint)
	{
		vram_put(0x00);
		flush_vram_update2();
	}
	ppu_on_all();
	select_word();
	reset_cur_level();
	draw_keyboard();
}

void draw_keyboard(void)
{
	ppu_off();
	// done in BG
	one_vram_buffer('Q', NTADR_A(TOP_KEYBOARD_X, TOP_KEYBOARD_Y));
	one_vram_buffer('W', NTADR_A(TOP_KEYBOARD_X + 2, TOP_KEYBOARD_Y));
	one_vram_buffer('E', NTADR_A(TOP_KEYBOARD_X + 4, TOP_KEYBOARD_Y));
	one_vram_buffer('R', NTADR_A(TOP_KEYBOARD_X + 6, TOP_KEYBOARD_Y));
	one_vram_buffer('T', NTADR_A(TOP_KEYBOARD_X + 8, TOP_KEYBOARD_Y));
	one_vram_buffer('Y', NTADR_A(TOP_KEYBOARD_X + 10, TOP_KEYBOARD_Y));
	one_vram_buffer('U', NTADR_A(TOP_KEYBOARD_X + 12, TOP_KEYBOARD_Y));
	one_vram_buffer('I', NTADR_A(TOP_KEYBOARD_X + 14, TOP_KEYBOARD_Y));
	one_vram_buffer('O', NTADR_A(TOP_KEYBOARD_X + 16, TOP_KEYBOARD_Y));
	one_vram_buffer('P', NTADR_A(TOP_KEYBOARD_X + 18, TOP_KEYBOARD_Y));
	flush_vram_update2();
	one_vram_buffer('A', NTADR_A(MID_KEYBOARD_X, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('S', NTADR_A(MID_KEYBOARD_X + 2, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('D', NTADR_A(MID_KEYBOARD_X + 4, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('F', NTADR_A(MID_KEYBOARD_X + 6, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('G', NTADR_A(MID_KEYBOARD_X + 8, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('H', NTADR_A(MID_KEYBOARD_X + 10, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('J', NTADR_A(MID_KEYBOARD_X + 12, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('K', NTADR_A(MID_KEYBOARD_X + 14, MID_KEYBOARD_Y) - 1);
	one_vram_buffer('L', NTADR_A(MID_KEYBOARD_X + 16, MID_KEYBOARD_Y) - 1);
	flush_vram_update2();
	one_vram_buffer('Z', NTADR_A(BOTTOM_KEYBOARD_X, BOTTOM_KEYBOARD_Y) - 1);
	one_vram_buffer('X', NTADR_A(BOTTOM_KEYBOARD_X + 2, BOTTOM_KEYBOARD_Y) - 1);
	one_vram_buffer('C', NTADR_A(BOTTOM_KEYBOARD_X + 4, BOTTOM_KEYBOARD_Y) - 1);
	one_vram_buffer('V', NTADR_A(BOTTOM_KEYBOARD_X + 6, BOTTOM_KEYBOARD_Y) - 1);
	one_vram_buffer('B', NTADR_A(BOTTOM_KEYBOARD_X + 8, BOTTOM_KEYBOARD_Y) - 1);
	one_vram_buffer('N', NTADR_A(BOTTOM_KEYBOARD_X + 10, BOTTOM_KEYBOARD_Y) - 1);
	one_vram_buffer('M', NTADR_A(BOTTOM_KEYBOARD_X + 12, BOTTOM_KEYBOARD_Y) - 1);
	flush_vram_update2();
	ppu_on_all();
}

void keyboard_movement(void)
{

	// keyboard rows are 10, 9, 7
	if (pad1_new & PAD_LEFT)
	{
		if (cursor_x_level > 0)
		{
			--cursor_x_level;
		}
	}
	if (pad1_new & PAD_RIGHT)
	{
		if (cursor_y_level == 0 && cursor_x_level < 9)
		{
			++cursor_x_level;
		}
		if (cursor_y_level == 1 && cursor_x_level < 8)
		{
			++cursor_x_level;
		}
		if (cursor_y_level == 2 && cursor_x_level < 6)
		{
			++cursor_x_level;
		}
	}
	if (pad1_new & PAD_DOWN)
	{
		// if we're moving down a row, we've gotta move the keyboard correctly
		if (cursor_y_level == 0 && cursor_x_level == 9)
		{
			cursor_x_level = 8;
		}
		if (cursor_y_level == 1 && cursor_x_level == 8)
		{
			cursor_x_level = 6;
		}

		if (cursor_y_level < 2)
		{
			++cursor_y_level;
		}
	}
	if (pad1_new & PAD_UP)
	{

		if (cursor_y_level > 0)
		{
			--cursor_y_level;
		}
	}

	if (pad1_new & PAD_A)
	{
		// get keyboard character
		if (cursor_y_level == 0)
		{ // qwertyuiop
			cur_guess_char = keyboard_zero[cursor_x_level];
		}
		if (cursor_y_level == 1)
		{ // qwertyuiop
			cur_guess_char = keyboard_one[cursor_x_level];
		}
		if (cursor_y_level == 2)
		{ // qwertyuiop
			cur_guess_char = keyboard_two[cursor_x_level];
		}

		switch (cur_guess_space)
		{
		case 0:
			cur_guess_one = cur_guess_char;
			break;
		case 1:
			cur_guess_two = cur_guess_char;
			break;
		case 2:
			cur_guess_three = cur_guess_char;
			break;
		case 3:
			cur_guess_four = cur_guess_char;
			break;
		case 4:
			cur_guess_five = cur_guess_char;
			break;
		default:
			break;
		}
		if (cur_guess_space < 5)
		{
			++cur_guess_space;
		}
	}
	if (pad1_new & PAD_B)
	{

		switch (cur_guess_space)
		{
		// case 0:
		// 	cur_guess_one = ' ';
		// 	break;
		case 1:
			cur_guess_one = ' ';
			break;
		case 2:
			cur_guess_two = ' ';
			break;
		case 3:
			cur_guess_three = ' ';
			break;
		case 4:
			cur_guess_four = ' ';
			break;
		case 5:
			cur_guess_five = ' ';
			break;
		default:
			break;
		}
		if (cur_guess_space > 0)
		{
			--cur_guess_space;
		}
	}

	if (pad1_new & PAD_START)
	{
		if (cur_guess_level < 5)
		{
			submit_guess();
			reset_cur_level();
		}
	}
}

void select_word(void)
{
	// todo: randomly grab a word here
	// word_to_guess = "CARGO";
}

void submit_guess(void)
{

// check all the letters
#pragma region CHECK_LETTERS
	if (word_to_guess[0] == cur_guess_one)
	{
		check_one = CHECK_HIT;
	}
	else if (word_to_guess[1] == cur_guess_one || word_to_guess[2] == cur_guess_one || word_to_guess[3] == cur_guess_one || word_to_guess[4] == cur_guess_one)
	{
		check_one = CHECK_CLOSE;
	}
	else
	{
		check_one = CHECK_MISS;
	}

	if (word_to_guess[1] == cur_guess_two)
	{
		check_two = CHECK_HIT;
	}
	else if (word_to_guess[0] == cur_guess_two || word_to_guess[2] == cur_guess_two || word_to_guess[3] == cur_guess_two || word_to_guess[4] == cur_guess_two)
	{
		check_two = CHECK_CLOSE;
	}
	else
	{
		check_two = CHECK_MISS;
	}

	if (word_to_guess[2] == cur_guess_three)
	{
		check_three = CHECK_HIT;
	}
	else if (word_to_guess[0] == cur_guess_three || word_to_guess[1] == cur_guess_three || word_to_guess[3] == cur_guess_three || word_to_guess[4] == cur_guess_three)
	{
		check_three = CHECK_CLOSE;
	}
	else
	{
		check_three = CHECK_MISS;
	}

	if (word_to_guess[3] == cur_guess_four)
	{
		check_four = CHECK_HIT;
	}
	else if (word_to_guess[0] == cur_guess_four || word_to_guess[1] == cur_guess_four || word_to_guess[2] == cur_guess_four || word_to_guess[4] == cur_guess_four)
	{
		check_four = CHECK_CLOSE;
	}
	else
	{
		check_four = CHECK_MISS;
	}

	if (word_to_guess[4] == cur_guess_five)
	{
		check_five = CHECK_HIT;
	}
	else if (word_to_guess[0] == cur_guess_five || word_to_guess[1] == cur_guess_five || word_to_guess[2] == cur_guess_five || word_to_guess[3] == cur_guess_five)
	{
		check_five = CHECK_CLOSE;
	}
	else
	{
		check_five = CHECK_MISS;
	}
#pragma endregion

	// draw the old guess as BG tiles! then I don't have to save it
	// but have to do attribute table work, too hard.

	guess_X_1 = cur_guess_one;
	guess_X_1_status = check_one;

	guess_X_2 = cur_guess_two;
	guess_X_2_status = check_two;

	guess_X_3 = cur_guess_three;
	guess_X_3_status = check_three;

	guess_X_4 = cur_guess_four;
	guess_X_4_status = check_four;

	guess_X_5 = cur_guess_five;
	guess_X_5_status = check_five;

	switch (cur_guess_level)
	{
	case 0:
		guess_1_1 = guess_X_1;
		guess_1_1_status = guess_X_1_status;
		guess_1_2 = guess_X_2;
		guess_1_2_status = guess_X_2_status;
		guess_1_3 = guess_X_3;
		guess_1_3_status = guess_X_3_status;
		guess_1_4 = guess_X_4;
		guess_1_4_status = guess_X_4_status;
		guess_1_5 = guess_X_5;
		guess_1_5_status = guess_X_5_status;
		break;
	case 1:
		guess_2_1 = guess_X_1;
		guess_2_1_status = guess_X_1_status;
		guess_2_2 = guess_X_2;
		guess_2_2_status = guess_X_2_status;
		guess_2_3 = guess_X_3;
		guess_2_3_status = guess_X_3_status;
		guess_2_4 = guess_X_4;
		guess_2_4_status = guess_X_4_status;
		guess_2_5 = guess_X_5;
		guess_2_5_status = guess_X_5_status;
		break;

	case 2:
		guess_3_1 = guess_X_1;
		guess_3_1_status = guess_X_1_status;
		guess_3_2 = guess_X_2;
		guess_3_2_status = guess_X_2_status;
		guess_3_3 = guess_X_3;
		guess_3_3_status = guess_X_3_status;
		guess_3_4 = guess_X_4;
		guess_3_4_status = guess_X_4_status;
		guess_3_5 = guess_X_5;
		guess_3_5_status = guess_X_5_status;
		break;

	case 3:
		guess_4_1 = guess_X_1;
		guess_4_1_status = guess_X_1_status;
		guess_4_2 = guess_X_2;
		guess_4_2_status = guess_X_2_status;
		guess_4_3 = guess_X_3;
		guess_4_3_status = guess_X_3_status;
		guess_4_4 = guess_X_4;
		guess_4_4_status = guess_X_4_status;
		guess_4_5 = guess_X_5;
		guess_4_5_status = guess_X_5_status;
		break;

	case 4:
		guess_5_1 = guess_X_1;
		guess_5_1_status = guess_X_1_status;
		guess_5_2 = guess_X_2;
		guess_5_2_status = guess_X_2_status;
		guess_5_3 = guess_X_3;
		guess_5_3_status = guess_X_3_status;
		guess_5_4 = guess_X_4;
		guess_5_4_status = guess_X_4_status;
		guess_5_5 = guess_X_5;
		guess_5_5_status = guess_X_5_status;
		break;

	case 5:
		guess_6_1 = guess_X_1;
		guess_6_1_status = guess_X_1_status;
		guess_6_2 = guess_X_2;
		guess_6_2_status = guess_X_2_status;
		guess_6_3 = guess_X_3;
		guess_6_3_status = guess_X_3_status;
		guess_6_4 = guess_X_4;
		guess_6_4_status = guess_X_4_status;
		guess_6_5 = guess_X_5;
		guess_6_5_status = guess_X_5_status;
		break;
	}

	++cur_guess_level;
}

void reset_cur_level(void)
{
	cur_guess_space = 0;
	cur_guess_one = ' ';
	cur_guess_two = ' ';
	cur_guess_three = ' ';
	cur_guess_four = ' ';
	cur_guess_five = ' ';
}