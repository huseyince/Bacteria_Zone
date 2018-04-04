#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Author: Hüseyin ALTUNAKAYNAK
// Date: 07.05.2016
// GCC 5.4.0
// Version: 1.0

int main(int argc, char const *argv[])
{
	char sinama[20], birSatir[20];
	char *c;
	char bakteri[50] = { '\0' }; // dizideki karakterleri sıfırlıyoruz
	char rule[250] = { '\0' };
	int sayac = 0, temp1, temp2, satir, sutun, kacDongu;

	FILE * cfPtr;

	// Kuralların olduğu dosyayı ekrana yazdırmak için
	if ((cfPtr = fopen("data.txt", "r")) == NULL)
		printf("Dosya açılamadı.\n");
	else {
		do {
			c = fgets(birSatir, 100, cfPtr); /* bir satir okuyalim */
			if (c != NULL)
				printf("%s", birSatir); /* ekrana yazalim   */
		} while (c != NULL);
	}
	fclose(cfPtr);

	// Program kaç adım ilerleyecek ?
	printf("\nDöngünün kaç kere tekrar etmesini istiyorsunuz:");
	scanf("%d", &kacDongu);
	printf("\n");

	// Dosyayı tekrardan okuduk.
	if ((cfPtr = fopen("data.txt", "r")) == NULL)
		printf("Dosya açılamadı.\n");
	else {
		fscanf(cfPtr, "%s", sinama);

		// Bakterileri çekiyoruz.
		if (sinama[0] == 'b') {
			while (true) {
				fscanf(cfPtr, "%s", sinama);
				if (sinama[0] != 'r')
					bakteri[sayac] = sinama[0];
				sayac++;
				if (sinama[0] == 'r')
					break;
			}
		}
		sayac = 0;

		// Kuralları oluşturma aşaması
		if (sinama[0] == 'r') {
			while (true) {
				fscanf(cfPtr, "%s", sinama);
				if (sinama[0] != 's') {
					rule[sayac] = sinama[0];
					fscanf(cfPtr, "%s", sinama);
					fscanf(cfPtr, "%s", sinama);
					sayac++;
					rule[sayac] = sinama[0];
				}
				sayac++;
				if (sinama[0] == 's')
					break;
			}
		}
		sayac = 0;

		// Bakterilerin yerleştirilip çoğalacağı matrisin oluşumu
		fscanf(cfPtr, "%d %s %d", &satir, sinama, &sutun);

		char **matris;
		char **ekstraMatris;
		
		matris = (char **)malloc(sizeof(char *)*satir);
		for (int y = 0; y < satir; y++)
		{
			matris[y] = (char *)malloc(sizeof(char)*sutun);
		}
		ekstraMatris = (char **)malloc(sizeof(char *)*satir);
		for (int y = 0; y < satir; y++)
		{
			ekstraMatris[y] = (char *)malloc(sizeof(char)*sutun);
		}

		// Matrisin bütün değerlerini NULL yapıyoruz.
		for (int y = 0; y < satir; y++)
		{
			for (int t = 0; t < sutun; t++)
			{
				matris[y][t] = '\0';
				ekstraMatris[y][t] = '\0';
			}
		}

		for (int y = 0; y < satir; y++)
		{
			for (int t = 0; t < sutun; t++)
			{
				matris[y][t] = '\0';
				ekstraMatris[y][t] = '\0';
			}
		}

		// Bakterileri başlangıç konumlarına yerleştirme
		fscanf(cfPtr, "%s", sinama);
		while (!feof(cfPtr)) {
			fscanf(cfPtr, "%s %d %d", sinama, &temp1, &temp2);
			matris[temp1][temp2] = sinama[0];
		}

		// Bakterileri yerleştirdikten sonra NULL olan
		// yerleri boşluk karakteri ile doldurduk
		// güzel gözükmesi için		
		for (int tempk1 = 0; tempk1 < satir; tempk1++)
		{
			for (int tempk2 = 0; tempk2 < sutun; tempk2++)
			{
				if (matris[tempk1][tempk2] == '\0')
					matris[tempk1][tempk2] = ' ';
				
				printf("[%c]", matris[tempk1][tempk2]);
				if (matris[tempk1][tempk2] == ' ')
					matris[tempk1][tempk2] = '\0';
			}
			printf("\n");
		}
		printf("Start\n\n");

		// Kuralların gerçeklemesi
		for (int den = 1; den <= kacDongu; den++) {
			while (bakteri[sayac] != '\0') {
				for (int i = 0; i < satir; i++)
				{
					for (int j = 0; j < sutun; j++)
					{
						if (matris[i][j] == bakteri[sayac]) {
							// ----------------------------
							if (j != (sutun - 1) && sutun != 0) {
								if (matris[i][j + 1] == '\0' || matris[i][j + 1] == bakteri[sayac])
									ekstraMatris[i][j + 1] = bakteri[sayac];
								else {
									for (int k = 1; rule[k] != '\0'; k += 2)
									{
										if (matris[i][j + 1] == rule[k] && rule[k - 1] == bakteri[sayac])
											ekstraMatris[i][j + 1] = bakteri[sayac];
									}
								}
							}
							// ----------------------------
							if (j != 0) {
								if (matris[i][j - 1] == '\0' || matris[i][j - 1] == bakteri[sayac])
									ekstraMatris[i][j - 1] = bakteri[sayac];
								else {
									for (int k = 1; rule[k] != '\0'; k += 2)
									{
										if (matris[i][j - 1] == rule[k] && rule[k - 1] == bakteri[sayac])
											ekstraMatris[i][j - 1] = bakteri[sayac];
									}
								}
							}
							// ----------------------------
							if(i!=satir-1)
							if (matris[i + 1][j] == '\0' || matris[i + 1][j] == bakteri[sayac])
								ekstraMatris[i + 1][j] = bakteri[sayac];
							else {
								for (int k = 1; rule[k] != '\0'; k += 2)
								{
									if (matris[i + 1][j] == rule[k] && rule[k - 1] == bakteri[sayac])
										ekstraMatris[i + 1][j] = bakteri[sayac];
								}
							}
							// ----------------------------
							if (i != 0)
								if ((matris[i - 1][j] == '\0' || matris[i - 1][j] == bakteri[sayac]))
									ekstraMatris[i - 1][j] = bakteri[sayac];
								else {
									for (int k = 1; rule[k] != '\0'; k += 2)
									{
										if (matris[i - 1][j] == rule[k] && rule[k - 1] == bakteri[sayac])
											ekstraMatris[i - 1][j] = bakteri[sayac];
									}
								}
						}
					}
				}

				// Geçici verileri tutmak için oluşturduğumuz
				// ekstra matristen NULL'a eşit olmayan verileri
				// asıl matrise aktarıyoruz. 
				for (int y = 0; y < satir; ++y)
				{
					for (int t = 0; t < sutun; ++t)
					{
						if (ekstraMatris[y][t] != '\0')
							matris[y][t] = ekstraMatris[y][t];
					}
				}

				sayac++;
			}
			sayac = 0;

			// O anki durumu yazdırmak için NULL olan değerleri
			// boşluğa çevirip yazdırdıktan sonra tekrar NULL 
			// yapıyoruz. Tamamen o anki ruh halim ile alakalı.
			for (temp1 = 0; temp1 < satir; temp1++)
			{
				for (temp2 = 0; temp2 < sutun; temp2++)
				{
					if (matris[temp1][temp2] == '\0')
						matris[temp1][temp2] = ' ';
					printf("[%c]", matris[temp1][temp2]);
					if (matris[temp1][temp2] == ' ')
						matris[temp1][temp2] = '\0';
				}
				printf("\n");
			}
			printf("%d. Turn\n\n", den);

			// Verileri tuttuğumuz ekstra matrisi sıfırlıyoruz.
			for (int y = 0; y < satir; y++)
			{
				for (int t = 0; t < sutun; t++)
				{
					ekstraMatris[y][t] = '\0';
				}
			}
		}
	}
	fclose(cfPtr);
	system("pause");
	return 0;
}