#pragma once
#include"Weapon.h"
#include"MapDraw.h"
#include"Character.h"
#include "Subject.h"
#include "Observer.h"

#define SHOP_MENU_COUNT 7
#define WEAPON_RESPAWN_TIME 6000

class Shop : virtual public Weapon, virtual public Character, public Subject
{
private:
	vector<Observer*> observerList;
	string m_buy_wp_name;
	int m_my_time;

	Character chr;
protected:
	Weapon_Info *wp;
	Weapon_Info *tmp_page1, *tmp_page2, *tmp_page3;

	Weapon_Info *Dagger;
	Weapon_Info *Gun;
	Weapon_Info *Sword;
	Weapon_Info *Wand;
	Weapon_Info *Bow;
	Weapon_Info *Hammer;

	MapDraw Draw_Gotoxy;
public:
	void Init_Weapon();
	void Show_Shop(Character_Info *name);
	int Create_Weapon(string name);
	void Create_Weapon2(string name, Weapon_Info *wp_name);
	void Weapon_Shop(Weapon_Info *wp_name, Character_Info *cr_name);
	void Weapon_Show(Weapon_Info *wp_name, int ht1, int ht2, int num);
	int Buy_Weapon(Weapon_Info *wp_name, Character_Info *cr_name, int select_menu, int page);

	virtual void Add_Observer(Observer* ob);
	virtual void Notify();
	int Shop_MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	Shop();
	~Shop();
};

