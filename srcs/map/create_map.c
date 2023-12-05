#include "../../includes/fdf.h"

//1 2 3,0x.. 4 5\n
//7 8 9 7 8 \n
//1,0x56 3 6 3 2 \n

//file=>char1
//1 2 3,0x.. 4 5\n7 8 9 7 8 \n1,0x56 3 6 3 2 \n
char	*get_map_in_char1(int map_fd)
{
	char *map_str;
	char *gnl_tmp;
	char *map_tmp;

	gnl_tmp = get_next_line(map_fd);
	if (!gnl_tmp)
		return (NULL);
	map_str = ft_strdup("");
	if (!map_str)
		return (free(gnl_tmp), NULL);
	while(gnl_tmp)
	{
		map_tmp = ft_strjoin(map_str, gnl_tmp);
		if (!map_tmp) //necess ?
			return (free_char1(map_str), free_char1(gnl_tmp), NULL);
		free_char1(gnl_tmp);
		free_char1(map_str);
		map_str = map_tmp;
		gnl_tmp = get_next_line(map_fd);
	}	
	free_char1(gnl_tmp);
	return (map_str);
}

//1 2 3,0x.. 4 5\n7 8 9 7 8 6\n1,0x56 3 6 3 2 1\n

//char1=>char2
//1 2 3,0x.. 4 5
//7 8 9 7 8 
//1,0x56 3 6 3 2 
char	**get_map_in_char2(char *map_str)
{
	char **map_strs;

	if (!map_str)
		return (NULL);
	map_strs = ft_split(map_str, '\n');
	free(map_str);
	return (map_strs);
}

//1 2 3,0x.. 4 5
//7 8 9 7 8 
//1,0x56 3 6 3 2 

//char2=>char3
//1\2\3,0x..\4\5
//7\8\9\7\8\6
//1,0x56\3\6\3\2\1
char	***get_map_in_char3(char **map_strs)
{
	size_t i;
	char	***map_char3;

	if (!map_strs)
		return (NULL);
	map_char3 = (char ***) ft_calloc(char2len(map_strs) + 1, sizeof(char **));
	if(!map_char3)
		return(free_char2(map_strs), NULL);
	i = 0;
	while (map_strs[i])
	{
		map_char3[i] = ft_split(map_strs[i], ' ');
		if (!map_char3[i])
			return (free_char2(map_strs), free_char3(map_char3), NULL);
		i++;
	}
	return (free_char2(map_strs), map_char3);
}

t_map_elem	**fill_map_elem2(char ***map_char3, t_map_elem **map_elem2)
{
	size_t	i;
	size_t	j;
	char	**el_split;

	i = 0;
	el_split = NULL;
	while (map_char3[i])
	{
		j = 0;
		while (map_char3[i][j])
		{
			el_split = ft_split(map_char3[i][j], ',');
			if (!el_split)
				return (free_char3(map_char3), free_elem2(map_elem2), NULL);
			map_elem2[i][j] = (t_map_elem) {j, i, ft_atoi(el_split[0]),
				ft_atoi(el_split[0]), strhexa_to_colorint(el_split[1]), 0};
			free_char2(el_split);
			j++;
		}
		map_elem2[i][j] = (t_map_elem){0, 0, 0, 0, 0, 1}; //equivaut a map_elem2.end = 1 => detection de fin de ligne
		i++;
	}
	return(free_char3(map_char3), map_elem2);
}

//1\2\3,0x..\4\5
//7\8\9\7\8\6
//1,0x56\3\6\3\2\1

//char3=>map_elem2
//map[0][0] = 1  \map[0][1] = 2\ map[0][2] = 3,0x..\ map[0][3] = 4\ map[0][4] = 5 
// map[1][0] = 7  etc...->      \8\9\7\8\6
//1,0x56\3\6\3\2\1
t_map_elem	**create_map_elem2(char ***map_char3)
{
	size_t i;
	t_map_elem **map_elem2;

	if (!map_char3)
		return (NULL);
	map_elem2 = (t_map_elem **) ft_calloc(char3len(map_char3) + 1, sizeof(t_map_elem *));
	if (!map_elem2)
		return (free_char3(map_char3), NULL);
	while (map_char3[i])
	{
		map_elem2[i] = (t_map_elem *) ft_calloc(char2len(map_char3[i]) + 1, sizeof(t_map_elem));
		if (!map_elem2[i])
			return(free_map_elem2(map_elem2), free_char3(map_char3), NULL);
		i++;
	}
	return (fill_map_elem2 (map_char3, map_elem2));
}

