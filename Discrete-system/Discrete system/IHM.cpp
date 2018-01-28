/*
Discrete_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:2.7

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


void mainLoop(IHM& ihm){
	/*
		Menu principal
	*/
	unsigned int request = 0;
	FCTDiscret testFCT;
	logfileconsole("_________Init Success_________");

	sysinfo information;
	initsdl(information);

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("Dev version: 2.7");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");



	loadAllTextures(information);
	information.ecran.statescreen = STATEecrantitre;
	rendueEcran(information);
	

	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty

	logfileconsole("_ Start mainLoop _");
	while (information.variables.continuer){
		SDL_WaitEvent(&event);
			switch (event.type){
			case SDL_QUIT:	// permet de quitter
				information.variables.continuer = false;
				break;
			case SDL_KEYDOWN: // test sur le type d'�v�nement touche enfonc�
				switch (event.key.keysym.sym) {
				case SDLK_F5:
					
					break;
				case SDLK_F6:
					
					break;
				case SDLK_ESCAPE:
					information.variables.continuer = false;
					break;
				case SDLK_SPACE:
					
					break;
				case SDLK_KP_1:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: // test sur le type d'�v�nement click souris (enfonc�)
				mouse(ihm, information, event);
				break;
			case SDL_MOUSEWHEEL:
				break;
			}
		}
	deleteAll(information);
	logfileconsole("_ End mainLoop _");
}
void loadAllTextures(sysinfo& information){

	// ______Writetxt_____ 
	information.ecran.statescreen = STATEecrantitre;
	loadwritetxt(information, "Dev version: 2.7", { 255, 255, 255, 255 }, 16, 0, 0);
	loadwritetxt(information, "Develop by SAUTER Robin", { 255, 255, 255, 255 }, 16, 0, 16);
	loadwritetxt(information, "Discret System", { 0, 255, 255, 255 }, 28, SCREEN_WIDTH / 2, 25, center_x);
	information.ecran.statescreen = STATEfunctionTransfer;
	loadwritetxt(information, "Transfert Function", { 0, 255, 255, 255 }, 24, SCREEN_WIDTH / 2, 0, center_x);
	information.ecran.statescreen = STATEstateSystem;
	loadwritetxt(information, "State System", { 0, 255, 255, 255 }, 24, SCREEN_WIDTH / 2, 0, center_x);
	information.ecran.statescreen = STATETFcreateNumDen;
	loadwritetxt(information, "Create the Transfer Function", { 0, 255, 255, 255 }, 24, SCREEN_WIDTH / 2, 0, center_x);
	information.ecran.statescreen = STATESSsimulate;
	loadwritetxt(information, "Simulate", { 0, 255, 255, 255 }, 24, SCREEN_WIDTH / 2, 0, center_x);
	information.ecran.statescreen = STATEreponseTemporelle;
	loadwritetxt(information, "Simulation", { 0, 255, 255, 255 }, 24, SCREEN_WIDTH / 2, 0, center_x);


	// ______Buttons_____
	information.ecran.statescreen = STATEecrantitre;
	int spacemenu = 64, initspacemenu = 150;
	createbutton(information, "Transfer Function", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, "State System", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Closed Loop", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Tests", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Quit", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.ecran.statescreen = STATEfunctionTransfer;
	spacemenu = 48, initspacemenu = 100;
	createbutton(information, "Main menu", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, 0);
	createbutton(information, "Create the Transfer Function", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, "Display the Transfer Function", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Jury", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Bode", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.ecran.statescreen = STATEstateSystem;
	spacemenu = 48, initspacemenu = 100;
	createbutton(information, "Main menu", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, 0);
	createbutton(information, "Edit Matrix A, B, C and D", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu, center);
	createbutton(information, "Compute A, B, C and D", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Display the State System", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);
	createbutton(information, "Simulate", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, SCREEN_WIDTH / 2, initspacemenu += spacemenu, center);

	information.ecran.statescreen = STATESSsimulate;
	createbutton(information, "Main menu", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, 0);
	createbutton(information, "Step", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 100, 100);
	createbutton(information, "Ramp", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 200, 100);
	createbutton(information, "Sinus", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 300, 100);
	createbutton(information, "Import Signal", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 400, 100);

	information.ecran.statescreen = STATEreponseTemporelle;
	createbutton(information, "Main menu", { 255, 64, 0, 255 }, { 64, 64, 64, 255 }, 24, 0, 0);

}
void rendueEcran(sysinfo& information){
	SDL_RenderClear(information.ecran.renderer);
	

	for (unsigned int i = 0; i < information.allTextures.tabTexture.size(); i++)
		information.allTextures.tabTexture[i]->renderTextureTestStates(information.ecran.renderer, information.ecran.statescreen, information.variables.select);

	for (unsigned int i = 0; i < information.tabbutton.size(); i++)
		information.tabbutton[i]->renderButton(information.ecran.renderer, information.ecran.statescreen);

	SDL_RenderPresent(information.ecran.renderer);
}




void logfileconsole(const std::string &msg) {
	const string logtxt = "bin/files/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}
void logSDLError(std::ostream &os, const std::string &msg){
	const std::string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log){
		os << msg << " error: " << SDL_GetError() << std::endl;
		log << msg << " error: " << SDL_GetError() << std::endl;
	}
	else
		cout << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt << endl;
}
void initsdl(sysinfo& information){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << endl << "SDL could not initialize! SDL_Error: " << SDL_GetError();
	else{
		information.ecran.window = SDL_CreateWindow("Discret System", 200, 200, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

		//	SDL_WINDOW_FULLSCREEN_DESKTOP or SDL_WINDOW_FULLSCREEN
		if (information.ecran.window == nullptr) 
			SDL_Quit();
		else
			logfileconsole("CreateWindow Success");
		information.ecran.renderer = SDL_CreateRenderer(information.ecran.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (information.ecran.renderer == nullptr) {
			SDL_DestroyWindow(information.ecran.window);
			SDL_Quit();
		}
		else
			logfileconsole("CreateRenderer Success");

		if (TTF_Init() != 0) {
			SDL_DestroyRenderer(information.ecran.renderer);
			SDL_DestroyWindow(information.ecran.window);
			SDL_Quit();
		}
		else
			logfileconsole("TTF_Init Success");

		
		const std::string fontFile = "arial.ttf";

		for (unsigned int i = 1; i < 80; i++)
			information.allTextures.font[i] = TTF_OpenFont(fontFile.c_str(), i);

		logfileconsole("SDL_Init Success");
	}
}
SDL_Texture* renderText(SDL_Renderer*& renderer, const std::string &message, SDL_Color color, TTF_Font* font[], int fontSize){

	SDL_Surface *surf = TTF_RenderText_Blended(font[fontSize], message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		logfileconsole("___________ERROR : renderText nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}
SDL_Texture* renderTextShaded(SDL_Renderer*& renderer, const std::string &message, SDL_Color color, SDL_Color colorback, TTF_Font* font[], int fontSize){

	SDL_Surface *surf = TTF_RenderText_Shaded(font[fontSize], message.c_str(), color, colorback);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr)
		logfileconsole("___________ERROR : renderTextShaded nullptr for : " + message);
	SDL_FreeSurface(surf);
	return texture;
}

void searchcenter(int &x, int &y, int &xc, int &yc, int iW, int iH, int centerbutton) {
	switch (centerbutton) {
	case nocenter:
		xc = x + iW / 2;
		yc = y + iH / 2;
		break;
	case center_x:
		xc = x;
		yc = y + iH / 2;
		x = x - iW / 2;
		break;
	case center_y:
		xc = x + iW / 2;
		yc = y;
		y = y - iH / 2;
		break;
	case center:
		xc = x;
		yc = y;
		x = x - iW / 2;
		y = y - iH / 2;
		break;
	}
}

void createbutton(sysinfo& information, const string& msg, SDL_Color color, SDL_Color backcolor, int size, int x, int y, int centerbutton) {
	int iW = 0, iH = 0;
	unsigned int i = 0;
	int xc = 0, yc = 0;
	SDL_Texture *image = nullptr;
	SDL_Texture *imageOn = nullptr;
	unsigned int tabsize = information.tabbutton.size();

	if (tabsize > 0) {
		i++;
	}
	for (i; i <= tabsize; i++) {
		if (i == tabsize) {
			image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font, size);
			imageOn = renderTextShaded(information.ecran.renderer, msg, color, { 64, 128, 64, 255 }, information.allTextures.font, size);
			SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
			searchcenter(x, y, xc, yc, iW, iH, centerbutton);
			information.tabbutton.push_back(new Buttons(image, msg, information.ecran.statescreen, information.variables.select, xc, yc, iW, iH, imageOn, x, y, size, color, backcolor));

			logfileconsole("Create Button n:" + to_string(i) + " msg = " + information.tabbutton[i]->GETname() + " Success");
			break;
		}
	}
}
void loadImage(sysinfo& information, unsigned int& index, const std::string &path, const std::string &msg, Uint8 alpha, int x, int y, int cnt) {


	int iW = 0, iH = 0, xc = 0, yc = 0;
	if (x != -1 && y != -1)
		xc = x, yc = y;

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(information.ecran.renderer, loadedSurface);
		iW = loadedSurface->w;
		iH = loadedSurface->h;
		if (newTexture != NULL) {
			if (alpha != (Uint8)255) {
				if (SDL_SetTextureAlphaMod(newTexture, alpha) != 0)
					logSDLError(cout, "alpha : ");
			}
			centrage(xc, yc, iW, iH, cnt);
			information.allTextures.tabTexture.push_back(new Texture(newTexture, msg, information.ecran.statescreen, information.variables.select, xc, yc, iW, iH));
			index++;
		}
		SDL_FreeSurface(loadedSurface);
	}
}

void loadwritetxt(sysinfo& information, const std::string &msg, SDL_Color color, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, msg, color, information.allTextures.font, size);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	information.allTextures.tabTexture.push_back(new Texture(image, msg, information.ecran.statescreen, information.variables.select, xc, yc, iW, iH));
}
void loadwritetxtshaded(sysinfo& information, const std::string &msg, SDL_Color color, SDL_Color backcolor, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font, size);
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);
	information.allTextures.tabTexture.push_back(new Texture(image, msg, information.ecran.statescreen, information.variables.select, xc, yc, iW, iH));
}
void writetxt(sysinfo& information, const std::string &msg, SDL_Color color, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderText(information.ecran.renderer, msg, color, information.allTextures.font, size);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}
void writetxtshaded(sysinfo& information, const std::string &msg, SDL_Color color, SDL_Color backcolor, int size, unsigned int x, unsigned int y, int cnt) {
	SDL_Texture *image = renderTextShaded(information.ecran.renderer, msg, color, backcolor, information.allTextures.font, size);
	loadAndWriteImage(information.ecran.renderer, image, x, y, cnt);
	SDL_DestroyTexture(image);
}

void loadAndWriteImage(SDL_Renderer*& renderer, SDL_Texture *image, unsigned int x, unsigned int y, int cnt) {
	int xc = x, yc = y, iW = 0, iH = 0;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	centrage(xc, yc, iW, iH, cnt);

	SDL_Rect dst;
	dst.x = xc;
	dst.y = yc;
	dst.w = iW;
	dst.h = iH;
	SDL_RenderCopy(renderer, image, NULL, &dst);
}


void centrage(int& xc, int& yc, int iW, int iH, int cnt) {
	switch (cnt) {
	case nocenter:
		break;
	case center_x:
		xc = xc - (iW / 2);
		break;
	case center_y:
		yc = yc - (iH / 2);
		break;
	case center:
		xc = xc - (iW / 2);
		yc = yc - (iH / 2);
		break;
	}
}

void mouse(IHM& ihm, sysinfo& information, SDL_Event event){
	/*
	Handle Mouse Event
	BUTTON_LEFT
	BUTTON_RIGHT

	*/
	string test, fct;

	if (event.button.button == SDL_BUTTON_LEFT){

		for (unsigned int i = 0; i < information.tabbutton.size(); i++){ // recherche si une bouton est dans ces coordonn�es

			// boutons du main menu

			if (information.tabbutton[i]->searchButton(fct = "Transfer Function", information.ecran.statescreen, event.button.x, event.button.y)){
				information.ecran.statescreen = STATEfunctionTransfer;
				rendueEcran(information);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "State System", information.ecran.statescreen, event.button.x, event.button.y)){
				information.ecran.statescreen = STATEstateSystem;
				rendueEcran(information);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Closed Loop", information.ecran.statescreen, event.button.x, event.button.y)){
				
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Tests", information.ecran.statescreen, event.button.x, event.button.y)){

				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Quit", information.ecran.statescreen, event.button.x, event.button.y)) {
				information.variables.continuer = false;
				break;
			}



			// bouton multiple

			if (information.tabbutton[i]->searchButton(fct = "Main menu", information.ecran.statescreen, event.button.x, event.button.y)){
				information.ecran.statescreen = STATEecrantitre;
				rendueEcran(information);
				break;
			}


			// boutons du menu TF

			if (information.tabbutton[i]->searchButton(fct = "Create the Transfer Function", information.ecran.statescreen, event.button.x, event.button.y)){
				CreateNumDen(ihm, information);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Display the Transfer Function", information.ecran.statescreen, event.button.x, event.button.y)){
				displayTF(ihm, information);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Jury", information.ecran.statescreen, event.button.x, event.button.y)){
				displayJury(ihm, information);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Bode", information.ecran.statescreen, event.button.x, event.button.y)){
				
				break;
			}




			// boutons du menu State System

			if (information.tabbutton[i]->searchButton(fct = "Edit Matrix A, B, C and D", information.ecran.statescreen, event.button.x, event.button.y)){
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Compute A, B, C and D", information.ecran.statescreen, event.button.x, event.button.y)){
				if (ihm.GETfct()->GETden().GETorder() > 0)
					computeABCD(ihm, information);
				else
					writetxt(information, "Order of Denominator is 0", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 130, 148, center_y);
				SDL_RenderPresent(information.ecran.renderer);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Display the State System", information.ecran.statescreen, event.button.x, event.button.y)){
				SYSETATDiscret SYS;
				if (SYS == *ihm.GETsys())
					writetxt(information, "SS doesn't exist", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 150, 196, center_y);
				else{
					displayStateSystem(ihm, information);
					writetxt(information, "OK", { 0, 255, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 150, 196, center_y);
				}
				SDL_RenderPresent(information.ecran.renderer);
				
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Simulate", information.ecran.statescreen, event.button.x, event.button.y)){
				SYSETATDiscret SYS;
				if (SYS == *ihm.GETsys())
					writetxt(information, "SS doesn't exist", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 150, 244, center_y);
				else{
					information.ecran.statescreen = STATESSsimulate;
					rendueEcran(information);
					
				}
				break;
			}




			if (information.tabbutton[i]->searchButton(fct = "Step", information.ecran.statescreen, event.button.x, event.button.y)){
				information.tabbutton[i]->changeOn();
				rendueEcran(information);
				Echelon step;
				createSignal(ihm, information, step);
				createStep(ihm, information, step);
				information.ecran.statescreen = STATEreponseTemporelle;
				rendueEcran(information);
				displayReponseTemp(ihm, information, step);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Ramp", information.ecran.statescreen, event.button.x, event.button.y)){
				information.tabbutton[i]->changeOn();
				rendueEcran(information);
				Rampe ramp;
				createSignal(ihm, information, ramp);
				createRamp(ihm, information, ramp);
				information.ecran.statescreen = STATEreponseTemporelle;
				rendueEcran(information);
				displayReponseTemp(ihm, information, ramp);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Sinus", information.ecran.statescreen, event.button.x, event.button.y)){
				Sinus sinus(500, 0.01, 1, 1, 0);
				/*
				information.tabbutton[i]->changeOn();
				rendueEcran(information);
				Sinus sinus;
				createSignal(ihm, information, sinus);
				createSinus(ihm, information, sinus);
				information.ecran.statescreen = STATEreponseTemporelle;
				rendueEcran(information);
				*/
				displayReponseTemp(ihm, information, sinus);
				break;
			}
			if (information.tabbutton[i]->searchButton(fct = "Import Signal", information.ecran.statescreen, event.button.x, event.button.y)){
				information.tabbutton[i]->changeOn();
				rendueEcran(information);
				break;
			}




		}



		// reset de l'affichage On des boutons
		/*
		for (unsigned int i = 0; i < information.tabbutton.size(); i++) {
			if (information.ecran.statescreen == STATEmainmap) 
				information.tabbutton[i]->resetOnStatescreen(information.variables.select, selectnothing);
		}
		*/
	}



	//if (event.button.button == SDL_BUTTON_RIGHT && information.ecran.statescreen == STATEmainmap)
	
}
unsigned int CinNumberUnsignedInt(sysinfo& information, const string& msg, unsigned int x, unsigned int y){
	bool continuer = true, ppostive = true;
	unsigned int number = 0, digit = 0;
	SDL_Event event;
	int SDL_EnableUNICODE(1); // on azerty
	
	while (continuer){
		SDL_WaitEvent(&event);
		switch (event.type){
		case SDL_QUIT:	// permet de quitter
			information.variables.continuer = false;
			continuer = false;
			break;
		case SDL_KEYDOWN: // test sur le type d'�v�nement touche enfonc�
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				information.variables.continuer = false;
				continuer = false;
				break;
			case SDLK_BACKSPACE:
				number = 0;
				digit = 0;
				break;
			case SDLK_RETURN:
				continuer = false;
				break;
			case SDLK_KP_ENTER:
				continuer = false;
				break;
			case SDLK_1:
				digit = 1;
				break;
			case SDLK_2:
				digit = 2;
				break;
			case SDLK_3:
				digit = 3;
				break;
			case SDLK_4:
				digit = 4;
				break;
			case SDLK_5:
				digit = 5;
				break;
			case SDLK_6:
				digit = 6;
				break;
			case SDLK_7:
				digit = 7;
				break;
			case SDLK_8:
				digit = 8;
				break;
			case SDLK_9:
				digit = 9;
				break;
			case SDLK_KP_1:
				digit = 1;
				break;
			case SDLK_KP_2:
				digit = 2;
				break;
			case SDLK_KP_3:
				digit = 3;
				break;
			case SDLK_KP_4:
				digit = 4;
				break;
			case SDLK_KP_5:
				digit = 5;
				break;
			case SDLK_KP_6:
				digit = 6;
				break;
			case SDLK_KP_7:
				digit = 7;
				break;
			case SDLK_KP_8:
				digit = 8;
				break;
			case SDLK_KP_9:
				digit = 9;
				break;
			}
			if (continuer){
				number = (number * 10) + digit;
				digit = 0;
				rendueEcran(information);
				writetxt(information, "Press ENTER to validate", { 255, 0, 0, 255 }, 16, 0, 50);
				writetxt(information, "Press Backspace to retry", { 255, 0, 0, 255 }, 16, 0, 66);
				writetxt(information, msg + to_string(number), { 0, 64, 255, 255 }, 18, x, y, center_x);
				SDL_RenderPresent(information.ecran.renderer);
			}
			break;
		}
	}
	return number;
}
void CreateNumDen(IHM& ihm, sysinfo& information){
	logfileconsole("_ Start CreateNumDen _");
	information.ecran.statescreen = STATETFcreateNumDen;
	rendueEcran(information);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 100, 50);

	writetxt(information, "Order of the Numerator : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 50, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETfct()->SETnumOrder(CinNumberUnsignedInt(information, "Order of the Numerator : ", SCREEN_WIDTH / 2, 50));
	loadwritetxt(information, "Order of the Numerator : " + to_string(ihm.GETfct()->GETnum().GETorder()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 50, center_x);
	rendueEcran(information);
	for (unsigned int z = 0; z <= ihm.GETfct()->GETnum().GETorder(); z++){
		writetxt(information, "coef n:" + to_string(z) + " = ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 75, center_x);
		SDL_RenderPresent(information.ecran.renderer);
		ihm.GETfct()->SETnumThisCoef(z, CinNumberUnsignedInt(information, "coef n:" + to_string(z) + " = ", SCREEN_WIDTH / 2, 75));
		rendueEcran(information);
	}


	writetxt(information, "Order of the Denominator : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 100, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETfct()->SETdenOrder(CinNumberUnsignedInt(information, "Order of the Denominator : ", SCREEN_WIDTH / 2, 100));
	loadwritetxt(information, "Order of the Denominator : " + to_string(ihm.GETfct()->GETden().GETorder()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 100, center_x);
	rendueEcran(information);
	for (unsigned int z = 0; z <= ihm.GETfct()->GETden().GETorder(); z++){
		writetxt(information, "coef n:" + to_string(z) + " = ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 125, center_x);
		SDL_RenderPresent(information.ecran.renderer);
		ihm.GETfct()->SETdenThisCoef(z, CinNumberUnsignedInt(information, "coef n:" + to_string(z) + " = ", SCREEN_WIDTH / 2, 125));
		rendueEcran(information);
	}

	writetxt(information, "Sampling time : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 150, center_x);
	SDL_RenderPresent(information.ecran.renderer);
	ihm.GETfct()->SETdeltaT(CinNumberUnsignedInt(information, "Sampling time : ", SCREEN_WIDTH / 2, 150));
	loadwritetxt(information, "Sampling time : " + to_string(ihm.GETfct()->GETdeltaT()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 150, center_x);
	rendueEcran(information);

	information.ecran.statescreen = STATEfunctionTransfer;
	rendueEcran(information);
	logfileconsole("_ End CreateNumDen _");
}
void displayTF(IHM& ihm, sysinfo& information){
	logfileconsole("_ Start displayTF _");
	ostringstream stream; string texte;
	string barre;
	FCTDiscret FCT;
	if (FCT == *ihm.GETfct()){
		writetxt(information, "TF doesn't exist", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 175, 148, center_y);
		SDL_RenderPresent(information.ecran.renderer);
	}
	else{
		unsigned int stringSize = 0;
		stringSize = max(ihm.GETfct()->GETnum().GETstringSize(), ihm.GETfct()->GETden().GETstringSize());
		for (unsigned int i = 0; i < ihm.GETfct()->GETden().GETstringSize(); i++)
			barre += "-";

		stream << ihm.GETfct()->GETnum().printOn(false); texte = stream.str(); stream.str(""); stream.clear();
		writetxt(information, texte, { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 400, center_x);
		writetxt(information, barre, { 0, 64, 255, 255 }, 24, SCREEN_WIDTH / 2, 414, center_x);
		stream << ihm.GETfct()->GETden().printOn(false); texte = stream.str(); stream.str(""); stream.clear();
		writetxt(information, texte, { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 436, center_x);
		SDL_RenderPresent(information.ecran.renderer);
	}
	logfileconsole("_ End displayTF _");
}
void displayJury(IHM& ihm, sysinfo& information){
	logfileconsole("_ Start displayJury _");
	unsigned int initspace = 180;
	string texte; ostringstream stream;
	FCTDiscret FCT;

	if (FCT == *ihm.GETfct()){
		writetxt(information, "TF doesn't exist", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 175, 196, center_y);
		SDL_RenderPresent(information.ecran.renderer);
	}
	else{
		if (ihm.GETfct()->tabJury())
			writetxt(information, "The system is stable", { 0, 255, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 100, 196, center_y);
		else
			writetxt(information, "The system is unstable", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 100, 196, center_y);

		for (unsigned int i = 0; i < ihm.GETfct()->GETjury().GETlength(); i++){
			stream << "|";
			for (unsigned int j = 0; j < ihm.GETfct()->GETjury().GETheight(); j++)
				stream << " " << ihm.GETfct()->GETjury().GETthiscoef(i, j) << " ";
			stream << "|";
			texte = stream.str();
			stream.str("");
			stream.clear();
			writetxt(information, texte, { 255, 255, 255, 255 }, 16, 0, initspace += 16);
		}
	}
	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_ End displayJury _");
}
void computeABCD(IHM& ihm, sysinfo& information){
	logfileconsole("_ Start computeABCD _");
	FCTDiscret FCT;
	if (FCT == *ihm.GETfct())
		writetxt(information, "TF doesn't exist", { 255, 0, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 150, 148, center_y);
	else{
		ihm.GETsys()->calculABCD(*ihm.GETfct());
		writetxt(information, "OK", { 0, 255, 0, 255 }, 16, (SCREEN_WIDTH / 2) + 150, 148, center_y);
	}
	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_ End computeABCD _");
}
void displayStateSystem(IHM& ihm, sysinfo& information){
	logfileconsole("_ Start displayStateSystem _");
	unsigned int initspace = 100;
	string texte; ostringstream stream;
	writetxt(information,"Matrix A", { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETA().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETA().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETA().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		writetxt(information, texte, { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	}

	initspace += 32;
	writetxt(information, "Matrix B", { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETB().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETB().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETB().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		writetxt(information, texte, { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	}

	initspace += 32;
	writetxt(information, "Matrix C", { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	for (unsigned int i = 0; i < ihm.GETsys()->GETC().GETlength(); i++){
		stream << "|";
		for (unsigned int j = 0; j < ihm.GETsys()->GETC().GETheight(); j++)
			stream << " " << ihm.GETsys()->GETC().GETthiscoef(i, j) << " ";
		stream << "|";
		texte = stream.str();
		stream.str("");
		stream.clear();
		writetxt(information, texte, { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	}

	initspace += 32;
	writetxt(information, "Matrix D", { 0, 64, 255, 255 }, 16, 0, initspace += 16);
	stream << "| " << ihm.GETsys()->GETD().GETthiscoef(0, 0) << " |";
	texte = stream.str();
	stream.str("");
	stream.clear();
	writetxt(information, texte, { 0, 64, 255, 255 }, 16, 0, initspace += 16);

	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_ End displayStateSystem _");
}
void createSignal(IHM& ihm, sysinfo& information, Signal& sig){
	logfileconsole("_ Start createSignal _");
	writetxt(information, "Number of samples : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 150, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 100, 150);
	SDL_RenderPresent(information.ecran.renderer);
	sig.SETnbech(CinNumberUnsignedInt(information, "Number of samples : ", SCREEN_WIDTH / 2, 150));
	loadwritetxt(information, "Number of samples : " + to_string(sig.GETnbech()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 150, center_x);
	rendueEcran(information);

	writetxt(information, "DeltaT : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 200, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 50, 200);
	SDL_RenderPresent(information.ecran.renderer);
	sig.SETdeltaT(CinNumberUnsignedInt(information, "DeltaT : ", SCREEN_WIDTH / 2, 200));
	loadwritetxt(information, "DeltaT : " + to_string(sig.GETnbech()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 200, center_x);
	rendueEcran(information);

	logfileconsole("_ End createSignal _");
}
void createStep(IHM& ihm, sysinfo& information, Echelon& step){
	logfileconsole("_ Start createStep _");

	writetxt(information, "Amplitude : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 250, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 70, 250);
	SDL_RenderPresent(information.ecran.renderer);
	step.SETamplitude(CinNumberUnsignedInt(information, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	loadwritetxt(information, "Amplitude : " + to_string(step.GETamplitude()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(information);

	logfileconsole("_ End createStep _");
}
void createRamp(IHM& ihm, sysinfo& information, Rampe& ramp){
	logfileconsole("_ Start createRamp _");

	writetxt(information, "Slope : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 250, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 50, 250);
	SDL_RenderPresent(information.ecran.renderer);
	ramp.SETslope(CinNumberUnsignedInt(information, "Slope : ", SCREEN_WIDTH / 2, 250));
	loadwritetxt(information, "Slope : " + to_string(ramp.GETslope()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(information);

	logfileconsole("_ End createRamp _");
}
void createSinus(IHM& ihm, sysinfo& information, Sinus& sinus){
	logfileconsole("_ Start createSinus _");

	writetxt(information, "Amplitude : ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 250, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 70, 250);
	SDL_RenderPresent(information.ecran.renderer);
	sinus.SETamplitude(CinNumberUnsignedInt(information, "Amplitude : ", SCREEN_WIDTH / 2, 250));
	loadwritetxt(information, "Amplitude : " + to_string(sinus.GETamplitude()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 250, center_x);
	rendueEcran(information);

	writetxt(information, "Angular velocity (w): ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 300, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 100, 300);
	SDL_RenderPresent(information.ecran.renderer);
	sinus.SETw(CinNumberUnsignedInt(information, "Angular velocity (w): ", SCREEN_WIDTH / 2, 300));
	loadwritetxt(information, "Angular velocity (w): " + to_string(sinus.GETw()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 300, center_x);
	rendueEcran(information);

	writetxt(information, "Phase (phi): ", { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 350, center_x);
	writetxt(information, "Enter a number", { 255, 215, 0, 255 }, 18, SCREEN_WIDTH / 2 + 70, 350);
	SDL_RenderPresent(information.ecran.renderer);
	sinus.SETdephasage(CinNumberUnsignedInt(information, "Phase (phi): ", SCREEN_WIDTH / 2, 350));
	loadwritetxt(information, "Phase (phi): " + to_string(sinus.GETdephasage()), { 0, 64, 255, 255 }, 18, SCREEN_WIDTH / 2, 350, center_x);
	rendueEcran(information);

	logfileconsole("_ End createSinus _");
}
void displayReponseTemp(IHM& ihm, sysinfo& information, Signal& sig){
	logfileconsole("_ Start displayReponseTemp _");
	string barre;
	barre = "0";
	for (unsigned int z = 0; z < 100; z++)
		barre += "-";
	barre += ">t(s)";
	writetxt(information, barre, { 255, 255, 255, 255 }, 16, 40, 250, center_y);
	barre = "";
	unsigned int initspace = 34;
	for (unsigned int z = 0; z < 30; z++)
		writetxt(information, "|", { 255, 255, 255, 255 }, 16, 50, initspace += 16, center_x);

	unsigned int x0 = 50, xmin = 50, xmax = 550;
	unsigned int y0 = 250, ymin = 450, ymax = 50;
	
	double max = 0, min = 0;
	for (unsigned int z = 0; z < sig.GETnbech(); z++){
		if (sig.GETthiscoef(z) > max)
			max = sig.GETthiscoef(z);
		if (sig.GETthiscoef(z) < min)
			min = sig.GETthiscoef(z);
	}
	double pasGraph = (xmax - xmin) / sig.GETnbech();
	writetxt(information, to_string(max), { 255, 0, 0, 255 }, 8, 20, 50, center);
	for (double z = xmin, n = 0; z < xmax, n < sig.GETnbech(); z += pasGraph, n++){
		writetxt(information, "|", { 255, 255, 255, 255 }, 8, z, y0, center);

		if (sig.GETthiscoef(n) > 0)
			writetxt(information, "+", { 255, 0, 0, 255 }, 8, z, y0 - ((sig.GETthiscoef(n) / max) * (y0 - ymax)), center);
		else if (sig.GETthiscoef(n) < 0)
			writetxt(information, "+", { 255, 0, 0, 255 }, 8, z, y0 + ((sig.GETthiscoef(n) / min) * (ymin - y0)), center);

		if (n == 10)
			writetxt(information, to_string(sig.GETdeltaT() * 10), { 255, 255, 255, 255 }, 8, z, y0 + 10, center);
	}
	SDL_RenderPresent(information.ecran.renderer);
	logfileconsole("_ Start displayReponseTemp _");
}

void deleteAll(sysinfo& information){
	logfileconsole("*********_________ Start DeleteAll _________*********");
	for (unsigned int i = 1; i < 80; i++)
		TTF_CloseFont(information.allTextures.font[i]);

	deleteDyTabPlayerAndTextures(information.allTextures.tabTexture, "Texture");
	deleteDyTabPlayerAndTextures(information.tabbutton, "Button");
	SDL_DestroyRenderer(information.ecran.renderer);
	SDL_DestroyWindow(information.ecran.window);
	information.ecran.renderer = nullptr;
	information.ecran.window = nullptr;
	logfileconsole("*********_________ End DeleteAll _________*********");
}
