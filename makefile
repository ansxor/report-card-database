##
# Report Card Database Project
#
# @file
# @version 0.1

reportcard: dbmenu.c report_card.c database.c main.c
	clang $^ -o $@


# end
