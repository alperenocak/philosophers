/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuocak <yuocak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:31:18 by yuocak            #+#    #+#             */
/*   Updated: 2025/08/20 20:11:04 by yuocak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t	kilit;

// Bu fonksiyon her bir thread tarafından çalıştırılacak
void	*hello_world(void *threadid)
{
	pthread_mutex_lock(&kilit);
	for (int i = 0; i < 100; i++)
	{
		printf("%d\n", i);
	}
}

int	main(void)
{
	// Oluşturmak istediğimiz thread sayısı
	// int thread_sayisi = 100;
	pthread_t threads1;
	pthread_t thread2;
	// int rc;
	// long t;

	// Belirlenen sayıda thread oluşturup başlatıyoruz
	// for (int t = 0; t < thread_sayisi; t++)
	// {
	// printf("Ana program: Thread %ld oluşturuluyor...\n", t);

	// 'pthread_create' fonksiyonu ile yeni bir thread oluşturuyoruz
	// Parametreler:
	// 1. Thread nesnesinin adresi
	// 2. Thread özelliklerini belirten nitelikler (genellikle NULL)
	// 3. Thread'in çalıştıracağı fonksiyon
	// 4. Fonksiyona gönderilecek argüman (bu örnekte thread ID'si)
	pthread_create(&threads1, NULL, hello_world, NULL);
	pthread_create(&thread2, NULL, hello_world, NULL);

	// 	if (rc)
	// 	{
	// 		printf("Hata: return (kodu %d\n", rc);
	// 		// İşlem başarısız olursa programı sonlandır
	// 		return (1);
	// 	}
	// }

	pthread_join(threads1, NULL);

	printf("Tüm thread'ler tamamlandı.\n");

	// Programın başarılı bir şekilde sonlandığını belirtir
	return (0);
}