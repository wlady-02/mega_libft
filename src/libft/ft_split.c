/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:01:58 by dwilun            #+#    #+#             */
/*   Updated: 2026/09/17 11:24:06 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mega_libft.h"

/**
 * @brief Conta i gruppi di caratteri separati da un delimitatore.
 *
 * Funzione di servizio di ft_split, serve a dimensionare la matrice.
 *
 * @param s Stringa da esaminare. Non puo' essere NULL.
 * @param c Carattere separatore.
 * @return int Il numero di parole trovate.
 */
static int	ft_count_words(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

/**
 * @brief Estrae in una nuova stringa la parola che inizia a una data posizione.
 *
 * @param s Stringa da cui estrarre. Non puo' essere NULL.
 * @param c Carattere separatore che chiude la parola.
 * @param index Posizione di partenza; viene spostata sul separatore finale.
 * @return char * La parola allocata, NULL se l'allocazione fallisce.
 */
static char	*ft_fill_matrix(char *s, char c, int *index)
{
	int		i;
	int		j;
	char	*word;

	i = *index;
	j = 0;
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	word = (char *)ft_calloc(j + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + i, j + 1);
	*index = i + j;
	return (word);
}

/**
 * @brief Libera una matrice di stringhe rimasta a meta'.
 *
 * Serve a ft_split per non perdere memoria quando un'allocazione fallisce prima
 * che la matrice sia completa.
 *
 * @param s Matrice da liberare.
 * @param w Indice dell'ultima stringa da liberare.
 * @return void * Sempre NULL, cosi' il chiamante puo' restituirlo direttamente.
 */
static void	*ft_free_matrix(char **s, int w)
{
	while (w >= 0)
	{
		free(s[w]);
		w--;
	}
	free(s);
	return (NULL);
}

/**
 * @brief Spezza una stringa in parole separate da un delimitatore.
 *
 * @param s Stringa da spezzare. Non puo' essere NULL.
 * @param c Carattere separatore.
 * @return char ** Una matrice terminata da NULL, da liberare stringa per
 *         stringa e poi nell'insieme; NULL se un'allocazione fallisce.
 */
char	**ft_split(char const *s, char c)
{
	int		nwords;
	char	**str;
	int		w;
	int		i;

	nwords = ft_count_words((char *)s, (char)c);
	str = (char **)ft_calloc(nwords + 1, sizeof(char *));
	if (!str)
		return (NULL);
	w = -1;
	i = 0;
	while (++w < nwords)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			str[w] = ft_fill_matrix((char *)s, c, &i);
			if (str[w] == NULL)
				return (ft_free_matrix(str, w));
		}
	}
	str[w] = NULL;
	return (str);
}
