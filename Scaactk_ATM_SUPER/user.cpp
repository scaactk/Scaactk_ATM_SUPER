#include"user.h"
User::User() {

}
User::User(string _name, int _id, int _pw, double _Mon, int _statue) {
	this->name = _name;
	this->id = _id;
	this->pw = _pw;
	this->Mon = _Mon;
	this->statue = _statue;
}