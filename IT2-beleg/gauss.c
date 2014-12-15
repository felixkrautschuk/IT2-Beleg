//
//  main.c
//  stringTest
//
//  Created by Benjamin Herzog on 15.12.14.
//  Copyright (c) 2014 Benjamin Herzog. All rights teileerved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 15

int row;
int col;

int getValueI(char *string);
float getValueF(char *string);
void printArray(char **array);
void beenden();

int Gaussalg (float a[][MAX_LENGTH], int n, float x[],int *r,int druck,float *det);

int main(int argc, const char * argv[]) {
    
    printf("Content-Type:text/html");
    
    puts("<!DOCTYPE html>");
    puts("<head>");
    puts("  <meta charset=\"utf-8\">");
    puts("</head>");
    puts("<body>");
    
    // Eingabestring
    char *data = getenv("QUERY_STRING");
    if(data == NULL)
    {
        printf("<P>Error! Error in passing data from form to script.");
        beenden();
        return -1;
    }
    
    printf("String: %s", data);
    
//    char data[512];
    
    // strtok holt die jeweiligen Werte heraus, getrennt durch "&"
    char *tempRow = strtok(data, "&");
    char *tempCol = strtok(NULL, "&");
    // rest wird zur weiteren Bearbeitung zwischengespeichert
    char *rest = strtok(NULL, "\0");
    
    // Zeilen und Spalten werden gesondert herausgesucht
    row = getValueI(tempRow);
    col = getValueI(tempCol);
    
//    printf("Rows: %d\n", row);
//    printf("Cols: %d\n\n", col);
    
    char ** teile  = NULL;
    char *  p    = strtok (rest, "&");
    int n_spaces = 0;
    
    
    /* split string and append tokens to 'teile' */
    
    while (p) {
        teile = realloc (teile, sizeof (char*) * ++n_spaces);
        
        if (teile == NULL)
            exit (-1); /* memory allocation failed */
        
        teile[n_spaces-1] = p;
        
        p = strtok (NULL, "&");
    }
    
    // Matrix wird erstellt
    float matrix[MAX_LENGTH][MAX_LENGTH];
    
    // Durch alle Variablen durchgehen und jeweilige Werte heraussuchen (letztes nicht mit Token "&", sondern "\0")
    int i;
    int tRow = 0;
    int tCol = 0;
    for (i = 0; i < row * col ; i++) {
        
        matrix[tRow][tCol] = getValueF(teile[i]);
        tCol++;
        if (tCol >= col) {
            tCol = 0;
            tRow++;
            if (tRow >= col ) tRow = 0;
        }
    }
    
    
    

    int n=col - 1;//Anzahl der Unbekannten(in der Regel =Anzahl Gleichungen)!!
    float x[3],d;
    int fall,rg;
    rg=n;
    fall=Gaussalg (matrix, n, x,&rg,1,&d);
    switch (fall ) {
        case 0: printf("<br><br>Widerspruch - LGS unloesbar<br><br>");break;
        case 1: printf ("<br><br><br>LGS eindeutig loesbar:");
            printf ("<br><br>Wert der Koeffizientendeterminante: %.4f<br><br>Loesungsvektor:<br>",d);
            for (i=0;i<n;i++) printf("<br>%10.7f",x[i]);
            printf("<br><br>");break;
        case 2: printf("<br><br>mehrdeutige Loesung, Rang=%d",rg);
            printf("<br>  %d Parameter erforderlich!<br><br>",n-rg);
    }
    
    beenden();
    
    return 0;
}

void beenden() {
    
    puts("</body>");
    puts("</html>");
}

int getValueI(char *string) {
    
    char *vBuf = strtok(string, "=");
    vBuf = strtok(NULL, "\0");
    
    return atoi(vBuf);
}
    
float getValueF(char *string) {
    
    char *vBuf = strtok(string, "=");
    vBuf = strtok(NULL, "\0");
    
    return atof(vBuf);
}

void printArray(char **array) {
    int i;
    for (i = 0; i < row * col; i++) {
        printf("Element %d: %s\n", i + 1, array[i]);
    }
}







int Gaussalg (float a[][MAX_LENGTH], int n, float x[],int *r,int druck,float *det)
//Spaltenanzahl muss immer angepasst werden, immer n+1!
{
    int   i, j;                      // Zeile, Spalte
    int   s;                         // Elimininationsschritt
    int   pzeile;                    // Pivotzeile
    float f;                         // Multiplikationsfaktor
    float h=0.0f,h1;                 // Hilfsvariable zur Identifikation mehrdeutige Loesg.
    float Epsilon = 0.000001f;       // Genauigkeit
    float Maximum;                   // Zeilenpivotisierung
    float mf[100];                   // Speicher Multiplikationsfaktor für Druck
    
    s = 0; mf[0]=0.0f; *det=0.0f;
    
    //Ausgabe Original-Matrix
    if (druck) {
        printf("Original-Koeffizientenmatrix mit rechter Seite:<br>");
        for (i = 0; i < n; i++) {
            printf("<br>");
            for (j = 0; j <= n; j++) printf("%7.2f   ",a[i][j]);
        }
    }
    do {             // die einzelnen Eliminationsschritte
        Maximum = fabs(a[s][s]);   // groesstes Element
        if (Maximum < Epsilon)  break;
        //nicht eindeutig loesbar oder Widerspruch (unloesbar)
        if (druck) printf( "<br><br>Schritt %2i von %2i", s+1, n-1);
        pzeile = s ;               // suchen
        for (i = s+1; i < n; i++)
            if (fabs(a[i][s]) > Maximum) {
                Maximum = fabs(a[i][s]) ;
                pzeile = i;
            };
        
        if (pzeile != s)  // falls erforderlich, Zeilen tauschen
        {   for (j = s ; j <= n; j++) {
            h1 = a[s][j];
            a[s][j] = a[pzeile][j];
            a[pzeile][j]= h1;
        }
            if (druck) printf( "  (Tausch Zeile %2i mit %2i)<br>",pzeile+1,s+1);
            else printf("<br>");
        }
        
        // Elimination --> Nullen in Spalte s ab Zeile s+1
        for (i = s + 1; i < n; i++ ) {
            f = -(a[i][s]/a[s][s]); mf[i]=f;      // Multiplikationsfaktor
            a[i][s] = 0.0f;
            for (j = s+1; j <= n ; j++)   // die einzelnen Spalten
                a[i][j] += f*a[s][j];       // Addition der Zeilen i, s
        }
        //Ausgabe Matrix nach jedem Schritt
        if (druck) {
            for (i = 0; i < n; i++) {
                printf("<br>");
                for (j = 0; j <= n; j++) printf("%7.2f   ",a[i][j]);
                if (i>s) printf("%7.2f   ",mf[i]);
            }
        }
        s++;
    } while ( s < n-1 ) ;
    
    *r=s;
    h=0.0f;
    for (j = 0; j < n ; j++) h=h+a[s][j];
    if (fabs(h)<0.00001f) {
        if (fabs(a[s][s+1])<0.00001f) return 2;
        else return 0;
    }
    
    // Berechnen der Loesungen aus der entstandenen Dreiecksmatrix
    // letzte Zeile
    x[n-1] =  a[n-1][n] / a[n-1][n-1];
    // restliche Zeilen
    for (i = n-2 ; i >= 0; i-- )
    {
        for (j = n-1 ; j > i ; j-- )
        {
            a[i][n] -= x[j]*a[i][j];    // rechte Seite berechnen
        } 
        x[i] = a[i][n] / a[i][i];       // Loesung
    }
    // Wert der Determinante (=Produkt der Hauptdiagonalelemente)
    f=1.0f; //Hilfsgroesse zur Produktbildung
    for (i = 0 ; i <n; i++ )
        f=f*a[i][i];
    *det=f;
    return 1;  
}




