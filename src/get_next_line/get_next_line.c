/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:23:54 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Toglie dal buffer di lettura la riga gia' consegnata al chiamante.
 *
 * @param fcontent Buffer di lettura. Puo' essere NULL.
 * @return char * Il resto del buffer in una nuova stringa, NULL se non era
 *         rimasto altro; il buffer vecchio viene liberato.
 */
char	*ft_freecontent(char *fcontent)
{
	char	*tmp;
	int		start;
	int		size;

	start = 0;
	if (fcontent == NULL)
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	if (fcontent[start] == '\0')
	{
		free (fcontent);
		return (NULL);
	}
	size = start + 1;
	while (fcontent[size] != '\0')
		size++;
	tmp = ft_calloc(size - start + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (fcontent[start + 1] != '\0')
		tmp[size++] = fcontent[(start++) + 1];
	free(fcontent);
	return (tmp);
}

/**
 * @brief Copia in una nuova stringa la prima riga del buffer di lettura.
 *
 * @param fcontent Buffer di lettura. Puo' essere NULL.
 * @return char * La riga allocata, a capo finale compreso se c'e'; NULL se il
 *         buffer e' vuoto o NULL.
 */
char	*ft_extractline(char *fcontent)
{
	char	*line;
	int		start;
	int		i;

	i = 0;
	start = 0;
	if (fcontent == NULL || fcontent[0] == '\0')
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	line = ft_calloc(start + 1 + (fcontent[start] == '\n'), sizeof(char));
	if (line == NULL)
		return (NULL);
	if (fcontent[start] == '\n')
		start++;
	while (i < start && fcontent[i] != '\0')
	{
		line[i] = fcontent[i];
		i++;
	}
	return (line);
}

/**
 * @brief Legge dal file finche' non trova un a capo o la fine.
 *
 * Legge a blocchi di BUFFER_SIZE byte e accoda quello che trova al buffer di
 * lettura.
 *
 * @param fd Descrittore aperto in lettura.
 * @param buffer Area di appoggio grande BUFFER_SIZE + 1 byte.
 * @param fcontent Buffer di lettura da estendere; puo' essere NULL la prima
 *        volta.
 * @return char * Il buffer di lettura aggiornato, NULL se la read fallisce.
 */
char	*ft_readline(int fd, char *buffer, char *fcontent)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!fcontent)
			fcontent = ft_calloc(2, sizeof(char));
		tmp = fcontent;
		fcontent = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (fcontent);
}

/**
 * @brief Restituisce la riga successiva di un file, a capo finale compreso.
 *
 * Quello che viene letto oltre la riga resta conservato in un array statico
 * indicizzato dal descrittore, quindi piu' file possono essere letti
 * contemporaneamente senza che le letture si mescolino. Richiede BUFFER_SIZE
 * maggiore di zero.
 *
 * @param fd Descrittore aperto in lettura, minore di 4096.
 * @return char * La riga allocata, da liberare con free; NULL a fine file, se
 *         fd non e' valido o in caso di errore.
 */
char	*get_next_line(int fd)
{
	static char	*fcontent[4096];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (ft_strchr(fcontent[fd], '\n') == NULL)
		fcontent[fd] = ft_readline(fd, buffer, fcontent[fd]);
	free(buffer);
	line = ft_extractline(fcontent[fd]);
	if (!line)
	{
		free(fcontent[fd]);
		fcontent[fd] = NULL;
		return (NULL);
	}
	fcontent[fd] = ft_freecontent(fcontent[fd]);
	return (line);
}
