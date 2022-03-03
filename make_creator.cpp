/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_creator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cleonia <1-d_x_d-1@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:13:43 by Cleonia           #+#    #+#             */
/*   Updated: 2022/03/03 13:13:54 by Cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <string>
# include <fstream>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h> 
# include <stdlib.h>

using namespace std;

typedef struct s_list
{
    char *file_name;
    struct s_list *next;
}   t_list;

int extension_check(char *file_name, char *file_extension)
{
    char *dot = NULL;

    while (*file_name)
    {
        if (*file_name == '.')
            dot = file_name + 1;
        file_name++;
    }
    if (!dot || strcmp(dot, file_extension) != 0)
        return (0);
    return (1);
}

char **read_dirrectory(char *dir_path, char *file_extension)
{
    DIR *dir;

    dir = opendir(dir_path);
    if (!dir)
    {
        cout << "path error" << endl;
        exit(1);
    }

    struct dirent *entry;
    t_list *list;
    t_list *first_list;
    int list_len = 0;

    list = (t_list *)malloc(sizeof(t_list));
    list->next = NULL;
    first_list = list;
    while ((entry = readdir(dir)) != NULL)
    {
        if (extension_check(entry->d_name, file_extension))
        {
            list->file_name = (char *)malloc(sizeof(char) * strlen(entry->d_name));
            strcpy(list->file_name, entry->d_name);
            list->next = (t_list *)malloc(sizeof(t_list));
            list = list->next;
            list_len++;
        }
    };
    closedir(dir);

    char **name_mas = (char **)malloc(sizeof(char *) * list_len + 1);
    int i = 0;
    for(; i < list_len; i++)
    {
        name_mas[i] = first_list->file_name;
        first_list = first_list->next;
    }
    name_mas[i] = NULL;
    return (name_mas);
}

int main(int argc, char **argv)
{
	string temp[] =
	{
		"NAME	=\t",
		"CPP		=\tc++ -Wall -Wextra -Werror -std=c++98",
		"SRCS	=\t",
		"OBJ		=\t$(SRCS:.cpp=.o)",
		"all		:\t$(NAME)",
		"%.o		:\t%.cpp",
		"			$(CPP) -c $< -o $@",
		"$(NAME)	:\t$(OBJ) MAKEFILE",
		"			$(CPP) $(OBJ) -o $(NAME)",
		"clean	:",
		"			rm -f $(OBJ)",
		"fclean	:\tclean",
		"			rm -f $(NAME)",
		"re		:\tfclean all",
		".PHONY	:\tall clean fclean re"
	};

	string prog_path = ".";
	char **files_cpp = NULL;
	char **files_hpp = NULL;
	if (argc > 1)
	{
		files_cpp = read_dirrectory(argv[1], (char *)"cpp");
		files_hpp = read_dirrectory(argv[1], (char *)"hpp");
		prog_path = argv[1];
	}
	string prog_name = "";
	if (argc > 2) 
		prog_name = argv[2];

	ofstream fout(prog_path + "/Makefile");
	fout 	<< temp[0] << prog_name << endl << endl
			<< temp[1] << endl
			<< temp[2];
	for (int i = 0; files_cpp && files_cpp[i] != NULL; i++)
		fout << files_cpp[i] << " ";
	fout	<< endl
			<< temp[3] << endl << endl
			<< temp[4] << endl << endl
			<< temp[5];
	for (int i = 0; files_hpp && files_hpp[i] != NULL; i++)
		fout << " " << files_hpp[i];
	fout	<< endl
			<< temp[6] << endl << endl
			<< temp[7] << endl
			<< temp[8] << endl << endl
			<< temp[9] << endl
			<< temp[10] << endl << endl
			<< temp[11] << endl
			<< temp[12] << endl << endl
			<< temp[13] << endl << endl
			<< temp[14] << endl;
	return (0);
}