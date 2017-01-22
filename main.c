// HOLY LOVENIA - 13515113
// IF2211 Strategi Algoritma (Bruteforce)


#include <stdio.h>
#include <time.h>


/* KAMUS GLOBAL, TIPE, FUNGSI, DAN PROSEDUR */

// Define
#define MaxNumber 10
#define NStringMax 100
#define NArrOfStringMax 100
#define NewLine '\n'
#define EndOfString '\0'
#define Operator '+'
#define boolean int
#define TRUE 1
#define FALSE 0
#define BLANK ' '

// Variabel
int count = 0;

// Tipe
typedef char String [NStringMax+1];
typedef struct
{
	String StringTab [NArrOfStringMax+1];
	int Neff;
} ArrOfString;
typedef struct
{
	char Alphabet;
	int Number;
} CollectionType;
typedef struct
{
	CollectionType Tab [MaxNumber+1];
	int Neff;
} AlphabetCollection;

// Fungsi dan Prosedur
boolean SearchAlphabet (char CC, AlphabetCollection AC)
{
	int i = 1;
	while ((AC.Tab[i].Alphabet != NewLine) && (AC.Tab[i].Alphabet != EndOfString) && (AC.Tab[i].Alphabet != CC))
	{
		i++;
	}
	
	return (AC.Tab[i].Alphabet == CC);
}

boolean SearchNumber (int N, int x, AlphabetCollection AC)
{
	int i = 1;
	while ((AC.Tab[i].Number != N) && (i < x))
	{
		i++;
	}
	
	return ((AC.Tab[i].Number == N) && (i < x));
}

long int Transform (String Sentence, AlphabetCollection AC)
{
	// KAMUS
	long int result;
	int	i, j;
	
		// ALGORITMA
		result = 0;
		j = 1;
		while (Sentence[j] != EndOfString)
		{
			for (i = 1; i <= AC.Neff; i++)
			{	
				if (Sentence[j] == AC.Tab[i].Alphabet)
				{
					if ((j == 1) && (AC.Tab[i].Number == 0))
					{
						return (-1);
					}
					result = result * 10 + AC.Tab[i].Number;
				}
			}
			j++;
		}
		return (result);
}

void Match (AlphabetCollection AC, ArrOfString Operand, String Result, String Divider)
{
	// KAMUS
	long int sum, outcome;
	int i, val;
	
		// ALGORITMA
		sum = 0;
		for (i = 1; i <= Operand.Neff; i++)
		{
			val = Transform(Operand.StringTab[i], AC);
			if (val == -1)
			{
				return;
			}
			else
			{
				sum += val;
			}
		}
		
		outcome = Transform(Result, AC);
		if (outcome == -1)
		{
			return;
		}
		else
		{		
			if (sum == outcome)
			{
				count++;
				for (i = 1; i <= Operand.Neff; i++)
				{
					printf("\n%ld", Transform(Operand.StringTab[i], AC));
				}
				printf("%c\n", Operator);
				i = 1;
				while (Divider[i] != EndOfString)
				{
					printf("%c", Divider[i]);
					i++;
				}
				printf("\n");
				printf("%ld\n\n", Transform(Result, AC));
			}
		}
}

void Solve (AlphabetCollection AC, ArrOfString Operand, String Result, String Divider, int x)
{
	// KAMUS
	int i;
	
		// ALGORITMA
		for (i = 0; i <= 9; i++)
		{
			if (x > AC.Neff)
			{
				Match(AC, Operand, Result, Divider);	
				break;
			}
			else
			{
				if (SearchNumber(i, x, AC))
				{
				}
				else
				{
					AC.Tab[x].Number = i;
					Solve(AC, Operand, Result, Divider, x+1);
				}
			}
		}
	
}

void ReadFile (String FileName, ArrOfString * Operand, String * Divider, String * Result, AlphabetCollection * AC)
{
	// KAMUS
	int i, j, iAC;
	FILE * F;
	char CC;
	
		// ALGORITMA
		F = fopen (FileName, "r");
		
		fscanf (F, "%c", &CC);		
		i = 0;
		iAC = 0;
		while (CC != Operator)
		{
			i++;
			j = 0;
			while ((CC != NewLine) && (CC != Operator))
			{
				if (CC != BLANK)
				{
					j++;
					(*Operand).StringTab[i][j] = CC;
					if (!SearchAlphabet(CC, *AC))
					{
						iAC++;
						(*AC).Tab[iAC].Alphabet = CC;
					}
				}
				fscanf (F, "%c", &CC);
			}
			(*Operand).StringTab[i][j+1] = EndOfString;
			if (CC == NewLine)
			{
				fscanf (F, "%c", &CC);
			}
		}
		(*Operand).Neff = i;
		fscanf (F, "%c", &CC); // NewLine
		fscanf (F, "%c", &CC);
		fscanf (F, "%c", &CC);
		j = 0;
		while (CC != NewLine)
		{
			j++;
			(*Divider)[j] = CC;
			fscanf (F, "%c", &CC);
		}
		fscanf (F, "%c", &CC);
		
		j = 0;
		while ((CC != NewLine) && (CC != EndOfString))
		{
			j++;
			(*Result)[j] = CC;
			if ((CC != BLANK) && (!SearchAlphabet(CC, *AC)))
			{
				iAC++;
				(*AC).Tab[iAC].Alphabet = CC;
			}
			fscanf (F, "%c", &CC);
		}
		(*AC).Tab[iAC+1].Alphabet = EndOfString;
		(*AC).Neff = iAC;
		
		
		for (i = 1; i <= (*Operand).Neff; i++)
		{
			printf("\n");
			j = 1;
			while ((*Operand).StringTab[i][j] != EndOfString)
			{
				printf("%c", (*Operand).StringTab[i][j]);
				j++;
			}
		}
		
		printf("%c\n", Operator);
		
		j = 1;
		printf("-");
		while ((*Divider)[j] != EndOfString)
		{
			printf("%c", (*Divider)[j]);
			j++;
		}
		printf("\n");
		
		j = 1;
		while ((*Result)[j] != EndOfString)
		{
			printf("%c", (*Result)[j]);
			j++;
		}
		printf("\n");
			
		fclose(F);
}


/* PROGRAM UTAMA */

int main ()
{
	// KAMUS
	ArrOfString Operand;
	String Divider;
	String Result;
	AlphabetCollection AC;
	clock_t begin, end;
	
	
		// ALGORITMA
		ReadFile("pitakar.txt", &Operand, &Divider, &Result, &AC);
		printf("\n");
		begin = clock();
		Solve(AC, Operand, Result, Divider, 1);
		if (count == 0)
		{
			printf("Tidak ada solusi\n");
		}
		end = clock();
		printf("Execution time: %lf ms\n", (double) (end-begin) * 1000 / CLOCKS_PER_SEC);
}