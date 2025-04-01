// #include <stdio.h>

// // void	swap(int *a, int *b)
// // {
// // 	int temp;

// // 	temp = *a;
// // 	*a = *b;
// // 	*b = temp;
// // }

// void	swap_words(char **a, char **b)
// {
// 	char *temp;

// 	temp = *a;
// 	*a = *b;
//     *b = temp;
// }

// // void sort_tab(int *tab, int len)
// // {
// // 	int i = 0;
// // 	int j = 1;
// // 	while(i < len && j < len)
// // 	{
// // 		if (tab[i] > tab[j])
// // 			swap(&tab[i], &tab[j]);
// // 		else
// // 			j++;
// // 		if (j == len)
// // 		{
// // 			i++;
// // 			j = i + 1;
// // 		}
// // 	}
// // }

// // ret 1 = swap nec
// // ret 0 = PAS de swap
// int	compare_words(char *w1, char *w2)
// {
// 	int i = 0;

// 	while (w1[i] && w2[i])
// 	{
// 		if (w1[i] < w2[i])
// 			return 0;// 
// 		if (w1[i] > w2[i])
// 			return 1;// b > a SWAP
// 		if  (w1[i] == w2[i])
// 			i++;
// 	}
//     if (w1[i])
// 		return 1;
// 	else
// 		return 0;
// }

// void	sort_words(char	**words, int len)
// {
// 	int	i = 0;
// 	int	j = 1;
// 	int c = 0;


// 	while(i < len && j < len)
// 	{
// 		if (compare_words(words[i], words[j]) == 1)
// 			swap_words(&words[i], &words[j]);
// 		else
// 			j++;
// 		if (j == len)
// 		{
// 			i++;
// 			j = i + 1;
// 		}
// 	}
// }

// int main()
// {
// 	int	tab[7] = {3, 1, 9, 7, 6, 2, 4};
// 	int	len = 5;
// 	int i = 0;
// 	// sort_tab(tab, len);

// 	char *words[5] = {"efeu", "Llise", "eair", "eai", " u"};
// 	sort_words(words, 5);

// 	while (i < len)
// 	{
// 		// printf("%i\n", tab[i]);
// 		printf("%s\n", words[i]);
// 		i++;
// 	}
// 	return 0;
// }