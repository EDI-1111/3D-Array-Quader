#include "Funktionen.h"




int main()
{
	system("chcp 65001");

	int i = 0;
	int j = 0;
	int auswahlDimension = 0;
	//Erstellt die 1.Dimension (Reihen) der Arrays

	int OffSetX = 0;
	int OffSetY = 0;

	position OffSet;
	OffSet.xOffSet = 0;
	OffSet.yOffSet = 0;
	OffSet.xStart = 0;
	OffSet.yStart = 0;


	// Speichert die eingegebene Größe der Achsen
	// Wird mit der mindest Größe der Achsen Initialisiert
	int groesseAchsen[6] = { 1,1,1,1,1,1 };

	//Achsen Namen zum Ausgeben im Text
	//string beschriftungAchsen[] = {					   "i"									 };
	//string beschriftungAchsen[] = {			 "i",	   "j"								     };
	//string beschriftungAchsen[] = { "i",	     "j",	   "k"									 };
	//string beschriftungAchsen[] = { "i",	     "j",	   "k",		"l"			  "m"		  "n"};
	string beschriftungAchsen[6] = { "Layer: ","Reihe: ","Zelle: ","Boxzelle: ","Boxreihe: ","Boxlayer: " };


	// Idee: Max Gößen der Achsen ermittel durch die Fenster Größe

	// mann muss berechnen wieviel platz da ist um die maximale Größe festzulegen
	// Für die jeweiligen Dimensionen 



	//Beinhaltet die werte für Maximale größe der jeweiligen Achsen.
	int maxGroesse[4][6]{ {5,5,5,1,1,1},   // Nur 3.Dimensionen Begrenst auf Max: 10x10x10x1
							{3,3,3,2,1,1},		// Ab 4. Dimensionen wird die 4. Dimension begrenst durch die Anzahl der 3. Dimensionen
							{3,3,3,2,2,1},		// Ab 5. Dimensionen 
							{1,1,1,3,3,3}		// Ab 6. Dimensionen
	};


	// Hinweiß zur Positionierung auf dem Richtigen Bildschirm


	Hinweisstext();
	// Ändern der Fenster Größe auf Vollbild
	system("cls");
	adjustConsoleSize();
	//Fixiert Fenster
	FixiereFensterGroesse();

	//Größe des Fensters Abfragen und speichern
	viewPort viewport = GetScreenSize();



	begruessung();
	hauptmenu(auswahlDimension, beschriftungAchsen, groesseAchsen, maxGroesse);






	system("cls");
	InfoAusgabe(beschriftungAchsen, groesseAchsen);
	for (int zeahlerBoxLayer = 0; zeahlerBoxLayer < groesseAchsen[5]; zeahlerBoxLayer++)
	{
		StartOffSet(groesseAchsen, zeahlerBoxLayer, OffSet);
		for (int zeahlerBoxReihen = 0; zeahlerBoxReihen < groesseAchsen[4]; zeahlerBoxReihen++)
		{
			if (zeahlerBoxReihen > 0)
			{
				OffSetBerechnenX(groesseAchsen, OffSet, auswahlDimension);
			}
			//Schleife für die 4. Dimension
			for (int zeahlerBoxZelle = 0; zeahlerBoxZelle < groesseAchsen[3]; zeahlerBoxZelle++)
			{
				if (zeahlerBoxZelle > 0)
				{
					OffSetBerechnenY(groesseAchsen, OffSet, auswahlDimension);
				}
				// 3. Dimensionen (Quader)
				switch (zeahlerBoxLayer)
				{
				case 0:
					SetzeFarbe(32);
					break;
				case 1:
					SetzeFarbe(31);
					break;
				case 2:
					SetzeFarbe(33);
					break;
				default:
					break;
				}
				Quader(groesseAchsen, OffSet);
				SetzeFarbe(0);
			}
			// Offsetreset
			OffSet.yOffSet = OffSet.yStart;
		}
		// Offsetreset
		OffSet.xOffSet = OffSet.xStart;
	}


	// Positionsberechnung (5% von der Breite und 10% von der Höhe)

	int startPosY = static_cast<int>(viewport.Height - 1);
	// Position auf Linkt unten Setzen
	printf("\033[%d;%dH", startPosY, 0);
	system("Pause");
	EdiTag();
	return 0;
}



