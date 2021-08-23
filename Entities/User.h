#ifndef USER_H
#define USER_H
class User {
    private:
        const char* username;
        const char* password;
        bool logged;
    
    public:
        User(const char*, const char*);
        const char* _username();
        const char* _password();
        void setLogged(bool);
        bool isLoggedIn();
};
#endif