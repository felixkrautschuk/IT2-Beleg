//Gausscher Algorithmus mit Pivotisierung  Stand 8.12.2012
//maximal 100 Gleichungen
//Genauigkeit des Ausdrucks betraegt nur 2 Dezimalen
//Achtung: die Spaltenanzahl der Matrix a in  der Kopfzeile der Funktion 
//Gaussalg muss immer als Konstante den Wert n+1 erhalten, 
//d.h. um eins groesser als die Anzahl der Unbekannten sein (rechte Seite!)

#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>

//  Gauss'sches Eliminationsverfahren mit Zeilenpivotisierung
//    Argumente:
//    float a[N][n+1]  erweiterte Koeffizientenmatrix         Read/Write
//            N        Anzahl der Gleichungen
//    int n            Anzahl der Unbekannten                 Read
//    float x[n]       Loesungen                              Write
//    int* r           Rangzahl (wird bei Rangabfall belegt)  Write
//    int druck        1 Druckprotokoll,0 kein Protokoll      Read
//    float *det       Determinante der Koeffizientenmatrix   Write 
//  Resultat: (Rueckkehrwert von Gaussalg)
//             0 fuer Widerspruch - unloesbar
//             1 fuer eindeutig loesbar
//             2 fuer mehrdeutig loesbar und Rang=r,
//                    Anzahl der Parameter ist n-r
//Beachte: Ist N<n, dann muss aber trotzdem die Koeffizientenmatrix
//                  mit N=n deklariert werden, aber die fehlenden Gleichungen
//                  müssen nicht eingegeben werden!
//         Ist N>n, dann muss die Koeffizientenmatrix mit N Zeilen deklariert werden  
int Gaussalg(float a[][4], int n, float x[], int *r, int druck, float *det)
//Spaltenanzahl muss immer angepasst werden, immer n+1!
{
	int   i, j;                      // Zeile, Spalte
	int   s;                         // Elimininationsschritt
	int   pzeile;                    // Pivotzeile
	float f;                         // Multiplikationsfaktor
	float h = 0.0f, h1;                 // Hilfsvariable zur Identifikation mehrdeutige Loesg.
	float Epsilon = 0.000001f;       // Genauigkeit
	float Maximum;                   // Zeilenpivotisierung
	float mf[100];                   // Speicher Multiplikationsfaktor für Druck

	s = 0; mf[0] = 0.0f; *det = 0.0f;

	//Ausgabe Original-Matrix 
	if (druck) {
		printf("Original-Koeffizientenmatrix mit rechter Seite:\n");
		for (i = 0; i < n; i++) {
			printf("\n");
			for (j = 0; j <= n; j++) printf("%7.2f   ", a[i][j]);
		}
	}
	do {             // die einzelnen Eliminationsschritte
		Maximum = fabs(a[s][s]);   // groesstes Element
		if (Maximum < Epsilon)  break;
		//nicht eindeutig loesbar oder Widerspruch (unloesbar)
		if (druck) printf("\n\nSchritt %2i von %2i", s + 1, n - 1);
		pzeile = s;               // suchen
		for (i = s + 1; i < n; i++)
			if (fabs(a[i][s]) > Maximum) {
				Maximum = fabs(a[i][s]);
				pzeile = i;
			};

		if (pzeile != s)  // falls erforderlich, Zeilen tauschen
		{
			for (j = s; j <= n; j++) {
				h1 = a[s][j];
				a[s][j] = a[pzeile][j];
				a[pzeile][j] = h1;
			}
			if (druck) printf("  (Tausch Zeile %2i mit %2i)\n", pzeile + 1, s + 1);
			else printf("\n");
		}

		// Elimination --> Nullen in Spalte s ab Zeile s+1
		for (i = s + 1; i < n; i++) {
			f = -(a[i][s] / a[s][s]); mf[i] = f;      // Multiplikationsfaktor
			a[i][s] = 0.0f;
			for (j = s + 1; j <= n; j++)   // die einzelnen Spalten
				a[i][j] += f*a[s][j];       // Addition der Zeilen i, s
		}
		//Ausgabe Matrix nach jedem Schritt
		if (druck) {
			for (i = 0; i < n; i++) {
				printf("\n");
				for (j = 0; j <= n; j++) printf("%7.2f   ", a[i][j]);
				if (i>s) printf("%7.2f   ", mf[i]);
			}
		}
		s++;
	} while (s < n - 1);

	*r = s;
	h = 0.0f;
	for (j = 0; j < n; j++)
	{
		h = h + a[s][j];
	}
	if (fabs(h)<0.00001f) {
		if (fabs(a[s][s + 1])<0.00001f) return 2;
		else return 0;
	}

	// Berechnen der Loesungen aus der entstandenen Dreiecksmatrix
	// letzte Zeile
	x[n - 1] = a[n - 1][n] / a[n - 1][n - 1];
	// restliche Zeilen
	for (i = n - 2; i >= 0; i--)
	{
		for (j = n - 1; j > i; j--)
		{
			a[i][n] -= x[j] * a[i][j];    // rechte Seite berechnen
		}
		x[i] = a[i][n] / a[i][i];       // Loesung
	}
	// Wert der Determinante (=Produkt der Hauptdiagonalelemente)
	f = 1.0f; //Hilfsgroesse zur Produktbildung
	for (i = 0; i <n; i++)
		f = f*a[i][i];
	*det = f;
	return 1;
}


void main()
{
	printf("Content-type: text/html\n\n");
	printf("<html>\n");
	printf("<body>\n");
	
	//aktuelle Spaltenanzahl muss immer in Definition von Gaussalg angepasst werden
	// float m[5][6]={{0,0,2,1,1,5},{1,0,0,2,1,5},{1,1,0,0,2,7},{2,1,1,0,0,12},{0,2,1,1,0,11}};
	// float m[6][7]={{5,0,-1,0,0,7,0},{1,0,0,0,1,0,-1},{0,-1,0,1,-1,0,0},
	//   {0,0,-1,3,1,0,0},{0,0,0,1,0,1,1},{-10,-5,0,0,2,0,0}};
	//   float m[5][4]={{1,3,2,19},{2,-18,1,-85},{-6,2,3,1},
	//    {5,2,-1,19},{3,1,5,161}};
	//   float m[5][4]={{3,-1,2,1},{7,-4,-1,0},{-1,-3,-12,-5},
	//    {-1,2,5,2},{0,5,17,7}};
	//   float m[5][4]={{3,-1,2,1},{7,-4,-1,-2},{-1,-3,-12,-5},
	//    {-1,2,5,2},{0,5,17,7}};
	//float m[3][4]={{-10,1,6,2},{8,-1,-16,10},{9,-1,-11,4}};
	//float m[3][4]={{-0.0125,0.025,0.0,0.5},{-0.0433,-0.0683,-0.0222,2.5},
	//                 {0.0588,0.0433,0.0333,-3.0}};
	float m[3][4] = { { 5, -1, 3, 26 }, { 1, -2, 1, 15 },
	{ -1, 3, 4, 15 } };
	//float m[3][4]={{1,5,2,5},{2,-2,4,5},{1,1,2,1}}; 
	//float m[3][4]={{-1,6,2,4},{3,-4,-2,1},{2,-2,-1,2}}; 
	//  float m[3][4]={{1,-2,-3,8},{2,1,-1,11},{1,3,2,3}}; 
	//  float m[3][4]={{-1,2,3,1},{2,1,-1,11},{1,3,2,3}}; 
	//float m[4][5]={{2,-1,3,-1,0},{5,3,2,1,0},{-1,-5,4,-3,0},{-1,6,-7,4,0}}; 
	//float m[3][4]={{2,3,4,1},{4,3,8,2},{3,2,1,4}};
	//float m[5][6]={{-1,2,-1,0,1,0},{10,0,3,4,1,12},{3,-1,1,1,0,4},{8,-1,2,3,1,12},{0,0,0,0,0,0}};
	//float m[5][6]={{1,3,5,7,9,1},{1,-2,3,-4,5,1},{2,11,12,25,22,-3},{0,0,0,0,0,0},{0,0,0,0,0,0}};
	//float m[3][4]={{2,1,1,0},{-6,3,9,6},{2,2,3,1}}; 
	//float m[3][4]={{2,1,1,0},{3,-1.5,9,6},{2,2,-1.5,1}}; 
	//float m[3][4]={{2,3,7,362},{1,-1,6,296},{-1,-10,5,210}};
	//  float m[3][4]={{1.0/2,1,1.0/3,16},{1.0/4,2,1.0/3,16},
	//  {1.0/3,1,5.0/9,16}}; 
	//float m[3][4]={{12,3,-5,-24},{8,-4,2,8},{7,2,-1,7}}; 
	//float m[3][4]={{1,-1,0,-1},{1,0,-1,6},{0,1,1,7}};
	//float m[4][5]={{5,-2,-1,4,25},{1,3,5,-1,-16},{2,1,6,1,-19},{8,-1,2,-2,18}}; 
	int n = 3;//Anzahl der Unbekannten(in der Regel =Anzahl Gleichungen)!!
	float x[3], d; int i, fall, rg;
	rg = n;
	fall = Gaussalg(m, n, x, &rg, 1, &d);
	switch (fall) {
	case 0: printf("\n\nWiderspruch - LGS unloesbar\n\n"); break;
	case 1: printf("\n\n\nLGS eindeutig loesbar:");
		printf("\n\nWert der Koeffizientendeterminante: %.4f\n\nLoesungsvektor:\n", d);
		for (i = 0; i<n; i++) printf("\n%10.7f", x[i]);
		printf("\n\n"); break;
	case 2: printf("\n\nmehrdeutige Loesung, Rang=%d", rg);
		printf("\n  %d Parameter erforderlich!\n\n", n - rg);
		//case 3:  printf ("\nGleichungssystem nicht loesbar oder nicht eindeutig loesbar\n");
		//        printf ("Rang=%d\n\n",rg);
	}
	//scanf("%d", &n); printf("\n\n");// Eingabe, damit Fenster offen bleibt!

	printf("</body>\n");
	printf("</html>\n");
}