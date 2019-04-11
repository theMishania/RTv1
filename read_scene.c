#include "RTv1.h"

void reading_error(void)
{
	ft_putendl("error");
	exit(-2);
}
/*
t_obj *new_object(t_scene *scene)
{
	t_obj **tmp;

	tmp = &(scene->objs);
	if (!(*tmp))
	{
		(*tmp) = (t_obj *)malloc(sizeof(t_obj));//check
		(*tmp)->next = NULL;
		puts("first obj");
		return (*tmp);

	}
	while (*tmp)
		*tmp = (*tmp)->next;
	(*tmp) = (t_obj *)malloc(sizeof(t_obj));//check
	(*tmp)->next = NULL;
	puts("some else obj");
	return (*tmp);
}*/

t_vector read_vector(char *str)
{
	t_vector ret;

	while (*str == ' ' || *str == '\t' || *str == '(')
		str++;
	ret.x = ft_atof(str);
	str = ft_strchr(str, ',') + 1;
	ret.y = ft_atof(str);
	str = ft_strchr(str, ',') + 1;
	ret.z = ft_atof(str);

	return (ret);
}

void set_obj_type(char *line, t_obj *obj)
{
	if (ft_strstr(line, "sphere"))
		obj->type = sphere;
	else if (ft_strstr(line, "cylinder"))
		obj->type = cylinder;
	else if (ft_strstr(line, "cone"))
		obj->type = cone;
	else if (ft_strstr(line, "plane"))
		obj->type = plane;
	else
		reading_error();
}

void set_light_type(char *line, t_light *light)
{
	if (ft_strstr(line, "point"))
		light->type = point;
	else if (ft_strstr(line, "directional"))
		light->type = directional;
	else if (ft_strstr(line, "ambient"))
		light->type = ambient;
	else
		reading_error();
}

t_obj *read_obj_parameters(char *line, t_obj **obj)
{
	if (ft_strchr(line, '}'))
		return (NULL);
	else if (ft_strstr(line, "type"))
		set_obj_type(line, *obj);
	else if (ft_strstr(line, "position"))
		(*obj)->center = read_vector(ft_strchr(line, '=') + 1);
	else if (ft_strstr(line, "radius"))
		(*obj)->radius = ft_atof(ft_strchr(line, '=') + 1);
	else if (ft_strstr(line, "color"))
		(*obj)->rgb = color_to_rgb(atoi(ft_strchr(line, '=') + 1));
	else if (ft_strstr(line, "angle"))
		(*obj)->angle = ft_atof(strchr(line, '=') + 1);
	else if (ft_strstr(line, "direction"))
		(*obj)->dir = vector_normalize(read_vector(ft_strchr(line, '=') + 1));
	else if (ft_strstr(line, "specular"))
		(*obj)->specular = ft_atof(ft_strchr(line, '=') + 1);
	else if (ft_strstr(line, "reflective"))
		(*obj)->reflective = ft_atof(ft_strchr(line, '=') + 1);
	return (*obj);
}

t_light *read_light_parameters(char *line, t_light **light)
{
	if (ft_strchr(line, '}'))
		return (NULL);
	else if (ft_strstr(line, "type"))
		set_light_type(line, *light);
	else if (ft_strstr(line, "position"))
		(*light)->center = read_vector(ft_strchr(line, '=') + 1);

	else if (ft_strstr(line, "direction"))
		(*light)->dir = vector_normalize(read_vector(ft_strchr(line, '=') + 1));

	else if (ft_strstr(line, "intensity"))
		(*light)->intensity = ft_atof(ft_strchr(line, '=') + 1);
	return (*light);
}

t_camera *camera_init(char *line, t_camera *camera)
{
	if (ft_strchr(line, '}'))
	{
	//	puts("camera inited");
		return (NULL);
	}
	else if (ft_strstr(line, "position"))
		camera->center = read_vector(ft_strchr(line, '=') + 1);
	else if (ft_strstr(line, "direction"))
		camera->dir = read_vector(ft_strchr(line, '=') + 1);
	return (camera);
}

void read_line_set_scene(char *line, t_scene *scene)
{
	static int i = -1;
	static int j = -1;
	static t_obj *obj = NULL;
	static t_light *light = NULL;
	static t_camera *camera = NULL;
	if (ft_strstr(line, "camera_init"))
		camera = camera_init(line, &(scene->camera));



	if (obj)
	{
		obj = read_obj_parameters(line, &obj);
	}
	else if (light)
	{
		light = read_light_parameters(line, &light);
	}

	else if (camera)
	{
		camera = camera_init(line, camera);
	}

	else if (ft_strstr(line, "new"))
	{
		if (ft_strstr(line, "object"))
		{
			i++;
			obj = &(scene->objs[i]);
		}

		else if (ft_strstr(line, "light"))
		{
			j++;
			light = &(scene->lights[j]);
		}
	}
	else if (!ft_strcmp(line, "end"))
	{
		scene->c_objs = i + 1;
		scene->c_lights = j + 1;
	}

}

void read_scene(t_scene *scene, char* file_name)
{
	int fd;
	char *line;

	fd = open(file_name, O_RDONLY);//check
	while (get_next_line(fd, &line) == 1)
	{
		read_line_set_scene(line, scene);

		free(line);
	}
	free(line);
	close(fd);
}