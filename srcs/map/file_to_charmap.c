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
			return (free_char1(&map_str), free_char1(&gnl_tmp), NULL);
		free_char1(&gnl_tmp);
		free_char1(&map_str);
		map_str = map_tmp;
		gnl_tmp = get_next_line(map_fd);
	}	
	free_char1(&gnl_tmp);
	ft_printf("map char 1 =%s", map_str);//
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
		return(free_char2(&map_strs), NULL);
	i = 0;
	while (map_strs[i])
	{
		map_char3[i] = ft_split(map_strs[i], ' ');
		if (!map_char3[i])
			return (free_char2(&map_strs), free_char3(&map_char3), NULL);
		i++;
	}
	return (free_char2(&map_strs), map_char3);
}

