#ifndef LEM_IN_BONUS_H
# define LEM_IN_BONUS_H

# include "get_next_line.h"
# include <stdio.h>

# define LINK "%c%c%c%c", 0xF0, 0x9F, 0x94, 0x97
# define ST_FLAG "%c%c%c%c", 0xF0, 0x9F, 0x9A, 0xA9
# define FINISH "%c%c%c%c", 0xF0, 0x9F, 0x8F, 0x81
# define ANT "%c%c%c%c", 0xF0, 0x9F, 0x90, 0x9C
# define HOUSE "%c%c%c%c", 0xF0, 0x9F, 0x8F, 0xA0

void    ft_handle_error(void);

#endif