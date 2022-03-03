/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_creator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cleonia <1-d_x_d-1@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:13:43 by Cleonia           #+#    #+#             */
/*   Updated: 2022/03/03 16:28:08 by Cleonia          ###   ########.fr       */
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

# define FILE_LEN 23

enum e_type
{
	TYPE_CPP = 1,
	TYPE_C = 0
};

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

int get_type_flag(int argc, char **argv)
{
	int type_flag;

	type_flag = TYPE_C;
	if (argc > 1 && strlen(argv[1]) > 1)
		type_flag = TYPE_CPP;
	return (type_flag);
}

string *get_make_template(int type_flag)
{
	ifstream fin;

	if (type_flag == TYPE_CPP)
		fin.open("cpp_pattern.mc");
	if (type_flag == TYPE_C)
		fin.open("c_pattern.mc");
	if (!fin)
	{
		cout << "pattern file open error" << endl;
		exit (0);
	}

	string *temp;

	temp = new string[23];
	for (int i = 0; i < 23; i++)
		getline(fin, temp[i]);
	return (temp);
}

void add_files_in_srcs(string *temp, char **files_cpp, char **files_hpp)
{
	int i = -1;
	while (files_cpp && files_cpp[++i])
		temp[3] = temp[3] + files_cpp[i] + " ";
	i = -1;
	while (files_hpp && files_hpp[++i])
		temp[8] = temp[8] + " " + files_hpp[i];
}

int main(int argc, char **argv)
{
	string	prog_path;
	string	*temp;
	char	**files_hpp;
	char	**files_cpp;
	int		type_flag;
	
	type_flag = get_type_flag(argc, argv);
	temp = get_make_template(type_flag);
	prog_path = ".";
	files_hpp = NULL;
	files_cpp = NULL;

	if (argc > 2)
	{
		if (type_flag == TYPE_CPP)
		{
			files_cpp = read_dirrectory(argv[2], (char *)"cpp");
			files_hpp = read_dirrectory(argv[2], (char *)"hpp");
		}
		if (type_flag == TYPE_C)
		{
			files_cpp = read_dirrectory(argv[2], (char *)"c");
			files_hpp = read_dirrectory(argv[2], (char *)"h");
		}
		prog_path = argv[2];
	}

	add_files_in_srcs(temp, files_cpp, files_hpp);

	if (argc > 3)
		temp[0] += argv[3];
	else
		temp[0] += "a.out";

	ofstream fout(prog_path + "/Makefile");
	if (!fout)
	{
		cout << "create Makefile error" << endl;
		exit (1);
	}
	for(int i = 0; i < 23; i++)
		fout << temp[i] << endl;
	return (0);
}

