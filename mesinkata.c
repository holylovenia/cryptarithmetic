// HOLY LOVENIA - 13515113

/* File: mesinkata.c */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "mesinkar.h"
#include "mesinkata.h"
#include <stdio.h>

Kata CKata;
boolean EndKata;


void IgnoreBlank()
{
	while ((CC == BLANK) && (CC != MARK))
	{
		ADV();
	}
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA()
{
	START();
	IgnoreBlank();
	if (CC == MARK)
	{
		EndKata = true;
	}
	else
	{
		EndKata = false;
		SalinKata();
	}
}
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA()
{
	IgnoreBlank();
	if (CC == MARK)
	{
		EndKata = true;
	}
	else
	{
		SalinKata();
		IgnoreBlank();
	}
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata()
{
	// KAMUS
	int i;
	
		// ALGORITMA
		i = 0;
		while ((i < NMax) && (CC != NL) && (CC != MARK))
		{
			i++;
			CKata.TabKata[i] = CC;
			ADV();
		}
		CKata.Length = i;
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi{} 
          CC = BLANK atau CC = MARK{} 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
