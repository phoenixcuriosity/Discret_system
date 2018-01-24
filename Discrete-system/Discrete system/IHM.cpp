/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.31

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"

using namespace std;

IHM::IHM() : _fct(0), _sys(0)
{
	_fct = new FCTDiscret;
	_sys = new SYSETATDiscret;
}
IHM::~IHM()
{	
	if (_fct != nullptr){
		delete _fct;
		_fct = nullptr;
	}
	if (_sys != nullptr){
		delete _sys;
		_sys = nullptr;
	}
}


void mainLoop(IHM& ihm){
	/*
		Menu principal
	*/
	bool continuer = true;
	unsigned int request = 0;
	FCTDiscret testFCT;
	logfileconsole("_________Init Success_________");

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("Dev version: 31");
	logfileconsole("Public release 1.0");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	while (continuer){
		logfileconsole("Main menu");
		logfileconsole("type 1 menu Transfert Fonction\n or type 2 menu State System\n or type 3 menu closed Loop\n or type 4 menu test\n or type 5 to exit the program\n");
		cin >> request;
		switch (request){
		case selectFCT:
			FCTLoop(ihm);
			break;
		case selectSYSETAT:
			SYSLoop(ihm);
			break;
		case selectFTBF:
			if (assertFCT(*ihm.GETfct(), testFCT))
				FTBF(ihm);
			break;
		case selectTest:
			test();
			break;
		case exitProgram:
			continuer = false;
			break;
		}
	}
}
void FCTLoop(IHM& ihm){
	/*
		Menu fonction de transfert permettant de r�aliser les m�thodes associ�es � la fonction de transfert
	*/
	system("cls");
	unsigned int request = 0;
	double deltaT = 0;
	bool continuer = true;
	FCTDiscret test;

	while (continuer){
		logfileconsole("Menu Transfert Fonction");
		logfileconsole("type 1 to create the numerator and the denominator");
		logfileconsole("or type 2 to edit the TF \nor type 3 to display the TF");
		logfileconsole("or type 4 for Jury \nor type 5 for Bode");
		logfileconsole("or type 6 to return to previous menu : ");
		cin >> request;
		switch (request){
		case createNumDen:
			cout << "Init deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			logfileconsole("deltaT of TF? : ");
			cin >> deltaT;
			ihm.GETfct()->SETdeltaT(deltaT);
			cout << "New deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			system("cls");
			if (createNum(ihm)){
				system("cls");
				if (createDen(ihm)){
					logfileconsole("You have created with SUCCESS the TF, Yeah!!! You did it!!!");
					logfileconsole("Now try to diplay it");
					cout << endl << endl;
				}
				else
					logfileconsole("______ERROR creatDen : den is 0");
			}
			else
				logfileconsole("______ERROR creatNum : num is 0");
			break;
		case editFCT:
			modifFCT(ihm);
			break;
		case displayFCT:
			if (assertFCT(*ihm.GETfct(), test)){
				logfileconsole("TF\n");
				logfileconsole(ihm.GETfct()->printOn(false));
			}
			break;
		case jury:
			if (assertFCT(*ihm.GETfct(), test)){
				if (ihm.GETfct()->tabJury())
					logfileconsole("the system is stable\n");
				else
					logfileconsole("the system is unstable\n");
			}	
			break;
		case bode:
			if (assertFCT(*ihm.GETfct(), test))
				diagBode(ihm);	
			break;
		case previousMenuFCT:
			continuer = false;
			break;
		}
	}
	system("cls");
}
void modifFCT(IHM& ihm){
	/*
		Menu permettant de modifier la fonction de transfert
	*/
	unsigned int request = 0;
	double deltaT = 0;
	unsigned int order = 0;
	double coef = 0;
	bool continuer = true;

	while (continuer){
		system("cls");
		logfileconsole("Menu edit TF");
		logfileconsole("type 1 to edit the numerator");
		logfileconsole("or type 2 to edit the denominator \nor type 3 to edit deltaT");
		logfileconsole("or type 4 to return to previous menu : ");
		cin >> request;
		switch (request){
		case editnum:
			createNum(ihm);
			break;
		case editden:
			logfileconsole("You have selected to edit the Denominator");
			createDen(ihm);
			break;
		case editdeltaT:
			cout << "Init deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			logfileconsole("deltaT of TF? : ");
			cin >> deltaT;
			ihm.GETfct()->SETdeltaT(deltaT);
			cout << "New deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			break;
		case previousMenuEditFCT:
			continuer = false;
			break;
		}
	}
}
bool createNum(IHM& ihm){
	system("cls");
	/*
	Cr�ation du num�rateur avec un test pour v�rifier l'ordre � la fin
	si l'ordre est de 0 et le coefficient est 0 alors la fonction renvoie false
	*/
	unsigned int order = 0, realOrderNum = 0;
	double coef = 0;

	logfileconsole("You have selected to create Numerator");
	logfileconsole("order of numerator? : ");
	cin >> order;
	ihm.GETfct()->SETnum(order);
	logfileconsole("new order = " + to_string(order));
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		logfileconsole("new coef n:" + to_string(i) + " = " + to_string(coef));
		ihm.GETfct()->SETnumThisCoef(i, coef);
	}
	for (int i = order; i >= 0; i--){
		if (ihm.GETfct()->GETnum().GETcoefTab(i) != 0){
			realOrderNum = i;
			break;
		}
		if (i == 0){
			if (ihm.GETfct()->GETnum().GETcoefTab(0) == 0)
				return false;
		}
	}

	ihm.GETfct()->SETnumOrder(realOrderNum);
	logfileconsole("You have created the numerator, order : " + to_string(realOrderNum));
	return true;
}
bool createDen(IHM& ihm){
	system("cls");
	/*
	Cr�ation du d�nominateur avec un test pour v�rifier l'ordre � la fin
	si l'ordre est de 0 et le coefficient est 0 alors la fonction renvoie false
	*/
	unsigned int order = 0, realOrderDen = 0;
	double coef = 0;

	logfileconsole("You have selected to create Denominator");
	logfileconsole("order of denominator? : ");
	cin >> order;
	ihm.GETfct()->SETden(order);
	logfileconsole("new order = " + to_string(order));
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		logfileconsole("new coef n:" + to_string(i) + " = " + to_string(coef));
		ihm.GETfct()->SETdenThisCoef(i, coef);
	}
	for (int i = order; i >= 0; i--){
		if (ihm.GETfct()->GETden().GETcoefTab(i) != 0){
			realOrderDen = i;
			break;
		}
		if (i == 0){
			if (ihm.GETfct()->GETden().GETcoefTab(0) == 0)
				return false;
		}
	}

	ihm.GETfct()->SETdenOrder(realOrderDen);
	logfileconsole("You have created the denominator, order : " + to_string(realOrderDen));
	return true;
}
void diagBode(IHM& ihm){
	/*
		Affiche le diagramme de Bode de la fonction de transfert avec les param�tres Wmin, Wmax et le nombre de points
	*/
	system("cls");
	double wMin = 0, wMax = 0;
	unsigned int nbpoint = 0;
	logfileconsole("Bode");
	logfileconsole("wMin ? : ");
	cin >> wMin;
	logfileconsole("new wMin = " + to_string(wMin));
	logfileconsole("wMax ? : ");
	cin >> wMax;
	logfileconsole("new wMax = " + to_string(wMax));
	logfileconsole("nbpoint ? : ");
	cin >> nbpoint;
	logfileconsole("new nbpoint = " + to_string(nbpoint));
	ihm.GETfct()->Bode(wMin, wMax, nbpoint);
}


void SYSLoop(IHM& ihm){
	/*
		Menu systeme d'�tat permettant de r�aliser les m�thodes associ�es au systeme d'�tat
	*/
	system("cls");
	unsigned int request = 0;
	bool continuer = true;
	FCTDiscret test;
	SYSETATDiscret Test;

	while (continuer){
		logfileconsole("Menu State System");
		logfileconsole("type 1 to edit A, B, C, D");
		logfileconsole("or type 2 to compute A, B, C, D \nor type 3 to display A,B,C,D \nor type 4 to simulate");
		logfileconsole("or type 5 to return to previous menu : ");
		cin >> request;
		switch (request){
		case editMatrice:
			editmatriceLoop(ihm);
			break;
		case calculMatriceABCD:
			if (assertFCT(*ihm.GETfct(),test))
				ihm.GETsys()->calculABCD(*ihm.GETfct());
			break;
		case displaySys:
			logfileconsole(ihm.GETsys()->printOn(false));
			break;
		case simulationTemporelle:
			if (*ihm.GETsys() == Test)
				logfileconsole("A,B,C,D doesn't exist");
			else{
				simulationLoop(ihm);
			}
			break;
		case previousMenuSYS:
			continuer = false;
			break;
		}
	}
}
void editmatriceLoop(IHM& ihm){
	/*
		Menu permettant d'�diter les matrices A, B, C et D
	*/
	system("cls");
	bool continuer = true;
	unsigned int request = 0, length = 0;
	logfileconsole("You have selected edit A, B, C, D");
	logfileconsole("On default matrix are filled with 0");

	logfileconsole("Default A :\n" + ihm.GETsys()->GETA().printOn(false));
	logfileconsole("Default B :\n" + ihm.GETsys()->GETB().printOn(false));
	logfileconsole("Default C :\n" + ihm.GETsys()->GETC().printOn(false));
	logfileconsole("Default D :\n" + ihm.GETsys()->GETD().printOn(false));
	
	logfileconsole("length or height of A : ");
	cin >> length;
	
	ihm.GETsys()->SETeditSizeA(length, length);
	ihm.GETsys()->SETeditSizeB(length, 1);
	ihm.GETsys()->SETeditSizeC(1, length);
	ihm.GETsys()->SETeditSizeD(1, 1);

	logfileconsole("A :\n" + ihm.GETsys()->GETA().printOn(false));
	logfileconsole("B :\n" + ihm.GETsys()->GETB().printOn(false));
	logfileconsole("C :\n" + ihm.GETsys()->GETC().printOn(false));
	logfileconsole("D :\n" + ihm.GETsys()->GETD().printOn(false));

	logfileconsole("Matrix A : ");
	double coef = 0;

	for (unsigned int i = 0; i < length; i++){
		for (unsigned int j = 0; j < length; j++){
			logfileconsole("coef " + to_string(i) + "," + to_string(j) + " = ");
			cin >> coef;
			ihm.GETsys()->SETthisCoefA(i, j, coef);
		}
	}

	logfileconsole("Matrix B : ");
	for (unsigned int i = 0; i < length; i++){
		logfileconsole("coef " + to_string(i) + ",0 = ");
		cin >> coef;
		ihm.GETsys()->SETthisCoefB(i, 0, coef);
	}

	logfileconsole("Matrix C : ");
	for (unsigned int j = 0; j < length; j++){
		logfileconsole("coef 0," + to_string(j) + " = ");
		cin >> coef;
		ihm.GETsys()->SETthisCoefC(0, j, coef);
	}

	logfileconsole("Matrix D : ");
	logfileconsole("coef 0,0 = ");
	cin >> coef;
	ihm.GETsys()->SETthisCoefD(0, 0, coef);

	logfileconsole("You have successfully created A, B, C, D");
}

void simulationLoop(IHM& ihm){
	/*
		Menu permettant la simulation
		s�l�ction du type d'entr�e et des conditions initiales
	*/
	system("cls");
	Echelon step;
	Rampe ramp;
	Sinus sinus;
	randomSignal sig;
	unsigned int requestInput = 0, requestInitial = 0;;
	bool continuer = true;
	double deltaT = 0, amplitude = 0, slope = 0, w = 0, dephasage = 0;
	unsigned int nbech = 0;

	logfileconsole("You have selected simulation");

	logfileconsole("What type of Input ?");
	while (continuer){
		logfileconsole("type 1 for a step");
		logfileconsole("or type 2 for a ramp \nor type 3 for a sinus \nor type 4 to import from load.txt : ");
		cin >> requestInput;
		switch (requestInput){
		case stepInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			step.SETnbech(nbech);
			logfileconsole("deltaT : ");
			cin >> deltaT;
			step.SETdeltaT(deltaT);
			logfileconsole("Amplitude : ");
			cin >> amplitude;
			step.SETamplitude(amplitude);
			continuer = false;
			break;
		case rampInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			ramp.SETnbech(nbech);
			logfileconsole("deltaT : ");
			cin >> deltaT;
			ramp.SETdeltaT(deltaT);
			logfileconsole("Slope : ");
			cin >> slope;
			ramp.SETslope(slope);
			continuer = false;
			break;
		case sinusInput:
			logfileconsole("number of samples : ");
			cin >> nbech;
			sinus.SETnbech(nbech);
			logfileconsole("deltaT : ");
			cin >> deltaT;
			sinus.SETdeltaT(deltaT);
			logfileconsole("Amplitude : ");
			cin >> amplitude;
			sinus.SETamplitude(amplitude);
			logfileconsole("w : ");
			cin >> w;
			sinus.SETw(w);
			logfileconsole("dephasage : ");
			cin >> dephasage;
			sinus.SETdephasage(dephasage);
			continuer = false;
			break;
		case load:
			loadFromFile(sig);
			continuer = false;
			break;
		}
	}
	continuer = true;
	double coef = 0;
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	logfileconsole("\ncondition initial : x0\n" + x0.printOn(false) + "\n");
	while (continuer){
		logfileconsole("\ntype 1 for a default initial condition");
		logfileconsole("or type 2 to edit initial condition : ");
		cin >> requestInitial;
		switch (requestInitial){
		case 1:
			continuer = false;
			break;
		case 2:
			for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
				logfileconsole("\ncoef n: " + to_string(i) + ",0 = ");
				cin >> coef;
				x0.SETthiscoef(i, 0, coef);
			}
			logfileconsole("\nnew x0 :\n" + x0.printOn(false) + "\n");
			continuer = false;
			break;
		}
	}
	if (requestInput == stepInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", step, x0);
	else if (requestInput == rampInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", ramp, x0);
	else if (requestInput == sinusInput)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", sinus, x0);
	else if (requestInput == load)
		ihm.GETsys()->simulation("ReponseTemporelle.txt", sig, x0);
	else
		logfileconsole("______No Input Signal");
}
void loadFromFile(Signal& sig){
	/*
		charge un signal d�fini par l'utilisateur dans le fichier load.txt
		format : temps , amplitude
	*/
	ifstream load("load.txt");
	string destroy = "";
	bool continuer = true;
	unsigned int initSize = 1;
	double deltaT1 = 0, deltaT2 = 0;
	double *bufferTime1 = new double[initSize], *bufferAmplitude1 = new double[initSize];
	double *bufferTime2 = new double[initSize], *bufferAmplitude2 = new double[initSize];
	bufferTime1[0] = 0; bufferTime2[0] = 0; bufferAmplitude1[0] = 0; bufferAmplitude2[0] = 0;
	unsigned int i = 0;

	while (continuer){
		if (load.eof()) // flag EOF
			continuer = false;
		load >> setprecision(3) >> bufferTime1[i];
		load >> destroy;
		// detection d'erreur format
		if (destroy.compare(",") != 0){
			logfileconsole("______ERROR while load from file load.txt : mismatch data");
			break;
		}
		load >> bufferAmplitude1[i];
		
		if (load.eof())
			continuer = false;
		else{
			/*
				creation du nouveaux tableaux de taille i + 1
			*/
			i++;
			delete bufferTime2;
			bufferTime2 = new double[initSize + i];
			for (unsigned int k = 0; k < i; k++)
				bufferTime2[k] = bufferTime1[k];
			bufferTime2[i] = 0;
			delete bufferTime1;
			bufferTime1 = new double[initSize + i];
			for (unsigned int k = 0; k <= i; k++)
				bufferTime1[k] = bufferTime2[k];

			delete bufferAmplitude2;
			bufferAmplitude2 = new double[initSize + i];
			for (unsigned int k = 0; k < i; k++)
				bufferAmplitude2[k] = bufferAmplitude1[k];
			bufferAmplitude2[i] = 0;
			delete bufferAmplitude1;
			bufferAmplitude1 = new double[initSize + i];
			for (unsigned int k = 0; k <= i; k++)
				bufferAmplitude1[k] = bufferAmplitude2[k];
		}
	}


	if (i >= 1){
		deltaT1 = bufferTime1[1] - bufferTime1[0];
		if (i >= 2){
			deltaT2 = bufferTime1[2] - bufferTime1[1];
			/*
				actuellement un probl�me avec l'importation des donn�es qui n'est pas fixe emp�che la v�rification du deltaT
				si dans le fichier il y a 0.1 l'importation le transforme en 0.1000000000001 ce qui n'est pas la meme chose
				de meme 0.2 se transforme en 0.199999999999
				la condition ne peut pas etre v�rifi�e correctement
			*/
			if (deltaT1 != deltaT2)
				logfileconsole("______ERROR loadFromFile : deltaT not const");
		}
		sig.SETdeltaT(deltaT1);
	}
	else
		sig.SETdeltaT(1); // defaut pour 1 echantillon
	

	sig.SETnbech(i + 1);
	for (unsigned int a = 0; a <= i; a++)
		sig.SETthiscoef(a, bufferAmplitude1[a]);

	if (bufferTime1 != nullptr){
		delete bufferTime1;
		bufferTime1 = nullptr;
	}
	if (bufferTime2 != nullptr){
		delete bufferTime2;
		bufferTime2 = nullptr;
	}
	if (bufferAmplitude1 != nullptr){
		delete bufferAmplitude1;
		bufferTime1 = nullptr;
	}
	if (bufferAmplitude2 != nullptr){
		delete bufferAmplitude2;
		bufferAmplitude2 = nullptr;
	}
}
void test(){
	system("cls");
	unsigned int request = 0;
	bool continuer = true;

	while (continuer){
		logfileconsole("Menu test");
		logfileconsole("type 1 to test the class Complexe");
		logfileconsole("or type 2 to test the class Polynome");
		logfileconsole("or type 3 to test the class Matrice");
		logfileconsole("or type 4 to test the class Signal");
		logfileconsole("or type 5 to test the class FCTDiscret");
		logfileconsole("or type 6 to test the class SYSETATDiscret");
		logfileconsole("or type 7 to test the class IHM");
		logfileconsole("or type 8 to return to previous menu : ");
		
		cin >> request;
		switch (request){
		case TESTComplexe:
			testComplexe();
			break;
		case TESTPolynome:
			testPolynome();
			break;
		case TESTMatrice:
			testMatrice();
			break;
		case TESTSignal:
			testSignal();
			break;
		case TESTFCTDiscret:
			testFCTDiscret();
			break;
		case TESTSysetatdiscret:
			testSYSETATDiscret();
			break;
		case TESTihm:
			testIHM();
			break;
		case exitTest:
			continuer = false;
			break;
		}
	}
}
void FTBF(IHM& ihm){
	/*
		Menu FTBF permet de calculer la fonction de transfert en boucle ferm�e
		Plusieurs possibilit�s sont disponibles comme : multiplier la TF par un int�grateur
		ou encore de modifier le gain de la boucle de retour
	*/
	system("cls");
	unsigned int request = 0;
	bool continuer = true;
	FCTDiscret resultFCT(*ihm.GETfct());
	FCTDiscret integrator;
	integrator.interg();
	FCTDiscret returnLoopFCT(1.0);
	

	while (continuer){
		request = 0;
		logfileconsole("Menu FTBF");
		logfileconsole("by default the gain of the return loop is 1");
		logfileconsole("type 1 to multiply your TF with an integrator");
		logfileconsole("type 2 to put -1 in return loop");
		logfileconsole("or type 3 to multiply the return loop by an integrator");
		logfileconsole("type 4 to compute FTBF");
		logfileconsole("or type 5 to return to previous menu : ");

		cin >> request;
		switch (request){
		case FTBFinteg:
			resultFCT = resultFCT * integrator;
			break;
		case FTBFreturnloopunit:
			returnLoopFCT.SETnumThisCoef(0, -1);
			break;
		case FTBFreturnloopinteg:
			returnLoopFCT = integrator;
			break;
		case calculFTBF:
			system("cls");
			closeLoop(resultFCT, returnLoopFCT);
			break;
		case exitFTBF:
			continuer = false;
			break;
		}
	}
}




void IHM::SETfct(FCTDiscret* fct){
	if (_fct != nullptr)
		delete _fct;
	_fct = fct;
}
void IHM::SETsys(SYSETATDiscret* sys){
	if (_sys != nullptr)
		delete _sys;
	_sys = sys;
}
FCTDiscret* IHM::GETfct()const{
	return _fct;
}
SYSETATDiscret* IHM::GETsys()const{
	return _sys;
}


bool assertFCT(const FCTDiscret fct, const FCTDiscret test){
	if (fct == test){
		logfileconsole("_____FCT doesn't exist");
		return false;
	}
	return true;
}

void testIHM(){
	cout << endl << endl << "___TEST IHM___" << endl << endl;

	IHM ihm;
	ihm.GETfct()->SETnumOrder(1);
	ihm.GETfct()->SETnumThisCoef(0, 0);
	ihm.GETfct()->SETnumThisCoef(1, 1);
	ihm.GETfct()->SETdenOrder(2);
	ihm.GETfct()->SETdenThisCoef(0, 0);
	ihm.GETfct()->SETdenThisCoef(1, 0.1);
	ihm.GETfct()->SETdenThisCoef(2, 1.1);
	ihm.GETfct()->printOn();

	ihm.GETsys()->calculABCD(*ihm.GETfct());
	ihm.GETsys()->SETTe(100);
	cout << endl << *ihm.GETsys();
	if (ihm.GETfct()->tabJury())
		cout << endl << "the system is stable";
	else
		cout << endl << "the system is unstable";
	cout << endl << "BODE" << endl;
	ihm.GETfct()->Bode(0.1, 10, 100);

	Echelon E(50, 0.1, 10.0);
	cout << E;
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	cout << endl << endl << endl << "Reponse temporelle avec E = 10.0" << endl;
	ihm.GETsys()->simulation("ReponseTemporelle.txt", E, x0);

	cout << endl << endl;
}
void logfileconsole(const std::string &msg) {
	const string logtxt = "log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}