#include "Funktionen.h"



// Größe des Fensters Abfragen und speichern
viewPort GetScreenSize()
{
	viewPort viewport;
	// Get a handle to the standard output handle
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the console screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
		std::cerr << "Error getting console screen buffer info" << std::endl;
	}

	// Extract the viewport dimensions
	viewport.Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	viewport.Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return viewport;
}
// Ändern der Fenster Größe auf Vollbild
void adjustConsoleSize() {
	// 1. Fenster maximieren
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_MAXIMIZE);

	// 2. Handle zum Console-Output abrufen
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) {
		std::cout << "Fehler beim Abrufen des Console-Handles" << std::endl;
		return;
	}

	// 3. Aktuelle Buffer-Informationen abrufen
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(hConsole, &info)) {
		std::cout << "Fehler bei GetConsoleScreenBufferInfo: " << GetLastError() << std::endl;
		return;
	}

	// 4. Buffergröße an Fenstergröße anpassen
	COORD newSize = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};

	// 5. Neue Buffergröße setzen
	if (!SetConsoleScreenBufferSize(hConsole, newSize)) {
		std::cout << "Fehler bei SetConsoleScreenBufferSize: " << GetLastError() << std::endl;
		return;
	}

	// 6. Fenstergröße aktualisieren
	SMALL_RECT rect = {
		0, 0,
		newSize.X - 1,
		newSize.Y - 1
	};

	if (!SetConsoleWindowInfo(hConsole, TRUE, &rect)) {
		std::cout << "Fehler bei SetConsoleWindowInfo: " << GetLastError() << std::endl;
		return;
	}
}
// Fixiert Fenster
void FixiereFensterGroesse()
{
	HWND console = GetConsoleWindow();
	if (console == NULL)
	{
		cout << "Fehler: Konsole nicht gefunden!" << endl;
		return;
	}

	// Aktuelle Größe abrufen
	RECT rect;
	GetWindowRect(console, &rect);

	// Fenstergröße festlegen
	SetWindowLong(console, GWL_STYLE,
		GetWindowLong(console, GWL_STYLE) &
		~(WS_SIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME));
}

void begruessung()
{
	system("cls");
	viewPort viewport = GetScreenSize();
	string text = "Willkommen!";
	string text1 = "Mit diesem Programm werden Arrays";
	string text2 = "in verschiedenen Dimensionen angezeigt";
	// Mitte berechnen von der Fenster größe
	int yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
	int xPos = (viewport.Height / 2) - 5;	// Mänge der Zeilen in dem Menu 
	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);
	cout << text;

	// Nächste Position wird berechnet
	yPos = viewport.Width / 2 - (text1.size() / 2);
	xPos += 2;

	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);
	cout << text1;

	// Nächste Position wird berechnet
	yPos = viewport.Width / 2 - (text2.size() / 2);
	xPos += 2;

	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);
	cout << text2;

	xPos += 2;

	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);

	system("Pause");
}

// Hauptmenu
void hauptmenu(int& auswahlDimension, string beschriftungAchsen[6], int groesseAchsen[6], int maxGroesse[4][6])
{
	int yPos;
	int xPos;
	viewPort viewport = GetScreenSize();
	string text = "Wählen Sie eine der Optionen:";
	string text1 = "1. Array Erstellen";
	string text2 = "2. Beenden";
	//Lokale Variable
	int auswahlHauptMenu;

	do
	{
		system("cls");

		//Menu


		// Mitte berechnen von der Fenster größe
		yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
		xPos = (viewport.Height / 2) - 5;	// Mänge der Zeilen in dem Menu 
		// Zu Position (x,y)
		printf("\033[%d;%dH", xPos, yPos);
		cout << text;

		// Nächste Position wird berechnet
		yPos = viewport.Width / 2 - (text1.size() / 2);
		xPos += 2;

		// Zu Position (x,y)
		printf("\033[%d;%dH", xPos, yPos);
		cout << text1;

		// Nächste Position wird berechnet
		yPos = viewport.Width / 2 - (text2.size() / 2);
		xPos += 2;

		// Zu Position (x,y)
		printf("\033[%d;%dH", xPos, yPos);
		cout << text2;

		xPos += 2;

		// Zu Position (x,y)
		printf("\033[%d;%dH", xPos, yPos);

		// Benutzer Eingabe
		cin >> auswahlHauptMenu;

		//Abfrage ob Zahl
		if (cin.fail())
		{
			cin.clear(); // Fehler löschen
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // restliche Eingabe verwerfen

			// Fehler Text 
			string text = "!!!Ungültige Eingabe!!!Bitte eine Zahl eingeben!!!";

			// Berechnung der Position (Mitte) in dem Fenster anhand der Fenster Größe
			yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
			xPos = (viewport.Height / 2) - 3;	// Mänge der Zeilen in dem Menu 
			// Zu Position (x,y)
			printf("\033[%d;%dH", xPos, yPos);
			cout << text;

			xPos += 2;
			// Zu Position (x,y)
			printf("\033[%d;%dH", xPos, yPos);

			system("Pause");
		}
	} while (auswahlHauptMenu < 1 || auswahlHauptMenu > 2);

	if (auswahlHauptMenu == 1) arrayAuswahlMenu(&auswahlDimension, beschriftungAchsen, groesseAchsen, maxGroesse);
	if (auswahlHauptMenu == 2) return;
}

void Hinweisstext()
{
	viewPort viewport = GetScreenSize();
	string text = "Falls mehrere Bildschirme vorhanden sind,";
	string text1 = "plazieren Sie das Fenster auf einem anderen Bildschirm,";
	string text2 = "andernfalls direkt mit  beliebiger Taste fortfahren";

	system("cls");

	// Mitte berechnen von der Fenster größe
	int yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
	int xPos = (viewport.Height / 2) - 5;	// Mänge der Zeilen in dem Menu 
	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);
	cout << text;

	// Nächste Position wird berechnet
	yPos = viewport.Width / 2 - (text1.size() / 2);
	xPos += 2;

	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);
	cout << text1;

	// Nächste Position wird berechnet
	yPos = viewport.Width / 2 - (text2.size() / 2);
	xPos += 2;

	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);
	cout << text2;

	xPos += 2;

	// Zu Position (x,y)
	printf("\033[%d;%dH", xPos, yPos);

	system("Pause");
}
// Ruft Auswahl Menu zur erstellung von Arrays auf
void arrayAuswahlMenu(int* auswahlDimension, string beschriftungAchsen[6], int groesseAchsen[6], int maxGroesse[4][6])
{
	viewPort viewport = GetScreenSize();
	string text = "Wie viele Dimensionen soll das Array haben?  1 - 6";
	string text1 = "Eingabe: ";
	int yPos;
	int xPos;

	do
	{
		system("cls");

		// Mitte berechnen von der Fenster größe
		yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
		xPos = (viewport.Height / 2) - 5;	// Mänge der Zeilen in dem Menu 
		// Zu Position (x,y)
		printf("\033[%d;%dH", xPos, yPos);
		cout << text;

		xPos += 2;

		// Zu Position (x,y)
		printf("\033[%d;%dH", xPos, yPos);
		cout << text1;

		// Benutzer Eingabe
		cin >> *auswahlDimension;

		//Abfrage ob Zahl
		if (cin.fail())
		{
			cin.clear(); // Fehler löschen
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // restliche Eingabe verwerfen

			// Fehler Text 
			text = "!!!Ungültige Eingabe!!!Bitte eine Zahl eingeben!!!";

			// Berechnung der Position (Mitte) in dem Fenster anhand der Fenster Größe
			yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
			xPos = (viewport.Height / 2) - 3;	// Mänge der Zeilen in dem Menu 
			// Zu Position (x,y)
			printf("\033[%d;%dH", xPos, yPos);
			cout << text;

			xPos += 2;
			// Zu Position (x,y)
			printf("\033[%d;%dH", xPos, yPos);

			system("Pause");
		}

	} while (*auswahlDimension < 1 || *auswahlDimension > 6);

	int j = 0;
	int i = 0;
	int maxgroesseindex = 0;
	// Setzen der richtigen Achsen beschriftung je nach Anzahl der Dimensionen

	//Achsen Namen zum Ausgeben im Text
	//string beschriftungAchsen[0] =	 {					   "i"			};
	//string beschriftungAchsen[1] =	 {			 "i",	   "j"			};
	//string beschriftungAchsen[2] =	 { "i",	     "j",	   "k"			};
	//string beschriftungAchsen[3] =	 { "i",	     "j",	   "k",		"l" };
	//string beschriftungAchsen[index] = { "Layer: ","Reihe: ","Zelle: ","Box: " };

	if (*auswahlDimension == 1)
	{
		i = 2;
	}
	if (*auswahlDimension == 2)
	{
		i = 1;
	}
	if (*auswahlDimension >= 4)
	{
		if (*auswahlDimension == 4)
		{
			maxgroesseindex = 1;
		}
		if (*auswahlDimension == 5)
		{
			maxgroesseindex = 2;
		}
		if (*auswahlDimension == 6)
		{
			maxgroesseindex = 3;
			j = 3;
			i = 3;
		}
	}

	text = "Bitte eine Zahl eingeben für die Größe der Achse: 1 - ";


	//Eingabe der Größe der Achsen
	for (; j < *auswahlDimension; i++, j++)
	{
		do
		{
			do
			{
				system("cls");

				// Mitte berechnen von der Fenster größe
				yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
				xPos = (viewport.Height / 2) - 5;	// Mänge der Zeilen in dem Menu 
				// Zu Position (x,y)
				printf("\033[%d;%dH", xPos, yPos);
				cout << text << maxGroesse[maxgroesseindex][j];

				// Nächste Position wird berechnet
				yPos = viewport.Width / 2 - (beschriftungAchsen[i].size() / 2);
				xPos += 2;

				// Zu Position (x,y)
				printf("\033[%d;%dH", xPos, yPos);

				// Giebt Den Jeweiligen Namen Der Achse Aus
				cout << beschriftungAchsen[i];

				// User Eingabe der Größe der jeweiligen Achsen
				cin >> groesseAchsen[i];

				//Abfrage ob Zahl
				if (cin.fail())
				{
					cin.clear(); // Fehler löschen
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // restliche Eingabe verwerfen

					// Fehler Text 
					string text = "!!!Ungültige Eingabe!!!Bitte eine Zahl eingeben!!!";

					// Berechnung der Position (Mitte) in dem Fenster anhand der Fenster Größe
					yPos = (viewport.Width / 2) - (text.size() / 2); // Hälfte der String Größe die geschrieben wird damit der Text immer mittig ist
					xPos = (viewport.Height / 2) - 3;	// Mänge der Zeilen in dem Menu 
					// Zu Position (x,y)
					printf("\033[%d;%dH", xPos, yPos);
					cout << text;

					xPos += 2;
					// Zu Position (x,y)
					printf("\033[%d;%dH", xPos, yPos);

					system("Pause");
				}
				//Überprüft die Eingabe
			} while (groesseAchsen[i] < 1 || groesseAchsen[i] > maxGroesse[maxgroesseindex][j]);
		} while (!true);
	}
}

void WechselZeichen(int groesseAchsen[6], int zeahlerReihen, int zeahlerLayer, int k, bool& pivotSet)
{
	// Einmalig vorkomende zeichen (Mittelpunkt)
	string Mittelpunkt = "0";

	// Wechselzeichen wenn Mittelpunkt erreicht. aber zähler Reihen nicht. bis es schräg wird.
	string GeradeU[4] = { "+",
						  "|",
						  "|",
						  "|", };

	string GeradeO[4] = { "+"
						,"|\\"
						,"| \\"
						,"|  \\" };

	string SchreagO[4] = { "+"
						   ,"\\"
						   ," \\"
						   ,"  \\" };

	// Wechselzeichen Unten 
	string SchreagU[4] = { "+",
							"\\  |",
							" \\ |",
							"  \\|" };


	// Abfrage welcher Zeichensatz benutzt werden muss


	if (zeahlerReihen != groesseAchsen[1] && zeahlerLayer != groesseAchsen[0])
	{
		cout << GeradeO[k];

		/*if (zeahlerLayer == groesseAchsen[0] && zeahlerLayer != groesseAchsen[0] && pivotSet == false)
		{
			cout << Mittelpunkt;
			pivotSet = true;
		}*/

	}
	else if (zeahlerReihen == groesseAchsen[1] && zeahlerLayer != groesseAchsen[0])
	{
		cout << SchreagO[k];
	}
	else if (zeahlerLayer == groesseAchsen[0] && pivotSet == false)
	{
		if (pivotSet == false)
		{
			cout << Mittelpunkt;
			pivotSet = true;

		}

	}
	else if (zeahlerReihen == groesseAchsen[1] && zeahlerLayer == groesseAchsen[0])
	{
		cout << SchreagU[k];
	}
	else if (zeahlerReihen != groesseAchsen[1] && zeahlerLayer == groesseAchsen[0])
	{
		cout << GeradeU[k];
	}

}

void FeldZeichen(int groesseAchsen[6], int k, int zeahlerLayer)
{
	// Universal Zeichenfolge für Trennzeiche der Felder Horizontal
	string KopfFussZeichen = "-----+";

	//Körper Zeichen Unten
	string Gerade = "     |";

	// Körperzeichen Oberehälfte
	string Schreag = "     \\";


	// Abfrage ob anfang der Reihe
	if (k == 0)
	{
		for (size_t j = 0; j < groesseAchsen[2]; j++)
		{
			cout << KopfFussZeichen;
		}
	}
	else
	{
		if (zeahlerLayer == groesseAchsen[0])
		{
			for (size_t j = 0; j < groesseAchsen[2]; j++)
			{
				cout << Gerade;
			}
		}
		else
		{
			for (size_t j = 0; j < groesseAchsen[2]; j++)
			{
				cout << Schreag;
			}
		}
	}
}

void KopfFussVorZeichen(int zeahlerVorzeichenKopfFuss, int k)
{
	// Zeichen Satz für Kopf und Fuß Bereich (Vorzeichen)
	string Vorzeichen = "+   ";

	if (k == 0)
	{
		for (size_t i = 0; i < zeahlerVorzeichenKopfFuss; i++)
		{
			cout << Vorzeichen;
		}
	}
}

void KoerperVorzeichen(int groesseAchsen[6], int zeahlerVorzeichenKoerper, int zeahlerLayer, int zeahlerReihen, int k)
{
	string Gerade[3] = { "|\\  ",
						 "| \\ ",
						 "|  \\" };

	string Schreag[3] = { "\\  |",
						  " \\ |",
						  "  \\|" };

	// Abfrage welcher Zeichensatz benutzt werden soll 
	if (zeahlerReihen == groesseAchsen[1] && k > 0 && zeahlerLayer <= groesseAchsen[0])
	{
		if (zeahlerReihen == groesseAchsen[1]) //&& zeahlerLayer != groesseAchsen[0])
		{
			for (size_t i = 0; i < zeahlerVorzeichenKoerper; i++)
			{
				cout << Schreag[k - 1];
			}
		}
	}
	else if (zeahlerReihen <= groesseAchsen[1] && zeahlerLayer <= groesseAchsen[0] && k > 0)
	{
		for (size_t i = 0; i < zeahlerVorzeichenKoerper; i++)
		{
			cout << Gerade[k - 1];
		}
	}
}

void SetzeFarbe(int farbe)
{
	cout << "\033[" << farbe << "m";
}

void StartOffSet(int groesseAchsen[6], int zeahlerBoxLayer, position& OffSet)
{
	// Berechnung der Größe des Quaders 
	int Breite = (4 * groesseAchsen[1]) + (6 * groesseAchsen[2]) + 1;
	int Hoehe = (4 * groesseAchsen[0]) + (4 * groesseAchsen[1]) + 1;

	switch (zeahlerBoxLayer)
	{
	case 1:
		OffSet.xOffSet = OffSet.xStart = (Hoehe * 1) + 1;
		OffSet.yOffSet = (OffSet.yStart = (Breite * 1));
		break;
	case 2:
		// Abstand nach Rechts und Unten
		OffSet.xOffSet = OffSet.xStart = (Hoehe * 2) + 2; //		!!!!!von 3 auf 2 geändert 
		OffSet.yOffSet = OffSet.yStart = (Breite * 2);
		break;
	default:
		break;
	}
}

void OffSetBerechnenY(int groesseAchsen[6], position& OffSet, int auswahlDimension)
{
	// Berechnung der Größe des Quaders 
	int Breite = (4 * groesseAchsen[1]) + (6 * groesseAchsen[2]) + 1;

	switch (auswahlDimension)
	{
	case 4:
		// Abstand nach Rechts und Unten
		OffSet.yOffSet += (Breite * 1.5);
		break;
	case 5:
		// Abstand nach Rechts und Unten
		OffSet.yOffSet += (Breite * 1.5);
		break;
	case 6:
		// Abstand nach Rechts und Unten
		OffSet.yOffSet += (Breite * 2);
		break;
	default:
		break;
	}

}

void OffSetBerechnenX(int groesseAchsen[6], position& OffSet, int auswahlDimension)
{
	// Berechnung der Größe des Quaders 
	int Hoehe = (4 * groesseAchsen[0]) + (4 * groesseAchsen[1]) + 1;



	// Abstand nach Rechts und Unten
	OffSet.xOffSet += (Hoehe * 1); //					!!!!!von 2  auf 1 geändert
}

void Quader(int groesseAchsen[6], position& OffSet)
{
	bool pivotSet = false;
	// Holt sich die Größe des Fensters 
	viewPort viewport = GetScreenSize();

	int k = 0;
	// Start Position für den Quader

	int startPosX = static_cast<int>(viewport.Height * 0.05f) + OffSet.xOffSet;
	int startPosY = static_cast<int>(viewport.Width * 0.4f) + OffSet.yOffSet;

	// Anzahl der Vorzeichen wird durch die Anzahl der Layer bestimmt
	// Zähler für die Vorzeichen schleife (Menge an Vorzeichen)
	int zeahlerVorzeichenKoerper = 0;
	int zeahlerVorzeichenKopfFuss = 0;
	int zeahlerZellen = 0;
	int zeahlerReihen = 0;
	int zeahlerLayer = 0;
	int zeahler = zeahlerLayer + zeahlerReihen;


	bool Kopf = false;
	bool Mitte = false;
	bool Ende = false;


	// 2. Schleife für die 3. Dimensionen 
	for (; zeahler < (groesseAchsen[0] + groesseAchsen[1]); zeahler++)
	{
		// Pro Schleifen durchlauf eine Reihe/Layer 
		for (k = 0; k < 4; k++, startPosX++)
		{
			// Neue Zeile ab. 2. Durchlauf
			printf("\033[%d;%dH", startPosX, startPosY);
			if (zeahlerLayer != 0)
			{
				if (zeahlerReihen == groesseAchsen[1])
				{
					if (k == 1)
					{
						startPosY++;
					}
					printf("\033[%d;%dH", startPosX, startPosY);
				}
			}

			KopfFussVorZeichen(zeahlerVorzeichenKopfFuss, k);
			KoerperVorzeichen(groesseAchsen, zeahlerVorzeichenKoerper, zeahlerLayer, zeahlerReihen, k);
			WechselZeichen(groesseAchsen, zeahlerReihen, zeahlerLayer, k, pivotSet);
			FeldZeichen(groesseAchsen, k, zeahlerLayer);
		}

		if (zeahlerLayer == groesseAchsen[0] || zeahlerReihen == groesseAchsen[1])
		{
			Kopf = true;
		}

		if (Kopf != true)
		{
			zeahlerVorzeichenKoerper++;
			zeahlerVorzeichenKopfFuss++;
		}
		else if (zeahlerLayer <= groesseAchsen[0] && zeahlerReihen == groesseAchsen[1])
		{

			startPosY += 3;
		}

		if (zeahlerLayer < groesseAchsen[0])
		{
			zeahlerLayer++;
		}
		if (zeahlerReihen < groesseAchsen[1])
		{
			zeahlerReihen++;
		}

		if (zeahlerReihen == groesseAchsen[1] && zeahlerLayer == groesseAchsen[0])
		{
			if (zeahlerVorzeichenKopfFuss > zeahlerVorzeichenKoerper)
			{
				zeahlerVorzeichenKopfFuss--;
			}
			if (zeahlerVorzeichenKoerper > 0)
			{
				zeahlerVorzeichenKoerper--;
			}
		}
	}

	//startPosY += 3;
	printf("\033[%d;%dH", startPosX, startPosY);
	cout << "+";
	for (int i = 0; i < groesseAchsen[2]; i++)
	{
		cout << "-----+";
	}
}

void InfoAusgabe(string beschriftungAchsen[6], int groesseAchsen[6])
{
	// Bildschirmgröße abrufen
	viewPort viewport = GetScreenSize();

	// Positionsberechnung (5% von der Breite und 10% von der Höhe)
	int startPosX = static_cast<int>(viewport.Width * 0.02f);
	int startPosY = static_cast<int>(viewport.Height * 0.1f);

	// ASCII-Art des Koordinatensystems
	vector<string> info = {
		"        ____                   ",
		"        |\\                    ",
		"        | \\          Zellen   ",
		" Layer --> \\           |      ",
		"            \\          |      ",
		"             \\        \\|/    ",
		"Null Punkt -> 0------------->	",
		"              |                ",
		"              |                ",
		"  Reihen -->  |                ",
		"              |                ",
		"             \\|/              "
	};

	// Positionierung im Terminal

	// Ausgabe des Koordinatensystems
	for (const auto& zeile : info)
	{
		printf("\033[%d;%dH", startPosY, startPosX);
		std::cout << zeile;
		startPosY++;
	}

	// Achsenbeschriftung
	startPosY += 10;
	for (int i = 0; i < 6; i++, startPosY += 2)
	{
		printf("\033[%d;%dH", startPosY, startPosX);
		cout << beschriftungAchsen[i] << groesseAchsen[i];
	}
}

void EdiTag()
{
	int abstandRand = 10;

	system("chcp 437");
	system("cls");
	cout << "\n\n\n\n\n";
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(6) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(4) << "" << setfill(' ') << setw(5) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(6) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(5) << "" << setfill(' ') << setw(4) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(7) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(2) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(7) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(2) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(6) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(2) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(6) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(2) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(7) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(2) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(7) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(2) << "" << setfill('\xDB') << setw(2) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << setfill(' ') << setw(abstandRand) << "" << setfill('\xDB') << setw(6) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(5) << "" << setfill(' ') << setw(4) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << "powerd by" << setfill(' ') << setw(abstandRand - 9) << "" << setfill('\xDB') << setw(6) << "" << setfill(' ') << setw(3) << "" << setfill('\xDB') << setw(4) << "" << setfill(' ') << setw(5) << "" << setfill('\xDB') << setw(2) << "" << endl;
	cout << "\n\n\n\n\n";
	system("Pause");
}

